"""
Consola para probar el protocolo de la contadora SB-7 / SB-9 por puerto serie.

Arma cada trama según el protocolo (Doc/PC_protocol_SB_MIB_series.md), la envía
y muestra decodificado lo que responde la máquina.

Uso:
  python probar_com.py                 (COM5, modelo sb9 a 115200)
  python probar_com.py --modelo mib9   (MIB-9: 57600 y su orden de billetes)
  python probar_com.py --puerto COM3
  python probar_com.py --ip 192.168.123.231   (por red, puerto 4101)
  python probar_com.py --prueba        (autoprueba sin máquina)

Cerrar IFD.exe antes: el puerto COM solo lo puede abrir un programa a la vez.
Escribir "ayuda" dentro de la consola para ver los comandos.
"""

import argparse
import json
import os
import re
import sys
import threading
import time
from datetime import datetime

import serial

import perfiles

AQUI = os.path.dirname(os.path.abspath(__file__))
PAUSA_MIN = 0.1  # el protocolo pide >= 100 ms entre tramas enviadas

# ---------------------------------------------------------------- tramas

def armar_trama(datos, estacion=0):
    """datos = [SubCommand, Param1, ...] (bytes); cada uno se envía como 2 nibbles."""
    nibbles = []
    for b in datos:
        nibbles += [(b >> 4) & 0x0F, b & 0x0F]
    cuerpo = [0x19, 0x02, 0x00, 0x00, 0x00, estacion] + nibbles
    largo = len(cuerpo) + 1           # LEN = total - 4
    suma = (largo + sum(cuerpo)) & 0xFF
    return bytes([0xF0, 0xF1, largo] + cuerpo + [suma >> 4, suma & 0x0F])


def verificar_trama(t):
    """Devuelve (ok, motivo, datos) con datos ya reunidos (nibbles -> bytes)."""
    if len(t) < 13 or t[0] != 0xF0 or t[1] != 0xF1:
        return False, "no empieza con F0 F1", []
    if t[2] + 4 != len(t):
        return False, f"LEN={t[2]:02X} no coincide con {len(t)} bytes", []
    suma = sum(t[2:-2]) & 0xFF
    if (t[-2], t[-1]) != (suma >> 4, suma & 0x0F):
        return False, f"checksum {t[-2]:02X} {t[-1]:02X}, esperado {suma >> 4:02X} {suma & 15:02X}", []
    nib = t[9:-2]
    if len(nib) % 2:
        return False, "cantidad impar de nibbles", []
    return True, "", [(nib[i] << 4) | nib[i + 1] for i in range(0, len(nib), 2)]


# ---------------------------------------------------------------- nombres

def cargar_monedas():
    """Toma los códigos de moneda de gpaCurrencyCode[] en IFDView.cpp (índice = código)."""
    try:
        src = open(os.path.join(AQUI, "..", "IFDView.cpp"), encoding="latin-1").read()
        bloque = src.split("gpaCurrencyCode[] = {", 1)[1].split("};", 1)[0]
        return re.findall(r'"([^"]*)"', bloque)
    except (OSError, IndexError):
        return []


MONEDAS = cargar_monedas()


def moneda(c):
    return f"{c} ({MONEDAS[c]})" if 0 < c < len(MONEDAS) else str(c)


SUBCMD = {
    0x30: "DEVICE_SET_LIVE", 0x31: "SETUP_STATE_DATA", 0x32: "COUNT_START",
    0x33: "CD_ERROR", 0x34: "RESULT_DATA", 0x35: "RESULT_REQUEST",
    0x36: "RESULT_CLEAR", 0x37: "START_STOP", 0x38: "DEVICE_SETUP2",
    0x39: "DEFAULT_LOADING", 0x3A: "CURRENCY_CHANGE", 0x3B: "SETUP_NO_ACCEPT",
    0x3D: "COUNT_STOP", 0x3E: "SENSOR_STATUS", 0x41: "SETUP_STATE_DATA2",
    0x43: "COUNTING_REPORT_DATA", 0x44: "SAVE_BMP_TO_USB", 0x45: "MC_STATUS",
    0x46: "SW_VERSION", 0x47: "OCR_RESULT", 0x48: "IFD_WING_MOTOR",
    0x49: "IFD_REJECT_DESIGNATED_NOTE", 0x4A: "SETUP_MAINTENANCE_ALARM",
    0x4C: "REQUEST_IFD_COUNT_LOG_DATA", 0x4D: "SEND_IFD_COUNT_LOG_DATA",
    0x4E: "SEND_IFD_REF_NUMBER", 0x4F: "RESULT_DATA2", 0x53: "SET_MACHINE_DATE_TIME",
    0x63: "SETUP_STATE_DATA_EX", 0xA8: "REBOOT",
}

