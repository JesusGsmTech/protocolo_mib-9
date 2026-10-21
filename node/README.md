# Herramientas Node.js — contadora SB-7 / SB-9

Versión en Node.js de las herramientas de la carpeta `python/` (que queda igual).
Mismos comandos y mismo comportamiento.

Requisitos: Node.js 20 o superior. Instalar una vez:
```
cd node
npm install
```

## Estructura

| Archivo | Qué es |
|---|---|
| `probar.js` | Consola interactiva: envía comandos y muestra las respuestas decodificadas |
| `escuchar.js` | Escucha el tráfico entre IFD.exe y la máquina (monitor / puente / proxy TCP) |
| `src/protocolo.js` | Protocolo: armar/verificar tramas, decodificar, cambios de configuración. Reutilizable en otra app |
| `src/conexion.js` | Conexión por puerto serie (`serialport`) o TCP, con la misma interfaz |
| `src/registro.js` | Pantalla + archivo de log en `logs/` |
| `src/autoprueba.js`, `test/` | Pruebas sin máquina con tramas reales capturadas |

## probar.js: hablar con la máquina sin IFD.exe

```
node probar.js --ip 192.168.123.231     # por red (puerto 4101)   = npm run red
node probar.js                          # por puerto serie COM5    = npm start
node probar.js --puerto COM3            # otro puerto serie
node probar.js --prueba                 # autoprueba sin máquina   = npm run prueba
npm test                                # pruebas unitarias
```
Cierra o desconecta IFD.exe antes: la máquina acepta una sola conexión.

Secuencia típica:
```
knock                 -> ACK + configuración (moneda, modo, lote...)
iniciar               -> cuenta: COUNT_START, billete a billete, COUNT_STOP, RESULT_DATA con monto
pedir resultado       -> último resultado
modo mixto | single   -> cambia el modo (y relee la configuración)
batch on · lote 50    -> cortar cada 50 billetes
divisa usd | ars      -> cambiar la divisa
denom 100             -> en SINGLE, aceptar solo $100 (vale para la siguiente pasada)
release · salir
```
`ayuda` muestra todos los comandos. `default`, `moneda` y `reboot` piden confirmación.

## escuchar.js: espiar la comunicación de IFD.exe

```
node escuchar.js tcp --maquina 192.168.123.231      # proxy; en bin/IFDCTRL.INI: ADDRESS=127.0.0.1
node escuchar.js monitor --puerto COM5              # solo lo que envía la máquina
node escuchar.js puente --real COM5 --virtual COM20 # serie, con com0com
```

## Usar el protocolo desde otra aplicación

```js
import { armarTrama, verificarTrama, decodificar, Separador } from "./src/protocolo.js";
import { abrirTcp } from "./src/conexion.js";

const con = await abrirTcp("192.168.123.231");
const sep = new Separador({
  onTrama: (t) => console.log(decodificar(verificarTrama(t).datos)),
  onByte: (b) => console.log("billete índice", b),
  onIncompleta: () => {},
});
con.on("data", (d) => sep.push(d));
con.escribir(armarTrama([0x30, 0x01])); // KNOCK
```

## Notas del equipo (ver también ../INSTALACION.md)

- Trama: `F0 F1 LEN 19 02 00 00 00 SID` + cada byte de datos en 2 nibbles + checksum
  (suma desde LEN, en 2 nibbles). LEN = total − 4. Mínimo 100 ms entre envíos.
- Versión de firmware: `pedir version` (parámetro 0x21, no documentado; capturado de IFD.exe).
- ARS: índices confirmados 3 = $100, 7 = $2000, 8 = $10000.
- La denominación fija (`denom`) solo dura una pasada; luego la máquina vuelve a DD.
- La capacidad de bandejas que informa 41h no es real en la SB-9: se muestra el código.
