# BAMBI

Firmware for the Mutable Instruments **Ambika** 6-voice hybrid polysynth,
built on top of [YAM](https://github.com/bjoeri/ambika) ("Yet Another
Mutation") by bjoeri, itself based on the original firmware by Emilie Gillet.

BAMBI focuses on sound and playability for a performance/sound-design
polysynth: smoother analog control voltages, envelope curves, per-voice
analog "vintage" drift, centered unison spread, faster editing, and MIDI
hooks for a web editor ([SHED](https://github.com/armandhammer/SHED)). No
sequencer/groovebox features. Existing YAM programs load and sound the same.
Internally the first release is still called **YAM+ 0.1** (the OS-info page
shows `YAMplus v0.1`).

- **What's new, MIDI/NRPN/SysEx additions:** [YAMPLUS.md](YAMPLUS.md)
- **Download:** [Releases](https://github.com/armandhammer/BAMBI/releases)
  (`AMBIKA.BIN` for the controller, `VOICE1.BIN`–`VOICE6.BIN` for the
  voicecards, installed from the SD card via the OS-info page)
- **Hardware test checklist:** [docs/HARDWARE_TESTS.md](docs/HARDWARE_TESTS.md)
- **Design notes:** [docs/AUDIT.md](docs/AUDIT.md) (audit of YAM, Elkhart,
  Shruthi YAM and the Ixox editor; ranked proposals; editor design) and
  [docs/PLAN.md](docs/PLAN.md) (wave-1 plan and measured results)
- The original YAM readme is in [README](README).

> **Status:** 0.1 is built and size-checked but not yet verified on
> hardware. Keep the stock YAM files on your SD card for rollback.

## Building

BAMBI must be built with **avr-gcc 4.3.5 / avr-libc 1.6.8**: newer compilers
miscompile the oscillator code (a constant metallic tone). A pinned Docker
image reproduces the shipped YAM190319 voicecard byte for byte.

```sh
git clone --recursive https://github.com/armandhammer/BAMBI.git
cd BAMBI
docker build --platform linux/386 -t ambika-squeeze:4.3.5 \
  -f toolchain/Dockerfile.squeeze-i386 toolchain   # once, needs network
bash toolchain/avr-make.sh . controller/makefile bin
bash toolchain/avr-make.sh . voicecard/makefile bin
bash toolchain/size-report.sh .                    # flash/RAM + gates
bash toolchain/package-release.sh test             # release/test/*.BIN
```

Compiles run with `--network none`. After editing `controller/resources/*.py`,
regenerate with `bash toolchain/avr-resources.sh . controller/makefile write`.
CI builds every push (`.github/workflows/build.yml`).

## License

GPL-3.0, like the original firmware (see the source file headers). Hardware
files are CC-BY-SA 3.0, as in the original repository.
