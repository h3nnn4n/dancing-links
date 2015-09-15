CC=gcc
CFLAGS=-lm -Wall
SOURCES=links.c main.c
BIN=dlx

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN)

clean:
	-@rm -rf $(BIN) core 2> /dev/null || true
