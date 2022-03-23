CFLAGS = -Wall -Wextra

all: task1

task1: task1.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

task1.o: task1.c
	$(CC) $(CFLAGS) -c -o $@ $^
	
clean:
	$(RM) task1 task1.o