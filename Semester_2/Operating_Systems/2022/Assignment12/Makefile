.PHONY : all clean
CFLAGS = -Wall -Werror -std=c11 -D _DEFAULT_SOURCE #-Wpedantic
CC = gcc

all: restaurant

restaurant: restaurant.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ -lrt -pthread

restaurant.o: restaurant.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) restaurant.o