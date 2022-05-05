#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex;

// user defines to change paameter
#define THREADS 1000
#define NUMBER_OF_ITERATIONS 10000

int* myThreadFunction(int x){

    for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i){
        pthread_mutex_lock(&mutex);
        ++x;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(&x);
}

int main()
{
    int x = 100000;

    pthread_t con[THREADS];

    // init the mutex
    pthread_mutex_init(&mutex, NULL);
    
    // create 10000 threads
    for (int i = 0; i < THREADS; ++i){
        pthread_create(&con[i], (int *)myThreadFunction, x, NULL);
    }

    for (int i = 0; i < THREADS; ++i){
        pthread_join(con[i], NULL);
    }

    printf("%d", x);
    // cleanup
    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}
