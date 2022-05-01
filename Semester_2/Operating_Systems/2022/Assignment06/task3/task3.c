#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "myqueue.h"

struct myqueue_head queue;
pthread_mutex_t threadMutex;
pthread_cond_t threadCond;

#define SUMUPTO 50000
#define THREADS 500

long long *consumer(void *cno)
{
    long long *ret = malloc(sizeof(long long));
    long long sum = 0;
    while (1)
    {
        pthread_mutex_lock(&threadMutex);
        pthread_cond_wait(&threadCond, &threadMutex);

        if (myqueue_pop(&queue) == 0)
        {
            pthread_mutex_unlock(&threadMutex);
            break;
        }

        sum += 1;
        pthread_mutex_unlock(&threadMutex);
    }

    *ret = sum;
    printf("Consumer %lld sum: %lld\n", *((long long *)cno), sum);
    pthread_exit(ret);
}

int main(void)
{

    pthread_t con[THREADS];
    pthread_mutex_init(&threadMutex, NULL);
    pthread_cond_init(&threadCond, NULL);
    void *status = 0;
    long long name[THREADS] = {0};

    for (long long i = 0; i < THREADS; ++i)
    {
        name[i] = i;
    }

    myqueue_init(&queue);

    for (long long i = 0; i < THREADS; ++i)
    {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&name[i]);
    }

    for (long long i = 0; i < SUMUPTO; ++i)
    {
        myqueue_push(&queue, 1);
        pthread_cond_signal(&threadCond);
    }

    for (long long i = 0; i < THREADS; ++i)
    {
        myqueue_push(&queue, 0);
        pthread_cond_signal(&threadCond);
    }

    long long sum_total = 0;

    for (long long i = 0; i < THREADS; ++i)
    {
        pthread_join(con[i], &status);
        sum_total += *(long long *)status;
    }

    printf("Final sum: %lld\n", sum_total);

    pthread_mutex_destroy(&threadMutex);
    pthread_cond_destroy(&threadCond);
    return EXIT_SUCCESS;
}
