// Protocolo PC <-> contadora SB-7 / SB-9 (Doc/PC_protocol_SB_MIB_series.md).
// Armado y verificación de tramas, decodificación de respuestas y cambios de
// configuración. No depende del medio (serie o TCP).

import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const AQUI = path.dirname(fileURLToPath(import.meta.url));

// ---------------------------------------------------------------- utilidades

export const h2 = (b) => b.toString(16).toUpperCase().padStart(2, "0");
export const hex = (buf) => [...buf].map(h2).join(" ");

// ---------------------------------------------------------------- tramas

/** datos = [SubCommand, Param1, ...]; cada byte se envía como 2 nibbles. */
export function armarTrama(datos, estacion = 0) {
  const nibbles = datos.flatMap((b) => [(b >> 4) & 0x0f, b & 0x0f]);
  const cuerpo = [0x19, 0x02, 0x00, 0x00, 0x00, estacion, ...nibbles];
  const largo = cuerpo.length + 1; // LEN = total - 4
  const suma = (largo + cuerpo.reduce((a, b) => a + b, 0)) & 0xff;
  return Buffer.from([0xf0, 0xf1, largo, ...cuerpo, suma >> 4, suma & 0x0f]);
}

/** Devuelve { ok, motivo, datos } con los datos ya reunidos (nibbles -> bytes). */
export function verificarTrama(t) {
  if (t.length < 13 || t[0] !== 0xf0 || t[1] !== 0xf1) {
    return { ok: false, motivo: "no empieza con F0 F1", datos: [] };
  }
  if (t[2] + 4 !== t.length) {
    return { ok: false, motivo: `LEN=${h2(t[2])} no coincide con ${t.length} bytes`, datos: [] };
  }
  let suma = 0;
  for (let i = 2; i < t.length - 2; i++) suma += t[i];
  suma &= 0xff;
  if (t[t.length - 2] !== suma >> 4 || t[t.length - 1] !== (suma & 0x0f)) {
    return {
      ok: false,
      motivo: `checksum ${h2(t[t.length - 2])} ${h2(t[t.length - 1])}, esperado ${h2(suma >> 4)} ${h2(suma & 15)}`,
      datos: [],
    };
  }
  const nib = t.subarray(9, t.length - 2);
  if (nib.length % 2) return { ok: false, motivo: "cantidad impar de nibbles", datos: [] };
  const datos = [];
  for (let i = 0; i < nib.length; i += 2) datos.push((nib[i] << 4) | nib[i + 1]);
  return { ok: true, motivo: "", datos };
}

/**
 * Separa el flujo recibido en tramas (F0 F1 ...) y bytes sueltos (1BYTE_COUNT_DATA).
 * Una trama que queda cortada más de `espera` ms se entrega como incompleta.
 */
export class Separador {
  constructor({ onTrama, onByte, onIncompleta, espera = 500 }) {
    Object.assign(this, { onTrama, onByte, onIncompleta, espera });
    this.buf = Buffer.alloc(0);
    this.timer = null;
  }

  push(trozo) {
    clearTimeout(this.timer);
    this.buf = Buffer.concat([this.buf, trozo]);
    while (this.buf.length) {
      const b = this.buf;
      if (b[0] === 0xf0 && (b.length < 2 || b[1] === 0xf1)) {
        if (b.length < 3 || b.length < b[2] + 4) break;
        const total = b[2] + 4;
        this.buf = b.subarray(total);
        this.onTrama(Buffer.from(b.subarray(0, total)));
      } else {
        this.buf = b.subarray(1);
        this.onByte(b[0]);
      }
    }
    if (this.buf.length) {
      this.timer = setTimeout(() => {
        const resto = this.buf;
        this.buf = Buffer.alloc(0);
        this.onIncompleta(resto);
      }, this.espera);
      this.timer.unref();
    }
  }

  detener() {
    clearTimeout(this.timer);
  }
}

