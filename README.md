# Protocolo contadora SB-9 / MIB-9

Banco de pruebas e **implementación de referencia** del protocolo de comunicación de las
contadoras de billetes **SB-7 / SB-9** (protocolo IFD, familia "SB and MIB Series").

El repositorio cumple dos funciones:

1. **Probar** la máquina real: consolas interactivas que envían cada comando y muestran la
   respuesta decodificada, sin depender del programa del fabricante.
2. **Servir de base** para otras aplicaciones: el protocolo está implementado, probado con
   la máquina y documentado, en **Python** y en **Node.js** (versiones equivalentes).

Probado con una **SB-9** (firmware 01.41) y una **MIB-9** (firmware antiguo), en pesos argentinos.

| Carpeta / archivo | Qué es |
|---|---|
| [`python/`](python/README.md) | Consola de pruebas y escucha de tráfico en Python |
| [`node/`](node/README.md) | Lo mismo en Node.js; el protocolo ya está separado como módulo (`src/protocolo.js`) |
| `perfiles.json` | Perfiles de configuración, compartidos por las dos versiones |
| `maquinas.json` | Modelos de máquina: velocidad del puerto serie y orden de billetes de cada una |
| `Doc/` | Protocolo del fabricante (`.xlsx`) y su conversión a Markdown |
| `INSTALACION.md` | Instalación del OCX, driver del cable USB-serie y notas del equipo |
| raíz, `bin/`, `res/` | Programa original del fabricante `IFD.exe` (C++/MFC + control `IFDX_SBM.ocx`). Solo referencia |

## Conexión con la máquina

- **Red (TCP)**: IP de la máquina, puerto **4101**.
- **Puerto serie**: adaptador USB-serie CH340 a **115200** baudios, 8N1.
  Con algunos adaptadores el driver nuevo de WCH falla; ver `INSTALACION.md`.

La máquina acepta **una sola conexión a la vez**: cerrar o desconectar `IFD.exe` y
cualquier otra consola antes de conectar.

## Modelos de máquina

Las máquinas difieren en la velocidad del puerto serie y en el **orden de los billetes**
(qué índice de denominación corresponde a cada billete). Se elige con `--modelo`; los valores
están en `maquinas.json`, compartido por Python y Node.

| Modelo | `--modelo` | Velocidad | Billetes ARS (índice 0 → 9) |
|---|---|---|---|
| SB-9, firmware 01.41 | `sb9` (por defecto) | 115200 | $10 → $20000 (ascendente) |
| MIB-9, firmware antiguo | `mib9` | 57600 | $20000 → $10 (descendente) |

`--baudios` reemplaza la velocidad del modelo si hace falta. Para otra máquina, agregar una
entrada en `maquinas.json`.

## Uso rápido

```
cd python && python probar_com.py --ip 192.168.123.231      # Python, SB-9 por red
cd python && python probar_com.py --modelo mib9             # Python, MIB-9 por COM5
cd node   && npm run red                                    # Node, SB-9 por red
cd node   && npm run mib9                                   # Node, MIB-9 por COM5
```
Dentro de la consola: `knock` → `perfil 1` → `iniciar` → `pedir resultado` → `salir`.
Detalle de instalación y opciones en el README de cada carpeta.

## Comandos de la consola

Iguales en Python y Node. `ayuda` dentro de la consola muestra la lista con su sintaxis.

| Grupo | Comandos |
|---|---|
| Conexión | `knock` (siempre primero) · `ack` · `release` · `salir` |
| Información | `pedir estado` · `estado2` · `resultado` · `error` · `sensores` · `disp2` · `reporte` · `version` · `reenviar` |
| Conteo | `iniciar` · `cancelar` |
| Perfiles | `perfiles` · `perfil <n> [lote]` · `perfil verificar <n> [lote]` |
| Configuración | `modo mixto\|single\|conteo\|cara\|orientacion` · `auto on\|off` · `batch on\|off` · `lote 1-200` · `sensor uv\|mr\|ir on\|off` · `divisa ars\|usd\|…` · `denom <billete>\|dd` · `bandejas <r> <s>` |
| Contadores | `limpiar rechazo\|salida\|total\|mixto\|simple\|jam\|reporte` |
| Equipo | `setup2 <billete a billete 0\|1> <teclado 0\|1>` · `usb on\|off` · `aletas on\|off` |
| Con confirmación | `reboot` · `default` · `moneda` |
| Manuales | `datos <hex…>` (arma la trama) · `crudo <hex…>` (bytes tal cual) |

