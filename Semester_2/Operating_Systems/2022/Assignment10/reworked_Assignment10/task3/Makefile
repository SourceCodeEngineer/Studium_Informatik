CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g -D_POSIX_SOURCE -D_BSD_SOURCE -O3#-fsanitize=address -Wconversion
LDFLAGS= -lrt -pthread

.PHONY: all
all: task1_global task1_thread_local task2_global task2_thread_local

.PHONY: clean
clean:
	$(RM) task1_global task1_thread_local task2_global task2_thread_local 

task1_global: ../task1/task1.c ../tests/membench.c
	$(CC) $(CFLAGS) -DGLOBAL_BENCH -o $@ $^ $(LDFLAGS)

task1_thread_local: ../task1/task1.c ../tests/membench.c
	$(CC) $(CFLAGS) -DTHREAD_LOCAL -DGLOBAL_BENCH -o $@ $^ $(LDFLAGS)

task2_global: ../task2/task2.c ../tests/membench.c
	$(CC) $(CFLAGS) -DGLOBAL_BENCH -o $@ $^ $(LDFLAGS)

task2_thread_local: ../task2/task2.c ../tests/membench.c
	$(CC) $(CFLAGS) -DTHREAD_LOCAL -DGLOBAL_BENCH -o $@ $^ $(LDFLAGS)
