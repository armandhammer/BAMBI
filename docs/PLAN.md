# YAM+ Wave 1 — Implementation Plan

> *Moved from the original YAM+ workspace into BAMBI. Paths such as `firmware/ambika/` mean this repository's root; `toolchain/` and `tools/yamplus_sysex.py` are now `toolchain/` and `utils/yamplus_sysex.py` here; `release/<name>/` folders correspond to [GitHub Releases](https://github.com/armandhammer/BAMBI/releases). The `yam-plus` branch is `main`.*

*Date: 2026-11-25 · Companion to [AUDIT.md](AUDIT.md). Nothing in this plan has been implemented yet.*

**Wave 1 scope:**
- **E1–E4** enablers
- **V1 + V2** SVF cutoff/VCA smoothing
- **V3** envelope curves
- **V4** vintage/slop
- **C1** centered unison
- **U1** encoder acceleration
- **H1–H4** editor SysEx hooks

Target: Ambika (controller + SVF voicecards). Shruthi work starts in wave 2.

### Status (2026-11-25)

All of wave 1 is implemented, built and committed on `firmware/ambika`
branch `yam-plus`, tagged `yamplus-0.1`. **Nothing has been verified on
hardware yet**: see [HARDWARE_TESTS.md](HARDWARE_TESTS.md).

| Milestone | Commit | Measured delta (flash / static RAM) | Notes |
|---|---|---|---|
| M0 probes | `23e3495` | C +216 / +0; V +134 / +2 | ISR +6–8 cycles/sample |
| M1 clock races | `1240a10`, `2a1089a` | C +46 / +0 | Found during M2: avr-libc 1.6.8 `cli()`/`sei()` aren't compiler barriers; `common/atomic.h` adds `InterruptsOff()`/`InterruptsRestore()` |
| M2 CV smoothing | `fdaba6e` | V +570 / +23 | Ramps at ¼ rate (8 steps / 32 samples) plus per-sample cutoff dither. ISR ≈ +25 cycles static, +45–50 moving (first per-sample version was ~2× that) |
| M3 env curves | `450f343` | C +104; V +118 / +3 | `crv1–3`, CC 110–112, NRPN 106–108 |
| M4 vintage | `ed1a849` | C +54; V +402 / +9 | Own xorshift per voice: all voicecards share one `Random` seed, so `Random` would have drifted every voice identically |
| M5 spread + encoder | `bdcfd00` | C +238 / +1 | Shift+encoder ×8 already existed in stock; increments now clamp instead of being dropped |
| M6 SysEx H1–H4 | `62f3ddf` | C +376 / +0 | `tools/yamplus_sysex.py` (offline self-test passes) |
| M7 release | `4c8f824` | C −2 | OS page `YAMplus v0.1`, voicecard version 0x11, `YAMPLUS.md` |

**Final:** controller 60,402 / 61,440 B flash (1,038 free; gate 512 ✅),
static RAM 3,856 B (240 free incl. stack; gate: measure `stk`). Voicecard
27,352 / 32,256 B (4,904 free ✅), 1,067 B RAM (981 free ✅). Voicecard CPU
gate: pending the hardware load readings.

