# PC Protocol — SB and MIB Series / IFD(PC)

> Convertido desde `PC_protocol_SB_MIB_series.xlsx`. Las flechas y formas dibujadas de los diagramas de secuencia no se conservan como imagen; se representan como tablas con columnas **SB Series → / ← IFD(PC)**.

## Hoja: List

# SB and MIB Series /IFD(PC) Initial Protocol

# Sctp_Tx/Rx Format

| Value of Command | Name of Command | Direction of Comuniation | Remark |
|---|---|---|---|
| 1. SubCommand = 30 (h) | DEVICE_SET_LIVE | SB Series  <---> IFD(PC) |  |
| 2. SubCommand = 31 (h) | SETUP_STATE_DATA | SB Series ---> IFD(PC) | basic state data |
| 3. SubCommand = 32 (h) | COUNT_START | SB Series <---> IFD(PC) |  |
| 4. SubCommand = 33 (h) | CD_ERROR | SB Series ---> IFD(PC) | add maintenance alarm |
| 5. SubCommand = 34 (h) | RESULT_DATA | SB Series ---> IFD(PC) |  |
| 6. SubCommand = 35 (h) | RESULT_REQUEST | SB Series <--- IFD(PC) |  |
| 7. SubCommand = 36 (h) | RESULT_CLEAR | SB Series <--- IFD(PC) |  |
| 8. SubCommand = 37 (h) | START_STOP | SB Series <--- IFD(PC) |  |
| 9. SubCommand = 38 (h) | DEVICE_SETUP2 | SB Series <---> IFD(PC) |  |
| 10. SubCommand = 39 (h) | DEFAULT_LOADING | SB Series <--- IFD(PC) |  |
| 11. SubCommand = 3A (h) | CURRENCY_CHANGE | SB Series <--- IFD(PC) |  |
| 12. SubCommand = 3B (h) | SETUP_NO_ACCEPT | SB Series ---> IFD(PC) |  |
| 13. SubCommand = 3D (h) | COUNT_STOP | SB Series ---> IFD(PC) |  |
| 14. SubCommand = 3E (h) | DEVICE_STATUS_REQ | SB Series ---> IFD(PC) |  |
| 15. SubCommand = 3F (h) | Reserved |  | Under discussion |
| 16. SubCommand = 40 (h) | PRINT_KEY | SB Series <--- IFD(PC) |  |
| 17. SubCommand = 41 (h) | SETUP_STATE_DATA2 | SB Series <---> IFD(PC) | included all data of SETUP_STATE_DATA (31h) |
| 18. SubCommand = 42 (h) | Reserved |  | Under discussion |
| 19. SubCommand = 43 (h) | COUNTING_REPORT_DATA | SB9 ---> IFD(PC) | optional function (only for SB-9 ) |
| 20. SubCommand = 44 (h) | SAVE_BMP_TO_USB | SB9 <--- IFD(PC) | optional function (only for SB-9 ) |
| 21. SubCommand = 45 (h) | MC_STATUS | SB Series ---> IFD(PC) | hopper clear |
| 22. SubCommand = 46 (h) | SW_VERSION | SB Series ---> IFD(PC) |  |
| 23. SubCommand = 47 (h) | OCR_RESULT | SB Series ---> IFD(PC) |  |
| 24. SubCommand = 48 (h) | IFD_WING_MOTOR | SB9 <--- IFD(PC) | start /stop  the wing motor  (only for SB-9 ) |
| 25. SubCommand = 49 (h) | IFD_REJECT_DESIGNATED_NOTE | SB9 <--- IFD(PC) | request to reject designated note (only for SB-9 & MIB-11 ) |
| 26. SubCommand = 4A (h) | SETUP_MAINTENANCE_ALARM | SB Series <--- IFD(PC) | setting on/off and period (only for SB-9 & MIB-11 ) |
| 27. SubCommand = 4C (h) | REQUEST_IFD_COUNT_LOG_DATA | SB Series <--- IFD(PC) |  |
| 28. SubCommand = 4D (h) | SEND_IFD_COUNT_LOG_DATA | SB Series ---> IFD(PC) |  |
| 29. SubCommand = 4E (h) | SEND_IFD_REF_NUMBER | SB Series <--- IFD(PC) |  |
| 30. SubCommand = 4F (h) | RESULT_DATA2 | SB Series ---> IFD(PC) |  |
| 31. SubCommand = A8 (h) | REBOOT | SB Series <---> IFD(PC) |  |
| 32. SubCommand = 63 (h) | SETUP_STATE_DATA_EX | SB Series <---> IFD(PC) | included all data of SETUP_STATE_DATA (31h) & (41h)(For TSS-oriented MIB-11 models only.) |
| 33. SubCommand = 53 (h) | SET_MACHINE_DATE_TIME | SB Series <---> IFD(PC) |  |
| 99. 1BYTE_COUNT_DATA |  | SB Series  ---> IFD(PC) |  |

- Command Tx/Rx state block diagram
---

## Hoja: Contents

# SB and MIB Series /IFD(PC) Initial Protocol

### 1) case 1

- SB Series On after IFD(PC) Executed

| SB Series |  | IFD(PC) |
|---|:---:|---|
| DEVICE_SET_LIVE(30h): KNOCK | → |  |
|  | ← | DEVICE_SET_LIVE(30h): ACK |
| 1bit Data or Detail Data Tx/Rx . | → |  |
| ⋮ |  | ⋮ |
| ⋮ |  | ⋮ |
|  | ← | DEVICE_SET_LIVE(30h): Release -> IFD mode Destory |

### 2) case 2

- IFD(PC) Execute after SB Series ON

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SET_LIVE(30h): KNOCK |
| DEVICE_SET_LIVE(30h): ACK | → |  |
| 1bit Data or Detail Data Tx/Rx . | → |  |
| ⋮ |  | ⋮ |
| ⋮ |  | ⋮ |
|  | ← | DEVICE_SET_LIVE(30h): Release -> IFD mode Destory |

- **Sctp_Tx/Rx Format** · protocol version 2

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | … | … | N-3 | N-2 | N-1 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Start Upper | Start Lower | Length = (N-2)-2+1 | IFD command | Protocol Version | Reserved | Reserved | Reserved | Station ID | Data (note1) |  |  |  | Check sum(note2) |  |

- **Data(note 1)** · : Data[n] is BCD Format as below

| 9 | 10 | 11 | 12 | 13 | … | … | N-4 | N-3 |  |
|---|---|---|---|---|---|---|---|---|---|
| 0C(h) | 03(h) | 05(h) | 07(h) |  |  |  |  |  | BCD Format |
| C3(h) | 57(h) | … | … |  |  |  |  |  | HEX Format |

    - **Data[0] = SubCommand**
    - **Data[1] = Parameter 1**
    - **Data[2] = Parameter 2**
    - …
    - …
- **Check sum (note 2)** · : Check sum is BCD Format

**Example:**

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 05 | 00 | 01 | 02 | 0F |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Start Upper** · Always F0(h)
- **Start Lower** · Always F1(h)
- **Length** · total packet length - 4   (4 means 'S.U' + 'S.L' + 'Check sum')
    - --> in this case, LEN = 15-4 = 11 = 0B(h)
