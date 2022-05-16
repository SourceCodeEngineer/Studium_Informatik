// worked together in a colaboration with csaz7620, csaz2055, csaz7804

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
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "myqueue.h"

typedef void *(*job_function)(void *args);
typedef void *job_arg;

typedef struct job
{
    job_function routine;
    job_arg arg;
    sem_t *workerLock;
} job;

typedef struct thread_pool
{
    size_t numberOfThreads;
    int statePool;
    myqueue work;
    pthread_mutex_t queue_mutex;
    pthread_cond_t mutex_condition;
    pthread_t *workers;
    unsigned int activeWork;
} thread_pool;

thread_pool *pool_init(size_t size)
{
    thread_pool *pool = (thread_pool *)malloc(sizeof(thread_pool));
    pool->workers = (pthread_t *)(malloc(sizeof(pthread_t) * size));
    pool->activeWork = 0;
    pool->numberOfThreads = size;
    pool->statePool = 1;
    pthread_mutex_init(&(pool->queue_mutex), NULL);
    pthread_cond_init(&(pool->mutex_condition), NULL);

    myqueue_init(&pool->work);

    return pool;
}

typedef struct work
{
    atomic_int decr;
} work;

void *jobFunc(void *args)
{
    struct work *argument = (struct work *)args;
    atomic_int *counter = (&(argument->decr));
    atomic_fetch_add(counter, -1);

    return NULL;
}

void *workerfunc(void *args)
{
    thread_pool *pool = (thread_pool *)args;

    while (1)

    {
        pthread_mutex_lock(&(pool->queue_mutex));
        while (myqueue_is_empty(&pool->work))
        {
            pthread_cond_wait(&(pool->mutex_condition), &(pool->queue_mutex));
        }

        job *task = myqueue_pop(&pool->work);

        pthread_mutex_unlock(&(pool->queue_mutex));

        if (task->routine == NULL)
        {
            sem_post(task->workerLock);
            break;
        }

        work *argument = (work *)task->arg;
        task->routine(argument);
        sem_post(task->workerLock);
    }

    return NULL;
}

job *pool_submit(thread_pool *pool, job_function start_routine, job_arg arg)
{

    job *task = (job *)malloc(sizeof(job));
    task->routine = start_routine;
    task->arg = arg;
    sem_t *sem = (sem_t *)malloc(sizeof(sem_t));
    task->workerLock = sem;

    sem_init((task->workerLock), 0, 0);
    pthread_mutex_lock(&(pool->queue_mutex));

    myqueue_push(&pool->work, task);
    pthread_cond_signal(&(pool->mutex_condition));
    pool->activeWork++;
    pthread_mutex_unlock(&(pool->queue_mutex));

    return task;
}
void pool_await(job *id)
{
    sem_wait((id->workerLock));
    free(id->workerLock);
    sem_close(id->workerLock);
}
void pool_destroy(thread_pool *pool, size_t size)
{

    for (size_t i = 0; i < size; ++i)
    {
        pool_await(pool_submit(pool, NULL, NULL));
    }

    for (size_t i = 0; i < size; ++i)
    {
        if (pthread_join(pool->workers[i], NULL) != 0)
        {
            printf("join failed");
        }
    }
}

void pool_create(thread_pool *pool, size_t size)
{

    for (size_t i = 0; i < size; ++i)
    {

        pthread_create(&(pool->workers[i]), NULL, workerfunc, pool);
    }
}

int main(void)
{
    size_t num = 10;
    work *argument = (work *)malloc(sizeof(work));
    argument->decr = 20000;
    thread_pool *pool = pool_init(num);
    pool_create(pool, num);
    size_t i = 0;

    while (i < 20000)
    {
        pool_await((pool_submit(pool, jobFunc, argument)));
        ++i;
    }

    pool_destroy(pool, num);
    printf("Atomic int is: %d\n", argument->decr);

    return EXIT_SUCCESS;
}
