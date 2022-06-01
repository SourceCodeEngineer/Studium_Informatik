CFLAGS = -std=c11 -Wall -Wextra #-Wpedantic -g -D_BSD_SOURCE -D_POSIX_SOURCE #-O3 #-fsanitize=address -Wconversion
LDFLAGS= -ldl

.PHONY: all
all: map_number doubles increase negate square

.PHONY: clean
clean:
	$(RM) map_number doubles.so increase.so negate.so square.so

map_number: map_number.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

doubles: doubles.c 
	$(CC) -shared -o doubles.so -fPIC doubles.c

increase: increase.c 
	$(CC) -shared -o increase.so -fPIC increase.c

negate: negate.c 
	$(CC) -shared -o negate.so -fPIC negate.c

square: square.c 
	$(CC) -shared -o square.so -fPIC square.c