// Modelos de máquina (../../maquinas.json, compartido con python/): velocidad del
// puerto serie y orden de billetes de cada una.

import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

import { usarBilletes } from "./protocolo.js";

export const RUTA = path.join(path.dirname(fileURLToPath(import.meta.url)), "..", "..", "maquinas.json");
export const MODELO_POR_DEFECTO = "sb9";

export const cargarMaquinas = () => JSON.parse(readFileSync(RUTA, "utf8"));

/** Aplica el orden de billetes del modelo y devuelve su configuración. Lanza error si no existe. */
export function usarModelo(nombre) {
  const modelo = cargarMaquinas()[nombre];
  if (!modelo) throw new Error(`Modelo desconocido: ${nombre}. Ver ${RUTA}`);
  usarBilletes(modelo.billetes);
  return modelo;
}
