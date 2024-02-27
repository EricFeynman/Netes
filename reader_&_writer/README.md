# IPC Shared Memory and Semaphores

This project demonstrates basic inter-process communication (IPC) using shared memory and semaphores in C. It consists of two main components: a `writer` program that accepts user input and writes it to a shared memory segment, and a `reader` program that reads from this shared memory segment and prints the contents to the console. The programs use semaphores to synchronize access to the shared memory, ensuring safe communication between processes.

## Getting Started

### Prerequisites

- A C compiler (GCC recommended)
- Unix-like environment (Linux, BSD, macOS)

### Compilation

The project includes a `Makefile` for easy compilation of the `writer` and `reader` programs. To compile, simply run the following command in the project directory:

```bash
make
```

This will generate two executable files: writer and reader.

## Running the Programs

To use the IPC mechanism, start both the writer and reader in separate terminal windows.

In the first terminal, run the writer program:

```bash
./writer
```

In the second terminal, start the reader program:

```bash
./reader
```

The writer program will prompt you to enter messages. These messages will be shared with the reader program via the shared memory segment. The reader program will print any messages it receives to the console. To stop both programs, enter "exit" as a message in the writer program.

## Cleanup

The programs are designed to clean up IPC resources (shared memory and semaphores) upon exiting. No additional steps are required for cleanup.

## Project Structure

- writer.c: Contains the source code for the writer program. It prompts the user for input and writes messages to a shared memory segment.
- reader.c: Contains the source code for the reader program. It reads messages from the shared memory segment and prints them to the console.
- Makefile: Used to compile the writer and reader programs.
