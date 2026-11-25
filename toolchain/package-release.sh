#!/usr/bin/env bash
# Copy the current build into release/<name>/ as SD-card update files
# (AMBIKA.BIN + VOICE1..6.BIN, one copy per voicecard port) and refresh
# release/SHA256SUMS. Run from the repository root after building.
#
# Usage: toolchain/package-release.sh <name>
set -euo pipefail
NAME="${1:?usage: $0 <name>}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT/release/$NAME"

rm -rf "$OUT"
mkdir -p "$OUT"
cp "$ROOT/build/ambika_controller/ambika_controller.bin" "$OUT/AMBIKA.BIN"
for i in 1 2 3 4 5 6; do
  cp "$ROOT/build/ambika_voicecard/ambika_voicecard.bin" "$OUT/VOICE$i.BIN"
done
(cd "$ROOT/release" && sha256sum */*.BIN > SHA256SUMS)
echo "packaged $OUT"
