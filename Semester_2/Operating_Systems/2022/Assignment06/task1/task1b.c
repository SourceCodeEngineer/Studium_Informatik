#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <limits.h> // for INT_MAX, INT_MIN

struct args
{
    int index;
    int *result;
    int *values;
};

void *sumArguments(void *arguments)
{
    int index = ((struct args *)arguments)->index;
    int *values = ((struct args *)arguments)->values;
    int *result = ((struct args *)arguments)->result;

    int sum = 0;

    for (int i = 0; i <= index; ++i)
    {
        sum = sum + values[i];
    }

    result[index] = sum;

    pthread_exit(result);
}
int main(int argc, char **argv)
{

    if (argc < 1)
    {
        printf("Usgae: ./task1b number(s)\n");
        return EXIT_FAILURE;
    }

    pthread_t *pt = (pthread_t *)malloc(sizeof(pthread_t) * argc - 1);

    struct args *arguments = (struct args *)malloc(sizeof(struct args) * argc - 1);

    int *values = malloc(sizeof(int) * argc - 1);
    int *result = malloc(sizeof(int) * argc - 1);

    if (values == NULL || result == NULL)
    {
        printf("malloc failed!\n");
        return EXIT_FAILURE;
    }

    char *p;

    for (int i = 0; i < argc - 1; ++i)
    {
        errno = 0;

        values[i] = strtol(argv[i + 1], &p, 10);

        if (errno != 0 || *p != '\0' || values[i] > INT_MAX || values[i] < INT_MIN)
        {
            // error handling
            printf("number fail\n");
            printf("Usage: ./task1b number(s)\n");
            return EXIT_FAILURE;
        }
        
    }

    for (int i = 0; i < argc - 1; ++i)
    {
        arguments[i].index = i;
        arguments[i].values = values;
        arguments[i].result = result;
        pthread_create(&pt[i], NULL, sumArguments, &arguments[i]);
    }

    for (int i = 0; i < argc - 1; ++i)
    {
        pthread_join(pt[i], NULL);
        printf("sum%d = %d\n", arguments->index + 1, arguments->result[i]);
    }

    free(result);
    free(values);
    free(arguments);
    free(pt);

    return EXIT_SUCCESS;
}
