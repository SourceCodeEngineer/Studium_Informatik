CFLAGS = -std=gnu11 -Wall -Wextra -O2 -pedantic -g3 -static
CFLAGSLIBCOMPILE = -c -fPIC
CFLAGSLIBTOSHARED = -shared -o
LFLAGS = -pthread

.PHONY: all
all: some_library my_program

.PHONY: clean
clean: 
	$(RM) some_library.so
	$(RM) some_library
	$(RM) my_program

some_library: some_library.c
	gcc $(CFLAGSLIBCOMPILE) $^ -o $@ 
	gcc $(CFLAGSLIBTOSHARED) some_library.so some_library

my_program: my_program.c
	gcc $(CFLAGS) my_program.c -o my_program