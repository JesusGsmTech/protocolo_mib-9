#!/usr/bin/env node
/**
 * Consola para probar el protocolo de la contadora SB-7 / SB-9.
 *
 * Arma cada trama según el protocolo (Doc/PC_protocol_SB_MIB_series.md), la envía
 * y muestra decodificado lo que responde la máquina.
 *
 * Uso:
 *   node probar.js                        (COM5, modelo sb9 a 115200)
 *   node probar.js --modelo mib9          (MIB-9: 57600 y su orden de billetes)
 *   node probar.js --puerto COM3
 *   node probar.js --ip 192.168.123.231   (por red, puerto 4101)
 *   node probar.js --prueba               (autoprueba sin máquina)
 *
 * Cerrar IFD.exe antes: la máquina acepta una sola conexión a la vez.
 * Escribir "ayuda" dentro de la consola para ver los comandos.
 */

import readline from "node:readline/promises";
import { parseArgs } from "node:util";
import { setTimeout as esperar } from "node:timers/promises";

import {
  armarTrama, verificarTrama, decodificar, hex, h2, Separador, estado,
  SUBCMD, BYTE_CONTEO, MODOS_CONSOLA, LIMPIEZAS, PEDIDOS,
  tramaCambiarModo, tramaBatch, tramaLote, tramaDivisa, tramaDenom, tramaBandejas,
  tramaSensor, tramaAuto, SENSORES, indiceDenom, codigoDivisa,
} from "./src/protocolo.js";
import { abrirSerie, abrirTcp } from "./src/conexion.js";
import { crearRegistro } from "./src/registro.js";
import { autoprueba } from "./src/autoprueba.js";
import * as perfiles from "./src/perfiles.js";
import { usarModelo, MODELO_POR_DEFECTO } from "./src/maquinas.js";

const PAUSA_MIN = 100; // el protocolo pide >= 100 ms entre tramas enviadas

const PELIGROSOS = {
  default: [[0x39, 0x01], "vuelve la máquina a la configuración de fábrica"],
  moneda: [[0x3a, 0x01], "cambia la moneda de la máquina"],
  reboot: [[0xa8, 0x01], "reinicia la máquina"],
};

const AYUDA = `
Comandos (cada uno arma y envía la trama):
  knock | ack | release        DEVICE_SET_LIVE (30h). Empezar siempre con knock.
  pedir <tipo>                 RESULT_REQUEST (35h). tipo: estado, estado2, resultado,
                               error, sensores, disp2, reenviar, reporte, version
  iniciar | cancelar           START_STOP (37h): iniciar conteo / cancelar inicio
  limpiar <tipo>               RESULT_CLEAR (36h). tipo: rechazo, salida, total,
                               mixto, simple, jam, reporte
  modo <tipo>                  Cambia el modo de conteo (41h), sin tocar el resto.
                               tipo: mixto, single, conteo, cara, orientacion
  auto on|off                  Auto: cuenta al poner billetes y acepta 'iniciar' desde la PC.
                               Manual: solo arranca con START en la máquina (41h)
  batch on|off                 Detener el conteo al llegar al lote (41h)
  lote <n>                     Cantidad de billetes del lote, 1 a 200 (41h)
  sensor uv|mr|ir on|off       Activa/desactiva un sensor de detección de falsos (41h)
  divisa <código>              Cambia la divisa (41h). Ej: divisa usd, divisa ars
  denom <billete>|dd           En SINGLE: acepta solo ese billete (41h).
                               Ej: denom 100 · denom dd (vuelve al primer billete)
  bandejas <rechazo> <salida>  EXPERIMENTAL: códigos 0-15 de capacidad de bandejas (41h).
                               Revisar en la pantalla de la máquina si cambió algo.
  perfiles                     Lista los perfiles de ../perfiles.json
  perfil <n> [lote]            Aplica el perfil n en una sola trama (41h) y verifica.
                               Ej: perfil 1 · perfil 2 · perfil 2 50 (lote de 50)
  perfil verificar <n> [lote]  Solo compara la máquina con el perfil, sin cambiar nada
  setup2 <conteo 0|1> <teclado 0|1>
                               DEVICE_SETUP2 (38h): datos billete a billete / bloquear teclado
  usb on|off                   SAVE_BMP_TO_USB (44h), solo SB-9
  aletas on|off                IFD_WING_MOTOR (48h), solo SB-9
  default | moneda | reboot    Cambian la máquina: piden confirmación
  datos <hex...>               Envía una trama con esos bytes de datos.
                               Ej: "datos 35 02" = pedir resultado
  crudo <hex...>               Envía los bytes tal cual (sin armar trama)
  ayuda | salir
`;

