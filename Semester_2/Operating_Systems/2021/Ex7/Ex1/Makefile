CFLAGS = -std=gnu11 -Wall -Werror -Wextra
LFLAGS = -pthread
.PHONY: all
all: Exercise1

.PHONY: clean
clean:
	$(RM) Exercise1

Exercise1: Exercise1.c
	gcc $(CFLAGS) Exercise1.c -o Exercise1 -lpthread $(LFLAGS)