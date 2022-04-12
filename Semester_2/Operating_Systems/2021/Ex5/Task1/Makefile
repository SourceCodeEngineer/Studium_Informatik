CFLAGS = -std=gnu11 -Wall -Werror -Wextra

.PHONY: all
all: Task1.o Task1

.PHONY: clean
clean:
	$(RM) Task1.o Task1

Task1.o: Task1.c
	$(CC) $(CFLAGS) -c Task1.c -o $@