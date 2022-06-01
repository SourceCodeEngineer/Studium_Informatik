CFLAGS = -std=c11 -Wall -Wextra #-Wpedantic -g -D_BSD_SOURCE -D_POSIX_SOURCE #-O3 #-fsanitize=address -Wconversion
LDFLAGS= -ldl

.PHONY: all
all: malloc_spy

.PHONY: clean
clean:
	$(RM) malloc_spy.so

malloc_spy: malloc_spy.c 
	$(CC) -shared -o malloc_spy.so -fPIC malloc_spy.c