- **IFD command** · Always 19(h)
- **Protocol Version** · Always 02(h)
- **Station ID** · IFD(PC) can communicate with SB Series that have same Station ID.
    - -. SB Series have Station ID from 1 ~ 99.
    - (if you want to check SB Series's Station ID, press key "Func -> 9 -> 6" on key pad)
    - -. If you set S.ID to "00", you can communcate with SB Series connected
    - to your PC regardless of SB Series's S.ID
- **Data[0]** · SubCommand = 35 (h)
- **Data[1]** · Parameter 1 = 01 (h)
- **Check sum** · = sum from 3rd byte (LEN) to last of Data[n]
    - -.in this case,
    - CheckSum = 0B(h)+19(h)+02(h)+00(h)+00(h)+00(h)+00(h)+03(h)+05(h)+00(h)+01(h)
    - = 2F(h)

### 1. SubCommand = 30 (h) — DEVICE_SET_LIVE — `SB Series <---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 00 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 30 (h) = SubCommand
- **Data[1]** · Bit 0 · KNOCK
    - Bit 1 · ACK
    - Bit 2 · RELEASE
    - : only 1 bit can be set at the same time

**Example:**

- DEVICE_SET_LIVE:KNOCK

```
F0  F1  0B  19  02  00  00  00  00  03  00  00  01  02  0A
```

- DEVICE_SET_LIVE:ACK

```
F0  F1  0B  19  02  00  00  00  00  03  00  00  02  02  0B
```

- DEVICE_SET_LIVE:RELEASE

```
F0  F1  0B  19  02  00  00  00  00  03  00  00  04  02  0D
```

### 2. SubCommand = 31 (h) — SETUP_STATE_DATA — `SB7 <---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 17 | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 01 | M. Speed |  | B.Status |  | Currency |  |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 |
|---|---|---|---|---|---|---|---|---|---|
| DD & C.M. |  | P.Cap |  | B.Count# |  | reserved |  | xx | xx |
| Data[4] |  | Data[5] |  | Data[6] |  | Data[7] |  | CheckSum |  |

- **Data[0]** · 31 (h) = SubCommand
- **Data[1]** · Motor Speed · PC read Only
    - Bit7~Bit4:
    - 0000 · 1000 rpm · MIB-11 · 800 rpm
    - 0001 · 1200 rpm · MIB-11 · 1000 rpm
    - 0010 · 1500 rpm · MIB-11 · 1200 rpm
    - 0011 · 600  rpm · MIB-9 only
    - 0100 · 800  rpm · MIB-9 only
    - 0101 · 900  rpm · MIB-9 only
- **Data[2]** · Basic Status · PC Read/Write
    - Bit 0 · Batch On/Off · 1 = On · 0 = Off
    - Bit 1 · reserved
    - Bit 2 · warning beep enable · 1 = Enable · 0 = Disable
    - Bit 3 · auto/manual · 1 = Auto · 0 = Manual
    - Bit 4 · add On/Off · 1 = On · 0 = Off
    - Bit 5 · UV Detection On/Off · 1 = On · 0 = Off
    - Bit 6 · MR Detection On/Off · 1 = On · 0 = Off
    - Bit 7 · Mode Lock On/Off · 1 = On · 0 = Off
- **Data[3]** · Currency Code · PC Read/Write
    - 01 (h) = US Dollar · 02 (h) = Mexico Peso
    - 03 (h) = Korea Won · 04 (h) = Euro
    - 05 (h) = Colombia Peso · 06 (h) = China YUAN
    - 07 (h) = Turkey Lira · 08 (h) = Costa Rica
    - 09 (h) = Nicaraqua · 10 (h) = Australia
    - 11 (h) = Singapore · 12 (h) = India
    - 13 (h) = Norway · 14 (h) = Newziland
    - 15 (h) = Poland · 16 (h) = Taiwan
    - 17 (h) = Czecho · 18 (h) = Lebanon
    - 19 (h) = Sweden · 20 (h) = Brasil
    - 21 (h) = Canada · 22 (h) = Syria
    - 23 (h) = Guatemala · 24 (h) = Iraq
    - 25 (h) = Israel · 26 (h) = Peru
    - 27 (h) = Coupon 1 · 28 (h) = Coupon 2
    - 29 (h) = Coupon 3 · 30 (h) = Coupon 4
    - 31 (h) = Coupon 5 · 32 (h) = Coupon 6
    - 33 (h) = Japan · 34 (h) = Papua New Guinea
    - 35 (h) = Russia · 36 (h) = South Africa
    - 37 (h) = Arab Emirates · 38 (h) = Thailand
    - 39 (h) = England · 40 (h) = Venezuela
    - 41 (h) = Barcode · 42 (h) = Ukraine
    - 43 (h) = Kazakhstan · 44 (h) = Switzerlnad
    - 45 (h) = Saudi Arabia · 46 (h) = Jordan
    - 47 (h) = Kyrgyzstan · 48 (h) = Malaysia
    - 49 (h) = Malaysia cheque · 50 (h) = Indonesia
    - 51 (h) = Sudan · 52 (h) = Romania
    - 53 (h) = Belarus · 54 (h) = Azerbaijani
    - 55 (h) = Serbia · 56 (h) = Dominica
    - 57 (h) = Suriname · 58 (h) = Canada
    - 59 (h) = Hungary · 60 (h) = Croatia
    - 61 (h) = Ghana
- **Data[4]** · Denomination & Counting mode
    - Bit7~Bit3: Denomination · if count, Mixed, and Serial No. mode  -> PC Read Only
    - if single, Face, and Orient mode   -> PC Read/Write
    - 0000 0 · denomination value is least · (if US$ mode, $1)
    - 0000 1 · (if US$ mode, $2)
    - …
    - 0011 0 · (if US$ mode, $100)
    - 1111 0 · ALL mode
    - 1111 1 · DD mode
    - Bit2~Bit0: · counting mode · PC Read/Write
    - 000 · COUNT mode
    - 001 · MIXED mode
    - 010 · SINGLE mode
    - 011 · reserved
    - 100 · reserved
    - 101 · reserved
    - 110 · ISSUE mode (optional)
- **Data[5]** · Pocket Capacity · PC Read/Write
    - Bit7~Bit6: · Reject Pocket Capacity
    - 00 · 30 PCS · MIB-11 · 100 PCS
    - 01 · 20 PCS · MIB-11 · 70 PCS
    - 10 · 10 PCS · MIB-11 · 50 PCS
    - 11 · reserved
    - Bit5~Bit4: · Stacker Pocket Capacity
    - 00 · 200 PCS · MIB-11 · 250 PCS
    - 01 · 150 PCS · MIB-11 · 200 PCS
    - 10 · 100 PCS · MIB-11 · 100 PCS
- **Data[6]** · Batch Counter number · PC Read/Write
- **Data[7]** · reserved

**Example:**

| | | | | | | | | | | | | | | | | |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 17 | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 01 | 00 | 00 | 00 | 0C | 00 | 01 |
|  |  |  |  |  |  |  |  |  |  |  | M. Speed |  | B.Status |  | Currency |  |
| 0F | 09 | 00 | 00 | 06 | 04 | 00 | 00 | 06 | 05 |  |  |  |  |  |  |  |
| DD & C.M. |  | P.Cap |  | B.Count# |  |  |  |  |  |  |  |  |  |  |  |  |

- **motor speed = 00(h) ->** · 1000 rpm
- **basic status =  0C(h) ->** · BATCH off · ADD off
    - warning beep enable · UV off
    - AUTO mode · MR off
    - MODE LOCK off
- **currenty = 01(h)      ->** · US dollar mode
- **DD & count mode = F9 (h) ->** · MIXED mode
    - : bit7~bit3-> meanless if COUNT, MIXED, and Serial No. mode
- **Pocket Capacity = 00(h)  ->** · Reject pocet : 30pcs · Stacker Pocket: 200pcs
- Batch Couner number = 64(h) -> · 64(h) = 100

### 3. SubCommand = 32 (h) — COUNT_START — `SB Series ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 02 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 32 (h) = SubCommand
- **Data[1]** · Bit 0 · Counting Start
    - Bit 1 · New Deposit

**Example:**

- COUNT_START: counting start & new deposit -> when there is no bank note in the stacker pocket

```
F0  F1  0B  19  02  00  00  00  00  03  02  00  03  02  0E
```

- COUNT_START: counting start -> when there is bank note in the stacker pocket

```
F0  F1  0B  19  02  00  00  00  00  03  02  00  01  02  0C
```

### 4. SubCommand = 33 (h) — CD_ERROR — `SB Series ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 03 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 33 (h) = SubCommand
- **Data[1]** · Bit 0 · JAM Error
    - Bit 1 · Feeding Error
    - Bit 2 · Main motor Error
    - Bit 3 · Clear hopper

### 5. SubCommand = 34 (h) — RESULT_DATA — `SB Series ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | xx | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 04 | N.of.R.P |  | N.of.O.S |  | N.of.D0 |  |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | … |  | 2N+15 | 2N+16 | 2N+17 | 2N+18 |  |  | 6N+11 | 6N+12 | 6N+13 | 6N+14 | 6N+15 | 6N+16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| N.of.D1 |  | … | … | Pre.N.of.D0 |  |  |  | … | … | Pre.N.of.D(N-1) |  |  |  | xx | xx |
| Data[4] |  | … |  | Data[N+3] |  | Data[N+4] |  |  |  | Data[3N+2] |  | Data[3N+3] |  | CheckSum |  |

- **Data[0]** · 34 (h) = SubCommand
- **Data[1]** · number of notes in the Reject Pocket
- **Data[2]** · number of notes in the output Stacker
- **Data[3]** · number of notes of Denom.0(if US$ mode, $1) in the output stacker
- …
- **Data[N+2]** · number of notes of Denom. N-1 (if US$ mode, $100) in the output stacker
- **Data[N+3]** · Previous number of notes of Denom.0 (Upper Byte) in ADD mode
- **Data[N+4]** · Previous number of notes of Denom.0 (Lower Byte) in ADD mode
- …
- **Data[3N+2]** · Previous number of notes of Denom. N-1 (Upper Byte) in ADD mode
- **Data[3N+3]** · Previous number of notes of Denom. N-1 (Lower Byte) in ADD mode
- note) N: Denom number
    - -> if US$ mode, N=7 ($1, $2, $5, $10, $20, $50, $100)
    - Denom = · 0 · -> · 1 · 3 · -> · $10
    - 1 · -> · 2 · 4 · -> · $20
    - 2 · -> · 5 · 5 · -> · $50
    - 6 · -> · $100
    - -> if EURO mode, N=7(€5, €10, €20, €50, €100, €200, €500)

**Example:** when US$ mode,,

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 37 | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 04 | 00 | 00 | 00 | 03 | 00 | 00 |
|  |  |  |  |  |  |  |  |  |  |  | n.of.R.P |  | n.of.O.S |  | D0 ($1) |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 01 | 00 | 00 | 00 | 02 | 00 | 00 | 00 | 00 |
| D1 ($2) |  | D2 ($5) |  | D3 ($10) |  | D4($20) |  | D5($50) |  | D6($100) |  |

| 29 | 30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 40 | 41 | 42 | 43 | 44 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 02 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 01 | 00 | 00 | 00 | 01 |

- **pre. D0 ($1)** · pre. D1 ($2) · pre. D2 ($5) · pre. D3 ($10)

| 45 | 46 | 47 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 01 | 00 | 00 | 00 | 02 | 00 | 00 | 00 | 01 | 06 | 07 |

- **pre. D4 ($20)** · pre. D5 ($50) · pre. D6 ($100) · CheckSum

- number of notes of Reject Pocket · 0
- number of note of Output Stacker · 3
- **current count value** · $1: · 0 · $2: · 0 · $5: · 1
    - $10: · 0 · $20: · 2 · $50: · 0
    - $100: · 0
- previos count value in ADD mode · $1: · 2 · $2: · 0 · $5: · 1
    - $10: · 1 · $20: · 1 · $50: · 2
    - $100: · 1

### 5-1. SubCommand = 47 (h) — OCR_RESULT — `SB Series ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | xx | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 07 |  |  |  |  |  |  |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |
|  |  | … |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  |  | … | … |  |  |  |  | … | … |  |  |  |  | xx | xx |  |
| Data[4] |  | … |  |  |  |  |  |  |  | Data[19] |  | Data[20] |  | CheckSum |  |  |

- **Data[0]** · 47 (h) = SubCommand
- **Data[1]** · 1st ASCII letter of OCR result (Upper 4bits, Lower 4bits)
- **Data[2]** · 2nd ASCII letter of OCR result (Upper 4bits, Lower 4bits)
- **Data[3]** · 3rd ASCII letter of OCR result (Upper 4bits, Lower 4bits)
- **…** · …
- **Data[18]** · 18th ASCII letter of OCR result (Upper 4bits, Lower 4bits)
- **Data[19]** · 19th ASCII letter of OCR result (Upper 4bits, Lower 4bits)
- **Data[20]** · 20th ASCII letter of OCR result (Upper 4bits, Lower 4bits)
- OCR Result Length is always 20

**Example:** OCR RESULT : CG03432394

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 31 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 07 | 04 | 03 | 04 | 07 | 03 | 00 |
|  |  |  |  |  |  |  |  |  |  |  | C (0x43) |  | G (0x47) |  | 0 (0x30) |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 03 | 03 | 03 | 04 | 03 | 03 | 03 | 02 | 03 | 03 | 03 | 09 | 03 | 04 | 00 | 00 |
| 3 (0x33) |  | 4 (0x34) |  | 3 (0x33) |  | 2 (0x32) |  | 3 (0x33) |  | 9 (0x39) |  | 4 (0x34) |  |  |  |