// ---------------------------------------------------------------- consola

class Consola {
  constructor(conexion) {
    this.con = conexion;
    this.reg = crearRegistro("probar");
    this.cola = Promise.resolve(); // envíos en orden y con la pausa mínima
    this.ultimoEnvio = 0;
    this.separador = new Separador({
      onTrama: (t) => this.recibirTrama(t),
      onByte: (b) => this.reg.mostrar(`MAQ -> PC  1BYTE_COUNT_DATA ${h2(b)}: ${BYTE_CONTEO[b] ?? `denominación índice ${b}`}`),
      onIncompleta: (t) => this.reg.mostrar(`MAQ -> PC  trama incompleta\n  ${hex(t)}`),
    });
    conexion.on("data", (d) => this.separador.push(d));
    conexion.on("error", (e) => this.reg.mostrar(`ERROR de conexión: ${e.message}`));
    conexion.on("cerrada", () => {
      if (!this.cerrando) this.reg.mostrar("Conexión cerrada por la máquina. Escribe 'salir'.");
    });
  }

  enviar(trama) {
    this.cola = this.cola.then(async () => {
      const falta = PAUSA_MIN - (Date.now() - this.ultimoEnvio);
      if (falta > 0) await esperar(falta);
      this.con.escribir(trama);
      this.ultimoEnvio = Date.now();
      const { datos } = verificarTrama(trama);
      const nombre = datos.length ? SUBCMD[datos[0]] ?? `${h2(datos[0])}h` : "?";
      this.reg.mostrar(`PC  -> MAQ  ${nombre}\n  ${hex(trama)}`);
    });
    return this.cola;
  }

  recibirTrama(t) {
    const { ok, motivo, datos: d } = verificarTrama(t);
    if (!ok) {
      this.reg.mostrar(`MAQ -> PC  TRAMA INVÁLIDA: ${motivo}\n  ${hex(t)}`);
      return;
    }
    const nombre = SUBCMD[d[0]] ?? `${h2(d[0])}h desconocido`;
    const detalle = decodificar(d).map((l) => "  " + l).join("\n");
    this.reg.mostrar(`MAQ -> PC  ${h2(d[0])}h ${nombre}\n  ${hex(t)}\n${detalle}`);
    if (d[0] === 0x30 && d.length > 1) {
      // igual que IFD.exe: tras el ACK pide la configuración (así se conoce la moneda)
      if (d[1] & 0x02) this.enviar(armarTrama([0x35, 0x12]));
      // si la máquina hace KNOCK (se encendió después), responder ACK
      else if (d[1] & 0x01) this.enviar(armarTrama([0x30, 0x02]));
    }
  }

  async cerrar() {
    this.cerrando = true;
    this.separador.detener();
    await this.cola;
    await this.con.cerrar();
    await this.reg.cerrar();
  }
}

// ---------------------------------------------------------------- comandos

function byte(s) {
  if (!/^(0x)?[0-9a-f]+$/i.test(s)) throw new Error(`hex inválido: ${s}`);
  return parseInt(s, 16) & 0xff;
}

/** Convierte un comando en datos de trama (array), bytes crudos (Buffer) o null. */
function interpretar(linea) {
  const p = linea.toLowerCase().split(/\s+/);
  const c = p[0];
  if (["knock", "ack", "release"].includes(c)) return [0x30, { knock: 1, ack: 2, release: 4 }[c]];
  if (c === "pedir" && p.length === 2 && p[1] in PEDIDOS) return [0x35, PEDIDOS[p[1]]];
  if (c === "iniciar") return [0x37, 0x01];
  if (c === "cancelar") return [0x37, 0x02];
  if (c === "limpiar" && p.length === 2 && p[1] in LIMPIEZAS) return [0x36, LIMPIEZAS[p[1]]];
  if (c === "setup2" && p.length === 3 && /^\d+$/.test(p[1]) && /^\d+$/.test(p[2])) {
    return [0x38, (Number(p[1]) & 1) | ((Number(p[2]) & 1) << 1)];
  }
  if ((c === "usb" || c === "aletas") && p.length === 2 && ["on", "off"].includes(p[1])) {
    return [c === "usb" ? 0x44 : 0x48, p[1] === "on" ? 1 : 0];
  }
  if (c === "datos" && p.length >= 2) return p.slice(1).map(byte);
  if (c === "crudo" && p.length >= 2) return Buffer.from(p.slice(1).map(byte));
  return null;
}

