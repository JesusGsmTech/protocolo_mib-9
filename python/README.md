# Herramientas Python — contadora SB-7 / SB-9

Carpeta de trabajo en Python. El resto del proyecto (C++/MFC, `bin/`) no se modifica.

Requisitos: Python 3 y `pyserial` (`pip install -r requirements.txt`).

## probar_com.py: hablar con la máquina sin IFD.exe

Consola interactiva que arma cada trama según el protocolo
(`Doc/PC_protocol_SB_MIB_series.md`), la envía por el puerto serie y muestra la
respuesta decodificada. Cierra `IFD.exe` antes de usarla.

```
python probar_com.py                # COM5 a 115200
python probar_com.py --prueba       # autoprueba sin máquina
```

Secuencia típica:
```
knock                 -> la máquina responde ACK
pedir estado2         -> configuración (41h)
iniciar               -> cuenta los billetes (COUNT_START ... COUNT_STOP, RESULT_DATA)
pedir resultado       -> último resultado (34h)
setup2 1 0            -> activa los datos billete a billete (1BYTE_COUNT_DATA)
release               -> suelta la máquina
```
Escribe `ayuda` para ver todos los comandos. `datos 35 02` envía una trama armada
con los bytes que indiques, y `crudo F0 F1 ...` envía bytes tal cual.
`default`, `moneda` y `reboot` modifican la máquina y piden confirmación.

Formato de trama: `F0 F1 LEN 19 02 00 00 00 SID` + cada byte de datos partido en
2 nibbles + checksum (suma desde LEN, también en 2 nibbles). LEN = total − 4.

## escuchar_puerto.py

Muestra en pantalla, en hexadecimal y ASCII y con la hora, los bytes que van
entre la PC y la máquina. También los guarda en `logs/`.

Un puerto COM solo lo puede abrir **un programa a la vez**. Por eso hay tres modos:

### 1. `monitor`: solo escuchar a la máquina
```
python escuchar_puerto.py monitor --puerto COM5
```
Cierra `IFD.exe` antes. Muestra lo que la máquina envía por su cuenta (por ejemplo,
resultados en modo Auto), pero no se ve lo que enviaría la PC.

### 2. `tcp`: espiar IFD.exe por red (recomendado, no necesita drivers)
```
python escuchar_puerto.py tcp --maquina 192.168.10.109
```
En `bin/IFDCTRL.INI` cambia `[SOCKET] ADDRESS=127.0.0.1` y conecta IFD.exe por TCP.
El programa reenvía todo a la máquina y muestra ambos sentidos
(`PC -> MAQ` y `MAQ -> PC`). Al terminar, vuelve a poner la IP real en el `.ini`.

### 3. `puente`: espiar IFD.exe por el puerto serie
Necesita **com0com**, que crea un par de puertos virtuales conectados entre sí
(por ejemplo, COM20 <-> COM21).
1. Instala com0com y crea el par COM20/COM21.
2. En `bin/IFDCTRL.INI` pon `PORT ID=21`, para que IFD.exe use el puerto virtual.
3. Ejecuta:
   ```
   python escuchar_puerto.py puente --real COM5 --virtual COM20
   ```
4. Abre IFD.exe y conecta. Verás ambos sentidos.

Al terminar, vuelve a poner `PORT ID=5` en el `.ini`.

## Formato de salida
```
14:32:10.512 PC -> MAQ (11 bytes)
    0000  0B 19 02 00 00 00 00 03 05 00 01              ...........
```
Los bytes que llegan seguidos (sin más de 20 ms de silencio entre ellos) se muestran como una sola trama.
