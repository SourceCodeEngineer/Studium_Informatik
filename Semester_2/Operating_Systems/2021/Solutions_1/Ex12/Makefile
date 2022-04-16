CFLAGS = -std=gnu11 -Wall -Werror -Wextra
LFLAGS = -pthread
.PHONY: all
all: Task1

.PHONY: clean
clean:
	$(RM) Task1

Task1: Task1.c
	gcc $(CFLAGS) Task1.c -o Task1 -lpthread $(LFLAGS)