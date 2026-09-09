#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

# shellcheck source=/dev/null
source "$ROOT/fuzz/afl_env.sh"

MODE="${1:-fuzz}"
if [[ "$MODE" == "cov" ]]; then
    BUILD_DIR="$ROOT/fuzz/build/cov"
    OUT="$ROOT/fuzz/mystring_fuzz_cov"
    LIB="$BUILD_DIR/libmystring_fuzz_cov.a"
else
    BUILD_DIR="$ROOT/fuzz/build"
    OUT="$ROOT/fuzz/mystring_fuzz"
    LIB="$BUILD_DIR/libmystring_fuzz.a"
fi

SOURCES=(
    mystring_6_1.cpp
    mystring_accessors.cpp
    mystring_aho_corasick.cpp
    mystring_append.cpp
    mystring_assignment.cpp
    mystring_compare.cpp
    mystring_constructors.cpp
    mystring_core.cpp
    mystring_erase.cpp
    mystring_find.cpp
    mystring_insert.cpp
    mystring_operators.cpp
    mystring_replace.cpp
    mystring_substr.cpp
    mystring_iterators_6_2.cpp
)

COMMON_FLAGS=(
    -std=c++17
    -Wall
    -Wextra
    -I.
    -g
    -fno-omit-frame-pointer
)

if [[ "$MODE" == "fuzz" ]]; then
    CXX="$AFL_CXX"
    EXTRA_FLAGS=(-fsanitize=address)
elif [[ "$MODE" == "cov" ]]; then
    CXX="${LLVM_PREFIX}/bin/clang++"
    EXTRA_FLAGS=(
        -fprofile-instr-generate
        -fcoverage-mapping
    )
else
    echo "Usage: $0 [fuzz|cov]" >&2
    exit 1
fi

mkdir -p "$BUILD_DIR"
LIB_OBJECTS=()

for src in "${SOURCES[@]}"; do
    obj="$BUILD_DIR/${src%.cpp}.o"
    "$CXX" "${COMMON_FLAGS[@]}" "${EXTRA_FLAGS[@]}" -c "$src" -o "$obj"
    LIB_OBJECTS+=("$obj")
done

rm -f "$LIB"
ar rcs "$LIB" "${LIB_OBJECTS[@]}"

harness_obj="$BUILD_DIR/mystring_fuzz.o"
"$CXX" "${COMMON_FLAGS[@]}" "${EXTRA_FLAGS[@]}" -c fuzz/mystring_fuzz.cpp -o "$harness_obj"

"$CXX" "${COMMON_FLAGS[@]}" "${EXTRA_FLAGS[@]}" "$harness_obj" "$LIB" -o "$OUT"

echo "Built $OUT (mode=$MODE)"
if [[ "$MODE" == "fuzz" ]]; then
    python3 "$ROOT/fuzz/gen_corpus.py"
    "$OUT" "$ROOT/fuzz/corpus/hello"
fi
