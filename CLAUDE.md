# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this repo is

Tools to drive a **SB-9 banknote counter** (vendor "IFD" protocol, "SB and MIB Series") from a PC without the vendor app. The repo is both a **test bench** (interactive consoles against the real machine) and the **reference implementation** of the protocol that other apps will copy/import — so protocol code should stay separable from the consoles (Node already has `src/protocolo.js`; Python still has it inside `probar_com.py`, extracting a `protocolo.py` is the planned next step). The user works in Spanish: code identifiers, comments, console output, logs and docs are all in Spanish — keep it that way.

- Root, `bin/`, `res/`: the vendor's MFC app `IFD.exe` + ActiveX `IFDX_SBM.ocx` (VS2008 project, 32-bit). Reference only; we don't build or modify it. `IFDView.cpp` is useful to see how the vendor sends commands and `gpaCurrencyCode[]` there is parsed at runtime by both consoles for currency names.
- `python/` and `node/`: our own implementations. **They are feature-for-feature twins** (same console commands, same frames, same self-test fixtures). Any protocol/command change must be made in both.
- `perfiles.json` (root): configuration profiles shared by both consoles.
- `maquinas.json` (root): machine models, selected with `--modelo` (default `sb9`). Each sets the serial baud rate and overrides the denomination order per currency (`BILLETES` in code holds the SB-9 base). Known: `sb9` = SB-9 fw 01.41, 115200, ARS ascending; `mib9` = MIB-9 old firmware, 57600, ARS **descending** ($20000 at index 0). Don't hard-edit `BILLETES`/default baud for another machine — add or edit a model.
- `Doc/PC_protocol_SB_MIB_series.md`: the protocol spec (converted from the vendor xlsx). It has known errata, see below.

## Commands

```bash
# Python (pyserial)
pip install -r python/requirements.txt
python python/probar_com.py --prueba            # offline self-test, must print "Autoprueba APROBADA"
python python/probar_com.py --ip 192.168.123.231 # console over TCP :4101
python python/probar_com.py --puerto COM5        # console over serial (default COM5, 115200 8N1)

# Node (>=20, serialport 13, ESM)
cd node && npm install
npm test                                         # node --test (test/protocolo.test.js)
node --test --test-name-pattern "perfiles"       # single test
npm run prueba                                   # same offline self-test as Python
npm run red / npm start                          # console over TCP / serial
```

There is no lint/build step. The machine accepts **one connection at a time** — IFD.exe or another console must be disconnected. Real-device testing is done by the user; ask them to paste output or read the newest file in `python/logs/` / `node/logs/` (gitignored).

## Architecture

**Python**: `probar_com.py` is self-contained (frame build/verify, decoder, config-change builders, console, self-test); `perfiles.py` holds profile logic. **Node** splits the same pieces: `src/protocolo.js` (pure protocol + `estado` object), `src/conexion.js` (serial/TCP behind one EventEmitter interface), `src/registro.js` (screen+log), `src/perfiles.js`, `src/autoprueba.js` (fixtures reused by tests). `escuchar*` are passive sniffers (monitor / com0com bridge / TCP proxy).

Frame format: `F0 F1 LEN 19 02 00 00 00 SID` + **every data byte split into two nibbles** (`0x41` → `04 01`) + checksum = sum(LEN..last data nibble) & 0xFF, also sent as two nibbles. `LEN = total − 4`. Data[0] is the SubCommand. Keep ≥100 ms between sent frames. During counting the machine streams **raw single bytes** outside frames (1BYTE_COUNT_DATA: denomination index, `20` suspect, `70` counterfeit, `71` stay note, `40` end), so the receive parser splits frames vs loose bytes.

Configuration changes are **read-modify-write of SETUP_STATE_DATA2 (41h)**: the last 41h received is cached (`config_actual` / `estado.config`, 11 params: currency, mode, status bits, mode lock, speed, denom, pockets, batch count, UV/MR/IR levels); a command changes only its field, resends all 11, then re-requests 41h (`35 12`) to verify. Hence most commands need a prior `knock` (after ACK the console auto-requests 41h, mirroring IFD.exe). Status byte (param 2) bits: 0 Batch, 2 beep, 3 Auto, 4 ADD, 5 UV, 6 MR, 7 IR.

## Hardware facts verified on the real SB-9 (not in, or contradicting, the spec)

- **Manual mode** (Auto bit off): the machine silently ignores START_STOP `37 01` from the PC (IFD.exe too). First thing to check when `iniciar` gets no COUNT_START.
- Firmware version is requested with RESULT_REQUEST param **0x21** (undocumented, captured from IFD.exe); reply is 46h.
- Its 41h reply carries **3 extra undocumented bytes** (LEN 25h vs 1Fh in the spec). Writes with the documented 11 params work.
- ARS (currency 115) has 10 denomination indices; confirmed 3=$100, 7=$2000, 8=$10000, rest assumed ascending ($10…$20000).
- Fixed denomination in SINGLE (41h param 5) only lasts **one count**, then the machine reverts to DD (0x1F).
- **Pocket capacity (41h param 6) is asymmetric**: on read the machine reports old 3-code groups (reject 30=0, 50/70/100=1; stacker 200/250/300=0, 150=1, 100=2); on write, `0x00` sets **reject 100 / stacker 300** (what the user wants; profiles write it). Meaning of other written codes is unknown — individual commands resend the read value (`0x10`), whose write effect is unverified.
- DEFAULT_LOADING (39h) only turns the warning beep on and sets stacker to 100.
- Spec errata: example checksums of 41h and 4Fh are wrong, 53h example LEN is wrong, 63h example has no checksum. Counting-report (43h), wing motor, BMP-to-USB are SB-9 only.

## Gotchas

- Python output must stay ASCII-safe for Git Bash/cp1252 (no emoji); the console strips a leading BOM from input and ends with `os._exit(0)` after closing.
- Self-test fixtures are real captured frames; when adding a decoder or command, extend both `autoprueba()` in Python and `src/autoprueba.js` / `test/` in Node.
- Wireshark captures live in `python/capturas/`; `tshark -r <file> -Y "tcp.port==4101 && tcp.len>0" -T fields -e ip.src -e tcp.payload` extracts the frames.
