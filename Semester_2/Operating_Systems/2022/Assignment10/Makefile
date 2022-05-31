CFLAGS = -Wall -Wextra -std=c11

.PHONY: all clean
LIBS = -lrt -pthread

all: task1 task2 task3 allocator_tests membench

task1: task1.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

task1.o: task1.c 
	$(CC) $(CFLAGS) -c -o $@ $^

task2: task2.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

task2.o: task2.c 
	$(CC) $(CFLAGS) -c -o $@ $^

task3: task3.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

task3.o: task3.c 
	$(CC) $(CFLAGS) -c -o $@ $^

allocator_tests: allocator_tests.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

allocator_tests.o: allocator_tests.c 
	$(CC) $(CFLAGS) -c -o $@ $^

membench: membench.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

membench.o: membench.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) task1 task1.o task2 task2.o task3 task3.o allocator_tests allocator_tests.o membench membench.c