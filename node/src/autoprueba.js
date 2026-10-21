// Autoprueba sin máquina: compara con ejemplos del protocolo y con tramas
// capturadas de la máquina real. La usan `node probar.js --prueba` y `npm test`.

import {
  armarTrama, verificarTrama, decodificar, hex, estado, SUBCMD, MODOS_CONSOLA,
  tramaCambiarModo, tramaBatch, tramaLote, tramaDivisa, tramaDenom, tramaBandejas,
  indiceDenom, codigoDivisa,
} from "./protocolo.js";

const desdeHex = (s) => Buffer.from(s.replace(/\s+/g, ""), "hex");

export const CASOS_ARMADO = [
  [[0x30, 0x01], "F0 F1 0B 19 02 00 00 00 00 03 00 00 01 02 0A"], // KNOCK (doc)
  [[0x35, 0x02], "F0 F1 0B 19 02 00 00 00 00 03 05 00 02 03 00"], // resultado (doc)
  [[0x37, 0x01], "F0 F1 0B 19 02 00 00 00 00 03 07 00 01 03 01"], // start (doc)
  [[0x36, 0x80], "F0 F1 0B 19 02 00 00 00 00 03 06 08 00 03 07"], // clear reporte (doc)
  [[0x35, 0x12], "F0 F1 0B 19 02 00 00 00 00 03 05 01 02 03 01"], // capturado de IFD.exe
];

// Respuesta real 41h (ARS, MIXED, lote 25) capturada con Wireshark
export const CONFIG_REAL = desdeHex(
  "f0f1251902000000000401070300010e0800000000010f01000109000300030003000000000000080a");

// Resultado real 34h: 2 billetes de $100
export const RESULTADO_ARS = desdeHex(
  "F0 F1 49 19 02 00 00 00 00 03 04 00 00 00 02 00 00 00 00 00 00 00 02 00 00 00 00 00 00 00 00 00 "
  + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 02 00 00 00 00 00 00 00 00 00 00 00 00 00 "
  + "00 00 00 00 00 00 00 00 00 00 00 07 01");

// Ejemplo RESULT_DATA del protocolo (US$)
export const EJEMPLO_34 = desdeHex(
  "F0F137190200000000030400000003000000000001000000020000000000000002"
  + "000000000000000100000001000000010000000200000001 0607");

export function autoprueba() {
  let ok = true;
  for (const [datos, esperado] of CASOS_ARMADO) {
    const t = hex(armarTrama(datos));
    const bien = t === esperado;
    ok &&= bien;
    console.log(`${bien ? "OK " : "MAL"} ${SUBCMD[datos[0]].padEnd(16)} ${t}`);
  }

  const r = verificarTrama(CONFIG_REAL);
  console.log("\nRespuesta real capturada (41h):", r.ok ? "checksum OK" : r.motivo);
  decodificar(r.datos).forEach((l) => console.log("  " + l));

  const r3 = verificarTrama(RESULTADO_ARS);
  console.log("\nResultado real ARS (2 billetes de $100):", r3.ok ? "checksum OK" : r3.motivo);
  decodificar(r3.datos).forEach((l) => console.log("  " + l));
  ok &&= r.ok && r3.ok;

  const t4 = tramaCambiarModo(MODOS_CONSOLA.single);
  const r4 = verificarTrama(t4);
  console.log("\nTrama para cambiar a SINGLE (desde la config real):", r4.ok ? "OK" : r4.motivo);
  console.log("  " + hex(t4));
  console.log("  " + decodificar(r4.datos).slice(0, 3).join("; "));
  ok &&= r4.ok && r4.datos[2] === 0x02;

  const d5 = verificarTrama(tramaBatch(true)).datos;
  const d6 = verificarTrama(tramaLote(100)).datos;
  console.log("\nbatch on ->", decodificar(d5).filter((l) => l.startsWith("estado")).join("; "));
  console.log("lote 100 ->", decodificar(d6).filter((l) => l.startsWith("lote")).join("; "));
  ok &&= (d5[3] & 1) === 1 && d6[8] === 100;

  const d7 = verificarTrama(tramaDivisa(codigoDivisa("usd"))).datos;
  console.log("divisa usd ->", decodificar(d7).filter((l) => l.startsWith("moneda")).join("; "),
    "| divisa ars ->", codigoDivisa("ars"));
  ok &&= d7[1] === 1 && codigoDivisa("ars") === 115;

  decodificar(r.datos); // volver a la configuración real (ARS) como base
  const d8 = verificarTrama(tramaDenom(indiceDenom("100"))).datos;
  console.log("denom 100 ->", decodificar(d8).filter((l) => l.startsWith("denominación")).join("; "));
  ok &&= (d8[6] & 0x1f) === 3 && indiceDenom("dd") === 0x1f;
  const d9 = verificarTrama(tramaBandejas(3, 4)).datos;
  console.log("bandejas 3 4 ->", decodificar(d9).filter((l) => l.startsWith("bandejas")).join("; "));
  ok &&= d9[7] === 0x34;
  decodificar(r.datos); // volver a la configuración real

  estado.moneda = 1; // el ejemplo del protocolo es en US$
  const r2 = verificarTrama(EJEMPLO_34);
  console.log("\nEjemplo RESULT_DATA del protocolo (US$):", r2.ok ? "checksum OK" : r2.motivo);
  decodificar(r2.datos).forEach((l) => console.log("  " + l));
  ok &&= r2.ok;

  console.log("\nAutoprueba", ok ? "APROBADA" : "FALLIDA");
  return ok;
}
