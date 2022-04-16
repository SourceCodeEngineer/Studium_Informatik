CFLAGS = -std=gnu11 -Wall -Werror -Wextra
LFLAGS = -pthread 
.PHONY: all
all: Exercise2

.PHONY: clean
clean:
	$(RM) Exercise2

Exercise2: Exercise2.c
	gcc $(CFLAGS) Exercise2.c -o Exercise2 -lpthread $(LFLAGS)