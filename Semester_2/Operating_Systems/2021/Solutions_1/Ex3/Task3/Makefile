CFLAGS = -std=gnu11 -Wall -Werror -Wextra

.PHONY: all
all: sigint.o sigint

.PHONY: clean
clean:
	$(RM) sigint.o sigint

sigint.o: sigint.c
	$(CC) $(CFLAGS) -c sigint.c -o $@