#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "myqueue.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdatomic.h> //module load gcc/9.2.0

atomic_flag atomic_locked1;

int value = 100000;

void lock1(void *locked)
{
    while (atomic_flag_test_and_set(locked))
    {
        sched_yield(); //with sched yield the output is wrong or sometimes wrong i dont know why
    }
    
}

void unlock1(void *locked)
{
    atomic_flag_clear(locked);
    
}

void *execute(void *q)
{
    int *sum = (int *)malloc(sizeof(int *));
    int temp;
    *sum = 0;
    myqueue *queue = q;
    while (1)
    {
        lock1(&atomic_locked1);
        
        if (!myqueue_is_empty(queue))
        {
            temp = myqueue_pop(q);
            *sum += temp;

            if (temp == 0)
            {
                printf("Consumer %ld sum: %d\n", pthread_self(), *sum);
                unlock1(&atomic_locked1);
                pthread_exit(sum);
            }
        }
        unlock1(&atomic_locked1);
        
    }
}

int main(void)
{

    pthread_t threads[50];
    myqueue *q = malloc(sizeof(myqueue));
    myqueue_init(q);

    int result = 0;
    int *sum[50];

    for (int i = 0; i < 50; i++)
    {
        if (pthread_create(&threads[i], NULL, &execute, (void *)q) != 0)
        {
            perror("Failed to create threads!\n");
        }
    }
    for (int i = 0; i < value; i++)
    {
        
        lock1(&atomic_locked1);
        myqueue_push(q, 1);
        unlock1(&atomic_locked1);
    }
    for (int i = 0; i < 50; i++)
    {
        lock1(&atomic_locked1);
        myqueue_push(q, 0);
        unlock1(&atomic_locked1);
    }

    for (int i = 0; i < 50; i++)
    {
        if (pthread_join(threads[i], (void *)&sum[i]) != 0)
        {
            perror("Failed to join threads!\n");
        }
    }
    for (int i = 0; i < 50; i++)
    {
        result += *sum[i];
        free(sum[i]);
    }
    printf("Final sum: %d\n", result);
    free(q);
}
//Task2:

//User time (seconds): 1.86
//System time (seconds): 1.68

//Task2lastweek:

//User time (seconds): 2.46
//System time (seconds): 10.60