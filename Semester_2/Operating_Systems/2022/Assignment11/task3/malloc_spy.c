#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>

void print_number(size_t number)
{
	if (number > 9)
	{
		print_number(number / 10);
	}
	const char digit = '0' + number % 10;
	write(STDOUT_FILENO, &digit, 1);
}

void *malloc(size_t sz)
{
	static void *(*fptr)() = 0;
	if (fptr == 0)
	{
		fptr = (void *(*)())dlsym(RTLD_NEXT, "malloc");
		if (fptr == NULL)
		{
			write(STDOUT_FILENO, dlerror(), sizeof(dlerror()));
			return (0);
		}
	}

	char all[20] = "allocating ";
	char bytes[20] = " bytes\n";

	write(STDOUT_FILENO, all, sizeof(all));
	print_number(sz);
	write(STDOUT_FILENO, bytes, sizeof(bytes));

	return ((*fptr)(sz));
}
