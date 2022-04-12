#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

int main(int argc, char **argv)
{

    void *handle;
    int (*double_value)(int);
    int (*square_value)(int);
    int (*negate_value)(int);
    int (*triple_value)(int);

    if (argc <= 2)
    {
        fprintf(stderr, "Give more arguements(.so files) !\n");
        return EXIT_FAILURE;
    }
    int number = atoi(argv[1]);
    int i;
    for (i = 2; i < argc; i++)
    {
        if (argv[i] != NULL)
        {
            if ((strcmp(argv[i], "./double.so") == 0))
            {
                handle = dlopen("./double.so", RTLD_LAZY);
                double_value = dlsym(handle, "double_value");
                printf("./double.so: %d\n", double_value(number));
            }
            else if ((strcmp(argv[i], "./square.so") == 0))
            {
                handle = dlopen("./square.so", RTLD_LAZY);
                square_value = dlsym(handle, "square_value");
                printf("./square.so: %d\n", square_value(number));
            }
            else if ((strcmp(argv[i], "./negate.so") == 0))
            {
                handle = dlopen("./negate.so", RTLD_LAZY);
                negate_value = dlsym(handle, "negate_value");
                printf("./negate.so: %d\n", negate_value(number));
            }
            else if ((strcmp(argv[i], "./triple.so") == 0))
            {
                handle = dlopen("./triple.so", RTLD_LAZY);
                triple_value = dlsym(handle, "triple_value");
                printf("./triple.so: %d\n", triple_value(number));
            }
        }
    }

    if (dlerror() != NULL)
    {
        dlclose(handle);
        return 2;
    }

    dlclose(handle);
    return 0;
}