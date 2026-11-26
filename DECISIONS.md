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

