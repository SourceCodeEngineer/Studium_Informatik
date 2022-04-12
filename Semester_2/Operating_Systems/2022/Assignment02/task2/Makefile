CFLAGS = -Wall -Wextra -D_POSIX_C_SOURCE -D_BSD_SOURCE

all: signal_handler

signal_handler: signal_handler.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

signal_handler.o: signal_handler.c
	$(CC) $(CFLAGS) -c -o $@ $^
	
clean:
	$(RM) signal_handler signal_handler.o
