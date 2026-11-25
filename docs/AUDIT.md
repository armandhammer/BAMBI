# Ambika / Shruthi YAM+ Audit — Phases 1–3

> *Moved from the original YAM+ workspace into BAMBI. Paths such as `firmware/ambika/` mean this repository's root; `toolchain/` and `tools/yamplus_sysex.py` are now `toolchain/` and `utils/yamplus_sysex.py` here; `release/<name>/` folders correspond to [GitHub Releases](https://github.com/armandhammer/BAMBI/releases). The `yam-plus` branch is `main`.*

*Date: 2026-11-25 · Scope: read-only audit, no firmware or web code written.*
*Reference trees cloned into `refs/` (see §0).*

---

## TL;DR

1. **The controller is the binding constraint, not the voicecards.** YAM Ambika's ATmega644p controller has **~2.0 KB flash** and **~241 B SRAM (stack included)** left. The ATmega328p voicecards have **~6.1 KB flash** and **~1 KB SRAM** free. Shruthi YAM is tighter still: **962 B flash** and **~282 B for the stack**.
   → New synthesis features should live on the **voicecard** wherever possible. Every controller feature has to be paid for with a reclaim first.
2. **Don't modernize the compiler.** Elkhart verified on hardware that avr-gcc 5.4/8.5 miscompile the YAM/MI oscillator DSP (constant metallic tone). Its digest-pinned avr-gcc 4.3.5 (Debian Squeeze) container is the single most valuable thing to take from Elkhart.
3. **Biggest musical gaps vs Rev2/OB-6/Peak-class polysynths:**
   - no per-voice analog "slop"/calibration
   - unison detune drifts sharp because it isn't centered
   - no envelope curve control
   - 980 Hz control rate with 8-bit cutoff PWM, which causes zipper on slow sweeps and blunts fast envelopes
   - no MPE or per-voice pitch bend
   - no tempo-synced voice LFO

   Ambika's mod matrix (14 slots + 4 modifiers) is already deeper than Rev2/OB-6.
4. **SVF hardware fact:** filter mode is switched by a **CD4052 mux** (MUX_A/MUX_B → 4 modes LP/BP/HP/Notch). Mode **morphing is impossible in firmware**: switching is discrete and clicks mid-note. SVF-specific wins are on the CV side instead: cutoff smoothing/dither, resonance gain compensation, and per-voice calibration.
5. **Protocol:** Ambika already sends NRPN on every front-panel edit (MIDI out mode ≥ `ctrl`), and offers SysEx dump/request plus raw RAM PEEK/POKE. Missing for a solid web editor:
   - patch-name transfer
   - version query
   - write-to-slot
   - reply messages that say which part they came from (single-part dump replies carry `arg = 0`)
   - a "dirty/changed" notification

   The Ixox editor clamps Osc Shape at 37, so YAM oscillators 38–42 (`oldsaw`, `qpwm`, `fmfb`, `csaw`, `vowel 2`) can't be selected from it.

---

## 0. Method & what was / wasn't measured

| Repo | Path | HEAD |
|---|---|---|
| pichenettes/ambika | `refs/ambika-orig` | `2c4a690` |
| bjoeri/ambika (YAM) | `refs/ambika-yam` | `d110867` (builds up to YAM190319) |
| voltagecontrolled/ambika-elkhart | `refs/ambika-elkhart` | `53b6cbf` (2026-08) |
| bjoeri/shruthi-1 (YAM) | `refs/shruthi-yam` | `041a94a` (YAM 0.05, based on upstream **1.02**) |
| pichenettes/shruthi-1 (extra, for upstream diff) | `refs/shruthi-orig` | `56bfe78` (upstream **1.03**) |
| Ixox/Shruthi-And-Ambika-Editors | `refs/ixox-editors` | `04b6aac` (YAM commit `2705a4b`, 2018) |

`avrlib` submodules were checked out at each repo's pinned commit (`refs/avril` worktrees).

**Toolchain:** no `avr-gcc` or `avr-size` on this machine (Windows or WSL), and `make` is not installed either. Budgets below come from:
- **Shruthi YAM 0.05:** section and symbol sizes parsed directly from the shipped `.elf` (exact, equivalent to `avr-size`).
- **Ambika YAM190319:** raw `.bin` sizes (= `.text + .data`, exact flash). Controller SRAM comes from Elkhart's measured YAM fork-point baseline (`CHANGELOG.md` "Phase 2": 3,855/4,096 B). Voicecard SRAM comes from Elkhart's measurement of a lightly modified YAM card (~1,050 B), so treat it as approximate.
- **App-area caps** come from the bootloader `--section-start` addresses and HFUSE values.

**Recommended first implementation step (needs your OK):** build Elkhart's pinned Squeeze container (`.github/docker/Dockerfile.squeeze`, Docker is installed). Pulling the image is a one-time download, after which every compile runs `--network none`. That gives exact `avr-size` output and `.map` files for both targets, and turns every estimate below into a measured delta.

---

## 1. Resource budgets

| Target | MCU | App flash cap | Used (YAM) | **Free** | SRAM used (static) | **SRAM free** | Source |
|---|---|---|---|---|---|---|---|
| Ambika controller | ATmega644p @20 MHz | 61,440 B (boot @ `0xF000`, 4 KB) | 59,370 B | **2,070 B** | 3,855 B | **241 B incl. stack** | **measured** (avr-gcc 4.3.5 build, see PLAN.md §1) |
| Ambika voicecard | ATmega328p @20 MHz | 32,256 B (boot @ `0x7E00`, 512 B) | 26,128 B | **6,128 B** | 1,030 B | **1,018 B** | **measured**; byte-identical to shipped YAM190319 |
| Shruthi-1 | ATmega644p @20 MHz | 64,512 B (boot @ `0xFC00`, 1 KB) | 63,552 B | **960 B** | 3,814 B | **282 B incl. stack** | **measured** |

