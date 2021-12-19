#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBinary(int n, int i)
{
	int k;
	for (k = i - 1; k >= 0; k--)
	{

		if ((n >> k) & 1)
			printf("1");
		else
			printf("0");
	}
}

typedef union
{
	float f;
	struct
	{
		unsigned int mantissa : 23;
		unsigned int exponent : 8;
		unsigned int sign : 1;

	} raw;
} myfloat;

void printIEEE(myfloat var)
{
	printf("   %d  ", var.raw.sign);
	printBinary(var.raw.exponent, 8);
	printf("  ");
	printBinary(var.raw.mantissa, 23);
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fputs("Fehler beim Einlesen des Parameters\n", stderr);
		return EXIT_FAILURE;
	}
	char *number = argv[1];
	char *foo;
	double d = strtod(number, &foo);

	char *cp = NULL;
	float v = strtof(*(argv + 1), &cp);

	if (*cp != 0)
	{
		fprintf(stderr, "ERROR: %s is not a valid float!\n", argv[1]);
		fprintf(stderr, "Extracted float component: %f\nRemaining: ", v);

		int lr = cp - *(argv + 1), lt = strlen(argv[1]);

		for (int i = 0; i < (lt - lr); i++)
		{
			putc(*(cp + i), stderr);
		}
		putc('\n', stderr);
		return EXIT_FAILURE;
	}

	myfloat var;
	var.f = d;

	// Get the IEEE floating point representation
	printf("Number: %f\n", v);
	printf("Binary representation:\n");

	printIEEE(var);

	printf("sign  exponent                 mantissa");

	return EXIT_SUCCESS;
}
