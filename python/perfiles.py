"""
Perfiles de configuración de la contadora (../perfiles.json, compartido con node/).

Un perfil indica cómo debe quedar la configuración 41h. Lo que no indica queda como
está en la máquina. "comun" se aplica a todos los perfiles y cada uno puede pisarlo.

Bandejas: la SB-9 usa códigos distintos para ESCRIBIR y para LEER (confirmado
2026-10-21 con la pantalla). Se escriben solo los valores con código de escritura
conocido (rechazo 100 y salida 300 = código 0); el resto solo se verifica. Al leer,
la máquina informa en grupos (salida 200/250/300 = mismo código).
"""

import json
import os

RUTA = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "perfiles.json")

MODOS = {"conteo": 0, "mixto": 1, "single": 2, "cara": 3, "orientacion": 4}
NOMBRE_MODO = {v: k for k, v in MODOS.items()}
BITS = {"batch": 0x01, "beep": 0x04, "auto": 0x08, "add": 0x10}   # param 2 de 41h
SENSORES = {"uv": 0x20, "mr": 0x40, "ir": 0x80}                     # param 2 de 41h
NIVELES = {"uv": 8, "mr": 9, "ir": 10}                              # índice en 41h
# Capacidad -> código para ESCRIBIR en la SB-9 (confirmado: "bandejas 0 0" deja 100 / 300)
ESCRIBIR_RECHAZO = {100: 0}
ESCRIBIR_SALIDA = {300: 0}
# Capacidad -> código que INFORMA la SB-9 al leer (confirmado 2026-10-21)
COD_RECHAZO = {30: 0, 50: 1, 70: 1, 100: 1}
COD_SALIDA = {100: 2, 150: 1, 200: 0, 250: 0, 300: 0}
GRUPO_RECHAZO = {0: "30", 1: "50/70/100"}
GRUPO_SALIDA = {0: "200/250/300", 1: "150", 2: "100"}
LOTE_POR_DEFECTO = 100


def cargar():
    """Devuelve {número: perfil} con lo común ya combinado."""
    with open(RUTA, encoding="utf-8") as f:
        datos = json.load(f)
    comun = datos.get("comun", {})
    return {k: {**comun, **v} for k, v in datos["perfiles"].items()}


def lote_de(perfil, lote=None):
    return lote or perfil.get("lote", LOTE_POR_DEFECTO)


def aplicar(p, perfil, codigo_divisa, lote=None):
    """Devuelve los 11 parámetros de 41h con el perfil aplicado."""
    p = list(p)
    if "divisa" in perfil:
        p[0] = codigo_divisa(perfil["divisa"])
    if "modo" in perfil:
        p[1] = MODOS[perfil["modo"]]
    for clave, bit in BITS.items():
        if clave in perfil:
            p[2] = p[2] | bit if perfil[clave] else p[2] & ~bit
    for s, bit in SENSORES.items():
        if s in perfil.get("sensores", {}):
            p[2] = p[2] | bit if perfil["sensores"][s] else p[2] & ~bit
    if perfil.get("denom") == "dd":
        p[5] = (p[5] & 0xE0) | 0x1F
    if perfil.get("batch"):
        p[7] = lote_de(perfil, lote)
    for s, i in NIVELES.items():
        if s in perfil.get("niveles", {}):
            p[i] = perfil["niveles"][s]
    b = perfil.get("bandejas", {})
    if b.get("rechazo") in ESCRIBIR_RECHAZO:
        p[6] = (ESCRIBIR_RECHAZO[b["rechazo"]] << 4) | (p[6] & 0x0F)
    if b.get("salida") in ESCRIBIR_SALIDA:
        p[6] = (p[6] & 0xF0) | ESCRIBIR_SALIDA[b["salida"]]
    return [b & 0xFF for b in p]


def verificar(p, perfil, codigo_divisa, lote=None):
    """Compara la configuración leída (p) con el perfil.
    Devuelve [(estado, campo, esperado, en_maquina)]; estado = 'OK', 'NO' o '!!' (bandejas)."""
    filas = []

    def fila(campo, esperado, actual):
        filas.append(("OK" if esperado == actual else "NO", campo, esperado, actual))

    on = lambda v: "on" if v else "off"
    if "divisa" in perfil:
        fila("divisa", codigo_divisa(perfil["divisa"]), p[0])
    if "modo" in perfil:
        fila("modo", perfil["modo"], NOMBRE_MODO.get(p[1], str(p[1])))
    for clave, bit in BITS.items():
        if clave in perfil:
            fila(clave, on(perfil[clave]), on(p[2] & bit))
    for s, bit in SENSORES.items():
        if s in perfil.get("sensores", {}):
            fila(f"sensor {s}", on(perfil["sensores"][s]), on(p[2] & bit))
    if perfil.get("batch"):
        fila("lote", lote_de(perfil, lote), p[7])
    if perfil.get("denom") == "dd":
        fila("denominación", "dd", "dd" if p[5] & 0x1F == 0x1F else f"índice {p[5] & 0x1F}")
    for s, i in NIVELES.items():
        if s in perfil.get("niveles", {}):
            fila(f"nivel {s}", perfil["niveles"][s], p[i])
    b = perfil.get("bandejas", {})
    if "rechazo" in b:
        cod = p[6] >> 4
        ok = COD_RECHAZO.get(b["rechazo"]) == cod
        filas.append(("OK" if ok else "!!", "bandeja rechazo", b["rechazo"], GRUPO_RECHAZO.get(cod, f"código {cod}")))
    if "salida" in b:
        cod = p[6] & 0x0F
        ok = COD_SALIDA.get(b["salida"]) == cod
        filas.append(("OK" if ok else "!!", "bandeja salida", b["salida"], GRUPO_SALIDA.get(cod, f"código {cod}")))
    return filas


def describir(n, perfil):
    partes = [perfil.get("modo", "")]
    if perfil.get("denom") == "dd":
        partes.append("denominación DD")
    partes.append(f"lote {lote_de(perfil)}" if perfil.get("batch") else "sin límite")
    return f"{n}  {perfil.get('nombre', '')}  ({', '.join(p for p in partes if p)})"
