#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>

int this_function_should_increment_a_number_by_ten(int x)
{
	return x + 10;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <number>\n", argv[0]);
		return EXIT_FAILURE;
	}

	printf("%d\n", this_function_should_increment_a_number_by_ten(atoi(argv[1])));
	return EXIT_SUCCESS;
}