| 33 | 33 | 35 | 36 | 37 | 38 | 39 | 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 |

| 49 | 50 | 51 | 52 |
|---|---|---|---|
| 00 | 00 | 09 | 0D |

### 6. SubCommand = 35 (h) — RESULT_REQUEST — `SB Series <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 05 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 35 (h) = SubCommand
- **Data[1]** · 0x01 · Setup status Data Request
    - 0x02 · Counting Result Request
    - 0x04 · Error State Request
    - 0x08 · Resending Request
    - 0x10 · Sensor & Stacker/Hopper status Request
    - 0x20 · device status2 data Reqest
    - 0x40 · Tthis bit is used for other command (optional function)
    - 0x80 · counting report Request · -> only for SB-9
    - 0x12 · Setup status Data2 Request · '-> only for MIB-11

**Example:**

- RESULT_REQUEST:Setup status data request

```
F0  F1  0B  19  02  00  00  00  00  03  05  00  01  02  0F
```

- RESULT_REQUEST:Counting result request

```
F0  F1  0B  19  02  00  00  00  00  03  05  00  02  03  00
```

- RESULT_REQUEST:Error state request

```
F0  F1  0B  19  02  00  00  00  00  03  05  00  04  03  02
```

- RESULT_REQUEST:Sensor & Stacker/Hopper status Request

```
F0  F1  0B  19  02  00  00  00  00  03  05  01  00  02  0F
```

- RESULT_REQUEST:counting report Request

```
F0  F1  0B  19  02  00  00  00  00  03  05  08  00  03  06
```

### 7. SubCommand = 36 (h) — RESULT_CLEAR — `SB Series <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 06 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 36 (h) = SubCommand
- **Data[1]** · 0x01 · Reject Pocket Clear
    - 0x02 · Stacker Pocket Clear
    - 0x04 · Total Clear
    - 0x08 · Mixed mode grand total clear
    - 0x10 · Single mode Grand Total clear
    - 0x20 · JAM Clear
    - 0x40 · Reserved
    - 0x80 · counting report Clear · -> only for SB-9

**Example:**

- RESULT_CLEAR: reject pocket No. clear

```
F0  F1  0B  19  02  00  00  00  00  03  06  00  01  03  00
```

- RESULT_CLEAR: Total clear

```
F0  F1  0B  19  02  00  00  00  00  03  06  00  04  03  03
```

- RESULT_CLEAR: Single mode Grand total clear

```
F0  F1  0B  19  02  00  00  00  00  03  06  01  00  03  00
```

- RESULT_CLEAR:counting report Clear

```
F0  F1  0B  19  02  00  00  00  00  03  06  08  00  03  07
```

### 8. SubCommand = 37 (h) — START_STOP — `SB Series <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 07 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 37 (h) = SubCommand
- **Data[1]** · Bit 0 · Start ON
    - Bit 1 · Stop · --> NOT IMPLEMENT
    - : only 1 bit can be set at the same time

**Example:**

- START_STOP:start ON

```
F0  F1  0B  19  02  00  00  00  00  03  07  00  01  03  01
```

### 9. SubCommand = 38 (h) — DEVICE_SETUP2 — `SB Series <---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 08 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 38 (h) = SubCommand
- **Data[1]** · device setup bits · PC read/write
    - Bit 0 · 1 byte counting data Tx during counting ENABLE/DISABLE
    - 1 = enable · 0 = disable
    - Bit 1 · Lock Keypad · 1 = Lock · 0 = Release
    - Bit 2~7 · reserved

**Example:**

- DEVICE_SETUP2: 1byte counting data Tx during counting -> Enable

```
F0  F1  0B  19  02  00  00  00  00  03  08  00  01  03  02
```

- DEVICE_SETUP2: 1byte counting data Tx during counting -> Disable

```
F0  F1  0B  19  02  00  00  00  00  03  08  00  00  03  01
```

### 10. SubCommand = 39 (h) — DEFAULT_LOADING — `SB Series <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 09 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 39 (h) = SubCommand
- **Data[1]** · Bit 0 · default loading · (always 1)

**Example:**

- DEFAULT_LOADING: default loading

```
F0  F1  0B  19  02  00  00  00  00  03  09  00  01  03  03
```

### 11. SubCommand = 3A (h) — CURRENCY_CHANGE — `SB Series <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 0A | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 3A (h) = SubCommand
- **Data[1]** · Bit 0 · Currency change · (always 1)

**Example:**

- CURRENCY_CHANGE: change

```
F0  F1  0B  19  02  00  00  00  00  03  0A  00  01  03  04
```

### 12. SubCommand = 3B (h) — SETUP_NO_ACCEPT — `SB Series ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 0B | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 3B (h) = SubCommand
- **Data[1]** · Bit 0 · Setup Data no accepted, because of Menu active: (always 1)

**Example:**

- SETUP_NO_ACCEPT

```
F0  F1  0B  19  02  00  00  00  00  03  0B  00  01  03  05
```

### 13. SubCommand = 3D (h) — COUNT_STOP — `SB Series ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 0D | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 3D (h) = SubCommand
- **Data[1]** · Bit 0 · Count Stop · (always 1)

**Example:**

- COUNT_STOP

```
F0  F1  0B  19  02  00  00  00  00  03  0D  00  01  03  07
```

### 14. SubCommand = 3E (h) — SENSOR_STATUS — `SB Series ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 13 | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 0E | Sensor1 |  | Sensor2 |  | Stacker # |  |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 |
|---|---|---|---|---|---|
| Reject # |  | Error # |  | xx | xx |
| Data[4] |  | Data[5] |  | CheckSum |  |

- **Data[0]** · 3E (h) = SubCommand
- **Data[1]** · Sensor status 1 · PC read Only
    - Bit 0 · reserved
    - Bit 1 · Solenoid position · 1 = to Stacker · 0 = to Rejector
    - Bit 2 · RP1 Left · 1 = On (normal) · 0 = Off (JAM or Front cover opened)
    - Bit 3 · RP1 Right · 1 = On (normal) · 0 = Off (JAM or Front cover opened)
    - Bit 4 · reserved
    - Bit 5 · reserved
    - Bit 6 · JP Left · 1 = On (normal) · 0 = Off (JAM or Front cover opened)
    - Bit 7 · JP Right · 1 = On (normal) · 0 = Off (JAM or Front cover opened)
- **Data[2]** · Sensor status 2 · PC read Only
    - Bit 0 · SP Left · 1 = On (normal) · 0 = Off (JAM or Rear cover opened)
    - Bit 1 · SP Right · 1 = On (normal) · 0 = Off (JAM or Rear cover opened)
    - Bit 2 · Stacker · 1 = On (empty) · 0 = Off (there is note on stacker pocket)
    - Bit 3 · Rejecter F · 1 = On (empty) · 0 = Off (there is note on reject pocket)
    - Bit 4 · Front cover · 1 = Opened · 0 = Closed
    - Bit 5 · Rear cover · 1 = Opened · 0 = Closed
    - Bit 6 · Rejecter R · 1 = On (empty) · 0 = Off (there is note on reject pocket)
    - Bit 7 · Hopper · 1 = bank notes · 0 = no bank note on hopper
- **Data[3]** · reserved
- **Data[4]** · reserved
- **Data[5]** · Error status
    - 0 = no error · 1 = jam1 error
    - 2 · jam2 error · 3 · jam3 error
    - 4 · jam4 error · 5 · feeding error
    - 6 · front cover open error · 7 · rear cover open error
    - 9 · main motor error

**Example:**

- SENSOR_STATUS:

```
F0  F1  13  19  02  00  00  00  00  03  0E  0F  0F  08  03  00  02
01  0E  00  00  07  09
```

- -. 2 notes in stacker  &  20 notes in reject  &  there is/are note(s) on hopper

### 17. SubCommand = 41 (h) — SETUP_STATE_DATA2 — `SB Series <---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 1F | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 01 | Currency |  | Mode |  | B.Status 1 |  |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| B.Status 2 |  | M.Speed |  | Denom. |  | Pocket Cap. |  | B.Count# |  | UV level |  | MR level |  | IR level |  | xx | xx |
| Data[4] |  | Data[5] |  | Data[6] |  | Data[7] |  | Data[8] |  | Data[9] |  | Data[10] |  | Data[11] |  | CheckSum |  |

- **Data[0]** · 41 (h) = SubCommand
- **Data[1]** · Currency Code · PC Read/Write
    - 01 (h) = US Dollar · 02 (h) = Mexico Peso
    - 03 (h) = Korea Won · 04 (h) = Euro
    - 05 (h) = Colombia Peso · 06 (h) = China Yuan
    - 07 (h) = Turkey Lira · 08 (h) = Costarica Colone
    - 09 (h) = Nicaragua · 0A (h) = Australia
    - 0B (h) = Sigapore · 0C (h) = India
    - 0D (h) = Norway · 0E (h) = Newziland
    - 0F (h) = Poland · 10 (h) = Taiwan
    - 11 (h) = Czecho · 12 (h) = Lebanon
    - 13 (h) = Sweden · 14 (h) = Brasil
    - 15 (h) = Canada · 16 (h) = Syria
    - 17 (h) = Guatemala · 18 (h) = Iraq
    - 19 (h) = Israel · 1A (h) = Peru
    - 21 (h) = Japan · 22 (h) = Papua New Guinea
    - 23 (h) = Russia · 24 (h) = South Africa
    - 25 (h) = Arab Emirates · 26 (h) = Thailand
    - 27 (h) = England · 28 (h) = Venezuela
    - 29 (h) = BarCode · 2A (h) = Ukraine
    - 2B (h) = Kazakhstan · 2C (h) = Switzerland
    - 2D (h) = Saudi Arabia · 2E (h) = Jordan
    - 2F (h) = Kyrgyzstan · 30 (h) = Malaysia
    - 31 (h) = Malaysia cheque · 32 (h) = Indonesia
    - 33 (h) = Sudan · 34 (h) = Romania
    - 35 (h) = BeloRussia · 36 (h) = Azerbaijan
    - 37 (h) = Serbia · 38 (h) = Dominican
    - 39 (h) = Suriname · 3A (h) = Canada Tire
    - 3B (h) = Hungary · 3C (h) = Croatia
    - 3D (h) = Ghana · 3E (h) = Georgia
    - 3F (h) = Egypt · 40 (h) = Uganda
    - 41 (h) = Morocco · 42 (h) = Srilanka
    - 43 (h) = Armenia · 44 (h) = Namibia
    - 45 (h) = Honduras · 46 (h) = Kuwait
    - 47 (h) = Hongkong · 48 (h) = Ethiopia
    - 49 (h) = Piliphin · 4A (h) = Mongolia
    - 4B (h) = Iran · 4C (h) = Swaziland
    - 4D (h) = Botswana · 4E (h) = Qatar
    - 4D (h) = Scotland
