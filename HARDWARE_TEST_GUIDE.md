# Hardware test guide

All physical checks for BAMBI live in
[`docs/HARDWARE_TESTS.md`](docs/HARDWARE_TESTS.md): flashing, the YAM+ 0.1
checklist, and the checks for each later change (newest at the end).

Everything that can be checked without the hardware is covered by the
native tests in [`test/native`](test/native/README.md) and by the size
gates in CI. The hardware checks are for what those can't see: audio,
analog behaviour, timing, the SD card and real MIDI devices.
