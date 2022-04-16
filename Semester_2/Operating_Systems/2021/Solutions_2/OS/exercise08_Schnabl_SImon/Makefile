.PHONY : all clean
CFLAGS=-std=gnu11 -Wall -Werror -Wpedantic -O3 -pthread
CC=gcc

BIN=bin
INCLUDE=include
SRC=src

time_task1_atomic: clean task1
	clear
	/usr/bin/time -v ./$(BIN)/task1 "atm"

time_task1_mutex: clean task1
	clear
	/usr/bin/time -v ./$(BIN)/task1 "int"

time_task2_atomic: clean task2_atomic
	clear
	/usr/bin/time -v ./$(BIN)/task2_atomic

time_task2_mutex: clean task2_mutex
	clear
	/usr/bin/time -v ./$(BIN)/task2_mutex
	
time_task3: clean task3
	clear
	/usr/bin/time -v ./$(BIN)/task3

task2_atomic: $(SRC)/task2.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ -I $(INCLUDE) -D MY_QUEUE

task2_mutex: $(SRC)/task2.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ -I $(INCLUDE)

task1: $(SRC)/task1.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

task3: $(SRC)/task3.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ -I $(INCLUDE)

clean:
	$(RM) -r $(BIN)/*
