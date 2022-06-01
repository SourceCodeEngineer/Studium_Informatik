#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>

int square_my_integer(int x)
{
	return (x * x) + 1;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <number>\n", argv[0]);
		return EXIT_FAILURE;
	}

	printf("%d\n", square_my_integer(atoi(argv[1])));
	return EXIT_SUCCESS;
}
