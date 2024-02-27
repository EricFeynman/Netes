# Fisher's equation (KPP equation)

## Overview

This project implements a numerical simulation that utilizes parallel processing to solve a specific mathematical problem efficiently. The core of the simulation is written in C and makes use of the POSIX threads (pthreads) library to divide the computation across multiple threads, enhancing performance on multicore processors.

## Prerequisites

Before building and running this project, ensure you have the following installed on your system:
- GCC (GNU Compiler Collection)
- POSIX Threads Library (pthread)

These dependencies are commonly available on Unix-like operating systems such as Linux and macOS. For Windows users, it is recommended to use a compatibility layer like Cygwin or WSL (Windows Subsystem for Linux).

## Building the Project

To compile the project, follow these steps:

1. Open a terminal and navigate to the project's directory.
2. Run the command `make` to initiate the compilation process.

This command uses GCC to compile `fisher.c` and creates an executable named `fisher`. The `Makefile` provided simplifies the compilation process and ensures that the necessary flags and libraries are included.

## Running the Program

After successfully building the project, you can run the simulation by executing the following command in your terminal:

```bash
./fisher
```

This will execute the fisher program, which starts the simulation based on the predefined parameters in the source code. The simulation's output will be displayed in the terminal, providing insights into the computation's progress and results.

```bash
make clean
```

This command will delete the fisher executable, ensuring a clean state for the next build.
