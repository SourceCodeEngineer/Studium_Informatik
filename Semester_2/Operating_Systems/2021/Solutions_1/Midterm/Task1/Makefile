CLFAGS = -std=gnu11 -Wall -Werror -Wextra -Wpedantic -pthread -g -O2

restaurant: restaurant.c
	$(CC) $(CLFAGS) $@.c -o $@

.PHONY: clean
clean:
	$(RM) restaurant