CFLAGS = -Wall -Wextra

all: even

even: even.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

even.o: even.c 
	$(CC) $(CFLAGS) -c -o $@ $^
	
clean:
	$(RM) even even.o
