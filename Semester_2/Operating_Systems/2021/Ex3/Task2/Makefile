CFLAGS = -std=gnu11 -Wall -Werror -Wextra

.PHONY: all
all: sleep.o sleep

.PHONY: clean
clean:
	$(RM) sleep.o sleep

sleep.o: sleep.c
	$(CC) $(CFLAGS) -c sleep.c -o $@