// ---------------------------------------------------------------- nombres

/** Códigos de moneda de gpaCurrencyCode[] en IFDView.cpp (índice = código). */
function cargarMonedas() {
  try {
    const src = readFileSync(path.join(AQUI, "..", "..", "IFDView.cpp"), "latin1");
    const bloque = src.split("gpaCurrencyCode[] = {")[1].split("};")[0];
    return [...bloque.matchAll(/"([^"]*)"/g)].map((m) => m[1]);
  } catch {
    return [];
  }
}

export const MONEDAS = cargarMonedas();

export const moneda = (c) => (c > 0 && c < MONEDAS.length ? `${c} (${MONEDAS[c]})` : String(c));

export const SUBCMD = {
  0x30: "DEVICE_SET_LIVE", 0x31: "SETUP_STATE_DATA", 0x32: "COUNT_START",
  0x33: "CD_ERROR", 0x34: "RESULT_DATA", 0x35: "RESULT_REQUEST",
  0x36: "RESULT_CLEAR", 0x37: "START_STOP", 0x38: "DEVICE_SETUP2",
  0x39: "DEFAULT_LOADING", 0x3a: "CURRENCY_CHANGE", 0x3b: "SETUP_NO_ACCEPT",
  0x3d: "COUNT_STOP", 0x3e: "SENSOR_STATUS", 0x41: "SETUP_STATE_DATA2",
  0x43: "COUNTING_REPORT_DATA", 0x44: "SAVE_BMP_TO_USB", 0x45: "MC_STATUS",
  0x46: "SW_VERSION", 0x47: "OCR_RESULT", 0x48: "IFD_WING_MOTOR",
  0x49: "IFD_REJECT_DESIGNATED_NOTE", 0x4a: "SETUP_MAINTENANCE_ALARM",
  0x4c: "REQUEST_IFD_COUNT_LOG_DATA", 0x4d: "SEND_IFD_COUNT_LOG_DATA",
  0x4e: "SEND_IFD_REF_NUMBER", 0x4f: "RESULT_DATA2", 0x53: "SET_MACHINE_DATE_TIME",
  0x63: "SETUP_STATE_DATA_EX", 0xa8: "REBOOT",
};

const MODOS2 = {
  0: "COUNT", 1: "MIXED", 2: "SINGLE", 3: "FACE", 4: "ORIENT", 5: "SERIAL No. PRINT",
  6: "ISSUE", 7: "DISPENSE", 8: "OCR", 9: "MIXED CURRENCY",
};
const VELOCIDAD = { 0: "1000 rpm", 1: "1200 rpm", 2: "1500 rpm", 3: "600 rpm", 4: "800 rpm", 5: "900 rpm" };

// Billetes por índice de denominación, según código de moneda. Valores base (SB-9);
// cada modelo de ../../maquinas.json puede reemplazar la lista de una moneda (usarBilletes).
// SB-9, ARS: confirmados con billetes reales (2026-09-29): 3 = $100, 7 = $2000, 8 = $10000.
export const BILLETES = {
  1: ["$1", "$2", "$5", "$10", "$20", "$50", "$100"],
  4: ["€5", "€10", "€20", "€50", "€100", "€200", "€500"],
  115: ["$10", "$20", "$50", "$100", "$200", "$500", "$1000", "$2000", "$10000", "$20000"],
};
const BILLETES_BASE = structuredClone(BILLETES);

/**
 * Aplica el orden de billetes de un modelo de máquina (ver src/maquinas.js):
 * parte de los valores base (SB-9) y reemplaza las monedas que el modelo define.
 */
export function usarBilletes(billetesModelo = {}) {
  for (const k of Object.keys(BILLETES)) delete BILLETES[k];
  Object.assign(BILLETES, structuredClone(BILLETES_BASE));
  for (const [k, v] of Object.entries(billetesModelo)) BILLETES[Number(k)] = [...v];
}

