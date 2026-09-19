# MyString

A from-scratch C++ string class with an API similar to `std::basic_string<char>`. The type manages its own dynamic buffer (`data_`, `size_`, `capacity_`) without relying on STL containers for storage.

## Features

- Constructors, assignment, append, insert, erase, replace, substr
- Search (`find`) and comparison operators
- Move semantics, numeric conversion (`to_int`, `to_float`)
- Multi-pattern search with Aho–Corasick (`find_any`)
- Bidirectional iterators (forward, reverse, const)
- Stream I/O and a **pybind11** Python module

## Requirements

- C++17 compiler (`clang++` in build scripts)
- [Google Test](https://github.com/google/googletest) — unit tests
- **pybind11** + Python 3.9 — Python wrapper
- **AFL++** (optional) — fuzzing under `fuzz/`

## Build & run

**Demo**

```bash
./build_demo.sh
```

**Tests** (Google Test + Python wrapper)

```bash
./build_test.sh
```

**Python module**

```bash
./build_wrapper.sh
python3 -c "import mystring; print(mystring.MyString('hello'))"
```

## Project layout

```
mystring.h              public interface
mystring_*.cpp          implementation (split by method group)
MyString_wrapper.cpp    pybind11 bindings
main.cpp                console demo
tests/                  unit tests
fuzz/                   AFL++ harness and scripts
```

Implementation is decomposed into private primitives (`init_from_cstr`, `ensure_capacity`, `append_cstr`, etc.) shared across the public API. See `build_call_graph.sh` for an optional method dependency graph.
