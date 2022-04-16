CFLAGS = -Wall -Werror -std=gnu11 -Wextra
LDFLAGS = -shared -fPIC
BINARYS = double.so square.so negate.so triple.so number_fun

.PHONY: all
all: $(BINARYS)

%.so: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

number_fun: number_fun.c
	$(CC) $(CFLAGS) -o $@ $^ -ldl

.PHONY: clean

clean:
	rm $(BINARYS)