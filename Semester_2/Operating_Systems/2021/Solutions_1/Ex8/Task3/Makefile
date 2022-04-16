CFLAGS = -std=gnu11 -Wall -Werror -Wextra -O3
LFLAGS = -pthread 
.PHONY: all
all: Task3

.PHONY: clean
clean:
	$(RM) Task3

Task3: Task3.c
	gcc $(CFLAGS) Task3.c -o Task3 -lpthread $(LFLAGS)