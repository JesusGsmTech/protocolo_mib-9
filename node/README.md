# Node.js — contadora SB-7 / SB-9

Consola de pruebas, escucha de tráfico, perfiles y el protocolo como **módulo reutilizable**.
Equivalente a la versión de [`../python`](../python/README.md). La referencia de comandos y el
resumen del protocolo están en el [README principal](../README.md).

## Instalación

Node.js 20 o superior:
```
npm install
```

## Archivos

| Archivo | Qué es |
|---|---|
| `src/protocolo.js` | **El protocolo**: armar/verificar tramas, `Separador`, decodificar, cambios de configuración. Sin dependencias del medio |
| `src/conexion.js` | Conexión por puerto serie (`serialport`) o TCP, con la misma interfaz |
| `src/perfiles.js` | Aplica y verifica los perfiles de `../perfiles.json` |
| `src/maquinas.js` | Modelos de `../maquinas.json`: `usarModelo("mib9")` aplica su orden de billetes y devuelve su velocidad |
| `src/registro.js` | Pantalla + archivo de log en `logs/` |
| `src/autoprueba.js`, `test/` | Pruebas sin máquina con tramas reales capturadas |
| `probar.js` | Consola interactiva |
| `escuchar.js` | Escucha el tráfico entre IFD.exe y la máquina (monitor / puente / proxy TCP) |

## probar.js: probar la máquina

```
npm run red                             # node probar.js --ip 192.168.123.231 (puerto 4101)
npm start                               # node probar.js, puerto serie COM5 a 115200
node probar.js --puerto COM3            # otro puerto serie
npm run mib9                            # node probar.js --modelo mib9 (57600, orden de billetes de la MIB-9)
npm run prueba                          # autoprueba sin máquina
npm test                                # pruebas unitarias
node --test --test-name-pattern perfiles  # una sola prueba
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
Cada sesión queda en `logs/probar_AAAAMMDD_HHMMSS.log`.

## escuchar.js: ver qué envía IFD.exe

```
node escuchar.js tcp --maquina 192.168.123.231      # proxy TCP; en bin/IFDCTRL.INI: ADDRESS=127.0.0.1
node escuchar.js monitor --puerto COM5              # solo lo que envía la máquina
node escuchar.js puente --real COM5 --virtual COM20 # serie, requiere com0com
```

## Usar el protocolo desde otra aplicación

Copiar `src/protocolo.js` y `src/conexion.js` (y `serialport` como dependencia, si se usa el
puerto serie). `protocolo.js` no depende de nada externo.

```js
import { armarTrama, verificarTrama, decodificar, Separador, estado } from "./src/protocolo.js";
import { abrirTcp } from "./src/conexion.js";   // o abrirSerie("COM5")

const con = await abrirTcp("192.168.123.231");
const sep = new Separador({
  onTrama: (t) => {
    const { ok, datos } = verificarTrama(t);
    if (!ok) return;
    if (datos[0] === 0x30 && datos[1] & 0x02) con.escribir(armarTrama([0x35, 0x12])); // ACK -> pedir config
    if (datos[0] === 0x34) console.log("Resultado:", decodificar(datos));           // fin de conteo
  },
  onByte: (b) => console.log("billete índice", b),  // datos billete a billete (fuera de trama)
  onIncompleta: () => {},
});
con.on("data", (d) => sep.push(d));
con.escribir(armarTrama([0x30, 0x01])); // KNOCK
```

| Exporta `src/protocolo.js` | Qué hace |
|---|---|
| `armarTrama(datos)` | `[comando, parámetros…]` → `Buffer` listo para enviar |
| `verificarTrama(buf)` | Valida inicio, largo y checksum → `{ ok, motivo, datos }` |
| `Separador` | Divide el flujo recibido en tramas y bytes sueltos, aunque lleguen partidos |
| `decodificar(datos)` | Traduce una respuesta a líneas de texto; actualiza `estado` |
| `estado` | Lo conocido de la máquina: `moneda`, `config` (última 41h), `version` |
| `tramaCambiarModo`, `tramaAuto`, `tramaBatch`, `tramaLote`, `tramaSensor`, `tramaDivisa`, `tramaDenom` | Arman un cambio de configuración a partir de `estado.config` |

Recordar esperar al menos 100 ms entre tramas enviadas (la consola lo hace con una cola en
`probar.js`, `Consola.enviar`).