- **Data[2]** · Counting mode · PC Read/Write
    - 00 (h) = COUNT mode · (piece count)
    - 01 (h) = MIXED mode
    - 02 (h) = SINGLE mode
    - 03 (h) = FACE mode
    - 04 (h) = ORIENT mode
    - 05 (h) = Serial No. Print Mode
    - 06 (h) = ISSUE mode
    - 07 (h) = DISPENSE mode
    - 08 (h) = OCR mode · MIB-11 only
    - 09 (h) = MIXED CURRENCY mode · MIB-11 only
- **Data[3]** · Basic Status · PC Read/Write
    - Bit0 · Batch On/Off · 1 = On · 0 = Off
    - Bit1 · reserved
    - Bit2 · warning beep enable · 1 = Enable · 0 = Disable
    - Bit3 · auto/manual · 1 = Auto · 0 = Manual
    - Bit4 · add on/off · 1 = On · 0 = Off
    - Bit5 · UV Detection On/Off · 1 = On · 0 = Off
    - Bit6 · MR Detection On/Off · 1 = On · 0 = Off
    - Bit7 · IR Detection On/Off · 1 = On · 0 = Off
- **Data[4]** · Basic Status · PC Read/Write
    - Bit0 · Mode Lock On/Off · 1 = On · 0 = Off
    - Bit7~Bit1 · reserved
- **Data[5]** · Motor Speed · PC read Only
    - Bit7~Bit4:
    - 0000 · 1000 rpm · MIB-11 · 800 rpm
    - 0001 · 1200 rpm · MIB-11 · 1000 rpm
    - 0010 · 1500 rpm · MIB-11 · 1200 rpm
    - 0011 · 600  rpm · MIB-9 only
    - 0100 · 800  rpm · MIB-9 only
    - 0101 · 900  rpm · MIB-9 only
- **Data[6]** · Denomination & Counting mode
    - Bit4~Bit0: Denomination · if count, Mixed, and Serial No. mode  -> PC Read Only
    - if single, Face, and Orient mode   -> PC Read/Write
    - 0000 0 · denomination value is least · (if US$ mode, $1)
    - 0000 1 · (if US$ mode, $2)
    - …
    - 0011 0 · (if US$ mode, $100)
    - 1111 0 · ALL mode
    - 1111 1 · DD mode
- **Data[7]** · Pocket Capacity · PC Read/Write
    - Bit7~Bit4: · Reject Pocket Capacity
    - 0000 · 30 PCS · MIB-11 · 100 PCS
    - 0001 · 20 PCS · MIB-11 · 70 PCS
    - 0010 · 10 PCS · MIB-11 · 50 PCS
    - Bit3~Bi0: · Stacker Pocket Capacity
    - 0000 · 200 PCS · MIB-11 · 250 PCS
    - 0001 · 150 PCS · MIB-11 · 200 PCS
    - 0010 · 100 PCS · MIB-11 · 100 PCS
- **Data[8]** · Batch Counter number · PC Read/Write
    - if Batch number > Stacker pocket -> stacker pocket number setting
    - ex) IFD Batch number = 210
    - Stacker pocket = 200 · Batch number set = 200
- **Data[9]** · UV Level · PC Read/Write
    - Bit2~Bit0: · UV Level setting (1 ~ 5) default:3
    - 001 · UV Level: 1
    - 010 · UV Level: 2
    - …
    - 101 · UV Level: 5
- **Data[10]** · MR Level · PC Read/Write
    - Bit2~Bit0: · MR Level setting (1 ~ 5) default:3
    - 001 · MR Level: 1
    - 010 · MR Level: 2
    - …
    - 101 · MR Level: 5
- **Data[9]** · IR Level · PC Read/Write
    - Bit2~Bit0: · IR Level setting (1 ~ 5) default:3
    - 001 · IR Level: 1
    - 010 · IR Level: 2
    - …
    - 101 · IR Level: 5

**Example:**

| | | | | | | | | | | | | | | | | | |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 1F | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 01 | 00 | 01 | 00 | 01 | 00 | 0C |  |
|  |  |  |  |  |  |  |  |  |  |  | Currency |  | Mode |  | B.Status1 |  |  |
| 00 | 00 | 00 | 00 | 01 | 0F | 00 | 00 | 06 | 04 | 00 | 03 | 00 | 03 | 00 | 03 | 07 | 02 |
| B.Status2 |  | M.Speed |  | Denom. |  | Pocket Cap. |  | B.Count# |  | UV level |  | MR level |  | IR level |  |  |  |

- **currenty = 01(h)      ->** · US dollar mode
- **count mode = F9 (h) ->** · MIXED mode
- **basic status =  0C(h) ->** · BATCH off · ADD off
    - warning beep enable · UV off
    - AUTO mode · MR off
    - IR off
- **basic status = 00(h) ->** · MODE LOCK off
- **motor speed = 00(h) ->** · 1000 rpm
- **Denomination = 1F(h) ->** · DD: meanles if COUNT, MIXED
- **Pocket Capacity = 00(h) ->** · Reject pocet : 30pcs · Stacker Pocket: 200pcs
- Batch Counter number = 64(h) = 100
- **UV Level = 03(h) ->** · Level 3: default value
- **MR Level = 03(h) ->** · Level 3: default value
- **IR Level = 03(h) ->** · Level 3: default value

### 19. SubCommand = 43 (h) — COUNTING_REPORT_DATA — `SB9 ---> IFD(PC)`

    - (Optional)

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 15 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 03 | MSB_SC |  | LSB_SC |  | 00 | 00 |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 |
|---|---|---|---|---|---|---|---|
| MSB_RC |  | LSB_RC |  | 00 | 00 | xx | xx |
| Data[4] |  | Data[5] |  | Data[6] |  | CheckSum |  |

- **Data[0]** · 43 (h) = SubCommand
- **Data[1]** · XX (h) · MSB_SC · Total of the Count in Stacker ( MSB )
- **Data[2]** · XX (h) · LSB_SC · Total of the Count in Reject ( LSB )
- **Data[3]** · 00 (h) = R · reserved
- **Data[4]** · XX (h) · MSB_RC · Total of the Count in Reject ( MSB )
- **Data[5]** · XX (h) · LSB_RC · Total of the Count in Reject ( LSB )
- **Data[6]** · 00 (h) = R · reserved

**Example:** Total of the Count in Stacker: 531 pcs. -> 213 (h)

    - Total of the Count in Reject: 124 pcs.-> 7C (h)

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 15 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 03 | 00 | 02 | 01 | 03 | 00 | 00 |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |
|  |  |  |  |  |  |  |  |  |  |  | MSB_SC |  | LSB_SC |  | R | R |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 |
|---|---|---|---|---|---|---|---|
| 00 | 00 | 07 | 0C | 00 | 00 | 05 | 00 |
| Data[3] |  | Data[4] |  | Data[5] |  | CheckSum |  |
| MSB_RC |  | LSB_RC |  | R | R |  |  |

### 20. SubCommand = 44 (h) — SAVE_BMP_TO_USB — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 04 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 44 (h) = SubCommand
- **Data[1]** · Bit 0 · USB · 1: ON (save) · 0: OFF (do not save)

**Example:**

- SAVE_BMP_TO_USB:  ON ( Save to USB )

```
F0  F1  0B  19  02  00  00  00  00  04  04  00  01  02  0F
```

- SAVE_BMP_TO_USB:  OFF (do not save)

```
F0  F1  0B  19  02  00  00  00  00  04  04  00  00  02  0E
```

### 21. SubCommand = 45 (h) — MC_STATUS — `SB Series ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 05 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 45 (h) = SubCommand
- **Data[1]** · Bit 0 · Hopper clear
    - Bit 1 · Stacker Check · -> Should send "RESULT_CLEAR (36(h))-JAM Clear(0x02)"
    - Bit 2 · Rejector Check · -> Should send "RESULT_CLEAR (36(h))-JAM Clear(0x02)"
    - Bit 3 · Rev.1
    - Bit 4 · Rev.2
    - Bit 5 · Rev.3

**Example:**

- DEFAULT_LOADING: default loading

```
F0  F1  0B  19  02  00  00  00  00  04  04  00  01  02  0F
```

### 22. SubCommand = 46 (h) — SW_VER — `SB Series <---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 15 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 06 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  |
|  |  |  |  |  |  |  |  |  |  |  | MSB |  | LSB |  |

| 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 |
|---|---|---|---|---|---|---|---|---|---|
| xx | xx | xx | xx | 00 | 00 | 00 | 00 | xx | xx |
| Data[3] |  | Data[4] |  | Data[5] |  | Data[6] |  | CheckSum |  |
| MSB |  | LSB |  | Rsv. |  | Rsv. |  |  |  |

- Chksum
- **Data[0]** · 46 (h) = SubCommand
- **Data[1]** · MSB · Upper version
- **Data[2]** · LSB · Lower version
- **Data[3] ~[6]** · Reserved

**Example:**

- Response software version(When version is 10.15)

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 15 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 06 | 01 | 00 | 01 | 05 |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  |

| 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 |
|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 04 | 01 |
| Data[3] |  | Data[4] |  | Data[5] |  | Data[6] |  | CheckSum |  |

### 24. SubCommand = 48 (h) — IFD_WING_MOTOR — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 08 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 48 (h) = SubCommand
- **Data[1]** · 0 or 1 · 0 = Stop Wing Motor,   1= Start Wing Motor

### 25. SubCommand = 49 (h) — IFD_REJECT_DESIGNATED_NOTE — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 1D | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 09 | xx | xx | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 33 | 34 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx |
| Data[4] |  | Data[5] |  | Data[6] |  | Data[7] |  | Data[8] |  | Data[9] |  | Data[10] |  | CheckSum |  |

- **Data[0]** · 49 (h) = SubCommand
- **Data[1] ~[10]** · Ref. · designate the notes to reject
    - each bit val :1 reject,  0: not reject

**Example:**

- ***  reject 2 & 5 on BRL mode** · (Refer. Sheet 'Ref.') · _1__BRL · _1__BRL

