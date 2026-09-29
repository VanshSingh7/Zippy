# Zippy

A file compressor and decompressor written in C, using Huffman coding.

## What it does

Zippy shrinks files by giving frequently occurring bytes shorter
binary codes, and rare bytes longer codes — instead of every byte
taking a fixed 8 bits, common bytes take fewer, and the file gets
smaller overall. It can then perfectly reconstruct the original
file from the compressed version (lossless compression).

## How it works

1. Count how often each byte appears in the input file
2. Build a binary tree (Huffman tree) where frequent bytes end up
   near the root (short codes) and rare bytes end up deep in the
   tree (long codes)
3. Encode the file using these codes, packing them tightly into
   real bits on disk
4. Store just enough info in a small header (a magic number, the
   original file size, and the frequency table) so the exact same
   tree can be rebuilt later during decompression

## Prerequisites
- GCC
- Make

## Build
```bash
make
```

## Usage
```bash
./zippy compress <input_file> <output_file>
./zippy decompress <input_file> <output_file>
```

### Example
```bash
./zippy compress book.txt book.zpy
./zippy decompress book.zpy restored.txt
diff book.txt restored.txt   # no output = identical files
```

## Project structure
```
zippy/
├── src/            — implementation files
├── include/         — header files
├── Makefile
└── README.md
```

## Notes
- Compression works best on larger files with uneven byte
  frequency distributions (e.g. natural language text). Very
  small files may not shrink, or may even grow slightly, since
  the header has a small fixed size overhead.
- Handles edge cases: empty files and files containing only one
  unique byte value.