// Estado que se va conociendo de la máquina.
export const estado = {
  moneda: null, // se actualiza al recibir 31h / 41h / 4Fh
  config: null, // últimos 11 parámetros de 41h, base para cambiar la configuración
  version: 0, // aumenta con cada 41h recibido (para esperar una relectura)
};

// Nombres de la consola -> código de modo en SETUP_STATE_DATA2 (41h)
export const MODOS_CONSOLA = { conteo: 0x00, mixto: 0x01, single: 0x02, cara: 0x03, orientacion: 0x04 };

export const LIMPIEZAS = { rechazo: 0x01, salida: 0x02, total: 0x04, mixto: 0x08, simple: 0x10, jam: 0x20, reporte: 0x80 };
export const PEDIDOS = {
  estado: 0x01, resultado: 0x02, error: 0x04, reenviar: 0x08, sensores: 0x10,
  disp2: 0x20, reporte: 0x80, estado2: 0x12,
  version: 0x21, // 0x21 no está en el protocolo; capturado de IFD.exe
};
const PEDIDOS_NOMBRE = Object.fromEntries(Object.entries(PEDIDOS).map(([k, v]) => [v, k]));

export function billete(i) {
  const lista = BILLETES[estado.moneda] ?? [];
  return i < lista.length ? lista[i] : `[${i}]`;
}

export function valorBillete(i) {
  const nombre = billete(i);
  const digitos = nombre.replace(/\D/g, "");
  return digitos && !nombre.startsWith("[") ? Number(digitos) : 0;
}

// Capacidad de bandejas por código, confirmada en la SB-9 (2026-10-21) cambiando cada
// valor en el teclado y leyendo 41h. La máquina informa en el formato antiguo de 3
// códigos, así que agrupa los valores que no existían en él.
const RECHAZO = { 0: "30", 1: "50, 70 o 100" };
const APILADOR = { 0: "200, 250 o 300", 1: "150", 2: "100" };
const capacidad = (tabla, codigo) => (codigo in tabla ? `${tabla[codigo]} billetes` : `código ${codigo}`);

const ERRORES_SENSOR = {
  0: "sin error", 1: "JAM1", 2: "JAM2", 3: "JAM3", 4: "JAM4", 5: "alimentación",
  6: "tapa frontal abierta", 7: "tapa trasera abierta", 9: "motor principal",
};

export const BYTE_CONTEO = {
  0x20: "SOSPECHOSO (a rechazo)", 0x40: "FIN de datos de conteo",
  0x70: "FALSO (CF)", 0x71: "STAY NOTE",
};

function bits(valor, nombres) {
  const activos = nombres.filter((n, i) => n && (valor >> i) & 1);
  return activos.length ? activos.join(", ") : "ninguno";
}

function denominacion(d) {
  if (d === 0x1f) return "DD (toma la del primer billete)";
  if (d === 0x1e) return "ALL";
  return `${billete(d)} (índice ${d})`;
}

const dos = (n) => String(n).padStart(2, "0");
const listaBilletes = (cantidades) =>
  cantidades.map((c, i) => (c ? `${billete(i)} x${c}` : null)).filter(Boolean).join("  ") || "todo 0";

