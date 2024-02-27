CC = gcc
CFLAGS = -I

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

all:
	$(CC) writer.c -o writer
	$(CC) reader.c -o reader

clean:
	rm -r writer && rm -r reader
