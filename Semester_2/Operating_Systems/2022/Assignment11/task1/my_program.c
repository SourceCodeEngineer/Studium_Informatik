#include <stdio.h>
#include <stdlib.h>

int this_function_should_increment_a_number_by_ten(int x)
{
	return x + 10;
}

int main(int argc, char argv[])
{
	if (argc != 2)
	{
		printf("Usage: %d <number>\n", argv[1]);
		return EXIT_FAILURE;
	}
	printf("%d\n", this_function_should_increment_a_number_by_ten(argv[1]));
	return EXIT_SUCCESS;
}
