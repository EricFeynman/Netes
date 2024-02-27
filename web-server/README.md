# HTTP Server 

## Description

This project comprises a simple http server application written in C. The server is capable of handling connections from clients, processing requests, and responding accordingly. It includes basic socket programming examples, such as creating a socket, binding to an address, listening for client connections, and accepting those connections.

## Installation

To compile the server application, you will need GCC installed on your system. Use the provided `Makefile` for an easy compilation process.

### Prerequisites

- GCC compiler
- Linux/Unix environment

### Compiling

Run the following command in the terminal within the project directory:

```bash
make all
```

This will compile the `server.c` source file into an executable named `server`.

### Cleaning up

To remove the compiled executable, you can use the `clean` target:

```bash
make clean
```

## Usage

After compilation, you can start the server by running:

```bash
./server
```

The server will listen for client connections. Details on how to connect to the server and the expected commands or requests should be documented based on the server's specific functionalities.