/** d = datos (bytes reales). Devuelve una lista de líneas. */
export function decodificar(d) {
  const sc = d[0];
  let p = d.slice(1);
  const L = [];
  if (sc === 0x30 && p.length) {
    L.push(bits(p[0], ["KNOCK", "ACK", "RELEASE"]));
  } else if (sc === 0x31 && p.length >= 6) {
    estado.moneda = p[2];
    L.push(
      `motor: ${VELOCIDAD[p[0] >> 4] ?? p[0]}`,
      "estado: " + bits(p[1], ["Batch", null, "beep aviso", "Auto", "ADD", "UV", "MR", "Mode Lock"]),
      `moneda: ${moneda(p[2])}`,
      `modo: ${MODOS2[p[3] & 7] ?? p[3] & 7}, denominación: ${denominacion(p[3] >> 3)}`,
      `bandejas: rechazo ${capacidad(RECHAZO, p[4] >> 6)}, salida ${capacidad(APILADOR, (p[4] >> 4) & 3)}`,
      `lote: ${p[5]}`,
    );
  } else if (sc === 0x41 && p.length >= 11) {
    estado.moneda = p[0];
    estado.config = p.slice(0, 11);
    estado.version += 1;
    L.push(
      `moneda: ${moneda(p[0])}`,
      `modo: ${MODOS2[p[1]] ?? p[1]}`,
      "estado: " + bits(p[2], ["Batch", null, "beep aviso", "Auto", "ADD", "UV", "MR", "IR"]),
      `mode lock: ${p[3] & 1 ? "On" : "Off"}`,
      `motor: ${VELOCIDAD[p[4] >> 4] ?? p[4]}`,
      `denominación: ${denominacion(p[5] & 0x1f)}`,
      `bandejas: rechazo ${capacidad(RECHAZO, p[6] >> 4)}, salida ${capacidad(APILADOR, p[6] & 0x0f)}`,
      `lote: ${p[7]}`,
      `niveles UV/MR/IR: ${p[8]}/${p[9]}/${p[10]}`,
    );
    if (p.length > 11) L.push("bytes extra (no documentados): " + hex(p.slice(11)));
  } else if (sc === 0x32 && p.length) {
    L.push(bits(p[0], ["inicio de conteo", "depósito nuevo"]));
  } else if (sc === 0x33 && p.length) {
    L.push("error: " + bits(p[0], ["JAM", "alimentación", "motor principal", "limpiar tolva"]));
  } else if (sc === 0x34 || sc === 0x4f) {
    if (sc === 0x4f) {
      estado.moneda = p[0];
      L.push(`moneda: ${moneda(p[0])}`);
      p = p.slice(1);
    }
    if (p.length >= 2 && (p.length - 2) % 3 === 0) {
      const n = (p.length - 2) / 3;
      const actual = p.slice(2, 2 + n);
      const prev = Array.from({ length: n }, (_, i) => (p[2 + n + 2 * i] << 8) | p[3 + n + 2 * i]);
      L.push(`rechazados: ${p[0]}   en bandeja de salida: ${p[1]}`);
      L.push("actual   : " + listaBilletes(actual));
      L.push("anterior : " + listaBilletes(prev));
      const total = actual.reduce((s, c, i) => s + c * valorBillete(i), 0);
      if (total) L.push(`monto actual: $${total.toLocaleString("es-AR")}`);
    } else {
      L.push("formato inesperado: " + hex(p));
    }
  } else if (sc === 0x38 && p.length) {
    L.push(bits(p[0], ["1BYTE_COUNT_DATA activo", "teclado bloqueado"]));
  } else if (sc === 0x35 && p.length) {
    L.push("pedido: " + (PEDIDOS_NOMBRE[p[0]] ?? `${h2(p[0])}h`));
  } else if (sc === 0x3e && p.length >= 5) {
    L.push(
      "sensores 1: " + bits(p[0], [null, "solenoide->salida", "RP1 izq", "RP1 der", null, null, "JP izq", "JP der"]),
      "sensores 2: " + bits(p[1], ["SP izq", "SP der", "salida vacía", "rechazo F vacío",
        "tapa frontal ABIERTA", "tapa trasera ABIERTA", "rechazo R vacío", "billetes en tolva"]),
      `billetes en salida: ${p[2]}   en rechazo: ${p[3]}`,
      `error: ${ERRORES_SENSOR[p[4]] ?? p[4]}`,
    );
  } else if (sc === 0x43 && p.length >= 5) {
    L.push(`total en salida: ${(p[0] << 8) | p[1]}   total rechazados: ${(p[3] << 8) | p[4]}`);
  } else if (sc === 0x45 && p.length) {
    L.push(bits(p[0], ["limpiar tolva", "revisar salida", "revisar rechazo"]));
  } else if (sc === 0x46 && p.length >= 2) {
    L.push(`versión de software: ${dos(p[0])}.${dos(p[1])}`);
    if (p.length >= 4) L.push(`checksum del firmware: ${h2(p[2]).toLowerCase()}${h2(p[3]).toLowerCase()}`);
  } else if (sc === 0x47) {
    L.push("OCR: " + p.filter((b) => b >= 32 && b < 127).map((b) => String.fromCharCode(b)).join(""));
  } else if (sc === 0x3b) {
    L.push("la máquina rechazó la configuración (menú abierto)");
  } else if (sc === 0x3d) {
    L.push("fin de conteo");
  } else {
    L.push("parámetros: " + (hex(p) || "(ninguno)"));
  }
  return L;
}