/** Comandos que cambian la configuración 41h. Devuelve una función que arma la trama, o null. */
function comandoConfig(c, p) {
  if (c === "bandejas") {
    const [r, s] = p.slice(1).map(Number);
    if (p.length !== 3 || !/^\d+$/.test(p[1]) || !/^\d+$/.test(p[2]) || r > 15 || s > 15) return null;
    console.log("EXPERIMENTAL: revisa en la pantalla de la máquina si cambiaron las bandejas.");
    return () => tramaBandejas(r, s);
  }
  if (c === "sensor") {
    if (p.length !== 3 || !(p[1] in SENSORES) || !["on", "off"].includes(p[2])) return null;
    if (p[2] === "off") console.log(`Aviso: sin el sensor ${p[1].toUpperCase()} la máquina detecta menos billetes falsos.`);
    return () => tramaSensor(p[1], p[2] === "on");
  }
  if (p.length !== 2) return null;
  const v = p[1];
  if (c === "modo" && v in MODOS_CONSOLA) return () => tramaCambiarModo(MODOS_CONSOLA[v]);
  if (c === "auto" && ["on", "off"].includes(v)) {
    if (v === "off") console.log("Aviso: en Manual la máquina ignora 'iniciar'; solo cuenta con START en su teclado.");
    return () => tramaAuto(v === "on");
  }
  if (c === "batch" && ["on", "off"].includes(v)) return () => tramaBatch(v === "on");
  if (c === "lote" && /^\d+$/.test(v) && Number(v) >= 1 && Number(v) <= 200) return () => tramaLote(Number(v));
  if (c === "divisa" && codigoDivisa(v) !== null) return () => tramaDivisa(codigoDivisa(v));
  if (c === "denom" && indiceDenom(v) !== null) {
    if (estado.config && ![2, 3, 4].includes(estado.config[1])) {
      console.log("Aviso: la denominación fija solo aplica en modo single/cara/orientacion.");
    }
    return () => tramaDenom(indiceDenom(v));
  }
  return null;
}

/** Pide 41h y espera la respuesta. Devuelve true si llegó. */
async function releerConfig(con, espera = 1500) {
  const version = estado.version;
  await con.enviar(armarTrama([0x35, 0x12]));
  const limite = Date.now() + espera;
  while (estado.version === version && Date.now() < limite) await esperar(50);
  return estado.version !== version;
}

/** perfiles · perfil <n> [lote] · perfil verificar <n> [lote] */
async function comandoPerfil(con, p) {
  let lista;
  try {
    lista = perfiles.cargar();
  } catch (e) {
    console.log(`No se pudo leer ${perfiles.RUTA}: ${e.message}`);
    return;
  }
  if (p[0] === "perfiles") {
    for (const [n, perfil] of Object.entries(lista)) console.log("  " + perfiles.describir(n, perfil));
    return;
  }
  const soloVerificar = p[1] === "verificar";
  const resto = soloVerificar ? p.slice(2) : p.slice(1);
  if (!resto.length || !(resto[0] in lista) || resto.length > 2 || (resto.length === 2 && !/^\d+$/.test(resto[1]))) {
    console.log("Uso: perfil <n> [lote] · perfil verificar <n> [lote] · perfiles");
    return;
  }
  const [n] = resto;
  const perfil = lista[n];
  const lote = resto.length === 2 ? Number(resto[1]) : undefined;
  if (lote !== undefined && (lote < 1 || lote > 200)) {
    console.log("El lote va de 1 a 200.");
    return;
  }
  if (!estado.config) {
    console.log("Primero lee la configuración: 'knock' o 'pedir estado2'.");
    return;
  }
  if (!soloVerificar) {
    const nuevo = perfiles.aplicar(estado.config, perfil, codigoDivisa, lote);
    if (nuevo.every((b, i) => b === estado.config[i])) {
      console.log(`La máquina ya tiene el perfil ${n}; no se envía nada.`);
    } else {
      await con.enviar(armarTrama([0x41, ...nuevo]));
      await esperar(300);
    }
  }
  if (!(await releerConfig(con))) {
    console.log("La máquina no respondió a la relectura de la configuración.");
    return;
  }
  const filas = perfiles.verificar(estado.config, perfil, codigoDivisa, lote);
  const lineas = [`Perfil ${n} · ${perfil.nombre ?? ""}`];
  for (const f of filas) {
    const nota = f.estado === "!!" ? "  -> ajustar desde el teclado" : "";
    lineas.push(`  [${f.estado}] ${f.campo.padEnd(16)} esperado: ${f.esperado}   máquina: ${f.actual}${nota}`);
  }
  const fallas = filas.filter((f) => f.estado !== "OK").length;
  lineas.push(fallas ? `  ${fallas} campo(s) no coinciden.` : "  Todo coincide.");
  con.reg.mostrar(lineas.join("\n"));
}

