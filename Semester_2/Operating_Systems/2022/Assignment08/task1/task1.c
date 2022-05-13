#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/queue.h>
#include <stdatomic.h>
#include <stdbool.h>
#include "myqueue.h"

// can't go higher then 32000 threads on my system, zid works with 50k.
#define NUMBER_OF_THREADS 32000
#define ATOMIC_VALUE 50000
#define THREAD_POOL 1000

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

// create job_id
typedef struct job_id
{
    // what goes in here?
} job_id;

// create thread_pool
typedef struct thread_pool
{
    // what goes in here?
} thread_pool;

typedef void *(*job_function)(void *);
typedef void *job_arg;

void *routine(void *counter)
{
    *(atomic_int *)counter -= 1;
    pthread_exit(0);
}

// The void pool_create(thread_pool* pool, size_t size) function initializes a thread_pool
// by starting size worker threads. Each thread checks for submitted jobs and runs them.
void pool_create(thread_pool *pool, size_t size)
{
    pthread_t threads[size];

    // creating size threads
    for (size_t i = 0; i < size; ++i)
    {
        if (pthread_create(&threads[0], NULL, pool_submit, NULL) != 0)
        {
            perror("Failed to create thread");
            return EXIT_FAILURE;
        }
    }

    // executing the job

    
}

// The job_id pool_submit(thread_pool* pool, job_function start_routine, job_arg arg)
// submits a job to the thread pool and returns a job_id.
job_id pool_submit(thread_pool *pool, job_function start_routine, job_arg arg)
{
    // doing the routine
    pthread_mutex_lock(&mutexQueue);

    // do stuff


    // unlock mutex
    pthread_mutex_unlock(&mutexQueue);
}

// The void pool_await(job_id id) function waits for the job with the given job_id to finish.
void pool_await(job_id id)
{
}

// shuts down the thread pool and frees all associated resources. Worker threads finish the
// currently running job (if any) and then stop gracefully.
void pool_destroy(thread_pool *pool)
{

}

int main(int argc, char **argv)
{

    if (argc != 1)
    {
        printf("Usgae: %s", argv[0]);
        return EXIT_FAILURE;
    }

    int selection = atoi(argv[1]);

    if (selection == 2)
    {
        // do task2

        // init mutex
        pthread_mutex_init(&mutexQueue, NULL);

        // creating pool
        pool_create();

        // submitting 50000 jobs
        for (int i = 0; i < 50000; ++i)
        {
            pool_submit();
        }
                
        // if queue is empty -> pool destroy
        pool_destroy();

        pthread_mutex_destroy(&mutexQueue);
    }
    else
    {
        // initalizing atomic value
        atomic_int counter = ATOMIC_VALUE;

        // creating array of size thread
        pthread_t con[NUMBER_OF_THREADS];

        // init the mutex and cond
        pthread_mutex_init(&mutexQueue, NULL);
        pthread_cond_init(&condQueue, NULL);

        for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        {
            if (pthread_create(&con[i], NULL, &routine, (void *)&counter) != 0)
            {
                perror("Failed to create thread");
            }
        }

        for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        {
            if (pthread_join(con[i], NULL) != 0)
            {
                perror("Failed to join thread");
            }
        }

        printf("%d\n", counter);
    }

    return EXIT_SUCCESS;
}
