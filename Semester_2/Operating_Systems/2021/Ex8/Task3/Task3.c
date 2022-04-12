#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "myqueue.h"
#include <sys/types.h>
#include <unistd.h>

int value = 100000;
pthread_mutex_t mutex_mainlock;
pthread_cond_t cond_var;
int val = 0;
void *execute(void *q)
{
    int *sum = (int *)malloc(sizeof(int *));
    int temp;
    *sum = 0;
    myqueue *queue = q;
    while (1)
    {
        pthread_mutex_lock(&mutex_mainlock);

        while (true) {
    pthread_cond_wait(&cond_var, &mutex_mainlock);
    if (!myqueue_is_empty(queue))
      break;
    }

        if (!myqueue_is_empty(queue))
        {
            temp = myqueue_pop(q);
            *sum += temp;

            if (temp == 0)
            {
                printf("Consumer %ld sum: %d\n", pthread_self(), *sum);
                --val;
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
    pthread_cond_init(&cond_var, NULL);

    pthread_t threads[500];
    myqueue *q = malloc(sizeof(myqueue));
    myqueue_init(q);

    int result = 0;
    int *sum[500];

    for (int i = 0; i < 500; i++)
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
        ++val;
        pthread_cond_signal(&cond_var);

        pthread_mutex_unlock(&mutex_mainlock);
    }
    for (int i = 0; i < 500; i++)
    {
        pthread_mutex_lock(&mutex_mainlock);
        myqueue_push(q, 0);

         ++val;
        pthread_cond_signal(&cond_var);

        pthread_mutex_unlock(&mutex_mainlock);
    }

    for (int i = 0; i < 500; i++)
    {
        if (pthread_join(threads[i], (void *)&sum[i]) != 0)
        {
            perror("Failed to join threads!\n");
        }
    }
    for (int i = 0; i < 500; i++)
    {
        result += *sum[i];
        free(sum[i]);
    }
    printf("Final sum: %d\n", result);
    free(q);
    pthread_cond_destroy(&cond_var);
    pthread_mutex_destroy(&mutex_mainlock);
}