#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "myqueue.h"

struct myqueue_head queue;
pthread_mutex_t threadMutex;
pthread_cond_t threadCond;

#define SUMUPTO 100000
#define THREADS 500

long long *consumer(void *cno)
{
    long long *ret = malloc(sizeof(long long));
    long long sum = 0;

    while (1)
    {
        pthread_mutex_lock(&threadMutex);
        pthread_cond_wait(&threadCond, &threadMutex);
        if (!myqueue_is_empty(&queue))
        {
            if (myqueue_pop(&queue) == 0)
            {
                pthread_mutex_unlock(&threadMutex);
                pthread_cond_signal(&threadCond);
                break;
            }
            sum += 1;
        }
        pthread_mutex_unlock(&threadMutex);
        pthread_cond_signal(&threadCond);
    }

    *ret = sum;
    printf("Consumer %lld sum: %lld\n", *((long long *)cno) + 1, sum);
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

    for (int i = 0; i < THREADS; ++i)
    {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&name[i]);
        // error handling
    }

    for (int i = 0; i < SUMUPTO; ++i)
    {
        myqueue_push(&queue, 1);
    }

    for (int i = 0; i < THREADS; ++i)
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