MODOS2 = {0: "COUNT", 1: "MIXED", 2: "SINGLE", 3: "FACE", 4: "ORIENT", 5: "SERIAL No. PRINT",
          6: "ISSUE", 7: "DISPENSE", 8: "OCR", 9: "MIXED CURRENCY"}
VELOCIDAD = {0: "1000 rpm", 1: "1200 rpm", 2: "1500 rpm", 3: "600 rpm", 4: "800 rpm", 5: "900 rpm"}
# Billetes por índice de denominación, según código de moneda. Valores base (SB-9);
# cada modelo de ../maquinas.json puede reemplazar la lista de una moneda (ver usar_modelo).
# SB-9, ARS: confirmados con billetes reales (2026-09-29): 3 = $100, 7 = $2000, 8 = $10000.
BILLETES = {
    1: ["$1", "$2", "$5", "$10", "$20", "$50", "$100"],
    4: ["€5", "€10", "€20", "€50", "€100", "€200", "€500"],
    115: ["$10", "$20", "$50", "$100", "$200", "$500", "$1000", "$2000", "$10000", "$20000"],
}
BILLETES_BASE = {k: list(v) for k, v in BILLETES.items()}
MODELO_POR_DEFECTO = "sb9"


def cargar_maquinas():
    """Modelos de ../maquinas.json: velocidad y orden de billetes de cada máquina."""
    with open(os.path.join(AQUI, "..", "maquinas.json"), encoding="utf-8") as f:
        return json.load(f)


def usar_modelo(nombre):
    """Aplica el orden de billetes del modelo y devuelve su configuración."""
    modelo = cargar_maquinas()[nombre]
    BILLETES.clear()
    BILLETES.update({k: list(v) for k, v in BILLETES_BASE.items()})
    BILLETES.update({int(k): v for k, v in modelo.get("billetes", {}).items()})
    return modelo
moneda_actual = [None]  # se actualiza al recibir 31h / 41h
config_actual = [None]  # últimos 11 parámetros de 41h, base para cambiar la configuración
config_version = [0]    # aumenta con cada 41h recibido (para esperar una relectura)

# Nombres de la consola -> código de modo en SETUP_STATE_DATA2 (41h)
MODOS_CONSOLA = {"conteo": 0x00, "mixto": 0x01, "single": 0x02, "cara": 0x03, "orientacion": 0x04}


def trama_config(modificar):
    """Reenvía la última configuración leída (41h) aplicándole solo el cambio indicado.
    Parámetros: [0] moneda, [1] modo, [2] estado (bit0 = Batch), [3] mode lock,
    [4] motor, [5] denominación, [6] bandejas, [7] lote, [8..10] niveles UV/MR/IR."""
    p = list(config_actual[0])
    modificar(p)
    return armar_trama([0x41] + p)


def trama_cambiar_modo(modo):
    return trama_config(lambda p: p.__setitem__(1, modo))


def trama_batch(activar):
    return trama_config(lambda p: p.__setitem__(2, p[2] | 0x01 if activar else p[2] & ~0x01))


def trama_auto(activar):
    """Auto/Manual (41h, param 2 bit 3). En Manual la máquina ignora 'iniciar' desde la PC."""
    return trama_config(lambda p: p.__setitem__(2, p[2] | 0x08 if activar else p[2] & ~0x08))


SENSORES = {"uv": 0x20, "mr": 0x40, "ir": 0x80}  # bits del estado (param 2) en 41h


def trama_sensor(nombre, activar):
    bit = SENSORES[nombre]
    return trama_config(lambda p: p.__setitem__(2, p[2] | bit if activar else p[2] & ~bit))


def trama_lote(n):
    return trama_config(lambda p: p.__setitem__(7, n))


def trama_denom(indice):
    """Denominación fija (0..) o 0x1F = DD (toma la del primer billete). Solo SINGLE/FACE/ORIENT."""
    return trama_config(lambda p: p.__setitem__(5, (p[5] & 0xE0) | (indice & 0x1F)))


def indice_denom(texto):
    """'dd', un valor de billete ('100', '$100') o 'i3' (índice directo). None si no existe."""
    t = texto.lower().lstrip("$")
    if t == "dd":
        return 0x1F
    if t.startswith("i") and t[1:].isdigit():
        return int(t[1:])
    for i, nombre in enumerate(BILLETES.get(moneda_actual[0], [])):
        if re.sub(r"\D", "", nombre) == t:
            return i
    return None


def trama_bandejas(rechazo, salida):
    """EXPERIMENTAL: código de capacidad de bandejas (41h, param 6: rechazo bits 7-4,
    salida bits 3-0). En la SB-9 no se sabe si tiene efecto; verificar en la pantalla."""
    return trama_config(lambda p: p.__setitem__(6, (rechazo & 0x0F) << 4 | (salida & 0x0F)))


