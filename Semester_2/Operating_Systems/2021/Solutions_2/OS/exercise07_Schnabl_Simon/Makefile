.PHONY : all clean
all: task1 task2 philosophers
CFLAGS = -g
LIBS = -lrt -pthread

task1: task1.c
	gcc -o $@ $^ $(LIBS)

task2: task2.c
	gcc -o $@ $^ $(LIBS)

philosophers: philosophers.c
	gcc -o $@ $^ $(LIBS)

clean:
	rm -rf *.o task1 task2 philosophers
