"""
Escucha el tráfico entre la PC y la contadora SB-7 / SB-9.

Modos:
  monitor  Abre el puerto COM y muestra todo lo que envía la máquina.
           (IFD.exe no puede usar el mismo puerto a la vez.)
  puente   Se pone en medio de IFD.exe y la máquina usando un par de puertos
           virtuales com0com. Muestra lo que va en ambos sentidos.
  tcp      Proxy TCP: IFD.exe se conecta a esta PC y el programa reenvía a la
           máquina. Muestra lo que va en ambos sentidos. No necesita drivers.

Ejemplos:
  python escuchar_puerto.py monitor --puerto COM5
  python escuchar_puerto.py puente --real COM5 --virtual COM20
  python escuchar_puerto.py tcp --maquina 192.168.10.109

Todo se guarda además en la carpeta logs/.
"""

import argparse
import os
import socket
import sys
import threading
import time
from datetime import datetime

import serial

BAUDIOS = 115200
PAUSA_TRAMA = 0.02  # silencio (s) que separa una trama de la siguiente


class Registro:
    """Imprime en pantalla y guarda en archivo, seguro entre hilos."""

    def __init__(self, modo):
        carpeta = os.path.join(os.path.dirname(os.path.abspath(__file__)), "logs")
        os.makedirs(carpeta, exist_ok=True)
        nombre = f"{modo}_{datetime.now():%Y%m%d_%H%M%S}.log"
        self.ruta = os.path.join(carpeta, nombre)
        self.archivo = open(self.ruta, "a", encoding="utf-8")
        self.lock = threading.Lock()

    def texto(self, msg):
        with self.lock:
            print(msg, flush=True)
            self.archivo.write(msg + "\n")
            self.archivo.flush()

    def datos(self, direccion, datos):
        hora = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        lineas = [f"{hora} {direccion} ({len(datos)} bytes)"]
        for i in range(0, len(datos), 16):
            bloque = datos[i:i + 16]
            hexa = " ".join(f"{b:02X}" for b in bloque)
            ascii_ = "".join(chr(b) if 32 <= b < 127 else "." for b in bloque)
            lineas.append(f"    {i:04X}  {hexa:<47}  {ascii_}")
        self.texto("\n".join(lineas))

    def cerrar(self):
        self.archivo.close()


def abrir_serie(puerto, baudios):
    return serial.Serial(puerto, baudios, bytesize=8, parity="N", stopbits=1,
                         timeout=PAUSA_TRAMA)


def leer_tramas_serie(ser, al_recibir, parar):
    """Junta los bytes que llegan seguidos y entrega cada trama completa."""
    buffer = bytearray()
    while not parar.is_set():
        try:
            trozo = ser.read(ser.in_waiting or 1)
        except serial.SerialException as e:
            al_recibir(None, e)
            return
        if trozo:
            buffer += trozo
            if len(buffer) < 4096:
                continue
        if buffer:
            al_recibir(bytes(buffer), None)
            buffer.clear()


def modo_monitor(args, reg):
    ser = abrir_serie(args.puerto, args.baudios)
    reg.texto(f"Escuchando {args.puerto} a {args.baudios} baudios. Ctrl+C para salir.")
    parar = threading.Event()

    def recibido(datos, error):
        if error:
            reg.texto(f"Error en {args.puerto}: {error}")
            parar.set()
        else:
            reg.datos("MAQ -> PC", datos)

    try:
        leer_tramas_serie(ser, recibido, parar)
    finally:
        ser.close()


