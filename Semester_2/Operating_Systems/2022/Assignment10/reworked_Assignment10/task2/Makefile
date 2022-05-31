CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g -D_BSD_SOURCE -D_POSIX_SOURCE -O3 #-fsanitize=address -Wconversion
LDFLAGS= -lrt -pthread

.PHONY: all
all: task2_test task2_bench task2_bench_system_malloc

.PHONY: clean
clean:
	$(RM) task2_test task2_bench task2_bench_system_malloc

task2_test: task2.c ../tests/allocator_tests.c
	$(CC) $(CFLAGS) -DTESTS -o $@ $^ $(LDFLAGS)

task2_bench: task2.c ../tests/membench.c
	$(CC) $(CFLAGS) -DGLOBAL_BENCH -o $@ $^ $(LDFLAGS)

task2_bench_system_malloc: task2.c ../tests/membench.c
	$(CC) $(CFLAGS) -DGLOBAL_BENCH_BUILTIN_ALLOC -o $@ $^ $(LDFLAGS)