*Update 2026-11-25: these rows were re-measured with the pinned toolchain. Two reclaim estimates in §3 were too optimistic: FatFs `_USE_MKFS=0` saves 0 B (already discarded), and YAM has a single 200 B static-init stub. See PLAN.md §1.*

Note: Elkhart's changelog reports "% full" against 65,536/32,768, which overstates headroom by the bootloader size.

### Real-time budgets

| Budget | Value | Implication |
|---|---|---|
| Voicecard sample rate | 39.2 kHz (20 MHz / 510) → **510 cycles/sample** total | Heavy oscillator pairs (fmfb, quad, vowel) already eat most of it. Elkhart's `hrm` oscillators audibly break when paired with a second shape, which shows the ceiling is near. |
| Voicecard control rate | `kAudioBlockSize = 40` → **~980 Hz** | Envelopes, LFO4, cutoff, resonance and VCA all update once per ms. |
| Cutoff / resonance CV | **8-bit PWM** (Timer0, pins 5/6, 39 kHz phase-correct); VCA via **12-bit DAC** | Cutoff quantization of about 0.4% of range per step, updated per block. |
| Controller → voicecard bus | 1 SPI byte per Timer2 tick (39.2 kHz), alternating even/odd buffers → **~39 kB/s total** | Part LFO1 refresh (~980 Hz) plus LFO2/3 (~490 Hz), × 2 bytes × 6 voices, is up to **~23.5 kB/s worst case**. That leaves about 40% for notes, edits and any new per-voice streams (MPE/poly-AT). |
| Controller ISRs | Timer1 4.9 kHz (MIDI in/out, UI poll), Timer2 39.2 kHz (clock tick + SPI byte) | MIDI-out granularity ~205 µs. |

### Storage-format slack

New parameters must fit here unless the patch format is bumped.

| Struct | Size | Spare bytes |
|---|---|---|
| `Patch` (`common/patch.h`) | 112 B | **6** (offsets 106–111) |
| `PartData` (`controller/part.h`) | 84 B | **4** (80–83) |
| `MultiData` | 56 B | **4** (52–55) |
| `SystemSettingsData` | — | **8** |
| Shruthi `Patch` | 92 B (SysEx) | `extra_data_[8]` and `op_data_` partly used |

---

## 2. Phase 1 — Audit

### 2.1 Original Ambika → YAM

The diff is small and focused: 10 source files, ~600 changed lines.

**Voicecard (`voicecard/oscillator.{cc,h}`, `voice.{cc,h}`, `resources/*`):**
- PolyBLEP saw/PWM replace the band-limited tables, saving flash.
- `csaw` (CS-80 notch), `qpwm`, `fmfb` (feedback FM/grit), and `vowel 2` were added. The original saw survives as `oldsaw`.
- Triangle is no longer band-limited and folds on modulation.
- Pitch increment LUT lookup is now **linearly interpolated**, giving finer tuning (backported from Shruthi).
- Phase57 velocity→cutoff and key-tracking→cutoff were added as fixed paths in `UpdateDestinations()`.
- A `POLIVOKS_FILTERBOARD` build flag inverts resonance.
- `patch_data_` is re-laid as a `[1]`-offset array: a small codegen trick for the rx path.

**Common (`common/patch.h`):**
- 5 new `WAVEFORM_*` entries appended (enum now 0–42), so old programs keep their oscillator numbers.
- `filter_velo` and `filter_kbt` take patch bytes 104–105, leaving 6 padding bytes.
- `FILTER_MODE_NOTCH` is exposed in the UI.

**Controller:**
- `parameter.cc`: params 73/74, CC 104/105, NRPN 104/105, filter-mode max raised to NOTCH.
- `part.cc`: init patch updated.
- `resources/waveforms.py`: the LFO wavetables were halved, 257 → 129 B per shape, about **−2 KB**. This is why YAM190319's controller is 2 KB smaller than YAM160303's (61,398 → 59,400 B; 160303 had only 42 B free).
- `common/lfo.h`: an interpolation hack for the stepped LFO shapes.
- Uppercase label for the active parameter.

**Untouched by YAM:** voice allocator, polyphony modes, envelopes, mod matrix structure, MIDI/SysEx protocol, storage, UI framework, bus protocol.

### 2.2 Elkhart — mined selectively (groovebox concept rejected)

Elkhart freed its headroom mainly by **deleting** what a polysynth needs: the voice allocator, arp, Part patch/LFO state, the mod matrix (replaced by 4 fixed routings), and aftertouch, pitch bend and mod wheel. None of that is applicable. The table below lists what *is* worth taking.

