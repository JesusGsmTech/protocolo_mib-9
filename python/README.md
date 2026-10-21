# Python — contadora SB-7 / SB-9

Consola de pruebas, escucha de tráfico y perfiles en Python. Equivalente a la versión de
[`../node`](../node/README.md). La referencia de comandos y el resumen del protocolo están en
el [README principal](../README.md).

## Instalación

Python 3 y `pyserial`:
```
pip install -r requirements.txt
```

## Archivos

| Archivo | Qué es |
|---|---|
| `probar_com.py` | Consola interactiva. Contiene también todo el protocolo: armar/verificar tramas, decodificar, cambios de configuración y autoprueba |
| `perfiles.py` | Aplica y verifica los perfiles de `../perfiles.json` |
| `escuchar_puerto.py` | Escucha el tráfico entre IFD.exe y la máquina (monitor / puente / proxy TCP) |
| `capturas/` | Capturas de Wireshark de la máquina real, usadas como referencia y en la autoprueba |
| `logs/` | Registro de cada sesión (no se sube a git) |

## probar_com.py: probar la máquina

```
python probar_com.py --ip 192.168.123.231     # por red (puerto 4101)
python probar_com.py                          # por puerto serie COM5, 115200
python probar_com.py --puerto COM3            # otro puerto serie
python probar_com.py --modelo mib9            # MIB-9: 57600 y su orden de billetes (../maquinas.json)
python probar_com.py --prueba                 # autoprueba sin máquina
```
Cierra o desconecta `IFD.exe` antes: la máquina acepta una sola conexión.

Sesión típica:
```
knock                 -> ACK + configuración actual
perfil 1              -> mixto sin límite, verificado campo por campo
iniciar               -> COUNT_START, un dato por billete, COUNT_STOP, resultado con monto
pedir sensores        -> tapas, tolva, bandejas, errores
salir
```
Cada sesión queda en `logs/probar_AAAAMMDD_HHMMSS.log`, con cada trama en hexadecimal y su traducción.

## escuchar_puerto.py: ver qué envía IFD.exe

Útil para descubrir comandos que el documento no describe.

```
python escuchar_puerto.py tcp --maquina 192.168.123.231      # proxy TCP, sin drivers (recomendado)
python escuchar_puerto.py monitor --puerto COM5              # solo lo que envía la máquina
python escuchar_puerto.py puente --real COM5 --virtual COM20 # serie, requiere com0com
```
- **tcp**: en `bin/IFDCTRL.INI` poner `[SOCKET] ADDRESS=127.0.0.1` y conectar IFD.exe por TCP.
  Al terminar, volver a poner la IP real.
- **puente**: crear con com0com un par de puertos virtuales (ej. COM20 ↔ COM21) y en
  `bin/IFDCTRL.INI` poner `PORT ID=21`. Al terminar, volver a `PORT ID=5`.

## Usar el protocolo desde otra aplicación

Las funciones del protocolo se pueden importar desde `probar_com.py` (la consola solo se
ejecuta con `python probar_com.py`, no al importar):

```python
import socket
from probar_com import armar_trama, verificar_trama, decodificar

s = socket.create_connection(("192.168.123.231", 4101))
s.sendall(armar_trama([0x30, 0x01]))            # KNOCK
ok, motivo, datos = verificar_trama(s.recv(64))  # ACK
print(decodificar(datos))                        # ['ACK']
s.sendall(armar_trama([0x35, 0x12]))            # pedir configuración
ok, motivo, datos = verificar_trama(s.recv(64))
print(decodificar(datos))                        # moneda, modo, estado, lote...
```

Funciones principales:

| Función | Qué hace |
|---|---|
| `armar_trama(datos)` | `[comando, parámetros…]` → bytes listos para enviar |
| `verificar_trama(bytes)` | Valida inicio, largo y checksum → `(ok, motivo, datos)` |
| `decodificar(datos)` | Traduce una respuesta a líneas de texto |
| `usar_modelo("mib9")` | Aplica el orden de billetes de un modelo de `../maquinas.json` y devuelve su configuración (velocidad) |
| `trama_cambiar_modo`, `trama_auto`, `trama_batch`, `trama_lote`, `trama_sensor`, `trama_divisa`, `trama_denom` | Arman el cambio de configuración a partir de la última leída (`config_actual`) |

**Limitación actual:** separar lo recibido en tramas y en bytes sueltos (los datos billete a
billete llegan fuera de trama) está dentro de la clase `Consola` (`Consola.leer`). Otra
aplicación tiene que replicar esa lógica. En Node ya está separada (`Separador`), y el
siguiente paso previsto es hacer lo mismo aquí con un `protocolo.py` independiente.
