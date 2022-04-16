.PHONY : all clean
CFLAGS= -Wall -Werror -Wpedantic -fpic
CC=gcc

all: some_library my_program

BIN=bin
INCLUDE=include
SRC=src

some_library: clean some_library_o
	clear
	$(CC) -shared -o some_library.so some_library.o

some_library: clean
	clear
	$(CC) -static my_program.c -o my_program

some_library_o:
	$(CC) $(CFLAGS) -c some_library.c 

clean:
	$(RM) some_library.o
