#!/usr/bin/env node
/**
 * Escucha el tráfico entre la PC y la contadora SB-7 / SB-9.
 *
 * Modos:
 *   monitor  Abre el puerto COM y muestra todo lo que envía la máquina.
 *            (IFD.exe no puede usar el mismo puerto a la vez.)
 *   puente   Se pone en medio de IFD.exe y la máquina usando un par de puertos
 *            virtuales com0com. Muestra lo que va en ambos sentidos.
 *   tcp      Proxy TCP: IFD.exe se conecta a esta PC y el programa reenvía a la
 *            máquina. Muestra lo que va en ambos sentidos. No necesita drivers.
 *
 * Ejemplos:
 *   node escuchar.js monitor --puerto COM5
 *   node escuchar.js puente --real COM5 --virtual COM20
 *   node escuchar.js tcp --maquina 192.168.123.231
 *
 * Todo se guarda además en la carpeta logs/.
 */

import net from "node:net";
import { parseArgs } from "node:util";

import { hex } from "./src/protocolo.js";
import { abrirSerie } from "./src/conexion.js";
import { crearRegistro } from "./src/registro.js";

const PAUSA_TRAMA = 20; // ms de silencio que separan una trama de la siguiente

function volcado(reg, direccion, datos) {
  const lineas = [`${direccion} (${datos.length} bytes)`];
  for (let i = 0; i < datos.length; i += 16) {
    const bloque = datos.subarray(i, i + 16);
    const ascii = [...bloque].map((b) => (b >= 32 && b < 127 ? String.fromCharCode(b) : ".")).join("");
    lineas.push(`    ${i.toString(16).toUpperCase().padStart(4, "0")}  ${hex(bloque).padEnd(47)}  ${ascii}`);
  }
  reg.mostrar(lineas.join("\n"));
}

/** Junta los bytes que llegan seguidos y entrega cada trama cuando hay un silencio. */
function agrupar(al_completar) {
  let buf = Buffer.alloc(0);
  let timer = null;
  return (trozo) => {
    buf = Buffer.concat([buf, trozo]);
    clearTimeout(timer);
    timer = setTimeout(() => {
      const t = buf;
      buf = Buffer.alloc(0);
      al_completar(t);
    }, PAUSA_TRAMA);
  };
}

async function modoMonitor(args, reg) {
  const con = await abrirSerie(args.puerto, Number(args.baudios));
  reg.mostrar(`Escuchando ${con.descripcion}. Ctrl+C para salir.`);
  con.on("data", agrupar((t) => volcado(reg, "MAQ -> PC", t)));
  con.on("error", (e) => reg.mostrar(`Error: ${e.message}`));
  return () => con.cerrar();
}

async function modoPuente(args, reg) {
  const real = await abrirSerie(args.real, Number(args.baudios));
  const virtual = await abrirSerie(args.virtual, Number(args.baudios));
  reg.mostrar(`Puente ${args.virtual} (IFD.exe) <-> ${args.real} (máquina). Ctrl+C para salir.`);
  virtual.on("data", agrupar((t) => { volcado(reg, "PC -> MAQ", t); real.escribir(t); }));
  real.on("data", agrupar((t) => { volcado(reg, "MAQ -> PC", t); virtual.escribir(t); }));
  for (const c of [real, virtual]) c.on("error", (e) => reg.mostrar(`Error: ${e.message}`));
  return async () => { await real.cerrar(); await virtual.cerrar(); };
}

async function modoTcp(args, reg) {
  const servidor = net.createServer((cliente) => {
    reg.mostrar(`IFD.exe conectado desde ${cliente.remoteAddress}:${cliente.remotePort}`);
    const maquina = net.connect({ host: args.maquina, port: Number(args["puerto-maquina"]) });
    maquina.setTimeout(5000, () => maquina.destroy(new Error("sin respuesta de la máquina")));
    maquina.once("connect", () => maquina.setTimeout(0));
    cliente.on("data", (d) => { volcado(reg, "PC -> MAQ", d); maquina.write(d); });
    maquina.on("data", (d) => { volcado(reg, "MAQ -> PC", d); cliente.write(d); });
    const cerrar = () => { cliente.destroy(); maquina.destroy(); };
    maquina.on("error", (e) => { reg.mostrar(`No se pudo hablar con la máquina: ${e.message}`); cerrar(); });
    cliente.on("error", cerrar);
    maquina.on("close", cerrar);
    cliente.on("close", () => { cerrar(); reg.mostrar("Conexión cerrada. Esperando una nueva..."); });
  });
  await new Promise((ok, falla) => {
    servidor.once("error", falla);
    servidor.listen(Number(args.local), "0.0.0.0", ok);
  });
  reg.mostrar(`Esperando a IFD.exe en el puerto ${args.local}; reenvío a ${args.maquina}:${args["puerto-maquina"]}. Ctrl+C para salir.`);
  reg.mostrar("En bin/IFDCTRL.INI poner [SOCKET] ADDRESS=127.0.0.1");
  return () => new Promise((ok) => servidor.close(() => ok()));
}

const MODOS = { monitor: modoMonitor, puente: modoPuente, tcp: modoTcp };

const { values: args, positionals } = parseArgs({
  allowPositionals: true,
  options: {
    puerto: { type: "string", default: "COM5" },
    baudios: { type: "string", default: "115200" },
    real: { type: "string", default: "COM5" },
    virtual: { type: "string", default: "COM20" },
    maquina: { type: "string", default: "192.168.123.231" },
    "puerto-maquina": { type: "string", default: "4101" },
    local: { type: "string", default: "4101" },
  },
});

const modo = positionals[0];
if (!(modo in MODOS)) {
  console.log("Uso: node escuchar.js monitor|puente|tcp [opciones]   (ver el encabezado del archivo)");
  process.exit(1);
}

const reg = crearRegistro(modo);
reg.mostrar(`Log: ${reg.ruta}`);
try {
  const cerrar = await MODOS[modo](args, reg);
  process.once("SIGINT", async () => {
    reg.mostrar("Detenido por el usuario.");
    await cerrar();
    await reg.cerrar();
    process.exit(0);
  });
} catch (e) {
  reg.mostrar(`No se pudo abrir: ${e.message}`);
  await reg.cerrar();
  process.exit(1);
}
