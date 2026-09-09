#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"

# shellcheck source=/dev/null
source "$ROOT/fuzz/afl_env.sh"

echo "=== AFL++ tools ==="
command -v afl-fuzz
command -v afl-clang-fast++
afl-fuzz 2>&1 | head -3 || true
echo

echo "=== Shared memory (AFL needs larger shmmax on macOS) ==="
sysctl kern.sysv.shmmax kern.sysv.shmseg 2>/dev/null || true
SHMMAX=$(sysctl -n kern.sysv.shmmax 2>/dev/null || echo 0)
if [[ "$SHMMAX" -lt 100000000 ]]; then
    echo "WARN: kern.sysv.shmmax is low ($SHMMAX)."
    echo "      Run once (needs password): sudo $(brew --prefix afl++)/bin/afl-system-config"
    echo "      Or reboot after running it. AFL may still work with AFL_NO_FORKSRV=1."
else
    echo "OK: shmmax looks sufficient."
fi
echo

echo "=== ReportCrash ==="
if launchctl list 2>/dev/null | grep -q 'com.apple.ReportCrash'; then
    echo "WARN: ReportCrash is loaded (may slow fuzzing)."
    echo "      Optional: sudo $(brew --prefix afl++)/bin/afl-system-config"
else
    echo "OK: ReportCrash unloaded."
fi
echo

echo "=== Build harness ==="
"$ROOT/fuzz/build_fuzz.sh" fuzz
echo

echo "=== Corpus smoke test ==="
python3 "$ROOT/fuzz/gen_corpus.py"
for f in "$ROOT/fuzz/corpus"/*; do
    [[ -f "$f" ]] || continue
    "$ROOT/fuzz/mystring_fuzz" "$f" || { echo "FAIL on $f"; exit 1; }
done
echo "All corpus seeds OK."
echo

echo "=== afl-showmap (instrumentation check) ==="
afl-showmap -o /tmp/afl_showmap_out -- "$ROOT/fuzz/mystring_fuzz" "$ROOT/fuzz/corpus/hello"
echo "showmap non-zero lines: $(wc -l < /tmp/afl_showmap_out | tr -d ' ')"
echo

echo "=== Ready ==="
echo "Run:  ./fuzz/run_fuzz.sh"
echo "Or:   source fuzz/afl_env.sh && afl-fuzz -i fuzz/corpus -o fuzz/findings -m none -- fuzz/mystring_fuzz @@"
