CFLAGS = -Wall -Wextra

.PHONY: all clean

all: task1a task1b

task1a: task1a.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ -lpthread

task1a.o: task1a.c 
	$(CC) $(CFLAGS) -c -o $@ $^

task1b: task1b.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ -lpthread

task1b.o: task1b.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) task1a task1a.o task1b task1b.o