def trama_divisa(codigo):
    return trama_config(lambda p: p.__setitem__(0, codigo))


def codigo_divisa(texto):
    """'usd', 'ars', ... o el número de código. None si no existe."""
    if texto.isdigit():
        return int(texto) if 0 < int(texto) < 256 else None
    t = texto.upper()
    return MONEDAS.index(t) if t in MONEDAS[1:] else None


def billete(i):
    lista = BILLETES.get(moneda_actual[0], [])
    return lista[i] if i < len(lista) else f"[{i}]"


def valor_billete(i):
    digitos = re.sub(r"\D", "", billete(i))
    return int(digitos) if digitos and not billete(i).startswith("[") else 0


# Capacidad de bandejas por código, confirmada en la SB-9 (2026-10-21) cambiando cada
# valor en el teclado y leyendo 41h. La máquina informa en el formato antiguo de 3
# códigos, así que agrupa los valores que no existían en él.
RECHAZO = {0: "30", 1: "50, 70 o 100"}
APILADOR = {0: "200, 250 o 300", 1: "150", 2: "100"}


def capacidad(tabla, codigo):
    return f"{tabla[codigo]} billetes" if codigo in tabla else f"código {codigo}"
ERRORES_SENSOR = {0: "sin error", 1: "JAM1", 2: "JAM2", 3: "JAM3", 4: "JAM4", 5: "alimentación",
                  6: "tapa frontal abierta", 7: "tapa trasera abierta", 9: "motor principal"}


def bits(valor, nombres):
    activos = [n for i, n in enumerate(nombres) if n and valor >> i & 1]
    return ", ".join(activos) if activos else "ninguno"


def denominacion(d):
    if d == 0x1F:
        return "DD (toma la del primer billete)"
    if d == 0x1E:
        return "ALL"
    return f"{billete(d)} (índice {d})"


def decodificar(d):
    """d = datos (bytes reales). Devuelve una lista de líneas."""
    sc, p = d[0], d[1:]
    L = []
    if sc == 0x30 and p:
        L.append(bits(p[0], ["KNOCK", "ACK", "RELEASE"]))
    elif sc == 0x31 and len(p) >= 6:
        moneda_actual[0] = p[2]
        L += [f"motor: {VELOCIDAD.get(p[0] >> 4, p[0])}",
              "estado: " + bits(p[1], ["Batch", None, "beep aviso", "Auto", "ADD", "UV", "MR", "Mode Lock"]),
              f"moneda: {moneda(p[2])}",
              f"modo: {MODOS2.get(p[3] & 7, p[3] & 7)}, denominación: {denominacion(p[3] >> 3)}",
              f"bandejas: rechazo {capacidad(RECHAZO, p[4] >> 6)}, salida {capacidad(APILADOR, p[4] >> 4 & 3)}",
              f"lote: {p[5]}"]
    elif sc == 0x41 and len(p) >= 11:
        moneda_actual[0] = p[0]
        config_actual[0] = list(p[:11])
        config_version[0] += 1
        L += [f"moneda: {moneda(p[0])}",
              f"modo: {MODOS2.get(p[1], p[1])}",
              "estado: " + bits(p[2], ["Batch", None, "beep aviso", "Auto", "ADD", "UV", "MR", "IR"]),
              f"mode lock: {'On' if p[3] & 1 else 'Off'}",
              f"motor: {VELOCIDAD.get(p[4] >> 4, p[4])}",
              f"denominación: {denominacion(p[5] & 0x1F)}",
              f"bandejas: rechazo {capacidad(RECHAZO, p[6] >> 4)}, salida {capacidad(APILADOR, p[6] & 0x0F)}",
              f"lote: {p[7]}",
              f"niveles UV/MR/IR: {p[8]}/{p[9]}/{p[10]}"]
        if len(p) > 11:
            L.append("bytes extra (no documentados): " + " ".join(f"{b:02X}" for b in p[11:]))
    elif sc == 0x32 and p:
        L.append(bits(p[0], ["inicio de conteo", "depósito nuevo"]))
    elif sc == 0x33 and p:
        L.append("error: " + bits(p[0], ["JAM", "alimentación", "motor principal", "limpiar tolva"]))
    elif sc in (0x34, 0x4F):
        if sc == 0x4F:
            moneda_actual[0] = p[0]
            L.append(f"moneda: {moneda(p[0])}")
            p = p[1:]
        if len(p) >= 2 and (len(p) - 2) % 3 == 0:
            n = (len(p) - 2) // 3
            actual = p[2:2 + n]
            prev = [p[2 + n + 2 * i] << 8 | p[3 + n + 2 * i] for i in range(n)]
            L.append(f"rechazados: {p[0]}   en bandeja de salida: {p[1]}")
            L.append("actual   : " + ("  ".join(f"{billete(i)} x{c}" for i, c in enumerate(actual) if c) or "todo 0"))
            L.append("anterior : " + ("  ".join(f"{billete(i)} x{c}" for i, c in enumerate(prev) if c) or "todo 0"))
            total = sum(c * valor_billete(i) for i, c in enumerate(actual))
            if total:
                L.append(f"monto actual: ${total:,}".replace(",", "."))
        else:
            L.append("formato inesperado: " + " ".join(f"{b:02X}" for b in p))
    elif sc == 0x38 and p:
        L.append(bits(p[0], ["1BYTE_COUNT_DATA activo", "teclado bloqueado"]) )
    elif sc == 0x35 and p:
        L.append("pedido: " + PEDIDOS_NOMBRE.get(p[0], f"{p[0]:02X}h"))
    elif sc == 0x3E and len(p) >= 5:
        L += ["sensores 1: " + bits(p[0], [None, "solenoide->salida", "RP1 izq", "RP1 der", None, None, "JP izq", "JP der"]),
              "sensores 2: " + bits(p[1], ["SP izq", "SP der", "salida vacía", "rechazo F vacío",
                                           "tapa frontal ABIERTA", "tapa trasera ABIERTA", "rechazo R vacío", "billetes en tolva"]),
              f"billetes en salida: {p[2]}   en rechazo: {p[3]}",
              f"error: {ERRORES_SENSOR.get(p[4], p[4])}"]
    elif sc == 0x43 and len(p) >= 5:
        L.append(f"total en salida: {p[0] << 8 | p[1]}   total rechazados: {p[3] << 8 | p[4]}")
    elif sc == 0x45 and p:
        L.append(bits(p[0], ["limpiar tolva", "revisar salida", "revisar rechazo"]))
    elif sc == 0x46 and len(p) >= 2:
        L.append(f"versión de software: {p[0]:02d}.{p[1]:02d}")
        if len(p) >= 4:
            L.append(f"checksum del firmware: {p[2]:02x}{p[3]:02x}")
    elif sc == 0x47:
        L.append("OCR: " + "".join(chr(b) for b in p if 32 <= b < 127))
    elif sc == 0x3B:
        L.append("la máquina rechazó la configuración (menú abierto)")
    elif sc == 0x3D:
        L.append("fin de conteo")
    else:
        L.append("parámetros: " + (" ".join(f"{b:02X}" for b in p) or "(ninguno)"))
    return L


