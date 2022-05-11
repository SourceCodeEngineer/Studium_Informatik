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

#define NUMBER_OF_THREADS 50000
#define ATOMIC_VALUE 50000
#define THREAD_POOL 1000

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

// create job_id
// create thread_pool

// start of FIFO queue implementation - pls do not touch below!
struct myqueue_entry
{
    int value;
    STAILQ_ENTRY(myqueue_entry)
    entries;
};

STAILQ_HEAD(myqueue_head, myqueue_entry);

typedef struct myqueue_head myqueue;

static void myqueue_init(myqueue *q)
{
    STAILQ_INIT(q);
}

static bool myqueue_is_empty(myqueue *q)
{
    return STAILQ_EMPTY(q);
}

static void myqueue_push(myqueue *q, int value)
{
    struct myqueue_entry *entry = malloc(sizeof(struct myqueue_entry));
    entry->value = value;
    STAILQ_INSERT_TAIL(q, entry, entries);
}

static int myqueue_pop(myqueue *q)
{
    assert(!myqueue_is_empty(q));
    struct myqueue_entry *entry = STAILQ_FIRST(q);
    const int value = entry->value;
    STAILQ_REMOVE_HEAD(q, entries);
    free(entry);
    return value;
}
// end of queue implementation - pls do not touch above!

void* routine(void* counter){
    *(atomic_int *)counter += -1;
    pthread_exit(0);
}

// The void pool_create(thread_pool* pool, size_t size) function initializes a thread_pool 
//by starting size worker threads. Each thread checks for submitted jobs and runs them.
void pool_create(thread_pool* pool, size_t size){

}

// The job_id pool_submit(thread_pool* pool, job_function start_routine, job_arg arg) 
//submits a job to the thread pool and returns a job_id.
job_id pool_submit(thread_pool* pool, job_function start_routine, job_arg arg){

}

// The void pool_await(job_id id) function waits for the job with the given job_id to finish.
void pool_await(job_id id){

}

// shuts down the thread pool and frees all associated resources. Worker threads finish the 
//currently running job (if any) and then stop gracefully.
void pool_destroy(thread_pool* pool){

}

int main(void){

    // initalizing atomic value
    atomic_int counter = ATOMIC_VALUE;

    // creating array of size thread
    pthread_t con[NUMBER_OF_THREADS];

    // init the mutex and cond
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);

    for (int i = 0; i < NUMBER_OF_THREADS; ++i){
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

    return EXIT_SUCCESS;
}