---|---|---|---|
| M0 | **Built; awaiting hardware check** (`firmware/ambika` `yam-plus` @ `23e3495`, files in `release/m0-probes/`) | C +216 B flash / +0 B RAM; V +134 B flash / +2 B RAM; ISR +6–8 cycles/sample | Image now pins the `linux/386` digest and includes numpy; resource regeneration verified identical; image backed up to `toolchain/ambika-squeeze-4.3.5.tar`. Checklist: [HARDWARE_TESTS.md](HARDWARE_TESTS.md#m0--measurement-probes-releasem0-probes) |
| M1–M7 | not started | | |

---

## 1. Measured baseline (pinned avr-gcc 4.3.5, built here)

The toolchain is done (E1 core): [toolchain/avr-make.sh](toolchain/avr-make.sh) + [toolchain/in-container-build.sh](toolchain/in-container-build.sh), image `ambika-squeeze:4.3.5`:
- base `debian/eol:squeeze` **i386**
- gcc-avr 1:4.3.5-1, avr-libc 1:1.6.8-2, binutils-avr 2.20.1-1
- builds run `--network none --cap-drop=ALL`

**Equivalence check:** our YAM voicecard build is **byte-identical** to the shipped `ambika_voicecard_YAM190319.bin`. Shruthi YAM 0.05 matches the shipped ELF to within 2 B.

| Target | text | data | bss | **Flash used / cap** | **Flash free** | **Static RAM** | **RAM free (incl. stack)** |
|---|---|---|---|---|---|---|---|
| Ambika controller (YAM src) | 59,270 | 100 | 3,755 | 59,370 / 61,440 | **2,070 B** | 3,855 / 4,096 | **241 B** |
| Ambika voicecard (YAM190319) | 26,076 | 52 | 978 | 26,128 / 32,256 | **6,128 B** | 1,030 / 2,048 | **1,018 B** |
| Shruthi-1 (YAM 0.05) | 63,202 | 350 | 3,464 | 63,552 / 64,512 | **960 B** | 3,814 / 4,096 | **282 B** |

(The shipped controller YAM190319 is 59,400 B. Its source state differs slightly from the repo HEAD.)

**Where the controller RAM goes:**

| Symbol | Size | Note |
|---|---|---|
| `Multi::parts_` | 2,082 B | 6 × 347 B |
| `Filesystem::fs_` | 558 B | FatFs + sector buffer |
| MIDI out low-priority ring | 128 B | |
| LCD local + remote buffers | 161 B | |
| LCD ring | 64 B | |
| voicecard TX rings | 2 × 64 B | |
| `Storage::tmp_buffer_` | 64 B | |
| `Library::loaded_objects_indices_` | 38 B | |
| `tick_duration_table_` | 32 B | |

**Voicecard sample interrupt** (`TIMER2_OVF`, `__vector_9`): about 99 instructions, no calls, `voicecard_rx.Receive()` inlined. Both DAC writes busy-wait on the UART-SPI, so a per-sample VCA write costs noticeably more than it looks. That is why V2 has a decimation knob.

### Corrections to AUDIT.md from the real map

- **FatFs `_USE_MKFS=0`:** saves 0 B. `f_mkfs` is already discarded by `--gc-sections`.
- **Static initializers:** YAM has one stub (`__static_initialization_and_destruction_0`, 200 B), not Elkhart's ~16. The reclaim ceiling is about 200 B.
- **Extra YAM race (beyond Elkhart's):** `lfo_refresh_counter_` (uint16) is `++` in the Timer2 interrupt and `-= kControlRate` in the main loop, unguarded. `tick_duration_` (uint16) is also written from the main loop while the interrupt reads it. Both are folded into M1.

**Consequence:** wave 1 needs only **~5 B of extra controller RAM**. E3 therefore becomes *measure the stack high-water mark first, and reclaim only if the margin is under ~96 B*. E4 has little to reclaim, but wave 1's estimated controller flash (~1.1 KB) fits in the 2,070 B free.

---

## 2. Ground rules

### Repos (default; tell me if you want something else)
- **`firmware/ambika/`**: a git clone of `bjoeri/ambika` @ `d110867`, on a new branch `yam-plus`. Upstream history is kept so it can rebase or send PRs.
- **`firmware/shruthi/`**: a clone of `bjoeri/shruthi-1`, untouched until wave 2.
- **Workspace root:** its own small git repo for `toolchain/`, `AUDIT.md`, `PLAN.md` and later `web/`. `refs/` and `firmware/` are gitignored there.
- `refs/` stays pristine for diffing.
- One feature per commit. Every commit message records the `avr-size` delta for both targets.

### Gates (checked by a `toolchain/size-report.sh` step after every build)

| Gate | Threshold |
|---|---|
| Controller flash free | ≥ **512 B** |
| Controller static RAM growth (wave total) | ≤ **+16 B**, and measured stack high-water margin ≥ **96 B** |
| Voicecard flash free | ≥ **2 KB** |
| Voicecard RAM free | ≥ **768 B** |
| Voicecard CPU | worst-case block load **< 90%** and **0 underruns** over 5 min on the heaviest patch (fmfb + qpwm + fuzz + crush, 6-note chords, full mod matrix), measured with the M0 load probe |
| Build hygiene | resources regenerate reproducibly; the YAM baseline still builds byte-identical from the untouched tree |

### Compatibility policy
- **Patch format unchanged** (112 B). Only the spare bytes are used, and **value 0 = today's YAM behaviour**, so every existing program sounds identical.
- **PartData** gains one byte, same rule.
- Old voicecards ignore the new bytes (harmless). New voicecards with an old controller see 0 (legacy behaviour).
- The Ixox editor keeps working: H1 changes only a reply argument Ixox ignores.

**Patch byte map** (`common/patch.h`):

| Offset | Field | 0 = | Range |
|---|---|---|---|
| 106 | `env_curve[0]` | stock YAM expo | 0..127: 0 = expo (stock), 64 = linear, 127 = inverse-expo |
| 107 | `env_curve[1]` | stock | same |
| 108 | `env_curve[2]` | stock | same |
| 109 | `vintage` | off | 0..127 |
| 110–111 | spare (reserved for V6 resonance comp / wave 2) | | |

**PartData byte map** (`controller/part.h`):

| Offset (NRPN) | Field | 0 = |
|---|---|---|
| 80 (192) | `spread_mode` | legacy (+i·spread) · 1 = centered · 2 = centered-curved |
| 81–83 | spare | |

### Flashing and rollback (you do this; I can't touch hardware)
- **Controller:** copy `AMBIKA.BIN` to the SD root and reboot. **Voicecards:** copy `VOICE1.BIN`…`VOICE6.BIN` and use the OS-info page update.
- Keep `ambika_controller_YAM190319.bin` / `ambika_voicecard_YAM190319.bin` on the card, renamed for rollback.
- Back up the SD card first.

---

## 3. Milestones

Order is chosen so measurement exists before any DSP change, and so each milestone is independently flashable.

### M0 — Infrastructure and measurement probes

| Task | Files | Notes | Est. cost |
|---|---|---|---|
| Fork and branch setup, root repo, `.gitignore` | — | as in §2 | — |
| Add `python-numpy` to the image so the resource compiler runs; check that regenerating `controller/resources.cc` / `voicecard/resources.cc` from the untouched `.py` matches the checked-in files (modulo the Windows `\` include) | `toolchain/Dockerfile.squeeze-i386` | Required before any new string or parameter. If the generator drifts, pin or fix it first. | — |
| `docker save` the image to `toolchain/ambika-squeeze-4.3.5.tar` (gitignored); vendor the `.deb` list | `toolchain/` | Elkhart's top toolchain-risk mitigation | — |
| `size-report.sh`: prints the §1 table plus the delta vs the previous build, and enforces the gates | `toolchain/` | | — |
| **Controller stack high-water probe:** paint free RAM `__bss_end..SP` with `0xA5` in `.init3`, scan at runtime, show "stack free" on the OS-info page (also readable via SysEx PEEK) | `controller/controller.cc`, `ui_pages/os_info_page.cc` | Decides whether E3 reclaims are needed | C ~80 B, 1 B RAM |
| **Voicecard load + underrun probe:** in `main()`, count samples consumed during `ProcessBlock` (difference in `audio_buffer.readable()`), max-hold it; count interrupt reads from an empty buffer; return both via a new blocking command `COMMAND_GET_LOAD = 0xFE` (same path as `GET_VERSION_ID`); show per-voice load on the OS-info page | `voicecard/voicecard.{cc}`, `voicecard_rx.*`, `common/protocol.h`, `controller/voicecard_tx.*`, `os_info_page.cc` | ~2.5% resolution (1 sample of 40); enough for the < 90% gate | V ~50 B, 3 B RAM, ~4 cycles/sample; C ~90 B |

**Acceptance (you, on hardware):**
1. Stack-free and voicecard load readouts show sane values on stock-equivalent firmware.
2. Record the baseline load for: an init patch, the "heaviest patch" above, and a few favourite programs.

### M1 — Clock and ISR race fixes (E2)

| Task | Files | Design |
|---|---|---|
| Claim pending clock events atomically | `controller/multi.cc` `UpdateClocks` | `cli(); n = num_clock_events_; num_clock_events_ = 0; sei(); while (n--) Clock();` |
| Guard `lfo_refresh_counter_` | `multi.cc` `UpdateClocks`, `multi.h` `Tick` | Same pattern: snapshot-and-subtract inside `cli/sei` |
| Guard the 16-bit `tick_duration_` store | `multi.cc` `ComputeInternalClockOverflowsTable`, `Start` | Write under `cli/sei` |
| Reset `clock_counter_` in `Start()` | `multi.cc` | First tick a full period after Start |

**Est. cost:** C +40–70 B, 0 RAM. **Risk:** Low.

**Acceptance:**
1. Internal clock at 120 BPM with MIDI out = `seq`: count `0xF8` for 60 s in a MIDI monitor. Expect 2,880 ± 1 (log the YAM baseline first for comparison).
2. Arp and clock-synced LFOs stay locked to a DAW over 5 min.

### M2 — SVF CV path smoothing (V1 + V2)

| Task | Files | Design |
|---|---|---|
| **V1 cutoff ramp + dither** | `voicecard/voice.{h,cc}` (expose 14-bit cutoff, `U14` before `>>6`), `voicecard/voicecard.cc` (main loop + interrupt) | The main loop computes `cutoff_step = (target16 − current16) >> 5` once per block. The interrupt does `current16 += step` (clamped at target after 32 samples), then first-order error feedback: `s = current16 + err; OCR0A = s >> 8; err = s & 0xFF`. The `vcf_cutoff_out.Write()` in the main loop is removed. |
| V1b resonance, same treatment (compile flag `SMOOTH_RESONANCE`) | same | Default on if the load budget allows |
| **V2 VCA ramp** | `voicecard/voice.{h,cc}` (16-bit VCA before `>>8`), `voicecard.cc` | Interpolate the 12-bit linearized VCA (`lut_res_vca_linearization` with an interpolated index, so 8-bit stepping on quiet release tails disappears too) from the previous to the next block value. Write the DAC every **K** samples, `VCA_DECIMATION ∈ {1, 2, 4}`. Start with K = 4 (~9.8 kHz update) and drop to 2 or 1 only if the load probe allows. |

**Est. cost:** V ~250–320 B flash, ~14 B RAM. Cycles per sample: V1 ~15, V1b ~10, V2 ~(30–60)/K. **Expected total at K = 4: ~35–40 cycles per sample (~7–8% of 510).**

**Risks:**
- Interrupt budget: gated by the M0 probe.
- `OCR0A` writes are double-buffered at TOP in phase-correct mode, so no glitches are expected. Confirm on a scope if you have one.
- The 39 kHz dither must sit under the card's CV RC corner. It already filters the 39 kHz PWM carrier, so it should.

**Acceptance (listening):**
1. A slow 30 s cutoff sweep at resonance ~50/63 has no audible stepping (A/B vs YAM190319).
2. A 0-attack/short-decay pluck clicks less and sounds tighter.
3. Long release tails fade smoothly to silence.
4. Gates: load < 90%, 0 underruns.

### M3 — Envelope curves (V3)

| Task | Files | Design |
|---|---|---|
| Curve shaping | `voicecard/envelope.h` | `Update(..., curve)`. For `curve ≤ 64`: `step = U8Mix(expo(phase), lin(phase), curve·4)`. For `> 64`: `U8Mix(lin, inv(phase), (curve−64)·4)`, where `inv(t) = 255 − expo(65535 − phase)` (one extra table lookup, only when curve > 64). Applies to A/D/R; the attack keeps the same mapping, so 0 = today's concave attack. |
| Wire patch bytes | `voicecard/voice.cc` (`Update` call per envelope), `common/patch.h` (bytes 106–108) | — |
| Parameters + UI | `controller/parameter.cc` (+3 entries, CC map: unused CCs, NRPN 106–108), `controller/resources/strings.py` (`crv1/crv2/crv3`, long "env1 curve"…), `controller/ui.cc` | `PAGE_VOICE_LFO` bottom row slots 4–6 (currently `0xff`), so all three curves are visible next to the voice LFO |

**Est. cost:** V ~100–130 B, 3 B RAM, ~2 cycles/sample amortized. C ~110–150 B. **Risk:** Low.

**Acceptance:**
1. Existing programs are bit-identical in sound with curve = 0. Spot-check 5 programs A/B.
2. curve = 64 gives a linear ramp, verified visually on a scope or a DAW recording of a slow VCA envelope.
3. curve = 127 gives a slow-start ramp.

### M4 — Vintage / slop (V4)

| Task | Files | Design |
|---|---|---|
| Voice identity | `common/protocol.h` (new `COMMAND_SET_VOICE_INDEX = 0x90 \| n`), `controller/voicecard_tx.*` (sent in `SyncAllVoices` and after `Reset`), `voicecard/voicecard_rx.*` | 4-bit index per slot. The personality follows the slot; in wave 2 it moves to voicecard EEPROM together with calibration (V5). |
| Static offsets | `voicecard/voice.cc` | A small PROGMEM table of 8 signed triplets (pitch, cutoff, env-time), picked by index and scaled by `vintage` (max ≈ ±8 cents, ±3% cutoff, ±1 env-step) |
| Slow drift | `voicecard/voice.cc` | Per voice: every ~64 control ticks pick a new `Random` target (seeded by index), one-pole lag toward it (~0.3–1 Hz), added to pitch and cutoff, scaled by `vintage` |
| Parameter + UI | `parameter.cc` (+1, NRPN 109), `strings.py` (`vint`), `ui.cc` | `PAGE_VOICE_LFO` slot 7 |

**Est. cost:** V ~200–250 B, ~10 B RAM, ~3 cycles/sample amortized. C ~70 B. **Risk:** Low.

**Acceptance:**
1. vintage = 0 is identical to before.
2. vintage = 64 on a 6-note chord of a saw pad gives audible but subtle chorusing and per-voice brightness differences.
3. Unison stays usable.

### M5 — Controller ergonomics and voicing (C1, U1)

| Task | Files | Design | Est. |
|---|---|---|---|
| **C1 spread mode** | `controller/part.{h,cc}` (`InternalNoteOn/Off` MONO loop, `UNISON_2X` pair, POLY per-voice spread), `parameter.cc` (+1 PART-level, NRPN 192), `strings.py`, `ui.cc` (`PAGE_PART`: replace nothing; add to `PAGE_PART` only if a slot is free, otherwise `PAGE_MULTI_CLOCK`'s free slots) | Mode 1: offset_i = `(2i − (n−1))·spread/2`. Mode 2: same, with a PROGMEM weight table (outer voices wider, JP-style). Default init part = 1; existing parts read 0 = legacy. | C ~150–200 B, 0 RAM |
| **U1 encoder acceleration** | `controller/ui.cc` (encoder event timestamping), `ui_pages/parameter_editor.cc` (`OnIncrement`) | Increments < 25 ms apart → ×4; < 50 ms → ×2; Shift+encoder → ×8. Only on value edits, never on page navigation. | C ~90–120 B, 3 B RAM |

**Acceptance:**
1. MONO with 6 voices and spread 20: the stack pitch center equals the played note (tuner check).
2. Mode 0 reproduces old programs.
3. A fast encoder spin covers 0–127 in about one turn; slow turns still step by 1.

### M6 — Editor SysEx hooks (H1–H4)

All in `controller/storage.cc` (`SysExParseCommand` / `SysExAcceptCommand`), plus `ui_pages/library.*` for name/location data.

| Hook | Wire format | Est. C |
|---|---|---|
| **H1** reply carries the part | Single-object requests (`0x11`–`0x15`) reply with `arg = part + 1` (was always 0). Multi dump unchanged (already 1–6). | ~10 B |
| **H2** version / capabilities (`0x1C`, mirrors Shruthi) | Reply cmd `0x0C`, payload: `fw_family(1=YAM+)`, `fw_major`, `fw_minor`, `WAVEFORM_LAST`, `patch_layout_ver`, `part_layout_ver`, 6 × voicecard `{slave_id, version}` | ~100–130 B |
| **H3** current programs (`0x1A`) | Reply cmd `0x0A`, payload: for each part, `{patch bank, slot, program bank, slot}` from `Library::loaded_objects_indices_`, plus multi bank/slot | ~100–130 B |
| **H4** program name read (`0x16`, `arg` = part) | Reply cmd `0x06`, payload: 16 name bytes of the loaded program for that part, read from SD via the existing `Storage::Load` name path into `tmp_buffer_` | ~150–200 B |

Name **write** and write-to-slot (H5) move to wave 2. Writing a name only makes sense together with saving.

**Risk:** Low–Med. H4 runs an SD read from the MIDI handler, which costs stack depth. The M0 probe checks that, and if it's tight, H4 defers the read to the main loop with a pending flag.

**Acceptance:**
1. A tiny Node/Python test script (in `tools/`, not firmware) sends each request and decodes the reply; checksums verify.
2. An Ixox pull still works.

### M7 — Release YAM+ 0.1
- Bump `kSystemVersion` (controller) and the voicecard version so H2 reports `YAM+ 0.1`.
- Build `AMBIKA.BIN` + `VOICE1–6.BIN`; write release notes (parameter list, NRPN map additions 106–109 and 192, SysEx additions).
- Update AUDIT.md budgets with the final measured numbers.

---

## 4. Budget ledger (estimates; replaced by measured deltas per commit)

| Item | C flash | C RAM | V flash | V RAM | V cycles/sample |
|---|---|---|---|---|---|
| M0 probes | ~170 | 1 | ~50 | 3 | ~4 |
| M1 clock fixes | ~60 | 0 | — | — | — |
| M2 V1+V1b+V2 (K = 4) | 0 | 0 | ~300 | ~14 | ~35–40 |
| M3 curves | ~130 | 0 | ~120 | 3 | ~2 |
| M4 vintage | ~70 | 0 | ~230 | ~10 | ~3 |
| M5 C1 + U1 | ~300 | 3 | — | — | — |
| M6 H1–H4 | ~400 | 0 (stack transient) | — | — | — |
| **Total** | **~1,130 B** of 2,070 | **~4 B** of 241 | **~700 B** of 6,128 | **~30 B** of 1,018 | **~45–50** of 510 |
| **After wave 1** | **~940 B free** ✅ (gate 512) | ~237 B incl. stack (gate: high-water margin) | **~5.4 KB free** ✅ | **~990 B** ✅ | **~9–10% added** (gate: < 90% worst case) |

If controller flash runs hot, the fallback reclaims (in order) are:
1. the 200 B static-init stub
2. dead strings
3. MIDI low-priority ring 128 → 64 B (RAM)

---

## 5. Risks and mitigations

| Risk | Mitigation |
|---|---|
| Voicecard interrupt / CPU overrun on heavy oscillator pairs | M0 load probe first; V2 decimation; V1b behind a flag; measure on the worst patch before merging |
| Controller stack overflow (241 B shared) | M0 high-water probe; H4 deferred SD read; reclaim list ready |
| Resource generator drift (strings/LUTs) | M0 reproducibility check before any parameter work |
| The toolchain image disappears upstream | `docker save` tarball + `.deb` manifest (M0) |
| Patch incompatibility | 0 = legacy for every new byte; A/B listening checks per milestone |
| Can't test on hardware myself | Each milestone ships a flashable pair + a 3–5 item listening/measurement checklist for you; rollback bins stay on SD |

---

## 6. Explicitly *not* in wave 1 (queued)

- **Wave 2:** V5 calibration (+ moving the vintage personality to EEPROM), V6 resonance compensation, C3 note priority, C4 velocity curves, U2 A/B compare, U3 naming, H5 write-to-slot + name write.
- **Shruthi:** S1 1.03 fixes, S2 curves (shared `envelope.h`), S3 board profiles, avrlib pin unification and the `shared/` DSP extraction.
- **Wave 3:** C6 MPE-lite (needs a bus/RAM study), V7 synced voice LFO, V8 mod-matrix additions, V9 wavefolder.
- **Web editor** (Phase 3 design in AUDIT §4): a separate track. It can start any time against stock YAM using the existing protocol, then pick up H1–H4 when M6 lands.
