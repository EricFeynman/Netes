CC = gcc
CFLAGS = -I
DEPS =
OBJ = server.o
USERID = 123456789

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all:
	$(CC) server.c -o server

clean:
	rm -r server 
