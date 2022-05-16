.PHONY =  all clean

CC = gcc

CFLAGS = -O3 -std=c11 -Wall -Wextra -Wpedantic  -D_POSIX_C_SOURCE -D_BSD_SOURCE
LFLAGS = -lm -lrt -pthread
BINS = task3

all: ${BINS}
	
task3: task3.o
	$(CC) -o $@ $^ $(LFLAGS)

task3.o: task3.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o ${BINS}