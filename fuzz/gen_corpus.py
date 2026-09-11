#!/usr/bin/env python3
"""Generate seed inputs for AFL++ harness (byte stream: [opcode][args...]*)."""

from pathlib import Path


def pack_cstr(s: bytes) -> bytes:
    s = s[:255]
    return bytes([len(s)]) + s


def write(path: Path, data: bytes) -> None:
    path.write_bytes(data)
    print(f"  {path.name}: {len(data)} bytes")


def main() -> None:
    corpus = Path(__file__).resolve().parent / "corpus"
    corpus.mkdir(exist_ok=True)

    write(corpus / "empty", b"")
    write(corpus / "noop", bytes([2]))
    write(corpus / "hello", bytes([0]) + pack_cstr(b"hello"))
    write(corpus / "append_chain", bytes([0]) + pack_cstr(b"ab") + bytes([3]) + pack_cstr(b"cdxyz"))
    write(
        corpus / "insert_erase",
        bytes([0]) + pack_cstr(b"abcdef") + bytes([4, 0, 0, 2, 3, 5, 0, 6, 0, 2]),
    )
    write(corpus / "iterators", bytes([0]) + pack_cstr(b"xyz") + bytes([12]))
    write(
        corpus / "find_compare",
        bytes([0]) + pack_cstr(b"test") + bytes([9]) + pack_cstr(b"es") + bytes([10]) + pack_cstr(b"test"),
    )
    write(corpus / "assignment", bytes([0]) + pack_cstr(b"assign") + bytes([1]) + pack_cstr(b"newval"))
    write(corpus / "replace_full", bytes([0]) + pack_cstr(b"abcdef") + bytes([7, 0, 0, 1, 2]) + pack_cstr(b"ZZ"))
    write(corpus / "append_substr", bytes([0]) + pack_cstr(b"12345") + bytes([3]) + pack_cstr(b"abc") + bytes([0, 0, 1, 2]))
    write(corpus / "file_io", bytes([0]) + pack_cstr(b"filedata") + bytes([15]))
    write(corpus / "find_any", bytes([0]) + pack_cstr(b"ababa") + bytes([13]) + pack_cstr(b"aba"))
    write(corpus / "conversions", bytes([14, 42, 0]) + pack_cstr(b"123"))
    write(corpus / "full_coverage", bytes([16]))


if __name__ == "__main__":
    main()
