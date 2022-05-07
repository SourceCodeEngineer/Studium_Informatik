// worked together in a colaboration with csaz7620, csaz2055, csaz7804

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>
#include <string.h>

#define VALUE_OF_VARIABLE 100000
#define NUMBER_OF_ITERATIONS 10000
#define NUMBER_OF_THREADS 1000

int count_i = VALUE_OF_VARIABLE;
atomic_int count_a = VALUE_OF_VARIABLE;

pthread_mutex_t mutex;

void *consumer_int()
{
    for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
    {
        pthread_mutex_lock(&mutex);
        --count_i;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer_atm()
{
    for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
    {
        --count_a;
    }
    return NULL;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("USAGE: %s atm/int\n", argv[0]);
        return EXIT_FAILURE;
    }

    pthread_t con[NUMBER_OF_THREADS];
    pthread_mutex_init(&mutex, NULL);

    if (!strcmp(argv[1], "atm"))
    {
        for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        {
            pthread_create(&con[i], NULL, consumer_atm, NULL);
        }
    }
    else
    {
        for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        {
            pthread_create(&con[i], NULL, consumer_int, NULL);
        }
    }

    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        pthread_join(con[i], NULL);
        printf("joined %d\n", i);
    }

    if (strcmp(argv[1], "atm"))
    {
        printf("Thread-Mutex-Count: %d\n", count_i);
    }
    else
    {
        printf("Thread-Atomic-Count: %d\n", count_a);
    }

    // cleanup
    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}
