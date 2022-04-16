.PHONY : all clean
CFLAGS= -std=gnu11 -Wall -Werror -Wpedantic -pthread
CC=gcc

all: server client server2 server3 client2

BIN=bin
INCLUDE=include
SRC=src

server: $(SRC)/server.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

client: $(SRC)/client.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@
	
server2: $(SRC)/server2.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

client2: $(SRC)/clients2.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

server3: $(SRC)/server3.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

clean:
	$(RM) -r $(BIN)/*
