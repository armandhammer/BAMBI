# YAM+ 0.1 for Ambika

YAM+ builds on [YAM](README) (bjoeri/ambika, YAM190319) for the Ambika
6-voice polysynth. It focuses on sound and playability: no sequencer or
groovebox features. **Existing programs sound the same**: every new
parameter's value 0 is YAM's behaviour, and the patch format is unchanged
(the new settings use spare bytes).

Update the controller (`AMBIKA.BIN`) **and** all six voicecards
(`VOICE1.BIN` … `VOICE6.BIN`). The OS-info page shows `YAMplus v0.1`, and
YAM+ voicecards report `v1.1`.

## What's new

### Smoother analog control voltages (voicecard)
The voice computes cutoff, resonance and VCA about 1,000 times a second.
YAM wrote them as steps: slow resonant sweeps zippered on the 8-bit cutoff
PWM, and fast envelopes moved in 1 ms stairs. YAM+ ramps every new value in
over 32 samples at ~10 kHz, and dithers the cutoff PWM so the voicecard's
CV filter sees sub-step resolution. Nothing to set; it's always on.

### Envelope curves: `crv1` `crv2` `crv3` (voice LFO page, bottom row)
One shape per envelope, applied to attack, decay and release:
- `0`: exponential, YAM's shape (fast-starting attack, natural decays)
- `64`: linear
- `127`: inverse exponential (slow-starting swells, "held" decays)

### Vintage: `vint` (voice LFO page, knob 8)
Analog-style variance between voices. Each voicecard slot gets its own
small pitch, cutoff and envelope-time offsets, plus a slow, independent
drift. At 127: up to about ±15 cents and ±5 cutoff steps per voice. Try
20–50 for a subtle, living poly sound.

*Since 0.2:* vintage also adds per-note slop (each new note starts up to
±6 cents and −2…+1 envelope-time steps off, like an old poly from note to
note), a separate slow drift on oscillator 2 (up to ±6 cents against
oscillator 1, so the two beat), and a per-voice resonance offset (up to ±2
steps). Still exactly YAM at 0.

### Spread mode: `sprm` (voice LFO page, top row, knob 4; part setting)
How the part's `spread` detunes stacked or allocated voices:
- `stck`: YAM behaviour. Voice *n* is raised by *n* × spread, so big mono
  stacks drift sharp. Existing parts load as `stck`.
- `cntr`: voices spread symmetrically around the played pitch (new parts
  default to this).
- `wide`: symmetric, with inner voices closer to the center and outer voices
  at the same extremes (supersaw-like).
- `sub-` (0.2): in `mono` and the unison modes, the last voice of the stack
  plays one octave below the played pitch and the others spread as in
  `cntr`. In the polyphonic modes it is the same as `cntr`.

### Unison stacks: `3x unison`, `4x unison` (0.2; part polyphony mode)
Like YAM's `2x unison` with three or four voices per note. With six voices,
`3x unison` plays two notes and `4x unison` one (the two leftover voices
stay silent rather than steal half a stack). A part with fewer voices than
the stack size stacks all of them. Spread and spread mode detune the stack.

### Voice steal: `stl` (0.3; voice LFO page, top row, knob 1; part setting)
Which held note a polyphonic part cuts when a new note finds every voice
held. Released voices (still ringing out) are always reused first, as in
YAM. Applies to `poly`, `chain` and the unison modes; `cyclic` keeps
rotating and `mono` has no voices to steal.
- `old`: YAM behaviour, the least recently played note. Existing parts load
  as `old`.
- `low`: the lowest held note (high-note priority: a melody played over a
  held chord keeps sounding). A new note below every held note is not
  played.
- `high`: the highest held note (low-note priority: keeps the bass). A new
  note above every held note is not played.
- `none`: never steal. A new note is not played until a voice is released.

A note that is not played is not forwarded down the chain either, and is
not played later when a voice frees up.

### Voice LFO trigger and slew, velocity curve (0.4; new third page)
Press the ENV/LFO group button a third time (after the voice LFO page) for
a page with the whole voice LFO and the velocity curve. Top row: `rate`
and `wave` (the same settings as on the voice LFO page), `trig`, `slew`;
bottom row: `velo`. All are patch settings, applied by each voicecard.
- `trig` (voice LFO trigger):
  - `free`: free running, as in YAM. Existing patches load as `free`.
  - `env~lfo`: every new note (not a legato note) restarts the voice's LFO
    at the start of its cycle; with `s&h` it draws a new random value.
  - `once`: one-shot. Like `env~lfo`, then the LFO stops at the end of its
    first cycle and holds its last value until the next note. With `ramp`
    it is a per-voice rising envelope (rate = time); with `s&h` a random
    value per note; with `tri`/`sqr` a single swell or a delayed step.
