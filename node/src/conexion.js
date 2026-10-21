// Conexión con la contadora por puerto serie o por TCP, con la misma interfaz:
//   eventos 'data' (Buffer), 'error' (Error), 'cerrada'
//   escribir(buf), cerrar()

import net from "node:net";
import { EventEmitter } from "node:events";

class Conexion extends EventEmitter {
  constructor(descripcion, escribir, cerrar) {
    super();
    this.descripcion = descripcion;
    this.escribir = escribir;
    this.cerrar = cerrar;
  }
}

/** Abre el puerto serie (8N1). */
export async function abrirSerie(puerto, baudios = 115200) {
  // Se importa aquí para que el modo TCP y la autoprueba funcionen sin el módulo nativo.
  const { SerialPort } = await import("serialport");
  const port = new SerialPort({
    path: puerto, baudRate: baudios, dataBits: 8, parity: "none", stopBits: 1, autoOpen: false,
  });
  await new Promise((ok, falla) => port.open((e) => (e ? falla(e) : ok())));
  const con = new Conexion(
    `${puerto} a ${baudios} baudios`,
    (buf) => port.write(buf),
    () => new Promise((ok) => (port.isOpen ? port.close(() => ok()) : ok())),
  );
  port.on("data", (d) => con.emit("data", d));
  port.on("error", (e) => con.emit("error", e));
  port.on("close", () => con.emit("cerrada"));
  return con;
}

/** Abre una conexión TCP con la máquina (puerto 4101 por defecto). */
export async function abrirTcp(ip, puerto = 4101, espera = 5000) {
  const sock = net.connect({ host: ip, port: puerto });
  await new Promise((ok, falla) => {
    sock.setTimeout(espera, () => sock.destroy(new Error(`sin respuesta de ${ip}:${puerto}`)));
    sock.once("connect", () => { sock.setTimeout(0); ok(); });
    sock.once("error", falla);
  });
  sock.setNoDelay(true);
  const con = new Conexion(
    `${ip}:${puerto}`,
    (buf) => sock.write(buf),
    () => new Promise((ok) => { sock.end(); sock.once("close", ok); setTimeout(ok, 500).unref(); }),
  );
  sock.on("data", (d) => con.emit("data", d));
  sock.on("error", (e) => con.emit("error", e));
  sock.on("close", () => con.emit("cerrada"));
  return con;
}
