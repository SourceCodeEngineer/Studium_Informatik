CFLAGS = -std=gnu11 -Wall -Werror -Wextra -Wpedantic
LFLAGS = -pthread 
.PHONY: all
all: servertask2 clienttask2

.PHONY: clean
clean:
	$(RM) servertask2 clienttask2

servertask2: servertask2.c
	gcc $(CFLAGS) servertask2.c -o servertask2 -lpthread $(LFLAGS)

clienttask2: clienttask2.c
	gcc $(CFLAGS) clienttask2.c -o clienttask2 -lpthread $(LFLAGS)