BYTE_CONTEO = {0x20: "SOSPECHOSO (a rechazo)", 0x40: "FIN de datos de conteo",
               0x70: "FALSO (CF)", 0x71: "STAY NOTE"}

# ---------------------------------------------------------------- consola

class Consola:
    def __init__(self, puerto, baudios):
        if puerto.startswith("socket://"):
            self.ser = serial.serial_for_url(puerto, timeout=0.05)
        else:
            self.ser = serial.Serial(puerto, baudios, bytesize=8, parity="N", stopbits=1, timeout=0.05)
        os.makedirs(os.path.join(AQUI, "logs"), exist_ok=True)
        self.log = open(os.path.join(AQUI, "logs", f"probar_{datetime.now():%Y%m%d_%H%M%S}.log"),
                        "a", encoding="utf-8")
        self.lock = threading.Lock()
        self.ultimo_envio = 0.0
        self.parar = threading.Event()
        threading.Thread(target=self.leer, daemon=True).start()

    def mostrar(self, texto):
        hora = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        with self.lock:
            for i, linea in enumerate(texto.splitlines()):
                s = f"{hora} {linea}" if i == 0 else f"{' ' * 13}{linea}"
                print(s, flush=True)
                self.log.write(s + "\n")
            self.log.flush()

    def enviar(self, trama):
        espera = PAUSA_MIN - (time.time() - self.ultimo_envio)
        if espera > 0:
            time.sleep(espera)
        self.ser.write(trama)
        self.ultimo_envio = time.time()
        _, _, d = verificar_trama(trama)
        nombre = SUBCMD.get(d[0], f"{d[0]:02X}h") if d else "?"
        self.mostrar(f"PC  -> MAQ  {nombre}\n  {trama.hex(' ').upper()}")

    def leer(self):
        buf = bytearray()
        ultimo = time.time()
        while not self.parar.is_set():
            try:
                trozo = self.ser.read(self.ser.in_waiting or 1)
            except serial.SerialException as e:
                self.mostrar(f"ERROR de puerto: {e}")
                return
            if trozo:
                buf += trozo
                ultimo = time.time()
            # procesar lo acumulado
            while buf:
                if buf[0] == 0xF0 and (len(buf) < 2 or buf[1] == 0xF1):
                    if len(buf) < 3 or len(buf) < buf[2] + 4:
                        if time.time() - ultimo > 0.5:   # trama cortada
                            self.mostrar(f"MAQ -> PC  trama incompleta\n  {bytes(buf).hex(' ').upper()}")
                            buf.clear()
                        break
                    total = buf[2] + 4
                    t = bytes(buf[:total])
                    del buf[:total]
                    ok, motivo, d = verificar_trama(t)
                    if not ok:
                        self.mostrar(f"MAQ -> PC  TRAMA INVÁLIDA: {motivo}\n  {t.hex(' ').upper()}")
                        continue
                    nombre = SUBCMD.get(d[0], f"{d[0]:02X}h desconocido")
                    detalle = "\n".join("  " + l for l in decodificar(d))
                    self.mostrar(f"MAQ -> PC  {d[0]:02X}h {nombre}\n  {t.hex(' ').upper()}\n{detalle}")
                    # igual que IFD.exe: tras el ACK pide la configuración (así se conoce la moneda)
                    if d[0] == 0x30 and len(d) > 1 and d[1] & 0x02:
                        self.enviar(armar_trama([0x35, 0x12]))
                    # si la máquina hace KNOCK (se encendió después), responder ACK
                    elif d[0] == 0x30 and len(d) > 1 and d[1] & 0x01:
                        self.enviar(armar_trama([0x30, 0x02]))
                else:
                    b = buf.pop(0)
                    self.mostrar(f"MAQ -> PC  1BYTE_COUNT_DATA {b:02X}: {BYTE_CONTEO.get(b, f'denominación índice {b}')}")

    def cerrar(self):
        self.parar.set()
        time.sleep(0.1)
        self.ser.close()
        self.log.close()


