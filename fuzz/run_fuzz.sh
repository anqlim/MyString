#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT/fuzz"

# shellcheck source=/dev/null
source "$ROOT/fuzz/afl_env.sh"

BIN="$ROOT/fuzz/mystring_fuzz"
CORPUS="$ROOT/fuzz/corpus"
FINDINGS="$ROOT/fuzz/findings"

if [[ ! -x "$BIN" ]]; then
    echo "Run ../fuzz/build_fuzz.sh first" >&2
    exit 1
fi

python3 "$ROOT/fuzz/gen_corpus.py"
mkdir -p "$FINDINGS"

INPUT="$CORPUS"
if [[ -d "$FINDINGS/default" && "${FRESH:-0}" != "1" ]]; then
    INPUT="-"
    export AFL_AUTORESUME=1
    echo "Resuming previous session (-i -, AFL_AUTORESUME=1)."
    echo "  Fresh start: rm -rf fuzz/findings   or   FRESH=1 ./fuzz/run_fuzz.sh"
else
    echo "Starting new fuzzing session."
fi

echo "Starting afl-fuzz (Ctrl+C to stop)..."
echo "  input:  $INPUT"
echo "  output: $FINDINGS"
echo "  AFL_NO_FORKSRV=$AFL_NO_FORKSRV"
echo

afl-fuzz -i "$INPUT" -o "$FINDINGS" -m none -t 1000 -- "$BIN" @@