| Item | Elkhart location | Verdict | Notes |
|---|---|---|---|
| **avr-gcc 4.3.5 pinned toolchain** + `--network none` build | `.github/docker/Dockerfile.squeeze`, `.github/workflows/scripts/squeeze-make.sh`, `docs/planning/TOOLCHAIN_RISK.md` | **Adopt** | Hardware-verified: gcc 5.4/8.5 produce a metallic artifact on YAM/MI DSP. Save the built image to a tarball and vendor the `.deb` files. |
| **Atomic swap of `num_clock_events_`** | CHANGELOG 2026-08-17 | **Adopt (bug exists in YAM)** | YAM `controller/multi.cc:217-220` does `--num_clock_events_` against a Timer2-ISR increment. Elkhart measured ~0.8% random tick loss, which makes the internal clock, arp and synced LFOs run slow and jitter. Related fixes: reset `clock_counter_` in `Start()`, and guard the 16-bit `tick_duration_` store against ISR tearing. |
| MIDI clock-out from ISR | same entry | Adapt (optional) | Only matters if Ambika is a clock master. Cheap. |
| **Envelope curve (linear↔expo blend)** | `voicecard/envelope.h` (`U8Mix(phase>>8, expo, curve_)`) | **Adapt** | Elkhart's version is decay/release only and replaces ADSR with rise/fall. Keep ADSR and apply the curve to attack too. A few dozen bytes plus 1 B per envelope. |
| LFO4 tempo sync, one-shot shapes, retrigger toggle; osc phase reset on note-on | CHANGELOG v4.4, RESOURCE_BUDGET | **Adapt** | Measured +336 B voicecard / +416 B controller. Sync works by broadcasting 1-byte clock ticks to voicecards. |
| Pre-filter wavefolder | `voicecard/voice.cc` (~200 B) | Adapt (optional) | Needs 1 patch byte. Skipped when off, so no CPU cost at zero. |
| sin16 FM carriers / `hrm` additive | voicecard | Reject for now | CPU-fragile, as Elkhart itself notes for `hrm`. |
| **"Orphaned" controller LFO wavetable, −1.9 KB** | CHANGELOG | **⚠ Does NOT apply to YAM** | It only became orphaned after Elkhart deleted the Part LFOs. In YAM, `common/lfo.h` → `wav_res_lfo_waveforms` is live for LFO1–3 shapes `WAVE_1..16` (`controller/part.cc` `UpdateLfos`). |
| C++ static-initializer stubs (`_GLOBAL__I_*`, ~16 TUs × ~156 B) | RESOURCE_BUDGET "Speculative" | **Investigate** | Up to ~1.2 KB of realistic controller flash. Make constructors trivial and call `Init()` explicitly. Should also apply to YAM. |
| FatFs trim (`_USE_MKFS=0`, maybe `_FS_MINIMIZE`) | RESOURCE_BUDGET | Investigate | ~1 KB. Costs the on-device card format, but the SD library and patch history must still work. |
| Removing the half-screen edit popup (−384 B) | CHANGELOG 2026-05-17 | Reject | It's a useful UX feature on a sound-design synth. |
| Shift+encoder ×8 coarse step | CHANGELOG | Adapt | Trivial. |
| `patch.h` self-contained `<avr/pgmspace.h>` include | CHANGELOG | Adopt | Build hygiene. |
| Groove/sequencer/locks/snapshots/EXT tracks | — | Reject | Groovebox scope. |

### 2.3 YAM Ambika vs YAM Shruthi: shared architecture and divergence

**Shared, near-identical code (same author lineage):**
- **Oscillators:** PolyBLEP saw/PWM/csaw, `qpwm`, `fmfb`, CZ, vowel, wavetable renderers. The function bodies are the same modulo namespace (`RenderPolyBlepSaw` diff is empty).
- **Envelope:** `voicecard/envelope.h` vs `shruthi/envelope.h` differ by ~25 lines (namespace, minor).
- **LFO** core, the **NRPN receive state machine** (`Part::ControlChange`), **NRPN echo on edit** (`OnEdit`), the SysEx nibble framing, and the MI manufacturer header.
- **Interpolated pitch LUT:** present in both (Shruthi upstream had it first; YAM ported it to Ambika).

**Divergence:**
- **avrlib pins differ:** Ambika YAM `7faa91d`, Shruthi YAM `36b988a`. Unify on one before sharing code.
- **Modulation:** Shruthi has a 12-slot matrix with built-in key tracking (cutoff += pitch) and two operator slots. Ambika has 14 slots + 4 modifiers, plus YAM's fixed velocity/key-tracking paths.
- **SysEx:** Shruthi's protocol is much richer:
  - name transfer `0x06`/`0x16`
  - full sequencer state
  - current program numbers `0x1A`
  - bank count `0x1B`
  - version `0x1C`
  - write-to-slot `0x21`/`0x22`
  - randomize `0x31`/`0x32`
  - bulk `0x40`–`0x50`

  Ambika only has dump `0x01`–`0x05`, request `0x11`–`0x15`, POKE `0x0F` and PEEK `0x1F`.
- **Shruthi OnEdit** sends **CC when a parameter has one, otherwise NRPN** (it scales the value into 0–127). **Ambika OnEdit** always sends NRPN, with running-address compression: it re-sends the address only on change or every 32 edits.
- **Filter boards:** Shruthi has a runtime `expansion_filter_board` enum (LPF, SSM, SVF, DSP, PVK, 4PM, DLY, SP) with board-specific CV math in `shruthi.cc:FillAudioBuffer` and `voice.cc:UpdateDestinations`. Ambika uses a compile-time `POLIVOKS_FILTERBOARD` flag.
- **Shruthi YAM is on upstream 1.02**, so it **lacks 1.03 fixes:**
  - arpeggiator re-clocking on external clock with no keys held
  - legato steps extending gate length in sequencer mode (`NextStep()`)
  - `AllSoundOff` vs `AllNotesOff` handling on stop
  - `arp_seq_step_` init