def byte(s):
    return int(s, 16) & 0xFF


LIMPIEZAS = {"rechazo": 0x01, "salida": 0x02, "total": 0x04, "mixto": 0x08,
             "simple": 0x10, "jam": 0x20, "reporte": 0x80}
PEDIDOS = {"estado": 0x01, "resultado": 0x02, "error": 0x04, "reenviar": 0x08,
           "sensores": 0x10, "disp2": 0x20, "reporte": 0x80, "estado2": 0x12,
           "version": 0x21}  # 0x21 no está en el protocolo; capturado de IFD.exe
PEDIDOS_NOMBRE = {v: k for k, v in PEDIDOS.items()}
PELIGROSOS = {"default": ([0x39, 0x01], "vuelve la máquina a la configuración de fábrica"),
              "moneda": ([0x3A, 0x01], "cambia la moneda de la máquina"),
              "reboot": ([0xA8, 0x01], "reinicia la máquina")}

AYUDA = """
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
"""


def interpretar(linea):
    """Convierte un comando de la consola en una lista de datos (o bytes crudos)."""
    p = linea.split()
    c = p[0].lower()
    if c in ("knock", "ack", "release"):
        return [0x30, {"knock": 1, "ack": 2, "release": 4}[c]]
    if c == "pedir" and len(p) == 2 and p[1] in PEDIDOS:
        return [0x35, PEDIDOS[p[1]]]
    if c == "iniciar":
        return [0x37, 0x01]
    if c == "cancelar":
        return [0x37, 0x02]
    if c == "limpiar" and len(p) == 2 and p[1] in LIMPIEZAS:
        return [0x36, LIMPIEZAS[p[1]]]
    if c == "setup2" and len(p) == 3:
        return [0x38, int(p[1]) & 1 | (int(p[2]) & 1) << 1]
    if c in ("usb", "aletas") and len(p) == 2 and p[1] in ("on", "off"):
        return [0x44 if c == "usb" else 0x48, 1 if p[1] == "on" else 0]
    if c == "datos" and len(p) >= 2:
        return [byte(x) for x in p[1:]]
    if c == "crudo" and len(p) >= 2:
        return bytes(byte(x) for x in p[1:])
    return None


def releer_config(con, espera=1.5):
    """Pide 41h y espera la respuesta. Devuelve True si llegó."""
    version = config_version[0]
    con.enviar(armar_trama([0x35, 0x12]))
    limite = time.time() + espera
    while config_version[0] == version and time.time() < limite:
        time.sleep(0.05)
    return config_version[0] != version