def modo_puente(args, reg):
    real = abrir_serie(args.real, args.baudios)
    virtual = abrir_serie(args.virtual, args.baudios)
    reg.texto(f"Puente {args.virtual} (IFD.exe) <-> {args.real} (máquina). Ctrl+C para salir.")
    parar = threading.Event()

    def reenviar(origen, destino, etiqueta):
        def recibido(datos, error):
            if error:
                reg.texto(f"Error: {error}")
                parar.set()
                return
            reg.datos(etiqueta, datos)
            destino.write(datos)
        leer_tramas_serie(origen, recibido, parar)

    hilos = [
        threading.Thread(target=reenviar, args=(virtual, real, "PC -> MAQ"), daemon=True),
        threading.Thread(target=reenviar, args=(real, virtual, "MAQ -> PC"), daemon=True),
    ]
    for h in hilos:
        h.start()
    try:
        while not parar.is_set():
            time.sleep(0.2)
    finally:
        parar.set()
        real.close()
        virtual.close()


def modo_tcp(args, reg):
    servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    servidor.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    servidor.bind(("0.0.0.0", args.local))
    servidor.listen(1)
    servidor.settimeout(0.5)
    reg.texto(f"Esperando a IFD.exe en el puerto {args.local}; reenvío a "
              f"{args.maquina}:{args.puerto_maquina}. Ctrl+C para salir.")
    reg.texto("En bin/IFDCTRL.INI poner [SOCKET] ADDRESS=127.0.0.1")

    while True:
        try:
            cliente, origen = servidor.accept()
        except socket.timeout:
            continue
        reg.texto(f"IFD.exe conectado desde {origen[0]}:{origen[1]}")
        try:
            maquina = socket.create_connection((args.maquina, args.puerto_maquina), timeout=5)
            maquina.settimeout(None)
        except OSError as e:
            reg.texto(f"No se pudo conectar a la máquina: {e}")
            cliente.close()
            continue

        def reenviar(a, b, etiqueta):
            try:
                while True:
                    datos = a.recv(4096)
                    if not datos:
                        break
                    reg.datos(etiqueta, datos)
                    b.sendall(datos)
            except OSError:
                pass
            finally:
                for s in (a, b):
                    try:
                        s.shutdown(socket.SHUT_RDWR)
                    except OSError:
                        pass

        hilos = [
            threading.Thread(target=reenviar, args=(cliente, maquina, "PC -> MAQ"), daemon=True),
            threading.Thread(target=reenviar, args=(maquina, cliente, "MAQ -> PC"), daemon=True),
        ]
        for h in hilos:
            h.start()
        while any(h.is_alive() for h in hilos):
            time.sleep(0.2)
        cliente.close()
        maquina.close()
        reg.texto("Conexión cerrada. Esperando una nueva...")


def main():
    p = argparse.ArgumentParser(description="Escucha el tráfico con la contadora SB-7 / SB-9.")
    sub = p.add_subparsers(dest="modo", required=True)

    m = sub.add_parser("monitor", help="escuchar directamente un puerto COM")
    m.add_argument("--puerto", default="COM5")
    m.add_argument("--baudios", type=int, default=BAUDIOS)

    b = sub.add_parser("puente", help="espiar IFD.exe <-> máquina con com0com")
    b.add_argument("--real", default="COM5", help="COM donde está la máquina")
    b.add_argument("--virtual", default="COM20", help="extremo del par com0com que NO usa IFD.exe")
    b.add_argument("--baudios", type=int, default=BAUDIOS)

    t = sub.add_parser("tcp", help="proxy TCP entre IFD.exe y la máquina")
    t.add_argument("--maquina", default="192.168.10.109", help="IP de la contadora")
    t.add_argument("--puerto-maquina", type=int, default=4101)
    t.add_argument("--local", type=int, default=4101, help="puerto donde escucha el proxy")

    args = p.parse_args()
    reg = Registro(args.modo)
    reg.texto(f"Log: {reg.ruta}")
    try:
        {"monitor": modo_monitor, "puente": modo_puente, "tcp": modo_tcp}[args.modo](args, reg)
    except serial.SerialException as e:
        reg.texto(f"No se pudo abrir el puerto: {e}")
        sys.exit(1)
    except KeyboardInterrupt:
        reg.texto("Detenido por el usuario.")
    finally:
        reg.cerrar()


if __name__ == "__main__":
    main()
