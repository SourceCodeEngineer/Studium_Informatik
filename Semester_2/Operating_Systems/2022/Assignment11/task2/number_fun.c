#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

char *strip(char *fname)
{
	char *end = fname + strlen(fname);
	while (end > fname && *end != '.')
	{
		--end;
	}

	if (end > fname)
	{
		*end = '\0';
	}
	return fname;
}

typedef int (*fptr)(int);

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Usage: %s <number> <plugin>\n", argv[1]);
		return EXIT_FAILURE;
	}

	void *handle;
	fptr func;
	char *src;

	for (int i = 2; i < argc; i++)
	{
		handle = dlopen(argv[i], RTLD_NOW);
		if (handle == NULL)
		{
			printf("%s\n", dlerror());
			return EXIT_FAILURE;
		}

		src = strip(argv[i]);
		func = (fptr)dlsym(handle, &src[2]);
		if (func == NULL)
		{
			printf("%s\n", dlerror());
			return EXIT_FAILURE;
		}
		printf("%s: %d\n", argv[i], (*func)(atoi(argv[1])));
	}
	return EXIT_SUCCESS;
}