```
F0  F1  1D  19  02  00  00  00  00  04  09  0C  03  00  00  00  00
00  00  00  00  00  00  00  00  00  00  00  00  00  00  05  04
```

### 26. SubCommand = 4A (h) — SETUP_MAINTENANCE_ALARM — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 15 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 0A | xx | xx | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 |
|---|---|---|---|---|---|---|---|
| xx | xx | xx | xx | xx | xx | xx | xx |
| Data[4] |  | Data[5] |  | Data[6] |  | CheckSum |  |

- **Data[0]** · 4A (h) = SubCommand
- **Data[1]** · Bit 0 · maintenance alarm
    - each bit val :1 alarm on,  0: alarm off
    - Bit 1 · request maintenance alarm(If set to 1, other values do not matter.)
    - each bit val :1 request alarm
- **Data[2] ~ [5]** · [5][4][3][2] · 32bit value data
    - if value is 1000000, [5]=0, [4]=0x0f, [3]=0x42, [2]=0x40
- **Data[6]** · reserved

**Example:**

- ***  alarm on and set 1,000,000** · (Refer. Sheet 'Ref.') · _1__BRL · _1__BRL

```
F0  F1  15  19  02  00  00  00  00  04  0A  00  01  04  00  04  02
00  0f  00  00  00  00  05  08
```

- ***  request alarm** · (Refer. Sheet 'Ref.') · _1__BRL · _1__BRL

```
F0  F1  15  19  02  00  00  00  00  04  0A  00  02  04  00  04  02
00  0f  00  00  00  00  05  09
```

### 27. SubCommand = 4C (h) — REQUEST_IFD_COUNT_LOG_DATA — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 15 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 0C | 00 | 01 | 03 | 04 |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  |

| 15 | 16 | 17 | 18 | 23 | 24 |
|---|---|---|---|---|---|
| 0B | 04 | 03 | 09 | xx | xx |
| Data[3] |  | Data[4] |  | CheckSum |  |

- **Data[0]** · 4C (h) = SubCommand
- **Data[1]~Data[2]** · Year(2023)
- **Data[3]** · Month(12)
- **Data[4]** · Day(25)
- **Data[1]~Data[4]** · 20231225(0x01 34 B4 39)

**Example:**

- Response Request ifd count log data
- SubCommand 4D SEND_IFD_COUNT_LOG_DATA

### 28. SubCommand = 4D (h) — SEND_IFD_COUNT_LOG_DATA — `SB9 ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 2B | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 0D |  |  |  |  |  |  |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |
|  |  | … |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  |  | … | … |  |  |  |  | … | … |  |  |  |  | xx | xx |  |
| Data[4] |  | … |  |  |  |  |  |  |  | Data[16] |  | Data[17] |  | CheckSum |  |  |

- response

- **Data[0]** · 4D (h) = SubCommand
- **Data[1]~Data[5]** · Reference No. 000012345678 -> (0x00 00BC 614E)
- **Data[6]~Data[11]** · YYYYMMDDHHmmSS    20230825131220 -> (0x1226 5B25 3CD4)
- **Data[12]~Data[15]** · Amount 50000 -> (0x0000 C350)
- **Data[16]** · Currency number YTL: 7 (reference gpaCurrencyCode include sample sw)

- **Data[17]** · Mode code (Upper 4bits, Lower 4bits)
    - 0 = piece count mode
    - 1 = count(mixed mode)
    - 2 = count(single mode)
    - 3 = face mode
    - 4 = orient mode
    - 5 = issue mode
    - 8 = ocr mode
    - 9 = mixed currency mode

- **Data[18]** · Number of denominations counted.
    - 3 = YTL10 1, YTL 50 20, YTL 200 15

- **Data[19]~Data[22]** · First denomination counted
- **Data[23]~Data[24]** · count
- **Data[25]~Data[28]** · Second denomination counted
- **Data[29]~Data[30]** · count

- **Data[19+n*6]~Data[22+n*6]** · n th denomination counted
- **Data[23+n*6]~Data[24+n*6]** · count

**Example:** 000012345678 2023-08-25 13:12:20 2000 YTL SINGLE 03 10 10 100 9 200 5

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 2B | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 0D | 00 | 00 | 00 | 00 | 0B | 0C |
|  |  |  |  |  |  |  |  |  |  |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 06 | 01 | 04 | 0E | 01 | 02 | 02 | 06 | 05 | 0B | 02 | 05 | 03 | 0C | 0D | 04 |
| Data[4] |  | Data[5] |  | Data[6] |  | Data[7] |  | Data[8] |  | Data[9] |  | Data[10] |  | Data[11] |  |

| 33 | 34 | 35 | 36 | 37 | 38 | 39 | 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 00 | 0c | 03 | 05 | 00 | 00 | 07 | 00 | 02 | 00 | 03 | 00 | 00 |
| Data[12] |  | Data[13] |  | Data[14] |  | Data[15] |  | Data[16] |  | Data[17] |  | Data[18] |  | Data[19] |  |

| 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 | 60 | 61 | 62 | 63 | 64 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 00 | 00 | 0A | 00 | 00 | 00 | 0A | 00 | 00 | 00 | 00 | 00 | 00 |
| Data[20] |  | Data[21] |  | Data[22] |  | Data[23] |  | Data[24] |  | Data[25] |  | Data[26] |  | Data[27] |  |

| 65 | 66 | 67 | 68 | 69 | 70 | 71 | 72 | 73 | 74 | 75 | 76 | 77 | 78 | 79 | 80 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 64 | 00 | 00 | 00 | 09 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | C8 | 00 | 00 |
| Data[28] |  | Data[29] |  | Data[30] |  | Data[31] |  | Data[32] |  | Data[33] |  | Data[34] |  | Data[35] |  |

| 81 | 82 | 83 | 84 |
|---|---|---|---|
| 00 | 05 | xx | xx |
| Data[36] |  | CheckSum |  |

### 29. SubCommand = 4E (h) — SEND_IFD_REF_NUMBER — `SB Series <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 15 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 0E | 01 | 0C | 0B | 0E |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  |

    - MSB

| 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 |
|---|---|---|---|---|---|---|---|
| 09 | 09 | 01 | 0A | 08 | 03 | xx | xx |
| Data[3] |  | Data[4] |  | Data[5] |  | CheckSum |  |

- **Data[0]** · 4E (h) = SubCommand
- **Data[1]~Data[5]** · MSB~LSB · 123456789123(0x1C BE 99 1A 83)

### 30. SubCommand = 4F (h) — RESULT_DATA2 — `SB Series ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | xx | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 0F | Cur.Code |  | N.of.R.P |  | N.of.O.S |  |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | … |  | 2N+17 | 2N+18 | 2N+19 | 2N+20 |  |  | 6N+11 | 6N+12 | 6N+13 | 6N+14 | 6N+15 | 6N+16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| N.of.D0 |  | … | … | Pre.N.of.D0 |  |  |  | … | … | Pre.N.of.D(N-1) |  |  |  | xx | xx |
| Data[4] |  | … |  | Data[N+4] |  | Data[N+5] |  |  |  | Data[3N+4] |  | Data[3N+5] |  | CheckSum |  |

- **Data[0]** · 34 (h) = SubCommand
- **Data[1]** · Currency code
- **Data[2]** · number of notes in the Reject Pocket
- **Data[3]** · number of notes in the output Stacker
- **Data[4]** · number of notes of Denom.0(if US$ mode, $1) in the output stacker
- …
- **Data[N+2]** · number of notes of Denom. N-1 (if US$ mode, $100) in the output stacker
- **Data[N+3]** · Previous number of notes of Denom.0 (Upper Byte) in ADD mode
- **Data[N+4]** · Previous number of notes of Denom.0 (Lower Byte) in ADD mode
- …
- **Data[3N+2]** · Previous number of notes of Denom. N-1 (Upper Byte) in ADD mode
- **Data[3N+3]** · Previous number of notes of Denom. N-1 (Lower Byte) in ADD mode
- note) N: Denom number
    - -> if US$ mode, N=7 ($1, $2, $5, $10, $20, $50, $100)
    - Denom = · 0 · -> · 1 · 3 · -> · $10
    - 1 · -> · 2 · 4 · -> · $20
    - 2 · -> · 5 · 5 · -> · $50
    - 6 · -> · $100
    - -> if EURO mode, N=7(€5, €10, €20, €50, €100, €200, €500)

**Example:** when US$ mode,,

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 39 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 0F | 00 | 01 | 00 | 03 | 00 | 00 |
|  |  |  |  |  |  |  |  |  |  |  | Cur.Code |  | n.of.R.P |  | n.of.O.S |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 00 | 00 | 01 | 00 | 00 | 00 | 02 | 00 | 00 | 00 | 00 |
| D0 ($1) |  | D1 ($2) |  | D2 ($5) |  | D3 ($10) |  | D4($20) |  | D5($50) |  | D6($100) |  |

| 29 | 30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 40 | 41 | 42 | 43 | 44 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 02 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 01 | 00 | 00 | 00 | 01 |

- **pre. D0 ($1)** · pre. D1 ($2) · pre. D2 ($5) · pre. D3 ($10)

| 45 | 46 | 47 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 00 | 00 | 00 | 01 | 00 | 00 | 00 | 02 | 00 | 00 | 00 | 01 | 06 | 07 |

- **pre. D4 ($20)** · pre. D5 ($50) · pre. D6 ($100) · CheckSum

- **Currency code** · 1 · (USD)
- number of notes of Reject Pocket · 0
- number of note of Output Stacker · 3
- **current count value** · $1: · 0 · $2: · 0 · $5: · 1
    - $10: · 0 · $20: · 2 · $50: · 0
    - $100: · 0
- previos count value in ADD mode · $1: · 2 · $2: · 0 · $5: · 1
    - $10: · 1 · $20: · 1 · $50: · 2
    - $100: · 1

### 31. SubCommand = A8 (h) — REBOOT — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 0A | 08 | 00 | 01 | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 32 (h) = SubCommand
- **Data[1]** · Bit 0 · Reboot machine : 0x01

### 32. SubCommand = 63 (h) — SETUP_STATE_DATA_EX — `SB9 <---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 57 | 19 | 02 | 00 | 00 | 00 | 00 | 06 | 03 | Currency |  | Mode |  | B.Status 1 |  |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| B.Status 2 |  | B.Status 3 |  | Pocket Cap1 |  |  |  | Pocket Cap3 |  | UV level |  | MR level |  | IR level |  |
| Data[4] |  | Data[5] |  | Data[6] |  | Data[7] |  | Data[8] |  | Data[9] |  | Data[10] |  | Data[11] |  |

