CFLAGS = -std=gnu11 -Wall -Werror -Wextra

.PHONY: all
all: montecarlo.o montecarlo

.PHONY: clean
clean:
	$(RM) montecarlo.o montecarlo

montecarlo.o: montecarlo.c
	$(CC) $(CFLAGS) -c montecarlo.c -o $@