CFLAGS = -std=gnu11 -Wall -Werror -Wextra -Wpedantic
LFLAGS = -pthread 
.PHONY: all
all: Task2 Task2lastweek

.PHONY: clean
clean:
	$(RM) Task2 Task2lastweek

Task2: Task2.c
	gcc $(CFLAGS) Task2.c -o Task2 -lpthread $(LFLAGS)

Task2lastweek: Task2lastweek.c
	gcc $(CFLAGS) Task2lastweek.c -o Task2lastweek -lpthread $(LFLAGS)