| 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 40 | 41 | 42 | 43 | 44 | 45 | 46 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Batch Type |  | Batch Cnt(4Byte) |  |  |  |  |  |  |  | 00 |  | REV. |  | REV. |  |
| Data[12] |  | Data[13] |  | Data[14] |  | Data[15] |  | Data[16] |  | Data[17] |  | Data[18] |  | Data[19] |  |

| 47 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 |
|---|---|---|---|---|---|---|---|---|---|

- REV.
- **Data[20]** · Data[21] · Data[22] · Data[23] · Data[24]

| 57 | 58 | 59 | 60 | 61 | 62 | 63 | 64 | 65 | 66 |
|---|---|---|---|---|---|---|---|---|---|

- REV.
- **Data[25]** · Data[26] · Data[27] · Data[28] · Data[29]

| 67 | 68 | 69 | 70 | 71 | 72 | 73 | 74 | 75 | 76 |
|---|---|---|---|---|---|---|---|---|---|

- REV.
- **Data[30]** · Data[31] · Data[32] · Data[33] · Data[34]

| 77 | 78 | 79 | 80 | 81 | 82 | 83 | 84 | 85 | 86 |
|---|---|---|---|---|---|---|---|---|---|

- **REV.** · xx · xx
- **Data[35]** · Data[36] · Data[37] · Data[38] · Data[39] · CheckSum

- **Data[0]** · 63 (h) = SubCommand
- **Data[1]** · Currency Code · PC Read/Write
    - 01 (h) = US Dollar · 02 (h) = Mexico Peso
    - 03 (h) = Korea Won · 04 (h) = Euro
    - 05 (h) = Colombia Peso · 06 (h) = China YUAN
    - 07 (h) = Turkey Lira · 08 (h) = Costa Rica
    - 09 (h) = Nicaraqua · 0A (h) = Australia
    - 0B (h) = Singapore · 0C (h) = India
    - 0D (h) = Norway · 0E (h) = Newziland
    - 0F (h) = Poland · 10 (h) = Taiwan
    - 11 (h) = Czecho · 12 (h) = Lebanon
    - 13 (h) = Sweden · 14 (h) = Brasil
    - 15 (h) = Canada · 16 (h) = Syria
    - 17 (h) = Guatemala · 18 (h) = Iraq
    - 19 (h) = Israel · 1A (h) = Peru
    - 1B (h) = Coupon 1 · 1C (h) = Coupon 2
    - 1D (h) = Coupon 3 · 1E (h) = Coupon 4
    - 1F (h) = Coupon 5 · 20 (h) = Coupon 6
    - 21 (h) = Japan · 22 (h) = Papua New Guinea
    - 23 (h) = Russia · 24 (h) = South Africa
    - 25 (h) = Arab Emirates · 26 (h) = Thailand
    - 27 (h) = England · 28 (h) = Venezuela
    - 29 (h) = Barcode · 2A (h) = Ukraine
    - 2B (h) = Kazakhstan · 2C (h) = Switzerlnad
    - 2D (h) = Saudi Arabia · 2E (h) = Jordan
    - 2F (h) = Kyrgyzstan · 30 (h) = Malaysia
    - 31 (h) = Malaysia cheque · 32 (h) = Indonesia
    - 33 (h) = Sudan · 34 (h) = Romania
    - 35 (h) = Belarus · 36 (h) = Azerbaijani
    - 37 (h) = Serbia · 38 (h) = Dominica
    - 39 (h) = Suriname · 3A (h) = Canada
    - 3B (h) = Hungary · 3C (h) = Croatia
    - 3D (h) = Ghana · 3E (h) = Georgia
    - 3F (h) = EGYPT · 40 (h) = UGANDA
    - 41 (h) = MOROCCO · 42 (h) = SriLanka
    - 43 (h) = ARMENIA · 44 (h) = Namibia
    - 45 (h) = Honduras · 46 (h) = Kuwait
    - 47 (h) = HongKong · 48 (h) = Ethiopia
    - 49 (h) = Philiphin · 4A (h) = Mongol
    - 4B (h) = IRAN · 4C (h) = SWAZILAND
    - 4D (h) = BOTSWANA · 4E (h) = QATAR
    - 4F (h) = SCOTLAND · 50 (h) = Angola
    - 51 (h) = MOZAMBIQUE · 52 (h) = OMAN
    - 53 (h) = YEMEN · 54 (h) = BULGARIA
    - 55 (h) = Pakistan · 56 (h) = Coupon
    - 57 (h) = Libya · 58 (h) = Nigeria
    - 59 (h) = Lesotho · 5A (h) = Bahrain
    - 5B (h) = Taiwan · 5C (h) = (ZAR+NAD)=ZAD
    - 5D (h) = Zambia · 5E (h) = Austria
    - 5F (h) = Chile · 60 (h) = Algeria
    - 61 (h) = Denmark · 62 (h) = new caledonia
    - 63 (h) = Macao · 64 (h) = Macedonia
    - 65 (h) = Fiji · 66 (h) = Bosnia and Herzegovina
    - 67 (h) = Vietram · 68 (h) = Kenya
    - 69 (h) = West African States · 6A (h) = Laos
    - 6B (h) = Myanma · 6C (h) = Bangladesh
    - 6D (h) = Cuba · 6E (h) = Moldova
    - 6F (h) = Scotland · 70 (h) = Ireland
    - 71 (h) = Central African States · 72 (h) = CANADA Coupon
    - 73 (h) = Argentina · 74 (h) = (GBP+IRP+SCP)= GIS
    - 75 (h) = Belarus · 76 (h) = Nepal
    - 77 (h) = Iraq · 78 (h) = Tanzania
    - 79 (h) = RWANDA · 7A (h) = Burundi
    - 7B (h) = ZIMBABWE · 7C (h) = Swiss check
    - 7D (h) = Albania · 7E (h) = Mauritius
    - 7F (h) = Tajikistan · 80 (h) = Cabo Verde
    - 81 (h) = Djibouti · 82 (h) = Venezuela
    - 83 (h) = Lebanon check · 84 (h) = Turkey check
    - 85 (h) = Jamaican · 86 (h) = Uzbekistan
    - 87 (h) = Syria check · 88 (h) = Congo
    - 89 (h) = korea coupon · 8A (h) = CAMBODIA
    - 8B (h) = Zimbabwe · 8C (h) = Brunei
    - 8D (h) = Test currency · 8E (h) = Test currency
    - 8F (h) = korea coupon · 90 (h) = korea coupon
    - 91 (h) = korea coupon · 92 (h) = korea coupon
    - 93 (h) = korea coupon · 94 (h) = korea coupon
    - 95 (h) = korea coupon · 96 (h) = korea coupon
    - 97 (h) = Paraguay · 98 (h) = Gambia
- **Data[2]** · Counting mode · PC Read/Write
    - 00 (h) = Rev.
    - 01 (h) = FACE mode
    - 02 (h) = ORIENT mode
    - 03 (h) = FITNESS mode
    - 04 (h) = PIECE COUNT mode
    - 05 (h) = MIXED mode
    - 06 (h) = SINGLE mode
    - 07 (h) = Rev.
    - 08 (h) = Rev.
    - 09 (h) = Rev.

> **Nota lateral (columna derecha de la hoja):**
> - Profis MIB11 · Counting mode
> - 00 (h) = PIECE Count mode
> - 01 (h) = COUNT mode
> - 02 (h) = COUNT SINGLE mode
> - 03 (h) = FACE mode
> - 04 (h) = ORIENT mode
> - 05 (h) = Rev.
> - 06 (h) = ISSUE mode
> - 07 (h) = Rev.
> - 08 (h) = OCR mode
> - 09 (h) = MIXED CURR. Mode

- **Data[3]** · Basic Status1 · PC Read/Write
    - Bit0 · key beep enable · 1 = Enable · 0 = Disable
    - Bit1 · warning beep enable · 1 = Enable · 0 = Disable
    - Bit2 · auto/manual · 1 = Auto · 0 = Manual
    - Bit3 · Rev.
    - Bit4 · add on/off · 1 = On · 0 = Off
    - Bit5 · UV Detection On/Off · 1 = On · 0 = Off
    - Bit6 · MR Detection On/Off · 1 = On · 0 = Off
    - Bit7 · IR Detection On/Off · 1 = On · 0 = Off
- **Data[4]** · Reserved
- **Data[5]** · Reserved
- **Data[6]** · Pocket Capacity1 · PC Read/Write
    - Bit5~Bit4: · Reject Pocket Capacity
    - 0000 · 100 PCS
    - 0001 · 70 PCS
    - 0010 · 50 PCS
    - Bit3~Bit2: · Rev.
    - 0000 · Rev.
    - 0000 · Rev.
    - 0000 · Rev.
    - Bit1~Bit0: · Stacker1 Pocket Capacity
    - 0000 · 200 PCS
    - 0001 · 150 PCS
    - 0010 · 100 PCS
- **Data[7]** · Reserved
- **Data[8]** · Reserved
- **Data[9]** · UV Level · PC Read/Write
    - Bit3~Bit0: · UV Level setting (1 ~ 15) default:9
    - 0001 · UV Level: 1
    - 0010 · UV Level: 2
    - …
    - 1111 · UV Level: 15
- **Data[10]** · MR Level · PC Read/Write
    - Bit3~Bit0: · MR Level setting (1 ~ 15) default:5
    - 0001 · MR Level: 1
    - 0010 · MR Level: 2
    - …
    - 1111 · MR Level: 15
- **Data[11]** · IR Level · PC Read/Write
    - Bit3~Bit0: · IR Level setting (1 ~ 15) default:9
    - 0001 · IR Level: 1
    - 0010 · IR Level: 2
    - …
    - 1111 · IR Level: 15
- **Data[12]** · Batch Type · PC Read/Write
    - 00 (h) = Batch Off
    - 01 (h) = Stacker1 and Stacker2 Count Set
    - 02 (h) = Total Amount
