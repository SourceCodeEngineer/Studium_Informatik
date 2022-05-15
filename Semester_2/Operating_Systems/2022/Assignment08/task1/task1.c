#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <stdatomic.h>
#include "myqueue.h"

// define threadpoolsize and jobs to do
#define THREADPOOL_SIZE 500
#define JOBS 50000

typedef struct work
{
    atomic_int decr;
} work;

typedef struct thread_pool
{
    pthread_t *workers;
    myqueue queue;
    pthread_mutex_t queue_mutex;
    pthread_cond_t mutex_condition;
} thread_pool;

void *jobFunc(void *arg)
{
    work *argument = (work *)arg;
    atomic_int *counter = (&(argument->decr));
    atomic_fetch_add(counter, -1);
    return arg;
}

void *workerfunc(void *args)
{
    // casting the pool
    thread_pool *pool = (thread_pool *)args;

    pthread_mutex_lock(&(pool->queue_mutex));

    // while q is empty, wait for the cond var
    while (1)
    {
        while (myqueue_is_empty(&(pool->queue)))
        {
            pthread_cond_wait(&(pool->mutex_condition), &(pool->queue_mutex));
        }

        // doing stuff
        job task = myqueue_pop(&(pool->queue));

        if (task.arg == 0){
            pthread_mutex_unlock(&(pool->queue_mutex));
            pthread_mutex_unlock(&(task.workerLock));
            break;
        }

        work *argument = (work *)task.arg;
        pthread_mutex_unlock(&(pool->queue_mutex));
        task.routine(task.arg);
        pthread_mutex_unlock(&(task.workerLock));
    }

    pthread_exit(args);
}

void pool_create(thread_pool *pool, size_t size)
{
    // allocating memory for the workers
    pthread_t *workers = (pthread_t *)malloc(sizeof(pthread_t) * size);
    pool->workers = workers;

    // init the queue
    myqueue_init(&(pool->queue));

    // init the mutexes
    pthread_mutex_init(&(pool->queue_mutex), NULL);
    pthread_cond_init(&(pool->mutex_condition), NULL);

    // creating threads and doing the workerfunc with parameter pool
    for (size_t i = 0; i < size; ++i)
    {
        pthread_create(&workers[i], NULL, workerfunc, pool);
    }
}

job *pool_submit(thread_pool *pool, job_function start_routine, job_arg arg)
{

    job *task = (job *)malloc(sizeof(job));
    task->routine = start_routine;
    task->arg = arg;

    // init mutexes
    pthread_mutex_init(&(task->workerLock), NULL);

    // lock them up
    pthread_mutex_lock(&(task->workerLock));
    pthread_mutex_lock(&(pool->queue_mutex));

    // push in the queue
    myqueue_push(&(pool->queue), *task);

    // signal that we have an element in the queue
    pthread_cond_signal(&(pool->mutex_condition));

    // unlock
    pthread_mutex_unlock(&(pool->queue_mutex));
    return task;
}

void pool_await(job *id)
{
    // try locking the mutex
    pthread_mutex_trylock(&(id->workerLock));

    // free the malloced space
    free(id);

    // unlock and destroy
    pthread_mutex_unlock(&(id->workerLock));
    pthread_mutex_destroy(&(id->workerLock));
}

void pool_destroy(thread_pool *pool, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (pthread_join(pool->workers[i], NULL) != 0)
        {
            printf("join failed");
        }
    }
}
int main(void)
{
    // number of tasks
    size_t tasks = THREADPOOL_SIZE;

    // allocating memory
    work *argument = (work *)malloc(sizeof(work));

    // setting the starting value
    argument->decr = JOBS;

    // creating a pool
    thread_pool pool;
    pool_create(&pool, tasks);

    // pushin jobs
    for (int i = 0; i < THREADPOOL_SIZE; ++i)
    {
        pool_await((pool_submit(&pool, jobFunc, argument)));
    }

    pool_await((pool_submit(&pool, jobFunc, 0)));

    // destroying the pool again
    pool_destroy(&pool, tasks);

    // printing the decremented result
    printf("Atomic int is now: %d\n", argument->decr);

    // free the allocated memory
    free(argument);

    return EXIT_SUCCESS;
}