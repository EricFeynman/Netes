# Binary File Sorting in C

## Overview
This project provides a set of tools written in C for creating binary files, reading binary files, converting text files to binary format, and efficiently sorting large binary files. It utilizes memory management, file I/O operations, and sorting algorithms optimized for large datasets.

## Features
- **File Creation**: Generate binary files with random double precision floating-point numbers.
- **File Reading**: Read and display the contents of binary files.
- **File Conversion**: Convert text files containing numerical values into binary format.
- **File Sorting**: Implement an external merge sort algorithm to sort very large binary files that do not fit entirely in memory.

## Getting Started

### Prerequisites
- GCC Compiler
- Make (optional for building with Makefile)

### Compilation
To compile the project, you can use the provided `Makefile`:

```bash
make
```

Or compile manually:

```bash
gcc -o create create.c
gcc -o sort sort.c
```

### Usage
- Creating a binary file:
```bash
./create
```
Follow the prompts to create a new binary file with random numbers.

- Reading a binary file:
```bash
./create
```
Choose the read option and specify the file name to display its contents.

- Converting a text file to binary:
```bash
./create
```
Choose the convert option and specify the text file name to convert it into binary format.

- Sorting a binary file:
```bash
./sort
```
This will sort the predefined binary file and measure the sorting time.