- **Data[13]** · Batch Counter number · PC Read/Write
- **Data[14]** · if Batch Type -> Batch Off(00h)
- **Data[15]** · Data[13] = 0
- **Data[16]** · Data[14] = 0
    - **Data[15] = 0**
    - **Data[16] = 0**
    - if Batch Type -> Stacker1 and Stacker2 Count Set(01h)
    - **Data[13] = 0** · Min:1 · Max:200
    - **Data[14] = 0** · Min:1 · Max:200
    - **Data[15] = 0**
    - **Data[16] = 0**
    - if Batch Type -> Total Amount(02h)
    - **Data[13] = 0** · Min:1 · Max:4000000000 · Bit31~Bit24 · (MSB)
    - **Data[14] = 0** · Bit23~Bit16
    - **Data[15] = 0** · Bit15~Bit8
    - **Data[16] = 0** · Bit7~Bit0 · (LSB)
- **Data[17]** · Reserved
- ~
- **Data[39]**

**Example:**

| | | | | | | | | | | | | | | | | |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 57 | 19 | 02 | 00 | 00 | 00 | 00 | 06 | 03 | 02 | 03 | 00 | 01 | 0e | 0f |
|  |  |  |  |  |  |  |  |  |  |  | Currency |  | Mode |  | B.Status1 |  |
| 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 09 | 00 | 05 | 00 | 09 |  |
| B.Status2 |  | Rev. |  | Stacker Recject |  | Rev. |  | Rev. |  | UV level |  | MR level |  | IR level |  |  |
| 00 | 01 | 06 | 04 | 06 | 04 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 |  |
| Batch Type |  | Batch Count or Batch Amount |  |  |  |  |  |  |  | Reserved |  | Rev. |  | Rev. |  |  |
| 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 |  |  |  |  |  |  |  |

- Rev.

```
00  00  00  00  00  00  00  00  00  00
00  00  00  00  00  00  00  00  00  00
```

- Rev.

```
00  00  00  00  00  00  00  00  00  00  xx  xx
```

    - check sum
- **currency =23(h)      ->** · RUR currency
- **count mode =01 (h) ->** · COUNT mode
- **basic status1 =  E7(h) ->** · 00000001 · key beep enable · 00010000 · Rev.
    - 00000010 · warning beep enable · 00100000 · UV on
    - 00000100 · AUTO mode · 01000000 · MR on
    - 00001000 · Rev. · 10000000 · IR on
- **Stacker, Reject = 00(h)** · Reject pocet : 100pcs · Stacker: 200pcs
- **UV Level = 09(h) ->** · Level 9: default value
- **MR Level = 05(h) ->** · Level 5: default value
- **IR Level = 09(h) ->** · Level 9: default value
- Batch Type = Stacker1 and Stacker2 Count Set -> 01(h)
- Batch Counter number = 64640000(h) = Stacker1 100, Stacker2 100

### 33. SubCommand = 53 (h) — SETUP_MAINTENANCE_DATE_TIME — `SB Series <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 17 | 19 | 02 | 00 | 00 | 00 | 00 | 05 | 03 | xx | xx | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx |
| Data[4] |  | Data[5] |  | Data[6] |  | Data[7] |  | Data[8] |  | CheckSum |  |

- **Data[0]** · 53 (h) = SubCommand
- **Data[1]~[4]** · [4][3][2][1] · 32bit value data(Date value)
    - if value is 20240815(2024.08.15),
    - [4]=0x1, [3]=0x34, [2]=0xD9, [1]=0xAF

- **Data[5]~[7]** · [7][6][5] · 32bit value data(Time value)
    - if value is 153515(15:35:15), [7]=0x02, [6]=0x57, [5]=0xAB

- **Data[8]** · Set or request
    - if value is 0: Request, 1: Set

**Example:**

- * set date and time 2024.08.15  15:35:15

```
F0  F1  17  19  02  00  00  00  00  05  03  0A  0F  0D  09  03  04
00  01  0A  0B  05  07  00  02  00  01  09  05
```

- * request date and time

```
F0  F1  17  19  02  00  00  00  00  05  03  XX  XX  XX  XX  XX  XX
XX  XX  XX  XX  XX  XX  XX  XX  00  00  XX  XX
```

### 99. 1BYTE_COUNT_DATA during counting — SB Series <---> IFD(PC)

    - 0 ~ (N-1) · Denom. Value · eg) when US$ mode, · N = 7
    - 0=$1, 1=$2, 2=$5, 3=$10
    - 4=$20, 5=$50, 6=$100
    - eg) when EURO mode · N = 7
    - 0=€5, 1=€10, 2=€20, 3=€50
    - 4=€100, 5=€200, 6=€500
    - 20 (h) = SUSPECT (when bank note comes to Reject Pocket)
    - 71 (h) = STAY NOTE (when bank note comes to Reject Pocket in single mode)
    - 70 (h) = CF (counterfeit)

### Command Tx/Rx state block diagram

**(When state request)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_REQUEST(SubCommand=35h): :Setup status Data request (bit0 = 1) |
| SETUP_STATE_DATA(31h): | → |  |

**(When count result request) (non OCR MODE)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_REQUEST(SubCommand=35h): :counting result request (bit1 = 1) |
| RESULT_DATA(34h): | → |  |

**(When count result request) (OCR MODE)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_REQUEST(SubCommand=35h): :counting result request (bit1 = 1) |
| RESULT_DATA(34h): | → |  |
| OCR_RESULT(47h): Repeat Number of OCR Result | → |  |
| OCR_RESULT(47h): | → |  |

**(When error state request)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_REQUEST(SubCommand=35h): :Error state request (bit2 = 1) |
| CD_ERROR(33h): | → |  |

**(When sensor status state request)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_REQUEST(SubCommand=35h): :Sensor & Stacker/Hopper status Request |
| SENSOR_STATUS(3Eh): (bit4 = 1) | → |  |

**(When device status 2 request)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_REQUEST(SubCommand=35h): :device status2 Request |
| DEVICE_SETUP2(38h): (bit5 = 1) | → |  |

**(When PC turn ON)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SET_LIVE(SubCommand=30h): :KNOCK (bit0 = 1) |
| DEVICE_SET_LIVE(30h): :ACK(bit1 = 1) | → |  |

**(When SB Series turn ON)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
| DEVICE_SET_LIVE(30h): :KNOCK (bit0 = 1) | → |  |
|  | ← | DEVICE_SET_LIVE(SubCommand=30h): :ACK(bit1 = 1) |

**(When PC Destroy)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SET_LIVE(SubCommand=30h): :RELEASE(bit2 = 1) |

**(to enable 'transmision of 1byte counting data' during couting)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SETUP2(SubCommand=38h): :1byte counting data Tx during counting(bit0 = 1) |

**(to lock Keypad of SB Series)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SETUP2(SubCommand=38h): :Lock keypad(bit1 = 1) |

**(to release Keypad of SB Series)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SETUP2(SubCommand=38h): :Lock keypad(bit1 = 0) |

**(Reject pocket clear)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_CLEAR(SubCommand=36h): :Reject pocket No. clear (bit0 = 1) |

**(Stacker pocket clear)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_CLEAR(SubCommand=36h): :Stacker pocket No. clear (bit1 = 1) |

**(Total clear)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_CLEAR(SubCommand=36h): :Total clear(bit2 = 1) |

**(Mixed mode grand total clear)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_CLEAR(SubCommand=36h): :Mixed mode grand total clear(bit3 = 1) |

**(JAM clear)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_CLEAR(SubCommand=36h): :JAM clear(bit5 = 1) |

**(Counting Report request)**

| SB9 |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_REQUEST(SubCommand=35h): :counting report Request (0x80) |
| COUNTING_REPORT_DATA(43h): | → |  |

**(Counting Report Clear)**

| SB9 |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_CLEAR(SubCommand=36h): :counting report Clear(0x40) |

**(to Save BMP to USB)**

| SB9 |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SETUP2(SubCommand=44h): : to USB ( 0x01) |

**(Bank note Counting)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | START_STOP(SubCommand=37h): :start on(bit0 = 1) |
| COUNT_START(32h): | → |  |
| 1BYTE_COUNT_DATA | → |  |
| Denom. Value | → |  |
| … … | → |  |
| 1BYTE_COUNT_DATA | → |  |
| 40(h):1BYTE_COUNT_DATA END | → |  |
| COUNT_STOP(3Dh): | → |  |
| RESULT_DATA(34h): | → |  |

**Example:**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | START_STOP(SubCommand=37h): :start on(bit0 = 1) |
| (SubCommand=32h)COUNT_START: | → |  |
| Denom. Value of $1: 00 (h) | → |  |
| Denom. Value of $20: 04 (h) | → |  |
| Denom. Value of CF: 70 (h) | → |  |
| Denom. Value of $1: 00 (h) | → |  |
| Denom. Value of $100: 06 (h) | → |  |
| 1BYTE_COUNT_DATA END: 40 (h) | → |  |
| (SubCommand=3Dh)COUNT_STOP: | → |  |
| (SubCommand=34h)RESULT_DATA: | → |  |

**Example:**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SETUP2(SubCommand=38h):(bit0=0) |
|  | ← | START_STOP(SubCommand=37h): :start on(bit0 = 1) |
| (SubCommand=32h)COUNT_START: | → |  |
| No data during counting.. note) SB Series can not response with PC's request during couning | → |  |
| (SubCommand=3Dh)COUNT_STOP: | → |  |
| (SubCommand=34h)RESULT_DATA: | → |  |

- **-.** · If the SB Series receives another packets from PC before sending RESULT_DATA,
    - the SB Series is not sure to send RESULT_DATA
- **-.** · "1byte counting data" may not be same with the result of SB Series,
    - so, you MUST recaculate from RESULT_DATA packet.
- **-.** · The SB Series could not receive packets from PC,
    - if you send another packets within 100ms after sending a packet.

**(Bank note Counting)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | START_STOP(SubCommand=37h): :Stop ( = Cancel Start) (bit1 = 1) |

**(not to Save BMP to USB)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SETUP2(SubCommand=44h): : to USB ( 0x00) |

### Anexo — Tabla `gpaCurrencyCode` (índice de moneda usado en SEND_IFD_COUNT_LOG_DATA)

