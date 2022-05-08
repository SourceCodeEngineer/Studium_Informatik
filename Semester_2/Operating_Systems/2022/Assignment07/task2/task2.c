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

// queue setup start
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
// queue setup end

#if USE_MY_MUTEX
volatile atomic_flag mutex = ATOMIC_FLAG_INIT;

#define MUTEX_LOCK(mutex) my_mutex_lock();
#define MUTEX_UNLOCK(mutex) my_mutex_unlock();
#define MUTEX_INIT(mutex) // set clear state

#else
pthread_mutex_t mutex;
#define MUTEX_LOCK(mutex) pthread_mutex_lock(&mutex)
#define MUTEX_UNLOCK(mutex) pthread_mutex_unlock(&mutex)
#define MUTEX_INIT(mutex)                          \
    if (pthread_mutex_init(&mutex, NULL) != 0)     \
    {                                              \
        perror("mutex init failed");           \
        return EXIT_FAILURE;                       \
    }

#endif

void my_mutex_lock()
{
    while (atomic_flag_test_and_set(&mutex))
    {
        // if flag isnt set than the it returns true. so the section is "locked"
    }
}
void my_mutex_unlock()
{
    atomic_flag_clear(&mutex);
    // clear value and "unlock"
}

myqueue queue;

void *consumer(void *args)
{
    int count = 0;
    while (1)
    {
        MUTEX_LOCK(mutex);
        if (myqueue_is_empty(&queue))
        {
            MUTEX_UNLOCK(mutex);
            continue;
        }
        if (myqueue_pop(&queue) == 0)
        {
            printf("Total sum: %d\n", count);
            MUTEX_UNLOCK(mutex);
            break;
        }
        count++;

        MUTEX_UNLOCK(mutex);
    }

    pthread_exit(args);
}
void *producer(void *args)
{
    for (int i = 0; i < 1000 * 1000; i++)
    {
        MUTEX_LOCK(mutex);
        myqueue_push(&queue, 1);
        MUTEX_UNLOCK(mutex);
    }
    MUTEX_LOCK(mutex);
    myqueue_push(&queue, 0);
    MUTEX_UNLOCK(mutex);

    pthread_exit(args);
}

int main(void)
{
    pthread_t threads[2];
    myqueue_init(&queue);

    MUTEX_INIT(mutex)
    if (pthread_create(&threads[0], NULL, producer, NULL) != 0)
    {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }
    if (pthread_create(&threads[1], NULL, consumer, NULL) != 0)
    {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < 2; i++)
    {

        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("Failed to join thread");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
