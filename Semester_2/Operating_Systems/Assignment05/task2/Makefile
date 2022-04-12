CFLAGS = -Wall -Wextra

all: task2 

task2: task2.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

task2.o: task2.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) task2 task2.o