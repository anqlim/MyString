#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

clang++ -std=c++17 -w -I. main.cpp mystring_*.cpp -o main
./main
