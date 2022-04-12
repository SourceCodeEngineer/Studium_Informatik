#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void print_number(size_t number) {
	if(number > 9) {
		print_number(number / 10);
	}
	const char digit = '0' + number % 10;
	write(STDOUT_FILENO, &digit, 1);
}
void *malloc(size_t size){

    void* (*malloc_pointer)(size_t);

    malloc_pointer = dlsym(RTLD_NEXT, "malloc");
    write(STDOUT_FILENO, "allocating ", 12);
	print_number(size);
	write(STDOUT_FILENO, " bytes.\n", 9);
	return(malloc_pointer(size));
}