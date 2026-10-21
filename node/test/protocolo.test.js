import { test } from "node:test";
import assert from "node:assert/strict";

import {
  armarTrama, verificarTrama, decodificar, hex, estado, Separador, MODOS_CONSOLA,
  tramaCambiarModo, tramaBatch, tramaLote, tramaDivisa, tramaDenom, tramaBandejas, tramaSensor, tramaAuto,
  indiceDenom, codigoDivisa,
} from "../src/protocolo.js";
import { CASOS_ARMADO, CONFIG_REAL, RESULTADO_ARS, EJEMPLO_34 } from "../src/autoprueba.js";
import * as perfiles from "../src/perfiles.js";

test("arma tramas idénticas a los ejemplos del protocolo y a IFD.exe", () => {
  for (const [datos, esperado] of CASOS_ARMADO) assert.equal(hex(armarTrama(datos)), esperado);
});

test("verifica y decodifica la configuración real (41h)", () => {
  const r = verificarTrama(CONFIG_REAL);
  assert.ok(r.ok, r.motivo);
  const lineas = decodificar(r.datos);
  assert.ok(lineas.includes("moneda: 115 (ARS)"));
  assert.ok(lineas.includes("modo: MIXED"));
  assert.ok(lineas.includes("lote: 25"));
  assert.deepEqual(estado.config, [0x73, 0x01, 0xe8, 0x00, 0x00, 0x1f, 0x10, 0x19, 3, 3, 3]);
});

test("decodifica el resultado real ARS: 2 x $100 = $200", () => {
  const r = verificarTrama(RESULTADO_ARS);
  assert.ok(r.ok, r.motivo);
  const lineas = decodificar(r.datos);
  assert.ok(lineas.includes("actual   : $100 x2"));
  assert.ok(lineas.includes("monto actual: $200"));
});

test("decodifica el ejemplo RESULT_DATA del protocolo en US$", () => {
  estado.moneda = 1;
  const lineas = decodificar(verificarTrama(EJEMPLO_34).datos);
  assert.ok(lineas.includes("actual   : $5 x1  $20 x2"));
  assert.ok(lineas.includes("monto actual: $45"));
});

test("detecta checksum incorrecto", () => {
  const t = Buffer.from(armarTrama([0x30, 0x01]));
  t[t.length - 1] ^= 1;
  assert.equal(verificarTrama(t).ok, false);
});

test("cambios de configuración 41h tocan solo su campo", () => {
  decodificar(verificarTrama(CONFIG_REAL).datos);
  const base = [...estado.config];
  const cambia = (trama, i, valor) => {
    const d = verificarTrama(trama).datos.slice(1);
    assert.equal(d[i], valor);
    d.forEach((v, j) => j !== i && assert.equal(v, base[j]));
  };
  cambia(tramaCambiarModo(MODOS_CONSOLA.single), 1, 0x02);
  cambia(tramaBatch(true), 2, base[2] | 1);
  cambia(tramaLote(100), 7, 100);
  cambia(tramaDivisa(codigoDivisa("usd")), 0, 1);
  cambia(tramaDenom(indiceDenom("100")), 5, (base[5] & 0xe0) | 3);
  cambia(tramaBandejas(3, 4), 6, 0x34);
  cambia(tramaSensor("uv", false), 2, base[2] & ~0x20);
  cambia(tramaSensor("uv", true), 2, base[2] | 0x20);
  cambia(tramaAuto(false), 2, base[2] & ~0x08);
  cambia(tramaAuto(true), 2, base[2] | 0x08);
  assert.equal(indiceDenom("dd"), 0x1f);
  assert.equal(codigoDivisa("ars"), 115);
});

test("perfiles: cada uno se aplica sobre la config real y queda verificado", () => {
  const lista = perfiles.cargar();
  assert.deepEqual(Object.keys(lista), ["1", "2", "3", "4"]);
  for (const [n, perfil] of Object.entries(lista)) {
    decodificar(verificarTrama(CONFIG_REAL).datos);
    const nuevo = perfiles.aplicar(estado.config, perfil, codigoDivisa);
    assert.ok(verificarTrama(armarTrama([0x41, ...nuevo])).ok, `perfil ${n}`);
    // las bandejas se escriben con un código y se leen con otro: se revisan aparte
    const malas = perfiles.verificar(nuevo, perfil, codigoDivisa)
      .filter((f) => f.estado !== "OK" && !f.campo.startsWith("bandeja"));
    assert.deepEqual(malas, [], `perfil ${n}`);
    assert.equal(nuevo[6], 0x00, `perfil ${n}: bandejas 0 0 = rechazo 100 / salida 300`);
  }
  // tras aplicarlo, la máquina informa 10h (rechazo 100 -> código 1 al leer): verificación OK
  const leido = perfiles.aplicar(estado.config, lista["1"], codigoDivisa);
  leido[6] = 0x10;
  assert.ok(perfiles.verificar(leido, lista["1"], codigoDivisa).every((f) => f.estado === "OK"));
  decodificar(verificarTrama(CONFIG_REAL).datos);
  const p2 = perfiles.aplicar(estado.config, lista["2"], codigoDivisa, 50);
  assert.equal(p2[7], 50); // lote indicado en el comando
  assert.equal(p2[2] & 1, 1); // batch on
  assert.equal(p2[6], 0x00); // bandejas: rechazo 100 / salida 300
});

test("separa tramas y bytes sueltos aunque lleguen partidos", () => {
  const tramas = [];
  const bytes = [];
  const s = new Separador({ onTrama: (t) => tramas.push(t), onByte: (b) => bytes.push(b), onIncompleta: () => {} });
  const knock = armarTrama([0x30, 0x01]);
  const flujo = Buffer.concat([Buffer.from([0x03, 0x07]), knock, Buffer.from([0x40])]);
  s.push(flujo.subarray(0, 6));
  s.push(flujo.subarray(6));
  s.detener();
  assert.deepEqual(bytes, [0x03, 0x07, 0x40]);
  assert.equal(tramas.length, 1);
  assert.deepEqual(tramas[0], knock);
});
