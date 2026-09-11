#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

LLVM_BIN="/opt/homebrew/opt/llvm/bin"
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PYTHON="/opt/homebrew/bin/python3.12"
DOT_UNMANGLER="${SCRIPT_DIR}/dot_unmangler.py"
GRAPH_DIR="callgraph"
CXX_FLAGS=(-std=c++17 -w -I.)

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

mkdir -p "${GRAPH_DIR}"
rm -f "${GRAPH_DIR}"/*.bc "${GRAPH_DIR}"/*.dot "${GRAPH_DIR}"/*.png

echo "[1/5] Compile sources to LLVM bitcode..."
for src in "${SOURCES[@]}"; do
    base="${src%.cpp}"
    "${LLVM_BIN}/clang++" "${CXX_FLAGS[@]}" -emit-llvm -c "${src}" -o "${GRAPH_DIR}/${base}.bc"
done

echo "[2/5] Link bitcode..."
"${LLVM_BIN}/llvm-link" "${GRAPH_DIR}"/*.bc -o "${GRAPH_DIR}/mystring.bc"

echo "[3/5] Build call graph (.dot)..."
"${LLVM_BIN}/opt" -passes=dot-callgraph -disable-output "${GRAPH_DIR}/mystring.bc"
mv "${GRAPH_DIR}/mystring.bc.callgraph.dot" "${GRAPH_DIR}/mystring.callgraph.dot"

echo "[4/5] Demangle names..."
"${PYTHON}" "${DOT_UNMANGLER}" -p "${GRAPH_DIR}/mystring.callgraph.dot" -o "${GRAPH_DIR}/mystring.callgraph.unmangled.dot" --cxxfilt "${LLVM_BIN}/llvm-cxxfilt"

echo "[5/6] Render full PNG..."
dot -Tpng "${GRAPH_DIR}/mystring.callgraph.unmangled.dot" -o "${GRAPH_DIR}/mystring_callgraph.png"

echo "[6/6] Build report-friendly graph..."
"${PYTHON}" "${SCRIPT_DIR}/filter_callgraph.py" \
    -i "${GRAPH_DIR}/mystring.callgraph.unmangled.dot" \
    -d "${GRAPH_DIR}/mystring_callgraph_report.dot" \
    -p "${GRAPH_DIR}/mystring_callgraph_report.png"

echo
echo "Done:"
echo "  ${GRAPH_DIR}/mystring.callgraph.dot"
echo "  ${GRAPH_DIR}/mystring.callgraph.unmangled.dot"
echo "  ${GRAPH_DIR}/mystring_callgraph.png          (full graph)"
echo "  ${GRAPH_DIR}/mystring_callgraph_report.png   (for report)"
