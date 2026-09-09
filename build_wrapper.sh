#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

clang++ -std=c++17 -shared -fPIC -Wall -Wextra \
    -I/Applications/Xcode.app/Contents/Developer/Library/Frameworks/Python3.framework/Versions/3.9/Headers \
    -I"$HOME/Library/Python/3.9/lib/python/site-packages/pybind11/include" \
    -undefined dynamic_lookup \
    MyString_wrapper.cpp mystring_*.cpp \
    -o mystring.cpython-39-darwin.so
