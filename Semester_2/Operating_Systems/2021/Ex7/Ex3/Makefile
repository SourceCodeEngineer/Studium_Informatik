CFLAGS = -std=gnu11 -Wall -Werror -Wextra
LFLAGS = -pthread 
.PHONY: all
all: philosophers

.PHONY: clean
clean:
	$(RM) philosophers

philosophers: philosophers.c
	gcc $(CFLAGS) philosophers.c -o philosophers -lpthread $(LFLAGS)