```c
const char *gpaCurrencyCode[] = {
    ,
    USD,
    MXN,
    KRW,
    EUR,
    COP,
    CNY,
    YTL,
    CRC,
    NIO,
    AUD,
    SGD,
    INR,
    NOK,
    NZD,
    PLN,
    NTD,
    CZK,
    LBP,
    SEK,
    BRL,
    CAD,
    SYP,
    GTQ,
    NID, // Iraq
    ILS,
    PEN,
    Coupon1,
    "Coupon2",
    "Coupon3",
    "Coupon4",
    "Coupon5",
    "Coupon6",
    "JPY",
    "PGK",
    "RUB",
    "ZAR",
    "AED",
    "THB",
    "GBP",
    VEB,
    BAR,
    UAH,
    KZT,
    CHF,
    SAR,
    JOD,
    KGS,
    MYR,
    MCQ,
    IDR,
    SDG,
    RON,
    BYB,
    AZN,
    RSD,
    DOP,
    SRD,
    TID,
    HUF,
    HRK,
    GHS,
    GEL,
    EGP,
    UGX,
    MAD,
    LKR,
    AMD,
    NAD,
    HNL,
    KWD,
    HKD,
    ETB,
    PHP,
    MNT,
    IRR,
    SZL,
    BWP,
    QAR,
    STL,
    AOA,
    MZN,
    OMR,
    YER,
    BGN,
    PKR,
    MSP,
    LYD,
    NGN,
    LSL,
    BHD,
    TWD,
    ZAD,
    ZMK,
    ATS,
    CLP,
    DZD,
    DKK,
    XPF,
    MOP,
    MKD,
    FJD,
    BAM,
    VND,
    KES,
    XOF,
    LAK,
    MMK,
    BDT,
    CUP,
    MDL,
    SCP,
    IRP,
    XAF,
    CP7,
    ARS,
    GIS,
    BYN,
    NPR,
    IQD,
    TZS,
    RWF,
    BIF,
    ZWD,
    REKA,
    ALL,
    MUR,
    TJS,
    CVE,
    DJF,
    VES,
    LCH,
    TCH,
    JMD,
    UZS,
    SYC,
    CDF,
    ONR,
    KHR,
    ZWL,
    BND,
    TEST1,
    TEST2,
    TEST3,
    TEST4,
    TEST5,
    TEST6,
    TEST7,
    TEST8,
    TEST9,
    TEST10,
    PYG,
    GMD,
    AFN,
    NHV, // NH bank Voucher
    GYD, // Guyana
    MGA, // Madagascar
    TND, // Tunisienne
    SJV, // Seongju Voucher
    PBV, // Paris Baguette Voucher
    SLL, // Sierra Leone
    GNF, // Guinea
    LRD, // Republic of Liberia
    WST, // Samoa
    Other
};
```

---

## Hoja: Ref.

# The value of Data[1]~Data[10] are depend  on the Currency type

### 1) BRL

| Byte | Bit | Value | Denomination | Action |
|---|---|---|---|---|
| Data[1] C3(h) | Bit 0 | 1 | BRL2 | reject |
|  | Bit 1 | 1 | BRL5 | reject |
|  | Bit 2 | 0 | BRL10 |  |
|  | Bit 3 | 0 | BRL20 |  |
|  | Bit 4 | 0 | BRL50 |  |
|  | Bit 5 | 0 | BRL100 |  |
|  | Bit 6 | 1 | BRL2N | reject |
|  | Bit 7 | 1 | BRL5N | reject |
| Data[2] 00(h) | Bit 0 | 0 | BRL10N |  |
|  | Bit 1 | 0 | BRL20N |  |
|  | Bit 2 | 0 | BRL50N |  |
|  | Bit 3 | 0 | BRL100N |  |
|  | Bit 4 | 0 | Reserved |  |
|  | Bit 5 | 0 | Reserved |  |
|  | Bit 6 | 0 | Reserved |  |
|  | Bit 7 | 0 | Reserved |  |

### 2) ETC.

| Byte | Bit | Value | Denomination | Action |
|---|---|---|---|---|
| Data[1] 03(h) | Bit 0 | 1 | UZS1000 | reject |
|  | Bit 1 | 1 | UZS5000 | reject |
|  | Bit 2 | 0 | UZS10000 |  |
|  | Bit 3 | 0 | UZS50000 |  |
|  | Bit 4 | 0 | UZS100000 |  |
|  | Bit 5 |  |  |  |
|  | Bit 6 |  |  |  |
|  | Bit 7 |  |  |  |
| Data[2] 00(h) | Bit 0 |  |  |  |
|  | Bit 1 |  |  |  |
|  | Bit 2 |  |  |  |
|  | Bit 3 |  |  |  |
|  | Bit 4 |  |  |  |
|  | Bit 5 |  |  |  |
|  | Bit 6 |  |  |  |
|  | Bit 7 |  |  |  |

---

## Hoja: Added_From_Eccos

### 1. COUNTING REPORT REQUEST

### 6. SubCommand = 35 (h) — RESULT_REQUEST — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 05 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 35 (h) = SubCommand
- **Data[1]** · 0x80 · counting report Request

**Example:**

- RESULT_REQUEST:counting report Request

```
F0  F1  0B  19  02  00  00  00  00  03  05  08  00  03  06
```

### 2. COUNTING REPORT CLEAR

### 7. SubCommand = 36 (h) — RESULT_CLEAR — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 06 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 36 (h) = SubCommand
- **Data[1]** · 0x80 · counting report Clear

**Example:**

- RESULT_CLEAR:counting report Clear

```
F0  F1  0B  19  02  00  00  00  00  03  06  08  00  03  07
```

### 3. COUNTING REPORT DATA

### 19. SubCommand = 43 (h) — COUNTING_REPORT_DATA — `SB9 ---> IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 15 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 03 | MSB_SC |  | LSB_SC |  | 00 | 00 |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 |
|---|---|---|---|---|---|---|---|
| MSB_RC |  | LSB_RC |  | 00 | 00 | xx | xx |
| Data[4] |  | Data[5] |  | Data[6] |  | CheckSum |  |

- **Data[0]** · 43 (h) = SubCommand
- **Data[1]** · XX (h) · MSB_SC · Total of the Count in Stacker ( MSB )
- **Data[2]** · XX (h) · LSB_SC · Total of the Count in Reject ( LSB )
- **Data[3]** · 00 (h) = R · reserved
- **Data[4]** · XX (h) · MSB_RC · Total of the Count in Reject ( MSB )
- **Data[5]** · XX (h) · LSB_RC · Total of the Count in Reject ( LSB )
- **Data[6]** · 00 (h) = R · reserved

**Example:** Total of the Count in Stacker: 531 pcs. -> 213 (h)

    - Total of the Count in Reject: 124 pcs.-> 7C (h)

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 15 | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 03 | 00 | 02 | 01 | 03 | 00 | 00 |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |
|  |  |  |  |  |  |  |  |  |  |  | MSB_SC |  | LSB_SC |  | R | R |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 |
|---|---|---|---|---|---|---|---|
| 00 | 00 | 07 | 0C | 00 | 00 | 05 | 00 |
| Data[3] |  | Data[4] |  | Data[5] |  | CheckSum |  |
| MSB_RC |  | LSB_RC |  | R | R |  |  |

### 4. SAVE BMP TO USB REQUEST

### 20. SubCommand = 44 (h) — SAVE_BMP_TO_USB — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 04 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 44 (h) = SubCommand
- **Data[1]** · Bit 0 · USB

**Example:**

- DEFAULT_LOADING: default loading

```
F0  F1  0B  19  02  00  00  00  00  04  04  00  01  02  0F
```

### Command Tx/Rx state block diagram

**(counting report request)**

| SB9 |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_REQUEST(SubCommand=35h): :counting report Request (0x80) |
| COUNTING_REPORT_DATA(43h): | → |  |

**(Counting result Clear)**

| SB9 |  | IFD(PC) |
|---|:---:|---|
|  | ← | RESULT_CLEAR(SubCommand=36h): :counting report Clear(0x40) |

**(to Save BMP to USB)**

| SB9 |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SETUP2(SubCommand=44h): : to USB ( 0x01) |

---

## Hoja: Eccos_Reques_20180329

### 8. SubCommand = 37 (h) — START_STOP — `SB Series <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 03 | 07 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 37 (h) = SubCommand
- **Data[1]** · 0x01 · Start (Start ON)
    - 0x02 · Stop (cancel start)
    - : only 1 bit can be set at the same time

**Example:**

- START_STOP:start ON

```
F0  F1  0B  19  02  00  00  00  00  03  07  00  01  03  01
```

- **START_STOP:** · Stop (cancel start)

```
F0  F1  0B  19  02  00  00  00  00  03  07  00  02  03  02
```

### 20. SubCommand = 44 (h) — SAVE_BMP_TO_USB — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 0B | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 04 | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | CheckSum |  |

- **Data[0]** · 44 (h) = SubCommand
- **Data[1]** · Bit 0 · USB · 1: ON (save) · 0: OFF (do not save)

**Example:**

- SAVE_BMP_TO_USB:  ON ( Save to USB )

```
F0  F1  0B  19  02  00  00  00  00  04  04  00  01  02  0F
```

- SAVE_BMP_TO_USB:  OFF (do not save)

```
F0  F1  0B  19  02  00  00  00  00  04  04  00  00  02  0E
```

**(Bank note Counting)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | START_STOP(SubCommand=37h): :Stop ( = Cancel Start) (bit1 = 1) |

**(not to Save BMP to USB)**

| SB Series |  | IFD(PC) |
|---|:---:|---|
|  | ← | DEVICE_SETUP2(SubCommand=44h): : to USB ( 0x00) |

---

## Hoja: Eccos_Request_20190902

### 25. SubCommand = 49 (h) — IFD_REJECT_DESIGNATED_NOTE — `SB9 <--- IFD(PC)`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F0 | F1 | 1D | 19 | 02 | 00 | 00 | 00 | 00 | 04 | 09 | xx | xx | xx | xx | xx | xx |
| S.U | S.L | LEN | IFD | P.V | R | R | R | S.ID | Data[0] |  | Data[1] |  | Data[2] |  | Data[3] |  |

| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 33 | 34 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx | xx |
| Data[4] |  | Data[5] |  | Data[6] |  | Data[7] |  | Data[8] |  | Data[9] |  | Data[10] |  | CheckSum |  |

- **Data[0]** · 49 (h) = SubCommand
- **Data[1] ~[10]** · Ref. · designate the notes to reject
    - each bit val :1 reject,  0: not reject

**Example:**

- ***  reject 2 & 5 on BRL mode** · (Refer. Sheet 'Ref.') · _1__BRL · _1__BRL

```
F0  F1  1D  19  02  00  00  00  00  04  09  0C  03  00  00  00  00
00  00  00  00  00  00  00  00  00  00  00  00  00  00  05  04
```

---
