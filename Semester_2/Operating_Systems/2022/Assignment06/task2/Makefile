CFLAGS = -Wall -Wextra

.PHONY: all clean
LIBS = -lrt -pthread

all: task2 

task2: task2.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ -O3

task2.o: task2.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) task2 task2.o