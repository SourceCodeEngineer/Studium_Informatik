CFLAGS = -Wall -Wextra 

.PHONY: all clean
LIBS = -lrt -pthread

all: task3 

task3: task3.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

task3.o: task3.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) task3 task3.o