def comando_perfil(con, p):
    """perfiles · perfil <n> [lote] · perfil verificar <n> [lote]"""
    try:
        lista = perfiles.cargar()
    except (OSError, ValueError, KeyError) as e:
        print(f"No se pudo leer {perfiles.RUTA}: {e}")
        return
    if p[0] == "perfiles":
        for n, perfil in lista.items():
            print("  " + perfiles.describir(n, perfil))
        return
    solo_verificar = len(p) > 1 and p[1] == "verificar"
    resto = p[2:] if solo_verificar else p[1:]
    if not resto or resto[0] not in lista or len(resto) > 2 or (len(resto) == 2 and not resto[1].isdigit()):
        print("Uso: perfil <n> [lote] · perfil verificar <n> [lote] · perfiles")
        return
    n, perfil = resto[0], lista[resto[0]]
    lote = int(resto[1]) if len(resto) == 2 else None
    if lote is not None and not 1 <= lote <= 200:
        print("El lote va de 1 a 200.")
        return
    if config_actual[0] is None:
        print("Primero lee la configuración: 'knock' o 'pedir estado2'.")
        return
    if not solo_verificar:
        nuevo = perfiles.aplicar(config_actual[0], perfil, codigo_divisa, lote)
        if nuevo == config_actual[0]:
            print(f"La máquina ya tiene el perfil {n}; no se envía nada.")
        else:
            con.enviar(armar_trama([0x41] + nuevo))
            time.sleep(0.3)
    if not releer_config(con):
        print("La máquina no respondió a la relectura de la configuración.")
        return
    filas = perfiles.verificar(config_actual[0], perfil, codigo_divisa, lote)
    lineas = [f"Perfil {n} · {perfil.get('nombre', '')}"]
    for estado, campo, esperado, actual in filas:
        nota = "  -> ajustar desde el teclado" if estado == "!!" else ""
        lineas.append(f"  [{estado}] {campo:<16} esperado: {esperado}   máquina: {actual}{nota}")
    fallas = sum(1 for f in filas if f[0] != "OK")
    lineas.append("  Todo coincide." if not fallas else f"  {fallas} campo(s) no coinciden.")
    con.mostrar("\n".join(lineas))


def consola(args):
    destino = f"socket://{args.ip}:{args.puerto_tcp}" if args.ip else args.puerto
    try:
        con = Consola(destino, args.baudios)
    except serial.SerialException as e:
        print(f"No se pudo abrir {destino}: {e}")
        print("¿Está IFD.exe u otro programa conectado a la máquina?")
        sys.exit(1)
    serie = "" if args.ip else f" a {args.baudios} baudios"
    print(f"Conectado a {destino}{serie} (modelo {args.nombre_modelo}). Escribe 'ayuda'. Empieza con 'knock'.")
    try:
        while True:
            try:
                linea = input().lstrip("﻿").strip()  # algunas terminales envían un BOM
            except EOFError:
                break
            if not linea:
                continue
            c = linea.split()[0].lower()
            if c in ("salir", "exit", "quit"):
                break
            if c == "ayuda":
                print(AYUDA)
                continue
            if c in ("perfil", "perfiles"):
                comando_perfil(con, linea.lower().split())
                continue
            if c in ("modo", "auto", "batch", "lote", "divisa", "denom", "bandejas", "sensor"):
                p = linea.lower().split()
                trama = None
                if c == "modo" and len(p) == 2 and p[1] in MODOS_CONSOLA:
                    trama = lambda: trama_cambiar_modo(MODOS_CONSOLA[p[1]])
                elif c == "auto" and len(p) == 2 and p[1] in ("on", "off"):
                    trama = lambda: trama_auto(p[1] == "on")
                    if p[1] == "off":
                        print("Aviso: en Manual la máquina ignora 'iniciar'; solo cuenta con START en su teclado.")
                elif c == "batch" and len(p) == 2 and p[1] in ("on", "off"):
                    trama = lambda: trama_batch(p[1] == "on")
                elif c == "lote" and len(p) == 2 and p[1].isdigit() and 1 <= int(p[1]) <= 200:
                    trama = lambda: trama_lote(int(p[1]))
                elif c == "divisa" and len(p) == 2 and codigo_divisa(p[1]) is not None:
                    trama = lambda: trama_divisa(codigo_divisa(p[1]))
                elif c == "denom" and len(p) == 2 and indice_denom(p[1]) is not None:
                    trama = lambda: trama_denom(indice_denom(p[1]))
                    if config_actual[0] and config_actual[0][1] not in (2, 3, 4):
                        print("Aviso: la denominación fija solo aplica en modo single/cara/orientacion.")
                elif (c == "bandejas" and len(p) == 3 and p[1].isdigit() and p[2].isdigit()
                      and int(p[1]) < 16 and int(p[2]) < 16):
                    trama = lambda: trama_bandejas(int(p[1]), int(p[2]))
                    print("EXPERIMENTAL: revisa en la pantalla de la máquina si cambiaron las bandejas.")
                elif c == "sensor" and len(p) == 3 and p[1] in SENSORES and p[2] in ("on", "off"):
                    trama = lambda: trama_sensor(p[1], p[2] == "on")
                    if p[2] == "off":
                        print(f"Aviso: sin el sensor {p[1].upper()} la máquina detecta menos billetes falsos.")
                if trama is None:
                    print("Uso: modo mixto|single|conteo|cara|orientacion  ·  auto on|off  ·  batch on|off  ·  "
                          "lote 1-200  ·  sensor uv|mr|ir on|off  ·  divisa usd|ars|<código>  ·  "
                          "denom <billete>|dd  ·  bandejas <0-15> <0-15>")
                elif config_actual[0] is None:
                    print("Primero lee la configuración: 'knock' o 'pedir estado2'.")
                else:
                    con.enviar(trama())
                    time.sleep(0.3)
                    con.enviar(armar_trama([0x35, 0x12]))  # releer para verificar
                continue
            if c in PELIGROSOS:
                datos, aviso = PELIGROSOS[c]
                if input(f"Esto {aviso}. ¿Seguro? (si/no): ").strip().lower() != "si":
                    print("Cancelado.")
                    continue
                con.enviar(armar_trama(datos))
                continue
            try:
                r = interpretar(linea)
            except ValueError:
                r = None
            if r is None:
                print("Comando no reconocido. Escribe 'ayuda'.")
            elif isinstance(r, bytes):
                con.enviar(r)
            else:
                con.enviar(armar_trama(r))
    except KeyboardInterrupt:
        pass
    finally:
        con.cerrar()
        print("Puerto cerrado.", flush=True)
        # Salida inmediata: el hilo lector puede quedar esperando en el socket y
        # trabar el cierre del intérprete (el log ya se cerró en con.cerrar()).
        os._exit(0)


