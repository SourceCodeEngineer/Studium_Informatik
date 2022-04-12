CFLAGS = -std=gnu11 -Wall -Werror -Wextra -Wpedantic
LFLAGS = -pthread 
.PHONY: all
all: server client

.PHONY: clean
clean:
	$(RM) server client

server: server.c
	gcc $(CFLAGS) server.c -o server -lpthread $(LFLAGS)

client: client.c
	gcc $(CFLAGS) client.c -o client -lpthread $(LFLAGS)