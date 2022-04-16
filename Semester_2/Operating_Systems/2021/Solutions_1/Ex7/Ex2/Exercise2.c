#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "myqueue.h"
#include <sys/types.h>
#include <unistd.h>

int value = 10000;
pthread_mutex_t mutex_mainlock;


void *execute(void *q)
{
    int *sum = (int *)malloc(sizeof(int *));
    int temp;
    *sum = 0;
    myqueue *queue = q;
    while (1)
    {
        pthread_mutex_lock(&mutex_mainlock);
        
        if (!myqueue_is_empty(queue))
        {
            temp = myqueue_pop(q);
            *sum += temp;

            if (temp == 0)
            {
                printf("Consumer %ld sum: %d\n", pthread_self(), *sum);
                pthread_mutex_unlock(&mutex_mainlock);
                
                pthread_exit(sum);
            }
        }

        pthread_mutex_unlock(&mutex_mainlock);
        
    }
}

int main(void)
{
    pthread_mutex_init(&mutex_mainlock, NULL);
    

    pthread_t threads[5];
    myqueue *q = malloc(sizeof(myqueue));
    myqueue_init(q);

    int result = 0;
    int *sum[5];

    for (int i = 0; i < 5; i++)
    {
        if (pthread_create(&threads[i], NULL, &execute, (void *)q) != 0)
        {
            perror("Failed to create threads!\n");
        }
    }
    for (int i = 0; i < value; i++)
    {
        pthread_mutex_lock(&mutex_mainlock);
        myqueue_push(q, 1);
        pthread_mutex_unlock(&mutex_mainlock);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutex_mainlock);
        myqueue_push(q, 0);
        pthread_mutex_unlock(&mutex_mainlock);
    }

    for (int i = 0; i < 5; i++)
    {
        if (pthread_join(threads[i], (void *)&sum[i]) != 0)
        {
            perror("Failed to join threads!\n");
        }
    }
    for (int i = 0; i < 5; i++)
    {
        result += *sum[i];
        free(sum[i]);
    }
    printf("Final sum: %d\n", result);
    free(q);
    pthread_mutex_destroy(&mutex_mainlock);
}