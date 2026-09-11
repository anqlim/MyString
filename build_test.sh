#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

GTEST_PREFIX="$(brew --prefix googletest)"

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

clang++ -std=c++17 -w -I. -Itests \
    tests/*_test.cpp "${SOURCES[@]}" \
    -I"${GTEST_PREFIX}/include" \
    -L"${GTEST_PREFIX}/lib" \
    -lgtest_main -lgtest -pthread \
    -o mystring_test

./mystring_test

PYTHON="${PYTHON:-/Applications/Xcode.app/Contents/Developer/usr/bin/python3}"

./build_wrapper.sh
"$PYTHON" mystring_test.py
