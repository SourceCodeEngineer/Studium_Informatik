#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

typedef int (*f_ptr)(int);

char *prepare_string(char *fname, int size)
{
	char *f_string = malloc(size - 4);
	for (int i = 2; i < size - 3; ++i)
	{
		f_string[i - 2] = fname[i];
	}
	f_string[size - 3] = '\0';
	return f_string;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Usage: %s <number> <plugin(s)>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int arg = atoi(argv[1]);

	for (int i = 2; i < argc; ++i)
	{
		// open .so file
		void *file = dlopen(argv[i], RTLD_NOW);
		if (file == NULL)
		{
			printf("%s\n", dlerror());
			return EXIT_FAILURE;
		}
		// link function
		f_ptr extern_function = (f_ptr)dlsym(file, prepare_string(argv[i], strlen(argv[i])));
		if (extern_function == NULL)
		{
			printf("%s\n", dlerror());
			return EXIT_FAILURE;
		}
		// calculate and print
		arg = extern_function(arg);

		printf("%s: %d\n", argv[i], arg);
		// close file link
		dlclose(file);
	}

	return EXIT_SUCCESS;
}
