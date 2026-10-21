// Perfiles de configuración de la contadora (../../perfiles.json, compartido con python/).
//
// Un perfil indica cómo debe quedar la configuración 41h. Lo que no indica queda como
// está en la máquina. "comun" se aplica a todos los perfiles y cada uno puede pisarlo.
//
// Bandejas: la SB-9 usa códigos distintos para ESCRIBIR y para LEER (confirmado
// 2026-10-21 con la pantalla). Se escriben solo los valores con código de escritura
// conocido (rechazo 100 y salida 300 = código 0); el resto solo se verifica. Al leer,
// la máquina informa en grupos (salida 200/250/300 = mismo código).

import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

export const RUTA = path.join(path.dirname(fileURLToPath(import.meta.url)), "..", "..", "perfiles.json");

const MODOS = { conteo: 0, mixto: 1, single: 2, cara: 3, orientacion: 4 };
const NOMBRE_MODO = Object.fromEntries(Object.entries(MODOS).map(([k, v]) => [v, k]));
const BITS = { batch: 0x01, beep: 0x04, auto: 0x08, add: 0x10 }; // param 2 de 41h
const SENSORES = { uv: 0x20, mr: 0x40, ir: 0x80 }; // param 2 de 41h
const NIVELES = { uv: 8, mr: 9, ir: 10 }; // índice en 41h
// Capacidad -> código para ESCRIBIR en la SB-9 (confirmado: "bandejas 0 0" deja 100 / 300)
const ESCRIBIR_RECHAZO = { 100: 0 };
const ESCRIBIR_SALIDA = { 300: 0 };
// Capacidad -> código que INFORMA la SB-9 al leer (confirmado 2026-10-21)
const COD_RECHAZO = { 30: 0, 50: 1, 70: 1, 100: 1 };
const COD_SALIDA = { 100: 2, 150: 1, 200: 0, 250: 0, 300: 0 };
const GRUPO_RECHAZO = { 0: "30", 1: "50/70/100" };
const GRUPO_SALIDA = { 0: "200/250/300", 1: "150", 2: "100" };
const LOTE_POR_DEFECTO = 100;

/** Devuelve { número: perfil } con lo común ya combinado. */
export function cargar() {
  const datos = JSON.parse(readFileSync(RUTA, "utf8"));
  const comun = datos.comun ?? {};
  return Object.fromEntries(Object.entries(datos.perfiles).map(([k, v]) => [k, { ...comun, ...v }]));
}

const loteDe = (perfil, lote) => lote ?? perfil.lote ?? LOTE_POR_DEFECTO;
const fijar = (valor, bit, activar) => (activar ? valor | bit : valor & ~bit);

/** Devuelve los 11 parámetros de 41h con el perfil aplicado. */
export function aplicar(config, perfil, codigoDivisa, lote) {
  const p = [...config];
  if ("divisa" in perfil) p[0] = codigoDivisa(perfil.divisa);
  if ("modo" in perfil) p[1] = MODOS[perfil.modo];
  for (const [clave, bit] of Object.entries(BITS)) if (clave in perfil) p[2] = fijar(p[2], bit, perfil[clave]);
  for (const [s, bit] of Object.entries(SENSORES)) {
    if (perfil.sensores && s in perfil.sensores) p[2] = fijar(p[2], bit, perfil.sensores[s]);
  }
  if (perfil.denom === "dd") p[5] = (p[5] & 0xe0) | 0x1f;
  if (perfil.batch) p[7] = loteDe(perfil, lote);
  for (const [s, i] of Object.entries(NIVELES)) if (perfil.niveles && s in perfil.niveles) p[i] = perfil.niveles[s];
  const b = perfil.bandejas ?? {};
  if (b.rechazo in ESCRIBIR_RECHAZO) p[6] = (ESCRIBIR_RECHAZO[b.rechazo] << 4) | (p[6] & 0x0f);
  if (b.salida in ESCRIBIR_SALIDA) p[6] = (p[6] & 0xf0) | ESCRIBIR_SALIDA[b.salida];
  return p.map((v) => v & 0xff);
}

/**
 * Compara la configuración leída con el perfil.
 * Devuelve [{ estado, campo, esperado, actual }]; estado = 'OK', 'NO' o '!!' (bandejas).
 */
export function verificar(p, perfil, codigoDivisa, lote) {
  const filas = [];
  const fila = (campo, esperado, actual) => filas.push({ estado: esperado === actual ? "OK" : "NO", campo, esperado, actual });
  const on = (v) => (v ? "on" : "off");
  if ("divisa" in perfil) fila("divisa", codigoDivisa(perfil.divisa), p[0]);
  if ("modo" in perfil) fila("modo", perfil.modo, NOMBRE_MODO[p[1]] ?? String(p[1]));
  for (const [clave, bit] of Object.entries(BITS)) if (clave in perfil) fila(clave, on(perfil[clave]), on(p[2] & bit));
  for (const [s, bit] of Object.entries(SENSORES)) {
    if (perfil.sensores && s in perfil.sensores) fila(`sensor ${s}`, on(perfil.sensores[s]), on(p[2] & bit));
  }
  if (perfil.batch) fila("lote", loteDe(perfil, lote), p[7]);
  if (perfil.denom === "dd") fila("denominación", "dd", (p[5] & 0x1f) === 0x1f ? "dd" : `índice ${p[5] & 0x1f}`);
  for (const [s, i] of Object.entries(NIVELES)) {
    if (perfil.niveles && s in perfil.niveles) fila(`nivel ${s}`, perfil.niveles[s], p[i]);
  }
  const b = perfil.bandejas ?? {};
  if ("rechazo" in b) {
    const cod = p[6] >> 4;
    filas.push({ estado: COD_RECHAZO[b.rechazo] === cod ? "OK" : "!!", campo: "bandeja rechazo", esperado: b.rechazo, actual: GRUPO_RECHAZO[cod] ?? `código ${cod}` });
  }
  if ("salida" in b) {
    const cod = p[6] & 0x0f;
    filas.push({ estado: COD_SALIDA[b.salida] === cod ? "OK" : "!!", campo: "bandeja salida", esperado: b.salida, actual: GRUPO_SALIDA[cod] ?? `código ${cod}` });
  }
  return filas;
}

export function describir(n, perfil) {
  const partes = [perfil.modo];
  if (perfil.denom === "dd") partes.push("denominación DD");
  partes.push(perfil.batch ? `lote ${loteDe(perfil)}` : "sin límite");
  return `${n}  ${perfil.nombre ?? ""}  (${partes.filter(Boolean).join(", ")})`;
}
