# Source before building or running AFL on macOS:
#   source fuzz/afl_env.sh

AFL_PREFIX="$(brew --prefix afl++ 2>/dev/null || echo /opt/homebrew/opt/afl++)"
LLVM_PREFIX="$(brew --prefix llvm 2>/dev/null || echo /opt/homebrew/opt/llvm)"

export PATH="${AFL_PREFIX}/bin:${LLVM_PREFIX}/bin:${PATH}"

# macOS: forkserver is unreliable; keep enabled unless afl-fuzz fails to start.
export AFL_NO_FORKSRV="${AFL_NO_FORKSRV:-1}"

# Avoid UI noise when running headless.
export AFL_SKIP_CPUFREQ=1
export AFL_NO_UI="${AFL_NO_UI:-0}"

# afl-clang-fast++ aborts if AFL_CXX is exported on a long compile line.
unset AFL_CXX AFL_CC 2>/dev/null || true
AFL_CXX="${AFL_PREFIX}/bin/afl-clang-fast++"