- **Shruthi's biggest symbols:**

  | Symbol | Size |
  |---|---|
  | `wav_res_waves` | 16,383 B |
  | `Voice::ProcessBlock` | 3,156 B |
  | `user_wavetable` (**.bss**) | 1,033 B |
  | `lut_res_tempo_phase_increment` | 804 B |

  `user_wavetable` is the only big RAM lever on Shruthi.

### 2.4 Polysynth gap analysis (Ambika YAM, 6 voices, SVF cards)

| Capability | Rev2 / P-6 / OB-6 | Peak | Super 6 / Nymphes | **Ambika YAM** | Gap / note |
|---|---|---|---|---|---|
| Osc per voice | 2 (+sub) | 3 + WT | 2 / 1 | 2 + sub + noise, 43 shapes, 6 mix operators (sum/sync/ring/xor/fold/bits), fuzz, crush | ✅ ahead |
| Filter | 4p/2p LP (OB-6: SEM LP↔notch↔HP **morph**) | 4p/2p multimode | ladder/OTA | 2-pole SVF, LP/BP/HP/Notch via **4052 mux** | Mode morph impossible (hardware). |
| Cutoff CV resolution/rate | analog / 16-bit DAC | high | high | **8-bit PWM @ ~1 kHz update** | **Gap:** zipper on slow high-Q sweeps, steppy fast envelopes |
| Envelopes | 3× ADSR (+delay), curves on some | ADSR + curves | ADSR | 3× ADSR, fixed expo curve, 8-bit endpoints, ~1 ms tick | **Gap:** no curve control |
| LFOs | 4 / 2 | 2/voice + 2 global | 1–2/voice | 3 part LFOs (shared, sent over bus) + 1 voice LFO | Voice LFO not tempo-syncable |
| Mod matrix | 8 slots | 16 slots | small | **14 slots + 4 modifiers** (sum/prod/att/max/min/xor/≥/≤/quant/lag) | ✅ ahead |
| Analog drift / "slop" | yes (per-voice) | — | yes | none | **Gap** |
| Voice calibration | auto-tune | — | auto | none (trimmers) | **Gap:** SVF card spread |
| Unison | N-voice, centered detune, chord memory | yes | Uni A/B, Tri, Duo (Nymphes) | MONO = all part voices at `+i·spread` (**not centered, drifts sharp**); UNISON_2X pairs only | **Gap** |
| Note priority (mono/unison) | low/high/last | yes | yes | last only | Gap (small) |
| Voice stealing | released-first, oldest | yes | yes | same-note reuse → LRU released → LRU oldest; cyclic mode | ✅ adequate |
| Poly AT | Rev2 yes | yes | Super 6 yes | **yes**, routed per voice in POLY/CYCLIC/CHAIN/UNISON_2X | ✅ |
| MPE / per-voice bend | — | Peak (fw) yes | Super 6 MPE | none | **Gap** (bus-budget limited) |
| Velocity curve | yes | yes | yes | raw | Gap (small) |
| Multitimbral | stack/split | 1 | 1 | **6 parts**, per-part channel/keyrange | ✅ ahead |
| Effects | digital FX | FPGA FX | binaural/FX | none (crush/fuzz only) | Out of scope (hardware) |
| Stereo/pan | yes | yes | binaural | 6 individual outs + mono mix | Hardware limit |

---

## 3. Phase 2 — Ranked proposals

Ranking = musical value ÷ (resource cost × risk), with the controller-RAM constraint applied hard.
Cost figures are **estimates** until E1 gives measured deltas. "C" = controller (644p), "V" = voicecard (328p), "S" = Shruthi.
"Patch bytes" = new storage. The 6 spare bytes in Ambika `Patch` are the main currency.

### Tier 0 — Enablers (do first; they gate everything else)

