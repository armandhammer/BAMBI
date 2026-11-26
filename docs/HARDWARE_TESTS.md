# YAM+ hardware test checklists

> *Moved from the original YAM+ workspace into BAMBI. Paths such as `firmware/ambika/` mean this repository's root; `toolchain/` and `tools/yamplus_sysex.py` are now `toolchain/` and `utils/yamplus_sysex.py` here; `release/<name>/` folders correspond to [GitHub Releases](https://github.com/armandhammer/BAMBI/releases). The `yam-plus` branch is `main`.*

**Start with `release/yamplus-0.1/`** (everything). If something misbehaves,
the per-milestone sets in `release/m0-probes/` … `release/m6-sysex-hooks/`
let you bisect: each adds one milestone on top of the previous one. Rollback
files (stock YAM190319) are in `release/rollback-yam190319/`. Checksums are
in `release/SHA256SUMS`. Feature notes: `release/yamplus-0.1/YAMPLUS.md`.

## Flashing (all milestones)

1. **Back up the SD card** (programs, multis, everything) to your computer.
2. **Controller:** copy `AMBIKA.BIN` to the SD root. Open the OS-info page
   (System group, the page showing `ambikaYAM v1.0 | port 1 device 1 v1.0`)
   and press **S1 "upgrade"**. The controller reboots into the SD loader and
   flashes itself.
3. **Voicecards:** copy `VOICE1.BIN` … `VOICE6.BIN` to the SD root (same
   binary, one file per port). On the OS-info page, turn the encoder to
   select `port N` and press **S4 "upgrade"**. Repeat for ports 1–6.
4. **Rollback:** do the same with the files from
   `release/rollback-yam190319/`.

Controller and voicecards can be updated independently for M0. A new
controller talking to old voicecards shows nonsense load numbers but works
otherwise.

---

## M0 — measurement probes (`release/m0-probes/`)

**What changed:** diagnostics only, no sound changes. The OS-info page's
bottom line now shows:

```
upgrade stk123 | upgrade ld 45% u  0             exit
         ^^^^^^             ^^^^^^^^^^^
   controller free stack    selected voicecard: peak CPU load, underruns
```

- `stkNNN`: worst-case free stack on the controller since boot, in bytes.
  It only goes down as you use more features.
- `ldNNN%`: worst-case CPU load of the selected voicecard since boot (or
  since the last clear). 100% means a block took exactly its time budget.
  Short peaks above 100% are absorbed by the audio buffer.
- `uNNN`: audio underruns (dropouts) on that voicecard. Should stay 0.
- **Encoder click** on this page clears the selected voicecard's `ld`/`u`.
- The page queries the voicecard on every refresh, which briefly stalls the
  controller. Play on another page, then come here to read the numbers.

**Checks:**

1. [ ] After flashing both, the instrument boots and plays normally. Programs
   load and sound the same as before (the audio path is unchanged).
2. [ ] OS-info shows `stk` with a plausible number (expected roughly
   100–200). Note the value right after boot.
3. [ ] Use the instrument for a few minutes: browse and load programs from
   the SD card, save one, turn knobs, play the arpeggiator. Come back and
   note `stk` again. **This is the controller's real headroom**; please send
   me the lowest value you see.
4. [ ] For each port 1–6, note `ld` and `u` after boot with no notes played
   (idle load).
5. [ ] **Baseline load:** for each of these, clear with an encoder click
   (port 1), play for ~1 minute on another page, then read `ld`/`u`:
   - a. init patch, 6-note chords
   - b. heaviest patch: osc1 `fmfb`, osc2 `qpwm`, fuzz and crush up, several
     mod-matrix slots active, 6-note chords with fast LFOs
   - c. two or three of your favourite programs
6. [ ] Any `u` above 0 anywhere? (That would also mean YAM190319 underruns
   on that patch, since the audio path is unchanged.)

**Please send back:** `stk` (after boot, and the lowest after use) and the
`ld`/`u` table for 4–5. Those numbers set the budget for M2 (SVF cutoff and
VCA smoothing).

---

## YAM+ 0.1 full check (`release/yamplus-0.1/`)

Flash the controller **and all six voicecards**. The OS-info page should
show `YAMplus v0.1`, and each port `device 1 v1.1`.

### A. Nothing changed that shouldn't (5 min)
1. [ ] Load 5 or more of your existing programs. They should sound like
   they did on YAM190319: same tuning, envelopes, filter. (The new
   parameters read 0 = stock behaviour; spread mode reads `stck`.)
2. [ ] MIDI in/out, program change and SD save/load work as before.

### B. M0: probes
3. [ ] The M0 checks above (`stk`, `ld`/`u` per port, idle and on the
   heaviest patch). **The `ld` values now include the M2 smoothing cost.**
   Gate: worst case below 90%, `u` stays 0. If a port underruns, tell me
   the patch: smoothing can be thinned at build time (`CV_DECIMATION=8`).