Los cambios de configuración leen la configuración actual, cambian solo ese valor, la
envían completa y la vuelven a leer para verificar.

## Perfiles

Definidos en `perfiles.json`. Todos dejan: ARS, Auto, sensores UV/MR/IR activos,
niveles 3, sin ADD ni beep, y **bandejas en rechazo 100 / salida 300**.

| Perfil | Modo | Límite |
|---|---|---|
| 1 | Mixto | sin límite (se detiene al llenar la bandeja) |
| 2 | Mixto | lote de 100 |
| 3 | Single (toma la denominación del primer billete) | sin límite |
| 4 | Single (toma la denominación del primer billete) | lote de 100 |

`perfil 2 50` aplica el perfil 2 con lote de 50. `perfil verificar 1` compara sin cambiar nada.

## El protocolo en resumen (para integrarlo en otra app)

Especificación completa: [`Doc/PC_protocol_SB_MIB_series.md`](Doc/PC_protocol_SB_MIB_series.md).

**Trama**: `F0 F1 LEN 19 02 00 00 00 SID` + datos + checksum
- Cada byte de datos se envía **partido en dos nibbles**: `0x41` → `04 01`. El primer byte es el comando.
- `LEN` = largo total − 4. Checksum = suma desde `LEN` hasta el último dato, & 0xFF, también en dos nibbles.
- Esperar al menos **100 ms** entre tramas enviadas.

**Flujo básico**
1. PC envía KNOCK (`30 01`) → la máquina responde ACK (`30 02`). Si la máquina se enciende
   después, es ella la que envía KNOCK y la PC responde ACK.
2. Pedir configuración: `35 12` → respuesta `41h` (moneda, modo, Auto, sensores, lote, niveles…).
3. Contar: `37 01` (solo funciona en **Auto**; en Auto la máquina también arranca sola al detectar billetes).
   La máquina envía `32h` COUNT_START → **un byte suelto por billete** (fuera de trama: índice
   de denominación, `20` sospechoso, `70` falso, `71` stay note, `40` fin) → `3Dh` COUNT_STOP →
   `34h` RESULT_DATA (rechazados, en salida, cantidad por denominación y conteo anterior).
4. Mientras cuenta, la máquina no atiende pedidos.

**Pedidos** (`35 xx`): `01` configuración básica · `12` configuración completa · `02` resultado ·
`04` error · `10` sensores · `20` opciones del equipo · `80` totales acumulados · `21` versión.

## Particularidades de la SB-9 comprobadas con la máquina

- En **Manual**, la máquina ignora la orden de iniciar conteo desde la PC (también con `IFD.exe`).
- La versión de firmware se pide con `35 21`, que no figura en el documento.
- La configuración (`41h`) trae 3 bytes extra no documentados.
- ARS tiene 10 denominaciones: confirmados índice 3 = $100, 7 = $2000, 8 = $10000 (el resto, en orden ascendente).
- La **denominación fija** en modo single solo vale para una pasada; después vuelve a "primer billete".
- Las **bandejas** se escriben y se leen con códigos distintos: escribir `00` deja rechazo 100 / salida 300,
  pero al leer la máquina solo informa grupos (salida "200, 250 o 300").
- `default` solo activa el beep y pone la salida en 100.
- El documento del fabricante tiene errores en algunos ejemplos (checksum de 41h y 4Fh, LEN de 53h).

## Pruebas sin máquina

```
python python/probar_com.py --prueba
cd node && npm test
```
Usan tramas reales capturadas de la máquina (`python/capturas/`).