| # | Proposal | Benefit | Files | Cost | Risk |
|---|---|---|---|---|---|
| **E1** | Pinned avr-gcc 4.3.5 container + per-build `.size`/`.map` diff report (C, V, S) | Exact budgets and a reproducible build. Avoids the gcc ≥5 miscompile. | new `toolchain/` (port Elkhart's Dockerfile + script), root `makefile` | 0 B | Low |
| **E2** | Clock-tick race fix (atomic swap), `Start()` phase reset, 16-bit tearing guard | Accurate internal clock, arp and synced LFOs | C: `controller/multi.cc` (`UpdateClocks`, `Start`, `ComputeInternalClockOverflowsTable`) | ~+20–60 B flash | Low |
| **E3** | Controller **RAM reclaim** to get ≥150 B of usable headroom | Gates every controller feature | C: `midi_dispatcher.h` (low-priority out ring 128 → 64 B: −64 B), `voicecard_tx` ring sizes, `multi.h` `tick_duration_table_` (32 B), static-init cleanup | net −100…−200 B RAM | Med (buffer sizing needs a MIDI-burst test) |
| **E4** | Controller **flash reclaim** to get ≥3 KB | Room for C-side features | C: static-initializer removal (≤~1.2 KB), FatFs `_USE_MKFS=0` (~0.5–1 KB), dead strings | −1.5…−2.5 KB | Med |
| **E5** | Decide on the per-part step sequencer (decision for you) | Removing it (keeping the arp) would free ~384 B RAM + a few KB flash | C: `part.{h,cc}`, `ui_pages/sequence_editor.*`, `storage` | big reclaim | Med: SysEx/SD format would keep the bytes as padding |

### Ambika — Voicecard (synthesis depth; preferred home for features)

| Rank | Proposal | Musical/functional benefit | Files | Est. cost | Risk |
|---|---|---|---|---|---|
| **V1** | **Per-sample cutoff ramp + error-feedback dither** in `TIMER2_OVF` | Removes zipper on slow sweeps at high resonance and makes filter envelopes snappier. Effectively ~12–14-bit cutoff resolution from the 8-bit PWM (the RC on the SVF CV line integrates the dithered LSB at 39 kHz). This is the biggest *SVF-specific* sound upgrade. | V: `voicecard.cc` (ISR + main loop write), `voice.h` (expose 16-bit target) | ~120–180 B flash, ~6 B RAM, **~12–20 cycles/sample** | **Med**: ISR budget. Verify with the `timing_signal` pin PD7 on the heaviest oscillator combos. |
| **V2** | **Per-sample VCA ramp** on the 12-bit DAC | Clickless, punchier fast attacks; no 1 ms stair-step on percussive envelopes | V: `voicecard.cc` (DAC write every sample instead of per block) | ~60–100 B, ~4 B RAM, ~25–35 cycles/sample (extra SPI frame) | Med (same ISR budget as V1; ship together behind one flag) |
| **V3** | **Envelope curve per envelope** (log↔lin↔exp, attack included); adapted from Elkhart | Analog-style concave attacks, plucky exponential decays, linear "digital" ramps | V: `envelope.h`, `voice.cc` (`Update`); C: `parameter.cc` (+3 params), `common/patch.h` (3 of 6 spare bytes, or pack 3 × 2-bit into 1 byte for 4 curve presets) | V ~80–120 B; C ~120 B; patch 1–3 B | Low |
| **V4** | **Per-voice "vintage/slop"**: static per-card offsets (pitch ± few cents, cutoff offset, env-time scale) + slow random drift (filtered noise, 0.2–2 Hz) scaled by one `vintage` amount | Prophet/OB-style organic polyphony; voices stop sounding cloned | V: `voice.cc` (pitch/cutoff/env paths), seed from voicecard EEPROM or a controller-sent voice index; C: 1 param, 1 patch byte | V ~150–250 B, ~8 B RAM; C ~60 B | Low |
| **V5** | **Per-voicecard calibration trims** (cutoff offset/scale, resonance max, VCA offset) stored in **voicecard EEPROM**, edited from a controller calibration page | Matched SVF cards, so slop becomes intentional rather than tolerance | V: `voicecard_rx.cc` (new write command), `voice.cc` apply; C: new `ui_pages/calibration_page.*`, `common/protocol.h` | V ~120 B; C ~400–600 B | Med (new bus command; needs a controller flash reclaim) |
| **V6** | **Resonance gain compensation** (VCA += f(resonance), optional depth) | SVF low end drops at high Q; keeps level and bass when resonance is swept | V: `voice.cc` `UpdateDestinations` | ~40–60 B | Low |
| **V7** | **Voice LFO (LFO4): tempo sync, one-shot shapes, retrigger toggle; osc phase reset on note-on**; adapted from Elkhart | Rhythmic per-voice modulation without the part-LFO bus cost; consistent attack transients | V: `common/lfo.h`, `voice.cc`, `voicecard_rx.cc` (tick command); C: `multi.cc` tick broadcast, `parameter.cc` | V ~340 B; C ~420 B (Elkhart measured) | Med (C flash; bus +6 B per MIDI clock) |
| **V8** | **Mod-matrix additions**: modifiers `S&H-on-gate`, `abs/rectify`, `curve`; destinations `portamento`, `env curve`, `vintage` | More expressive routings without new hardware | V: `voice.cc` (`ProcessModulationMatrix`, `LoadSources`); C: `parameter.cc`, strings | V ~100–200 B; C ~150 B | Low–Med |
| **V9** | **Wavefolder** (pre-filter, iterative); adapted from Elkhart | Timbral depth (west-coast character) feeding the analog SVF | V: `voice.cc`; C: param + 1 patch byte | V ~200 B; C ~60 B | Low (skipped when 0) |
| — | Continuous SVF mode morph | — | — | — | **Infeasible** (4052 mux; would need a hardware mod) |
| — | Audio-rate filter FM (poly-mod osc→cutoff) | — | — | — | **Infeasible** at an 8-bit/39 kHz PWM CV without hardware change. V1 helps up to ~sub-kHz rates only. |

### Ambika — Controller (voice allocation and expressiveness)

| Rank | Proposal | Benefit | Files | Est. cost | Risk |
|---|---|---|---|---|---|
| **C1** | **Centered unison detune + curve** (symmetric ±n·spread; optional JP-style non-linear table), applied to MONO and UNISON_2X | Fat unison that stays in tune; today MONO stacks drift sharp by up to 5·spread | C: `part.cc` `InternalNoteOn/Off` (pitch_drift loop), `UNISON_2X` branch | ~100–200 B flash, 0 RAM | Low |
| **C2** | **Unison voice count** (2/3/6 per note → "UNISON_N", covering Nymphes Tri/Duo-style modes) | Thicker stacks with residual polyphony (6 voices / 2 = 3-note poly, / 3 = 2-note) | C: `part.{h,cc}` (`PolyphonyMode`, `InitializeAllocators`), `parameter.cc` | ~250–400 B | Low–Med |
| **C3** | **Note priority** for MONO/unison: last / low / high | Bass-line playing; correct trill behaviour | C: `part.cc`, `note_stack.h`; 1 `PartData` spare byte | ~150 B, 0 RAM | Low |
| **C4** | **Velocity curves** (soft/lin/hard/fixed) per part | Matches keyboards; consistent velocity→filter (phase57) response | C: `part.cc` (at `voicecard_tx.Trigger`); 1 `PartData` byte | ~60–100 B | Low |
| **C5** | **Voice stealing tweaks**: optional "protect lowest note" and "steal oldest released first" (already effectively released-first) | Keeps bass notes when overplaying 6 voices | C: `voice_allocator.cc` | ~80 B | Low |
| **C6** | **MPE-lite**: a part listens on N channels (lower zone), channel→voice map, per-voice bend/pressure/CC74 → `VOICECARD_DATA_MODULATION`, with **coalescing** (latest value per voice per control tick) | Expressive controllers (Roli/Linnstrument/Osmose) | C: `multi.cc` (channel routing), `part.cc`, new tiny `mpe` state; V: per-voice bend range | C ~700–1,000 B flash, **~30 B RAM**; bus up to +~6 kB/s | **Med–High** (RAM + bus; needs E3/E4) |
| **C7** | **Mono legato/auto-glide** (portamento only on overlapping notes) | Classic mono-lead behaviour | C: `part.cc` legato path (already passes `legato` flag); V: `voice.cc` portamento gating | ~40 B | Low |

### UI & performance ergonomics (controller)

| Rank | Proposal | Benefit | Files | Est. cost | Risk |
|---|---|---|---|---|---|
| **U1** | **Encoder acceleration** (time-based) + **Shift+encoder ×8** | Faster value and patch navigation | C: `ui.cc` encoder event, `ui_pages/parameter_editor.cc` | ~80–120 B, 2 B RAM | Low |
| **U2** | **A/B compare** using the existing SD clipboard/history (YAM still has Copy/Swap/Paste/Snapshot on Shift+1/2/3/7) | Compare edited vs stored without the RAM cost of a 112 B buffer | C: `ui_pages/*` (one key binding), `storage.cc` (`Swap` reuse) | ~150–250 B, 0 RAM | Low–Med (SD latency ~100 ms) |
| **U3** | **Faster naming**: pot *n* edits character *n*; encoder click cycles char class (A / a / 0 / symbol) | Naming in seconds | C: `ui_pages/library.cc` name editor | ~150 B | Low |
| **U4** | **Instance cycling shortcut** (ENV/LFO/MOD slot: hold page button + encoder) | Fewer button presses in deep editing | C: `ui.cc`, `parameter_editor.cc` | ~80 B | Low (verify the current page model on hardware) |
| **U5** | **Calibration page** (front end for V5) | — | C: new page | see V5 | Med |

### Shruthi (shared DSP and control backports)

Every Shruthi item has to fit in **962 B flash / ~282 B stack** unless reclaimed.

| Rank | Proposal | Benefit | Files | Est. cost | Risk |
|---|---|---|---|---|---|
| **S1** | **Upstream 1.03 fixes**: arp reclock on ext clock, legato seq steps, stop/AllNotesOff handling | Correct sequencing/arp behaviour | S: `shruthi/part.cc` | ~+100–200 B | Low |
| **S2** | **Envelope curves** (shared implementation with V3) | Same as V3 | S: `shruthi/envelope.h`, `voice.cc`, `parameter.cc`, `patch.h` (`extra_data_` spare) | ~150–250 B | Low |
| **S3** | **Filter-board profile ("custom" board)**: resonance knee, CV1/CV2 source, mode-bit mapping, cutoff offset, stored in system settings | Third-party CS-80 / IR3109 boards get correct resonance scaling and CV routing without hard-coding; SMR4 and Polivoks keep their existing paths | S: `shruthi.cc` `FillAudioBuffer`, `voice.cc`, `system_settings.h`, `parameter.cc` | ~250–400 B | Med |
| **S4** | **Vintage drift** (slow pitch/cutoff drift; single voice) | Organic mono lines | S: `voice.cc` | ~100 B, 4 B RAM | Low |
| **S5** | **Flash/RAM reclaim** (decision): drop `user_wavetable` (−1,033 B **RAM**) and/or rarely used tables; compute `lut_res_tempo_phase_increment` (804 B) | Makes S1–S4 fit comfortably | S: `oscillator.cc`, `resources` | −0.8…−2 KB flash, −1 KB RAM | Med (feature loss: user wavetable) |

### Code sharing (YAM Ambika ↔ YAM Shruthi)

1. **One avrlib pin** for both trees. A prerequisite.
2. **`shared/dsp/`**: PolyBLEP saw/PWM/csaw, `qpwm`, `fmfb`, vowel, plus the `envelope.h` curve logic. These are header-only templates parameterized by namespace and resource tables, compiled into each target. Today's bodies are identical, so this is a mechanical move. It also lets V3/S2 ship once.
3. **`shared/midi/`**: NRPN receive state machine plus `OnEdit` echo, with one documented encoding for both (§4.1). The web editor then has one protocol layer.
4. **Do not share:** voice/part structures, filter-board CV math, UI. The hardware differs too much.

---

## 4. Phase 3 — Web MIDI editor

### 4.1 Extracted protocol (from YAM firmware source + Ixox)

**SysEx frame (both synths):**

```
F0 00 21 02 00 <dev> <cmd> <arg> <payload as hi/lo nibbles…> <cksum hi> <cksum lo> F7
dev: 0x04 = Ambika, 0x02 = Shruthi
cksum = (sum of decoded payload bytes) & 0xFF   (Ambika PEEK reply: address bytes included)
```

Requests have an empty payload but still carry `00 00` checksum nibbles (9-byte body, as Ixox sends).

**Ambika commands** (`controller/storage.cc` `SysExParseCommand` / `SysExAcceptCommand`):

| cmd | Object | Payload | `arg` |
|---|---|---|---|
| `0x01` | Patch | 112 B | target part: `0` = active part, `1–6` = part *n* |
| `0x02` | Sequence (PartData offsets 8–79) | 72 B | same |
| `0x03` | Program (patch + part) | — | dump arrives as two messages, `0x01` + `0x05` |
| `0x04` | Multi | 56 B | — (Ixox comment "docs say 5" is wrong; 4 is correct) |
| `0x05` | Part (PartData) | 84 B | same |
| `0x0F` | **POKE** RAM | `addr_lo, addr_hi, data…` | `arg` = length |
| `0x11–0x15` | Request object (`cmd − 0x10`) | none | part as above |
| `0x1F` | **PEEK** RAM | `addr_lo, addr_hi` | `arg` = length; reply is cmd `0x0F` with address + data |

Reply `arg` = `location.alias`: **`0` for single-part requests** (not the part number!) and `1–6` only inside a Multi dump. Multi dump order is Multi, then for each part: Patch, Part.

**Ambika NRPN map:**
- NRPN number = **raw byte address**: 0–111 = `Patch`, 112–195 = `PartData` (e.g. 127 = polyphony mode).
- `NRPN MSB` (CC99) = address bit 7; `NRPN LSB` (CC98) = address & 0x7F.
- `Data MSB` (CC6) = value bit 7 (0/1); `Data LSB` (CC38) = value & 0x7F, and **commits the write**.
- Signed params are two's-complement bytes; decode as `v > max ? v − 256 : v` (Ixox rule).
- CC98 must follow CC99 (LSB resets the MSB latch), and CC6 must precede CC38. Data inc/dec (CC96/97) are supported.
- Rx is gated by System → `rx nrpn`.
- **Per-part channel:** NRPN goes to every part listening on that channel.

**Ambika CC map** (`controller/parameter.cc` `midi_cc` column, e.g. 104/105 = filter velo/kbt): CC values are *scaled* 0–127 → param range, so the CC path is lossy for small-range params. **Use NRPN for editing.**

**Ambika hardware → host feedback:** `MidiDispatcher::OnEdit` sends NRPN for every *user-initiated* `Part::SetValue` (pots, encoder) when **MIDI out mode ≥ `ctrl`**. It re-sends the NRPN address only when it changes or every 32 values (running-address compression). Program change out happens only in `full` mode.

**Shruthi:**
- `Patch` = 92 B on the wire (name at bytes 68–75).
- Commands: `0x01` patch, `0x02` sequence, `0x03` wavetable, `0x04` system, `0x05` step seq, `0x06` name, `0x07` full seq state; requests `0x11`–`0x17`; `0x1A` current numbers; `0x1B` bank count; `0x1C` version; `0x21`/`0x22` write to slot; `0x31`/`0x32` randomize; `0x40`–`0x43`/`0x50` bulk.
- NRPN: MSB = 0, LSB = patch offset. Signed values are range-checked on rx.
- `OnEdit` sends **CC if the parameter has one, otherwise NRPN**, and only in `ctrl`/`full` modes.

**Ixox edge cases and bugs worth avoiding:**
- **Osc Shape max = 37** → YAM 38–42 can't be selected or displayed correctly, and the label list omits `vowel 2`.
- Single-part dump replies can't be attributed (`arg = 0`). Ixox works around this with one-shot `canReceiveSysexPatch` flags. That means one outstanding request at a time, and multiple plugin instances race each other.
- Multi decode reads 52 B but sends 56 B.
- Patch push = 16 part NRPNs + one patch SysEx. Sequences are pushed as 64 individual NRPNs. Without pacing, a USB-MIDI → 31.25 kbaud bridge can overflow.
- No patch names for Ambika: names live only in SD filenames and never go over SysEx.

### 4.2 Firmware hooks to add (YAM+)

Ordered by editor value ÷ controller cost. Most are SysEx-only, so they add flash but **no RAM**, which matters with 241 B free.

| # | Hook | Why | Est. C flash |
|---|---|---|---|
| H1 | **Dump replies carry the real part number** (`alias = part+1` for single requests) | Unambiguous sync and multiple outstanding requests | ~10 B |
| H2 | **Version/capabilities query** (`0x1C`, mirroring Shruthi): firmware ID, YAM+ version, `WAVEFORM_LAST`, patch layout version, voicecard versions (already readable via `COMMAND_GET_VERSION_ID`) | Editor picks the right parameter map automatically | ~80–120 B |
| H3 | **Current program query** (`0x1A`): per part bank/slot + name | Librarian shows what's loaded | ~120 B |
| H4 | **Name transfer** (`0x06`/`0x16`): read/write the SD name of the active program per part | Ambika patch names in the browser | ~150–250 B |
| H5 | **Write-to-slot** (`0x21`: part, bank, slot; uses the existing `storage.Save` path) | Librarian can store to the SD card | ~100–150 B |
| H6 | **Change notification**: send a short SysEx/NRPN when a program is loaded on the front panel (`full` mode already sends PC; add it for `ctrl`) | Browser knows to re-pull | ~40 B |
| H7 | **Edit echo for non-user changes** (optional flag): echo NRPN for CC-driven changes too | Keeps the browser in sync when a DAW automates via CC | ~30 B |
| H8 | (Shruthi) everything above already exists except H7 and the YAM+ capability bytes in `0x1C` | — | ~50 B |

Leave POKE/PEEK in place: they are a debugging and recovery tool for the editor, e.g. reading the voicecard version table. But **don't** build normal sync on raw addresses, because they shift with every build.

### 4.3 Architecture (TypeScript + Vite, static SPA, no backend)

```
src/
  midi/
    access.ts          navigator.requestMIDIAccess({sysex:true}); port pick/persist; hot-plug
    framer.ts          SysEx assemble/split, nibble codec, checksum; running-status safe parser
    nrpn.ts            NRPN encoder (address/data MSB/LSB order) + decoder w/ running-address cache
    scheduler.ts       outbound queue: per-port byte budget (≈2.5 kB/s safe for 31.25 kbaud),
                       priority lanes (realtime edits > requests > bulk), pacing between SysEx
  protocol/
    ambika.ts          command table §4.1, object sizes, part addressing, reply correlation
    shruthi.ts
    capabilities.ts    H2 probe → selects param map; fallback = stock YAM map
  model/
    params/ambika-yam.ts   single source of truth: address, name, unit, min/max, signedness,
    params/shruthi-yam.ts  enum labels (incl. all 43 YAM osc), CC#, page/group, visual widget
    patch.ts           typed views over Uint8Array (112/92 B), diff, validate/clamp
    state.ts           reactive store per device/part; "dirty vs hardware" tracking
  sync/
    engine.ts          bidirectional sync (below)
  librarian/
    syx.ts             .syx import/export (single, program, multi, bank; Ixox/MI format compatible)
    db.ts              IndexedDB: banks, tags, favourites, history
    morph.ts           param-aware interpolation (continuous: lerp; enums: switch at t=0.5;
                       mod-matrix slots: crossfade amounts only)
    randomize.ts       constrained random (lock groups, ranges, "musical" presets per section)
  ui/                  framework-light (Lit or Preact): panels, mod-matrix graph, envelope/LFO
                       editors, SVF response viz, multi/part view, librarian
```

**Bidirectional sync engine:**
- **Browser → hardware:** UI drag events are coalesced per parameter (keep only the latest value) and flushed at **~30–50 Hz per parameter** through `scheduler.ts`. The engine uses running-address NRPN, mirroring the firmware's compression, and re-sends the address every 32 values or on change. While a drag is active, the outbound address is marked "owned by browser".
- **Hardware → browser:** NRPN echoes from `OnEdit` update the store. An echo for a parameter the browser is currently dragging is ignored for ~150 ms (*echo suppression*), so pot and slider don't fight.
- **Pull:** request patch + part (+ multi), correlated by H1's part number. Until H1 lands, fall back to one outstanding request at a time with a timeout.
- **Push:** a full patch goes as one SysEx (`0x01`). A single edit goes as NRPN, never SysEx. Part settings go as NRPN.
- **Drift detection:** after a burst, re-pull the patch and diff it against the model. Highlight mismatches instead of silently overwriting.
- **Throttling floor:** keep ~25% of the 31.25 kbaud budget free for notes. Pause bulk transfers while notes are arriving.
- **De-zippering** is ultimately the synth's job: per-block parameter updates. V1/V2 make browser-driven cutoff sweeps smooth on SVF cards.

**UI map (unified Ambika/Shruthi):**
- **Header:** device/port, synth type (auto via H2), part selector (Ambika 1–6), pull/push, sync status LED, MIDI-out-mode warning (if hardware isn't in `ctrl`/`full`, explain how to set it).
- **Voice panel:** 2× oscillator cards (shape picker with all YAM shapes and a mini waveform preview), mixer with operator, sub, noise, fuzz, crush.
- **Filter panel:** cutoff/res/env/LFO/velo/kbt, **SVF mode visualizer** (LP/BP/HP/Notch magnitude response drawn from cutoff/resonance; discrete mode buttons that make the 4052 switching explicit), plus per-board profiles for Shruthi.
- **Modulation:** 3 envelopes with draggable ADSR (+ curve if V3), 3 part LFOs + voice LFO, **mod-matrix graph** (sources left, destinations right, edges = amount, colour = sign), modifier slots as nodes.
- **Part/Multi:** voice-allocation grid (6 voices × 6 parts), channel, keyrange, polyphony mode, spread/unison (+ C1/C2), legato/portamento, arp.
- **Librarian:** IndexedDB banks, drag-drop `.syx`, per-patch tags, A/B compare in the browser (free: no synth RAM), morph slider between two patches, constrained randomizer, "send to slot" (H5).

**Browser requirements:** Chrome/Edge on a secure context (localhost or https). `sysex: true` triggers a permission prompt. Firefox works only with the Web MIDI add-on gate, and Safari not at all: document this.

---

## 5. Decisions needed from you

1. **Toolchain:** OK to pull and build Elkhart's pinned Debian-Squeeze avr-gcc 4.3.5 image in Docker for exact baselines and maps?
2. **Feature priorities:** my recommended first wave is
   - **E1 + E2 + E3/E4** (enablers)
   - **V1 + V2** (SVF cutoff/VCA smoothing)
   - **V3** (envelope curves, shared with S2)
   - **V4** (vintage/slop)
   - **C1** (centered unison)
   - **U1** (encoder acceleration)
   - **H1–H4** (editor hooks)

   All of these are low-RAM.
3. **Reclaims that remove features:**
   - Ambika per-part step sequencer (E5)
   - Shruthi user wavetable (S5)
   - FatFs on-device format (E4)
4. **Patch-format policy:** stay within the 6 spare bytes (pack curve presets etc.), or bump the format with a migration?
5. **Shruthi filter boards:** which setting do your CS-80 and IR3109 boards currently run under (LPF/SSM/4PM)? This shapes S3.
