#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

# shellcheck source=/dev/null
source "$ROOT/fuzz/afl_env.sh"

BIN="$ROOT/fuzz/mystring_fuzz_cov"
PROF_DIR="$ROOT/fuzz/coverage/profraw"
PROFDATA="$ROOT/fuzz/coverage/merged.profdata"
REPORT="$ROOT/fuzz/coverage/report.txt"
LLVM_COV="${LLVM_PREFIX}/bin/llvm-cov"
LLVM_PROFDATA="${LLVM_PREFIX}/bin/llvm-profdata"

QUEUE="$ROOT/fuzz/findings/default/queue"
CORPUS="$ROOT/fuzz/corpus"

echo "=== 1/4 Build coverage binary (separate from AFL fuzz binary) ==="
"$ROOT/fuzz/build_fuzz.sh" cov

echo "=== 2/4 Replay corpus + AFL queue ==="
rm -rf "$PROF_DIR" "$PROFDATA" "$REPORT"
mkdir -p "$PROF_DIR"

export LLVM_PROFILE_FILE="$PROF_DIR/%p.profraw"
COUNT=0
replay() {
    local dir="$1"
    [[ -d "$dir" ]] || return 0
    for f in "$dir"/*; do
        [[ -f "$f" ]] || continue
        perl -e 'alarm shift; exec @ARGV' 2 "$BIN" "$f" >/dev/null 2>&1 || true
        COUNT=$((COUNT + 1))
        if (( COUNT % 100 == 0 )); then
            echo "  replayed $COUNT inputs..."
        fi
    done
}

replay "$CORPUS"
if [[ -d "$QUEUE" ]]; then
    replay "$QUEUE"
else
    echo "WARN: $QUEUE not found — only corpus replayed."
fi

echo "Replayed $COUNT inputs."

echo "=== 3/4 Merge profiles ==="
"$LLVM_PROFDATA" merge -sparse "$PROF_DIR"/*.profraw -o "$PROFDATA"

echo "=== 4/4 Coverage report (mystring_*.cpp) ==="
"$LLVM_COV" report "$BIN" -instr-profile="$PROFDATA" \
    mystring_*.cpp fuzz/mystring_fuzz.cpp | tee "$REPORT"

echo
echo "Saved: $REPORT"
echo
echo "Annotated source for one file:"
echo "  ${LLVM_COV} show $BIN -instr-profile=$PROFDATA mystring_core.cpp | less"
