# Engineering decisions

Decisions taken without the owner during autonomous work, with the reason.
Newest last. Revisit any of them by opening an issue or reverting the commit.

## 2026-11-26 — native test harness

- **Host-compiled firmware instead of simavr.** simavr isn't available on
  the build machine or CI, and a host build runs the logic at full speed
  under AddressSanitizer. The cost is that AVR-specific details (16-bit
  `int`, the assembly versions of `avrlib/op.h`) aren't reproduced; the
  AVR build and size gates still run in CI for those.
- **avrlib stays a pristine submodule.** Native-only changes to its headers
  are `sed` patches into `build/native/override`, checked at build time.
- **Wavequence parameter 80–127 clamps to wave 79.** Stock YAM read past
  the 80-wave table into whatever data or code followed, which changes with
  every build, so no patch could rely on those sounds. Values 0–79 are
  unchanged. (Alternative considered: scale 0–127 onto the 80 waves; it
  would have changed every existing wavequence patch.)
- **polyBLEP index clamps to the last table entry** (the continuous limit
  of the correction). Only affects edges where the 1/increment
  approximation overshot.
- **Cyclic voice allocation clears released slots to 0** instead of 0xff
  (which read as "active, note 127"), and only releases active slots.
- **Poly aftertouch halves the allocator size in CHAIN mode, not CYCLIC.**
  That is what the code clearly meant: in CHAIN mode the upper half of the
  allocator holds notes forwarded down the chain.

## 2026-11-26 — SysEx/NRPN hardening

- **Loaded patches and parts are clamped to the parameter table ranges**
  (SysEx and SD card). Values outside the ranges can't be entered on the
  Ambika, and some of them crash a voicecard (oscillator shape and similar
  enums index function tables). Cost: about 100 bytes of controller flash.
  Bytes the table doesn't describe (padding, sequencer data) are untouched.
- **SysEx object commands reject part arguments above 6** (0 still means
  the active part). The multi ignores the argument as before.
- **A SysEx header mismatch ignores everything up to the next F0.**
  Previously it waited for F7 and could re-accept the previous command.
- **Tempo pot minimum is 39 (`ext`)**, not the out-of-range 38 the even-BPM
  rounding produced.


## 2026-11-26 — unison stacks and vintage expansion (YAM+ 0.2-dev)

- **Unison 3x/4x are new polyphony mode values 5 and 6**, after `chain`,
  so stock patches and parts (0–4) keep their meaning. `2x unison` keeps
  YAM's rounding (with an odd voice count the last note shares a voice
  with the first); 3x/4x round down so stacks never overlap, and the
  leftover voices stay silent. With six voices that means 4x plays one note.
  Alternative considered: let the second 4x note use voices 5, 6, 1, 2,
  which steals half of the first stack on every second note.
- **No 6x unison mode**: `mono` with six voices already is one.
- **No stereo pan spread**: the Ambika has no per-voice panning (each
  voicecard has its own output and the mix bus is mono).
- **Sub-octave voice is a spread mode (`sub-`)**, not a separate
  parameter: it needs no new patch/part byte, and it only makes sense
  together with the stack detune. In the polyphonic modes it falls back to
  `cntr`, because every slot there is a different note.
- **The unison, poly, cyclic and chain paths share one function
  (`Part::SlotVoices`)**: needed to fit the controller flash (the first,
  separate version cost 415 bytes and failed the 512-byte gate; this one
  costs 158).
- **Vintage keeps one knob.** Per-note slop, oscillator 2 drift and
  resonance tolerance scale with the existing `vint` value instead of new
  parameters: no patch-format change, and 0 is still exactly YAM. Existing
  patches with vintage > 0 sound slightly livelier than on 0.1; 0.1 was a
  pre-release that hasn't been tested on hardware, so no installed base
  depends on the old amounts.
- **Version numbers:** YAM+ 0.2 (`kYamPlusVersion` 0x02) and voicecard
  0x12, so editors can offer the new values only to firmware that has them.


## 2026-11-26 — voice steal modes (YAM+ 0.3-dev)

- **One part setting (`stl`, part byte 81) instead of separate "note
  priority" and "stealing" settings.** In a polyphonic part both questions
  have the same answer: the note that would lose its voice is the one with
  the lowest priority. `low` / `high` name the note that gets stolen, so
  the values fit the 4-character display.
- **A new note that would itself be the victim is not played** (`low`: a
  note below every held note; `high`: above). That is what high/low-note
  priority means on monosynths; stealing anyway would make the setting
  pointless for the case it exists for (a held chord under a melody).
- **No "note return"**: a refused or stolen note whose key is still held
  does not come back when a voice is released. It would need a held-note
  list for the poly modes (the part's 12-note `pressed_keys_` stack is
  already used by the arpeggiator) and more controller flash than is left
  (560 B after this change, gate 512).
- **`cyclic` ignores the setting**: its point is strict rotation (the
  voice that sounds next is fixed), so it can't choose a victim.
- **Released voices are still reused first in every mode**, so release
  tails behave as before; the steal mode only matters with all voices held.
- **CC 115** (next to spread mode's 114, undefined in the MIDI spec), NRPN
  193, and SysEx part dumps carry it.
- **Version numbers:** YAM+ 0.3 (`kYamPlusVersion` 0x03), part layout 2.
  Cost: 146 B controller flash, no RAM.
