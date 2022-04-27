#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "myqueue.h"

struct myqueue_head queue;
pthread_mutex_t mutex;

long long *consumer(void *cno)
{
    long long *ret = malloc(sizeof(long long));
    long long sum = 0;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (!myqueue_is_empty(&queue))
        {
            if (myqueue_pop(&queue) == 0)
            {
                pthread_mutex_unlock(&mutex);
                break;
            }
            sum += 1;
        }
        pthread_mutex_unlock(&mutex);
    }
    *ret = sum;
    printf("Consumer %lld sum: %lld\n", *((long long *)cno), sum);
    pthread_exit(ret);
}

int main(void)
{

    pthread_t con[5];
    pthread_mutex_init(&mutex, NULL);
    void *status = 0;
    long long name[5] = {1, 2, 3, 4, 5};

    myqueue_init(&queue);

    for (long long i = 0; i < 5; ++i)
    {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&name[i]);
    }

    for (long long i = 0; i < 10000; ++i)
    {
        myqueue_push(&queue, 1);
    }

    for (long long i = 0; i < 5; ++i)
    {
        myqueue_push(&queue, 0);
    }

    long long sum_total = 0;
    
    for (long long i = 0; i < 5; ++i)
    {
        pthread_join(con[i], &status);
        sum_total += *(long long *)status;
    }

    printf("Final sum: %lld\n", sum_total);

    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}
