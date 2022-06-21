CC = gcc
CFLAGS = -Wall -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wpointer-arith -Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Wredundant-decls -Wold-style-declaration -Wold-style-definition -std=c11 -O2
LDFLAGS = -pthread -lrt


all: restaurant

restaurant: restaurant.c

memcheck: restaurant.c
	$(CC) $^ -g -o restaurant $(LDFLAGS)
	valgrind --tool=memcheck --leak-check=full ./restaurant 1 5 3

.PHONY: clean
clean:
	find . -maxdepth 1 -type f ! -name "*.c" ! -name "*.h" ! -name "*.txt" ! -name "Makefile" -exec rm {} \;