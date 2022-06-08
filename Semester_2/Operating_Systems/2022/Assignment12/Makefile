.PHONY : all clean
CFLAGS= -std=c11 -Wall -Werror -Wpedantic
CC=gcc

all: restaurant

reatsurant: restaurant.c
	$(CC) $(CFLAGS) restaurant.c -o restaurant -pthread

clean:
	$(RM) some_library.o