CFLAGS = -std=gnu11 -Wall -Wextra -O2 -Wpedantic
CFLAGSLIBCOMPILE = -c -fPIC
CFLAGSLIBTOSHARED = -shared -o
LFLAGS = -pthread

.PHONY: all
all: malloc_spy

.PHONY: clean
clean: 
	$(RM) malloc_spy.so
	$(RM) malloc_spy

malloc_spy: malloc_spy.c
	gcc $(CFLAGSLIBCOMPILE) $^ -o $@ 
	gcc $(CFLAGSLIBTOSHARED) malloc_spy.so malloc_spy -ldl