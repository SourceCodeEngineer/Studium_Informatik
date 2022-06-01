CFLAGS = -Wall -Wextra -std=c11

.PHONY: all clean
LIBS = -lrt -pthread

all: malloc_spy.c some_library task3 allocator_tests membench

malloc_spy: malloc_spy.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

malloc_spy.o: malloc_spy.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) malloc_spy malloc_spy.o 