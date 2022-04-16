.PHONY : all clean

all: malloc_spy

malloc_spy: malloc_spy.c
	gcc -std=c11 -fPIC -shared malloc_spy.c -o malloc_spy.so -ldl

clean:
	$(RM) malloc_spy.so