# ---------------------------------------------------------------- autoprueba

def autoprueba():
    """Compara con ejemplos del protocolo y con tramas capturadas de la máquina real."""
    casos = [
        ([0x30, 0x01], "F0 F1 0B 19 02 00 00 00 00 03 00 00 01 02 0A"),   # KNOCK (doc)
        ([0x35, 0x02], "F0 F1 0B 19 02 00 00 00 00 03 05 00 02 03 00"),   # resultado (doc)
        ([0x37, 0x01], "F0 F1 0B 19 02 00 00 00 00 03 07 00 01 03 01"),   # start (doc)
        ([0x36, 0x80], "F0 F1 0B 19 02 00 00 00 00 03 06 08 00 03 07"),   # clear reporte (doc)
        ([0x35, 0x12], "F0 F1 0B 19 02 00 00 00 00 03 05 01 02 03 01"),   # capturado de IFD.exe
    ]
    ok = True
    for datos, esperado in casos:
        t = armar_trama(datos).hex(" ").upper()
        bien = t == esperado
        ok &= bien
        print(f"{'OK ' if bien else 'MAL'} {SUBCMD[datos[0]]:<16} {t}")
    respuesta = bytes.fromhex("f0f1251902000000000401070300010e0800000000010f01000109000300030003000000000000080a")
    v, motivo, d = verificar_trama(respuesta)
    print("\nRespuesta real capturada (41h):", "checksum OK" if v else motivo)
    for linea in decodificar(d):
        print("  " + linea)
    resultado_ars = bytes.fromhex(  # capturado de la máquina real, 2 billetes de $100
        "F0 F1 49 19 02 00 00 00 00 03 04 00 00 00 02 00 00 00 00 00 00 00 02 00 00 00 00 00 00 00 00 00 "
        "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 02 00 00 00 00 00 00 00 00 00 00 00 00 00 "
        "00 00 00 00 00 00 00 00 00 00 00 07 01")
    v3, motivo3, d3 = verificar_trama(resultado_ars)
    print("\nResultado real ARS (2 billetes de $100):", "checksum OK" if v3 else motivo3)
    for linea in decodificar(d3):
        print("  " + linea)
    v = v and v3
    t = trama_cambiar_modo(MODOS_CONSOLA["single"])
    v4, motivo4, d4 = verificar_trama(t)
    print("\nTrama para cambiar a SINGLE (desde la config real):", "OK" if v4 else motivo4)
    print("  " + t.hex(" ").upper())
    print("  " + "; ".join(decodificar(d4)[:3]))
    v = v and v4 and d4[2] == 0x02
    _, _, d5 = verificar_trama(trama_batch(True))
    _, _, d6 = verificar_trama(trama_lote(100))
    print("\nbatch on ->", "; ".join(l for l in decodificar(d5) if l.startswith("estado")))
    print("lote 100 ->", "; ".join(l for l in decodificar(d6) if l.startswith("lote")))
    v = v and d5[3] & 1 == 1 and d6[8] == 100
    _, _, d7 = verificar_trama(trama_divisa(codigo_divisa("usd")))
    print("divisa usd ->", "; ".join(l for l in decodificar(d7) if l.startswith("moneda")),
          "| divisa ars ->", codigo_divisa("ars"))
    v = v and d7[1] == 1 and codigo_divisa("ars") == 115
    decodificar(d)  # volver a la configuración real (ARS) como base
    _, _, d8 = verificar_trama(trama_denom(indice_denom("100")))
    print("denom 100 ->", "; ".join(l for l in decodificar(d8) if l.startswith("denominación")))
    v = v and d8[6] & 0x1F == 3 and indice_denom("dd") == 0x1F
    _, _, d9 = verificar_trama(trama_bandejas(3, 4))
    print("bandejas 3 4 ->", "; ".join(l for l in decodificar(d9) if l.startswith("bandejas")))
    v = v and d9[7] == 0x34
    decodificar(d)
    _, _, d10 = verificar_trama(trama_sensor("uv", False))
    print("sensor uv off ->", "; ".join(l for l in decodificar(d10) if l.startswith("estado")))
    v = v and d10[3] == 0xE8 & ~0x20
    decodificar(d)
    _, _, d11 = verificar_trama(trama_auto(False))
    print("auto off ->", "; ".join(l for l in decodificar(d11) if l.startswith("estado")))
    v = v and d11[3] == 0xE8 & ~0x08
    decodificar(d)  # volver a la configuración real
    decodificar(d)  # configuración real como base
    print("\nPerfiles aplicados sobre la configuración real:")
    for n, perfil in perfiles.cargar().items():
        nuevo = perfiles.aplicar(config_actual[0], perfil, codigo_divisa)
        # las bandejas se escriben con un código y se leen con otro: se revisan aparte
        filas = [f for f in perfiles.verificar(nuevo, perfil, codigo_divisa) if not f[1].startswith("bandeja")]
        bien = (all(f[0] == "OK" for f in filas) and nuevo[6] == 0x00
                and verificar_trama(armar_trama([0x41] + nuevo))[0])
        v = v and bien
        print(f"  {'OK ' if bien else 'MAL'} {perfiles.describir(n, perfil)}  ->  {armar_trama([0x41] + nuevo).hex(' ').upper()}")
    ejemplo_34 = bytes.fromhex("F0F137190200000000030400000003000000000001000000020000000000000002"
                               "00000000000000010000000100000001000000020000000106 07".replace(" ", ""))
    moneda_actual[0] = 1  # el ejemplo del protocolo es en US$
    v2, motivo2, d2 = verificar_trama(ejemplo_34)
    print("\nEjemplo RESULT_DATA del protocolo (US$):", "checksum OK" if v2 else motivo2)
    for linea in decodificar(d2):
        print("  " + linea)
    print("\nModelos de ../maquinas.json (moneda ARS, índices 3 y 6):")
    for nombre, esperado in (("mib9", ("$1000", "$100")), ("sb9", ("$100", "$1000"))):
        m = usar_modelo(nombre)
        moneda_actual[0] = 115
        bien = (billete(3), billete(6)) == esperado
        v = v and bien
        print(f"  {'OK ' if bien else 'MAL'} {nombre}: {m['nombre']}, {m['baudios']} baudios, "
              f"índice 3 = {billete(3)}, índice 6 = {billete(6)}")
    print("\nAutoprueba", "APROBADA" if ok and v and v2 else "FALLIDA")


def main():
    ap = argparse.ArgumentParser(description="Probar el protocolo de la contadora por puerto serie.")
    ap.add_argument("--modelo", default=MODELO_POR_DEFECTO,
                    help="máquina de ../maquinas.json (sb9, mib9): velocidad y orden de billetes")
    ap.add_argument("--puerto", default="COM5")
    ap.add_argument("--baudios", type=int, help="por defecto, la del modelo")
    ap.add_argument("--ip", help="conectar por red a esta IP en vez de por puerto serie")
    ap.add_argument("--puerto-tcp", type=int, default=4101)
    ap.add_argument("--prueba", action="store_true", help="autoprueba sin máquina")
    args = ap.parse_args()
    if args.prueba:
        autoprueba()
        return
    try:
        modelo = usar_modelo(args.modelo)
    except (OSError, ValueError, KeyError):
        print(f"Modelo desconocido: {args.modelo}. Ver ../maquinas.json")
        sys.exit(1)
    args.baudios = args.baudios or modelo.get("baudios", 115200)
    args.nombre_modelo = modelo.get("nombre", args.modelo)
    consola(args)


if __name__ == "__main__":
    main()
