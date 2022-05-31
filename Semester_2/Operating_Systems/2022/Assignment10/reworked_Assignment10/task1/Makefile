CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g -D_BSD_SOURCE -D_POSIX_SOURCE -O3 #-fsanitize=address -Wconversion
LDFLAGS= -lrt -pthread

.PHONY: all
all: task1_test task1_bench task1_bench_system_malloc

.PHONY: clean
clean:
	$(RM) task1_test task1_bench task1_bench_system_malloc

task1_test: task1.c ../tests/allocator_tests.c
	$(CC) $(CFLAGS) -DTESTS -o $@ $^ $(LDFLAGS)

task1_bench: task1.c ../tests/membench.c
	$(CC) $(CFLAGS) -DGLOBAL_BENCH -o $@ $^ $(LDFLAGS)

task1_bench_system_malloc: task1.c ../tests/membench.c
	$(CC) $(CFLAGS) -DGLOBAL_BENCH_BUILTIN_ALLOC -o $@ $^ $(LDFLAGS)