async function consola(args) {
  let conexion;
  try {
    conexion = args.ip
      ? await abrirTcp(args.ip, Number(args["puerto-tcp"]))
      : await abrirSerie(args.puerto, Number(args.baudios));
  } catch (e) {
    const destino = args.ip ? `${args.ip}:${args["puerto-tcp"]}` : args.puerto;
    console.log(`No se pudo abrir ${destino}: ${e.message}`);
    console.log("¿Está IFD.exe u otro programa conectado a la máquina?");
    process.exitCode = 1;
    return;
  }
  const con = new Consola(conexion);
  console.log(`Conectado a ${conexion.descripcion} (modelo ${args.nombreModelo}). Escribe 'ayuda'. Empieza con 'knock'.`);

  const rl = readline.createInterface({ input: process.stdin, output: process.stdout });
  const cerrada = new Promise((ok) => rl.once("close", () => ok(null)));
  rl.on("SIGINT", () => rl.close());
  const leer = (pregunta = "") => Promise.race([rl.question(pregunta).catch(() => null), cerrada]);

  for (;;) {
    const entrada = await leer();
    if (entrada === null) break;
    const linea = entrada.trim();
    if (!linea) continue;
    const p = linea.toLowerCase().split(/\s+/);
    const c = p[0];
    if (["salir", "exit", "quit"].includes(c)) break;
    if (c === "ayuda") {
      console.log(AYUDA);
      continue;
    }
    if (c === "perfil" || c === "perfiles") {
      await comandoPerfil(con, p);
      continue;
    }
    if (["modo", "auto", "batch", "lote", "divisa", "denom", "bandejas", "sensor"].includes(c)) {
      const armar = comandoConfig(c, p);
      if (!armar) {
        console.log("Uso: modo mixto|single|conteo|cara|orientacion  ·  auto on|off  ·  batch on|off  ·  lote 1-200  ·  "
          + "sensor uv|mr|ir on|off  ·  divisa usd|ars|<código>  ·  denom <billete>|dd  ·  bandejas <0-15> <0-15>");
      } else if (!estado.config) {
        console.log("Primero lee la configuración: 'knock' o 'pedir estado2'.");
      } else {
        await con.enviar(armar());
        await esperar(300);
        await con.enviar(armarTrama([0x35, 0x12])); // releer para verificar
      }
      continue;
    }
    if (c in PELIGROSOS) {
      const [datos, aviso] = PELIGROSOS[c];
      const r = await leer(`Esto ${aviso}. ¿Seguro? (si/no): `);
      if (r?.trim().toLowerCase() !== "si") {
        console.log("Cancelado.");
        continue;
      }
      await con.enviar(armarTrama(datos));
      continue;
    }
    let r;
    try {
      r = interpretar(linea);
    } catch {
      r = null;
    }
    if (r === null) console.log("Comando no reconocido. Escribe 'ayuda'.");
    else await con.enviar(Buffer.isBuffer(r) ? r : armarTrama(r));
  }

  rl.close();
  await con.cerrar();
  console.log("Conexión cerrada.");
  process.exit(0);
}

// ---------------------------------------------------------------- main

const { values: args } = parseArgs({
  options: {
    modelo: { type: "string", default: MODELO_POR_DEFECTO }, // ../maquinas.json: sb9, mib9
    puerto: { type: "string", default: "COM5" },
    baudios: { type: "string" }, // por defecto, la del modelo
    ip: { type: "string" },
    "puerto-tcp": { type: "string", default: "4101" },
    prueba: { type: "boolean", default: false },
  },
});

if (args.prueba) {
  process.exitCode = autoprueba() ? 0 : 1;
} else {
  let modelo;
  try {
    modelo = usarModelo(args.modelo);
  } catch (e) {
    console.log(e.message);
    process.exit(1);
  }
  args.baudios ??= String(modelo.baudios ?? 115200);
  args.nombreModelo = modelo.nombre ?? args.modelo;
  await consola(args);
}
