CFLAGS = -Wall -Wextra -std=c11

.PHONY: all clean
LIBS = -lrt -pthread

all: map_number.c some_library task3 allocator_tests membench

map_number: map_number.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

map_number.o: map_number.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) map_number map_number.o