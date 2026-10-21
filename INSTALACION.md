# IFD SB-7 / SB-9 — Instalación y notas de conexión

Programa de prueba (C++/MFC) para comunicar una PC con contadoras de billetes
serie SB-7 / SB-9 usando el control ActiveX del fabricante `IFDX_SBM.ocx`.

## Contenido de la carpeta

| Ruta | Descripción |
|---|---|
| `bin/IFD.exe` | Programa compilado, listo para usar |
| `bin/IFDX_SBM.ocx` | Control ActiveX (32 bits) que implementa el protocolo |
| `bin/IFDCTRL.INI` | Configuración que usa `IFD.exe` (puerto COM, IP, etc.) |
| `Doc/PC protocol_SB&MIB_series.xlsx` | Especificación del protocolo PC ↔ contadora |
| `IFDView.cpp` | Lógica principal: botones y eventos del OCX |
| `ifdx_sb7.h/.cpp` | Wrapper del OCX (lista completa de métodos disponibles) |
| `IFD.sln` / `IFD.vcproj` | Proyecto Visual Studio 2008 (compilar solo en **Win32**) |

> `ReadMe.txt` es la plantilla genérica de AppWizard (VC++ 6); no tiene información del equipo.

## Instalación

1. **Copiar el OCX** a `C:\Windows\SysWOW64` (es de 32 bits, no va en System32).
2. **Registrarlo** desde PowerShell/CMD **como administrador**:
   ```powershell
   Copy-Item ".\bin\IFDX_SBM.ocx" C:\Windows\SysWOW64\
   C:\Windows\SysWOW64\regsvr32.exe C:\Windows\SysWOW64\IFDX_SBM.ocx
   ```
3. **Configurar `bin/IFDCTRL.INI`**:
   ```ini
   [COMM PORT]
   PORT ID=5          ; número de COM del adaptador
   BAUDRATE=115200    ; obligatorio 115200
   [SOCKET]
   ADDRESS=192.168.10.109
   PORT=4101
   ```
   `IFD.exe` lee el `.ini` de su propia carpeta (`bin/`). El `ifdctrl.ini` de la raíz no se usa al ejecutar desde `bin/`.

## Problema del adaptador USB-serie (CH340) — RESUELTO

- **Síntoma:** `IFD.exe` mostraba *"COMx Port Open Error"* y Windows devolvía
  *"Uno de los dispositivos conectados al sistema no funciona"* al abrir el puerto,
  aunque el Administrador de dispositivos mostraba el adaptador como "OK".
- **Causa:** driver WCH CH340 **3.9.2024.9** incompatible con el adaptador (chip clon).
- **Solución:** volver al driver **3.4.2014.8** (Administrador de dispositivos →
  Puertos (COM y LPT) → USB-SERIAL CH340 → Controlador → Revertir / elegir de la lista).
- Tras el cambio, el adaptador quedó en **COM5**.
- **Ojo:** Windows Update puede reinstalar el driver nuevo. Si vuelve el error,
  revisar primero la versión del driver.

Otros detalles:
- *"Acceso denegado"* al abrir el COM = el puerto ya está abierto por otro programa
  (incluido otro `IFD.exe`). No pulsar **Connect** dos veces.
- El número de COM cambia si se conecta el cable en otro puerto USB; actualizar `PORT ID`.

## Conexión por red (TCP)

También funciona por red: IP de la contadora en `[SOCKET] ADDRESS`, puerto **4101**.
Útil como alternativa si falla el cable serie.

## Uso básico / prueba

1. Abrir `bin/IFD.exe` y conectar (menú CommPort, serie o TCP).
2. **Device Set Live** → debe llegar `MSG_DEVICE_SET_LIVE : ACK` y la configuración.
3. **Count Start ON** → contar billetes; llegan `MSG_COUNT_START`,
   `MSG_BYTE_COUNT_DATA` (índice de cada billete en tiempo real),
   `MSG_COUNT_STOP` y los `MSG_RESULT_DENOM`.
4. **Send Request → SW Version Request** → versión de firmware.

### Configuración leída de la máquina (2026-09-28)

| Parámetro | Valor |
|---|---|
| Firmware | 01.41 (checksum 2b3f) |
| Divisa | ARS — peso argentino (código 115) |
| Modo | MIXED (denominación 31 = todas) |
| Auto / ADD / Batch | Auto / On / On, 100 billetes |
| UV / MR / IR | On, nivel 3 |
| Bandejas | Rechazo 20 / Salida 200 |

### Cómo leer los resultados

- `MSG_RESULT_DENOM`: conteo actual. `Reject Pocket` = rechazados,
  `Stack Pocket` = total en salida, `lDenomNumber N` = cantidad por denominación.
- `MSG_RESULT_PRE_DENOM`: conteo **anterior** (modo ADD).
- Índice de denominación: según el protocolo, **0 = billete de menor valor**, ascendente.
  El Excel no incluye la tabla de ARS. La máquina informa **10 índices**.
  **Confirmados con billetes reales (2026-09-29): 3 = $100, 7 = $2000, 8 = $10000.**
  El resto sigue el orden ascendente y falta confirmarlo ($10, $20, $50, $200, $500,
  $1000, $20000):

  | Índice | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
  |---|---|---|---|---|---|---|---|---|---|---|
  | ARS | $10 | $20 | $50 | $100 | $200 | $500 | $1000 | $2000 | $10000 | $20000 |

  Verificar contando un fajo con billetes conocidos.

## Captura del tráfico

- **TCP:** Wireshark con filtro `tcp.port == 4101` → *Follow TCP Stream* (Hex Dump).
- **Serie:** Wireshark no captura puertos COM; usar HHD Free Serial Port Monitor,
  Device Monitoring Studio o com0com. (USBPcap captura el USB del CH340, pero en crudo.)

## Errores conocidos en el código fuente (sin corregir)

1. `AddStrToSendEdit` / `AddStrToReceiveEdit` (`IFDView.cpp` ~1397): búfer fijo de
   128 bytes sin control de largo → posible desbordamiento con textos largos (OCR, barcode).
2. `OnOcrIfdxctrl` (~1478): para EUR y TRY usa el tamaño de la tabla USD como límite;
   la tabla TRY tiene 6 elementos → lectura fuera de rango.
3. `OnCdErrorIfdxctrl` (~976): código 3 mostrado como "Main Motor Error" (la constante es 16);
   `lErrorCode / 2` marca "Feeding Error" para casi cualquier código.
4. `OnButtonDeviceSetup2` (~668): etiquetas del log cruzadas; las casillas no se
   desmarcan si la máquina informa 0.
5. Velocidad del motor: el `switch` solo cubre 0–2 (el `.ini` usa 3 o 4) → línea vacía.
6. `OnSetupStateData2Ifdxctrl` (~1289): el encabezado dice `MSG_SETUP_STATE_DATA` en vez de `..._DATA2`.
7. `OnTcpConnect`: marca el serie como desconectado sin cerrarlo.
