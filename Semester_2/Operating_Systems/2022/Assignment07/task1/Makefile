CFLAGS = -Wall -Wextra -st=c11

.PHONY: all clean
LIBS = -lrt -pthread

all: task1 

task1: task1.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

task1.o: task1.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) task1 task1.o