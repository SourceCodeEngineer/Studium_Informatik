CFLAGS = -Wall -Wextra -std=c11

.PHONY: all clean
LIBS = -lrt -pthread

all: my_program.c some_library task3 allocator_tests membench

my_program: my_program.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

my_program.o: my_program.c 
	$(CC) $(CFLAGS) -c -o $@ $^

some_library: some_library.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

some_library.o: some_library.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) my_program my_program.o some_library some_library.o