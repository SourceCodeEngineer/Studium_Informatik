#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdatomic.h>

int threadsize = 1000;

int duration = 10000;
pthread_mutex_t mutex_lock;

void *decrementX(void *arg)
{
    _Atomic int *x; //with Atomic
    x = (_Atomic int *)arg;
    //int* x;
    //x = (int*) arg; //with mutex
    for (int i = 0; i < duration; i++)
    {
        //pthread_mutex_lock(&mutex_lock);
        x--;
        //pthread_mutex_unlock(&mutex_lock);
    }

    pthread_exit(x);
}

int main(void)
{
    int value = 10000000;
    int *x;
   
    pthread_t threads[1000];

    for (int i = 0; i < threadsize; i++)
    {
        if (pthread_create(&threads[i], NULL, &decrementX, (void *)&value) != 0)
        {
            perror("Failed to create threads!\n");
        }
    }

    for (int i = 0; i < threadsize; i++)
    {
        if (pthread_join(threads[i], (void *)&x) != 0)
        {
            perror("Failed to join threads!\n");
        }
    }
    printf("%d\n", *x);
    //pthread_mutex_destroy(&mutex_lock);
    return EXIT_SUCCESS;
}
//with Atomic:

//User time (seconds): 0.00
//System time (seconds): 0.06

//with mutex:

//User time (seconds): 1.41
//System time (seconds): 1.41