// ---------------------------------------------------------------- configuración (41h)

/**
 * Reenvía la última configuración leída (41h) aplicándole solo el cambio indicado.
 * Parámetros: [0] moneda, [1] modo, [2] estado (bit0 = Batch), [3] mode lock,
 * [4] motor, [5] denominación, [6] bandejas, [7] lote, [8..10] niveles UV/MR/IR.
 */
export function tramaConfig(modificar) {
  const p = [...estado.config];
  modificar(p);
  return armarTrama([0x41, ...p]);
}

export const tramaCambiarModo = (modo) => tramaConfig((p) => { p[1] = modo; });
export const tramaBatch = (activar) => tramaConfig((p) => { p[2] = activar ? p[2] | 0x01 : p[2] & ~0x01; });
export const tramaLote = (n) => tramaConfig((p) => { p[7] = n; });

/** Auto/Manual (41h, param 2 bit 3). En Manual la máquina ignora 'iniciar' desde la PC. */
export const tramaAuto = (activar) => tramaConfig((p) => { p[2] = activar ? p[2] | 0x08 : p[2] & ~0x08; });

export const SENSORES = { uv: 0x20, mr: 0x40, ir: 0x80 }; // bits del estado (param 2) en 41h
export const tramaSensor = (nombre, activar) =>
  tramaConfig((p) => { p[2] = activar ? p[2] | SENSORES[nombre] : p[2] & ~SENSORES[nombre]; });
export const tramaDivisa = (codigo) => tramaConfig((p) => { p[0] = codigo; });

/** Denominación fija (0..) o 0x1F = DD (toma la del primer billete). Solo SINGLE/FACE/ORIENT. */
export const tramaDenom = (indice) => tramaConfig((p) => { p[5] = (p[5] & 0xe0) | (indice & 0x1f); });

/**
 * EXPERIMENTAL: código de capacidad de bandejas (41h, param 6: rechazo bits 7-4,
 * salida bits 3-0). En la SB-9 no se sabe si tiene efecto; verificar en la pantalla.
 */
export const tramaBandejas = (rechazo, salida) =>
  tramaConfig((p) => { p[6] = ((rechazo & 0x0f) << 4) | (salida & 0x0f); });

/** 'dd', un valor de billete ('100', '$100') o 'i3' (índice directo). null si no existe. */
export function indiceDenom(texto) {
  const t = texto.toLowerCase().replace(/^\$+/, "");
  if (t === "dd") return 0x1f;
  if (/^i\d+$/.test(t)) return Number(t.slice(1));
  const lista = BILLETES[estado.moneda] ?? [];
  const i = lista.findIndex((nombre) => nombre.replace(/\D/g, "") === t);
  return i >= 0 ? i : null;
}

/** 'usd', 'ars', ... o el número de código. null si no existe. */
export function codigoDivisa(texto) {
  if (/^\d+$/.test(texto)) {
    const n = Number(texto);
    return n > 0 && n < 256 ? n : null;
  }
  const i = MONEDAS.indexOf(texto.toUpperCase());
  return i > 0 ? i : null;
}