### C. M1: clock
4. [ ] Internal clock at 120 BPM, MIDI out mode `seq`, arpeggiator running:
   count MIDI clock messages (0xF8) for 60 s in a MIDI monitor. Expect
   2,880 ± 1. (On YAM190319 it was likely slower; optional comparison.)
5. [ ] Arpeggio and clock-synced LFOs stay locked to a DAW over a few
   minutes; the first arp note comes right on the key press.

### D. M2: SVF smoothing (listen; A/B against YAM190319 if you can)
6. [ ] Init patch, resonance ~50, slow 30 s cutoff sweep with the knob or a
   slow LFO: no audible stepping.
7. [ ] Fast pluck (attack 0, short decay, filter env amount high): tighter,
   no clicky stair-steps; long VCA releases fade smoothly.
8. [ ] Fast filter-envelope "zaps" and VCA tremolo still sound right (no
   smearing beyond ~1 ms).

### E. M3: envelope curves (voice LFO page, bottom row `crv1`–`crv3`)
9. [ ] `crv1` = 0 sounds identical to before. 64 gives linear ramps (most
   audible on a slow attack/release of the VCA envelope), 127 slow-start
   swells.

### F. M4: vintage (voice LFO page, knob 8 `vint`)
10. [ ] `vint` 0: identical to before. 30–60 on a 6-note saw pad: gentle
    chorusing and slightly different brightness per voice. 127: clearly
    "sloppy" but still musical.
11. [ ] Mono unison (polyphony mono, 6 voices) with `vint` 40: thick,
    drifting stack.

### G. M5: spread and encoder
12. [ ] Part in mono with 6 voices, spread 20: `sprm` `stck` = old sound
    (stack sharp of the played note); `cntr` = stack centered on the note
    (check with a tuner); `wide` = centered, supersaw-like.
13. [ ] A new/init part shows `sprm` = `cntr`.
14. [ ] Spinning the encoder fast on a 0–127 value covers the range in about
    a turn; slow turns step by 1; page navigation doesn't jump.
    Shift(S1)+encoder ×8 reaches the min/max exactly.

### H. M6: SysEx (optional, needs a computer)
15. [ ] `pip install mido python-rtmidi`, then from the workspace:
    `python tools/yamplus_sysex.py --list`, then e.g.
    `python tools/yamplus_sysex.py --in "<port>" --out "<port>" version`,
    `... locations`, `... name --part 1 --object program`,
    `... dump --part 2 --object patch` (the reply should say argument 2).
16. [ ] The Ixox editor still pulls and pushes patches and multis.

**Please send back:** `stk` values, the `ld`/`u` table, the 0xF8 count, and
anything that sounds wrong (with the program name).

---

## BAMBI 0.2-dev: fixes found by the native test harness

These came out of `test/native` (firmware compiled for a PC and
unit-tested). Each one is covered by a test there; these checks confirm
the hardware agrees. Flash the controller *and* all six voicecards.

### I. Patches still reach the voicecards (5 min)
The voicecard now writes incoming patch bytes straight into its patch
(stock YAM went through a 1-byte array and relied on the linker).
1. [ ] Load a few factory programs: each sounds as before.
2. [ ] Turn cutoff, an envelope time, an oscillator shape and a mod-matrix
   amount on part 1: each change is heard immediately on all its voices.
3. [ ] Change part volume and portamento: heard on all voices.

### J. Voice allocation (10 min)
4. [ ] Part 1 with 6 voices, polyphony `cyclic`: hold six notes, then
   release them; play six new ones. All six voices sound, in rotation.
5. [ ] Still `cyclic`: play and release a few notes, then play note 127 (or
   transpose up until the top key is G9) and release it. It stops (no
   hanging note).
6. [ ] Needs a keyboard with polyphonic aftertouch. Route aftertouch to
   cutoff in the mod matrix. Polyphony `cyclic`, hold six notes and press
   each key harder: *every* voice responds (stock YAM: only half did).
7. [ ] Same in `chain` with a second Ambika (or just watch the voicecard
   LEDs): pressing harder on a note that was passed down the chain must
   not change any local voice.

### K. Oscillators (5 min)
8. [ ] Osc 1 shape `wavquence`, sweep the
   parameter 0–127: up to 79 it steps through the waves as before; from 80
   up it stays on the last wave (stock YAM played random flash data here).
9. [ ] Shapes `saw`, `pwm` and `csaw`: play the top two octaves with
   pitch bend and PWM modulation. Listen for clicks or crackles: there
   should be none (and no change below the top octaves).

### L. Library (2 min)
10. [ ] With an SD card: save a program, edit it, save again, and use the
    version manager to go back one version. Works as before.

**Please send back:** anything that sounds different from YAM+ 0.1 in
I or K.