- `slew` (0-127): smooths the voice LFO output (one-pole lag), 0 = off.
  Takes the edges off `s&h` and `sqr` (glides between random values); about
  3 ms at 1, 0.5 s at 64, 2.6 s at 96.
- `velo` (velocity curve): `lin` (as YAM), `soft` (more output from soft
  playing; half velocity gives 75%) or `hard` (needs a firmer touch; half
  velocity gives 25%). It shapes the velocity modulation source, so it
  applies to every velocity routing in the matrix and to `velo~vcf`.
  Existing patches load as `lin`.

### Faster editing
- Encoder acceleration: turning quickly moves values ×2/×4 (page navigation
  is not accelerated). Shift(S1)+encoder ×8 still works.
- Coarse and accelerated steps now stop at the parameter's minimum/maximum
  instead of refusing to move.

### Diagnostics (OS-info page, bottom line)
- `stkNNN`: worst-case free stack on the controller since boot.
- `ldNNN% uNNN`: worst-case CPU load and audio underruns of the selected
  voicecard. Encoder click clears them.

### Fixes
- The internal clock lost about 1% of its ticks (race between the timer
  interrupt and the main loop), so the arpeggiator, sequencer, clock out and
  synced LFOs ran slow and jittered. Fixed, along with two related 16-bit
  races; the clock now starts in phase with Start.

## MIDI

| Parameter | CC | NRPN | Range |
|---|---|---|---|
| env1/2/3 curve | 110 / 111 / 112 | 106 / 107 / 108 | 0–127 |
| vintage | 113 | 109 | 0–127 |
| spread mode (part) | 114 | 192 | 0 stck, 1 cntr, 2 wide, 3 sub- (0.2) |
| polyphony mode (part) | 107 | 127 | as YAM (0–4), 5 3x unison, 6 4x unison (0.2) |
| voice steal (part) | 115 | 193 | 0 old, 1 low, 2 high, 3 none (0.3) |
| voice LFO trigger | 116 | 110 | 0 free, 1 env~lfo, 2 once (0.4) |
| voice LFO slew | 117 | 111 | 0-127 (0.4) |
| velocity curve | 118 | 30 | 0 lin, 1 soft, 2 hard (0.4) |

NRPN encoding as in YAM: NRPN MSB (CC99) = address bit 7, LSB (CC98) = address
bits 0–6; data MSB (CC6) = value bit 7, LSB (CC38) = value bits 0–6.

### SysEx additions
Frame: `F0 00 21 02 00 04 <cmd> <arg> <payload as hi/lo nibbles> <checksum
hi/lo> F7`, checksum = sum of payload bytes & 0xff. Requests have an empty
payload (checksum `00 00`) unless noted.

| Request | Reply | Payload |
|---|---|---|
| `0x11`–`0x15` (dump patch/sequence/program/multi/part; arg = part, 0 = active) | `0x01`–`0x05`, **arg = part 1–6** (YAM: 0) | as YAM |
| `0x16` name (arg = part; payload: 1 byte object 0 patch, 1 sequence, 2 program, 3 multi) | `0x06`, arg = part | object, bank (0 = A), slot, SD status (0 = ok), 16-char name |
| `0x1a` current locations | `0x0a` | 19 little-endian words `bank << 8 \| slot`: part × 3 + {patch, sequence, program}, then multi |
| `0x1c` version | `0x0c` | family (1 = YAM+), controller version, YAM+ version (0x01 = 0.1, 0x02 = 0.2, 0x03 = 0.3, 0x04 = 0.4), oscillator shape count, patch layout, part layout, then per voicecard port: slave id, version |

`utils/yamplus_sysex.py` exercises these from a computer.

### Voicecard bus additions (controller ↔ voicecard)
`0x9n` set voice index *n*, `0xf6` clear load probe, `0xf7` get underruns,
`0xfe` get peak load.

## Patch / part data

| Offset | Field |
|---|---|
| patch 106–108 | `env_curve[3]` |
| patch 109 | `vintage` |
| patch 30 | `env_lfo[0].padding`: velocity curve (0.4; patch layout 2) |
| patch 110 | `voice_lfo_mode` (0.4; patch layout 2) |
| patch 111 | `voice_lfo_slew` (0.4; patch layout 2) |
| patch 38, 46 | spare (`env_lfo[1..2].padding`) |
| part 80 (address 192) | `spread_mode` |
| part 81 (address 193) | `steal_mode` (0.3; part layout 2) |
| part 82–83 | spare |

## Building

Use avr-gcc 4.3.5 / avr-libc 1.6.8: newer compilers miscompile the
oscillator code. `toolchain/` has a pinned Docker toolchain that
reproduces the shipped YAM190319 voicecard byte for byte; see README.md.
