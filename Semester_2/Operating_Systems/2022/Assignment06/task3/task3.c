#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "myqueue.h"

struct myqueue_head queue;
pthread_mutex_t mutex;

int *consumer(void *cno)
{
    int *ret = malloc(sizeof(int));
    int sum = 0;
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
    printf("Consumer %d sum: %d\n", *((int *)cno), sum);
    pthread_exit(ret);
}

int main(void)
{

    pthread_t con[500];
    pthread_mutex_init(&mutex, NULL);
    void *status = 0;
    int name[500] = {0};

    for (int i = 0; i < 500; ++i)
    {
        name[i] = i;
    }

    myqueue_init(&queue);

    for (int i = 0; i < 500; ++i)
    {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&name[i]);
    }

    for (int i = 0; i < 100000; ++i)
    {
        myqueue_push(&queue, 1);
    }

    for (int i = 0; i < 500; ++i)
    {
        myqueue_push(&queue, 0);
    }

    int sum_total = 0;
    for (int i = 0; i < 500; ++i)
    {
        pthread_join(con[i], &status);
        sum_total += *(int *)status;
    }

    printf("Final sum: %d\n", sum_total);

    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}
