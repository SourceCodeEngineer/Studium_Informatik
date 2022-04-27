CFLAGS = -Wall -Wextra

.PHONY: all clean

all: task3 

task3: task3.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

task3.o: task3.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) task3 task3.o