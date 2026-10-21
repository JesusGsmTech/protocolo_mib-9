// Muestra en pantalla y guarda en node/logs/<prefijo>_AAAAMMDD_HHMMSS.log

import { createWriteStream, mkdirSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const CARPETA = path.join(path.dirname(fileURLToPath(import.meta.url)), "..", "logs");
const dos = (n) => String(n).padStart(2, "0");

export function hora(d = new Date()) {
  return `${dos(d.getHours())}:${dos(d.getMinutes())}:${dos(d.getSeconds())}.${String(d.getMilliseconds()).padStart(3, "0")}`;
}

export function crearRegistro(prefijo) {
  mkdirSync(CARPETA, { recursive: true });
  const d = new Date();
  const sello = `${d.getFullYear()}${dos(d.getMonth() + 1)}${dos(d.getDate())}_${dos(d.getHours())}${dos(d.getMinutes())}${dos(d.getSeconds())}`;
  const ruta = path.join(CARPETA, `${prefijo}_${sello}.log`);
  const archivo = createWriteStream(ruta, { flags: "a", encoding: "utf8" });
  return {
    ruta,
    /** Primera línea con la hora; las siguientes, sangradas debajo. */
    mostrar(texto) {
      const h = hora();
      const salida = texto.split("\n").map((l, i) => (i === 0 ? `${h} ${l}` : `${" ".repeat(13)}${l}`)).join("\n");
      console.log(salida);
      archivo.write(salida + "\n");
    },
    texto(linea) {
      console.log(linea);
      archivo.write(linea + "\n");
    },
    cerrar: () => new Promise((ok) => archivo.end(ok)),
  };
}
