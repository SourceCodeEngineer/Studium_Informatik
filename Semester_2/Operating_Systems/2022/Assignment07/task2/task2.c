// worked together in a colaboration with 

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/queue.h>
#include <stdatomic.h>

// queue setup start
struct myqueue_entry {
	int value;
	STAILQ_ENTRY(myqueue_entry) entries;
};

STAILQ_HEAD(myqueue_head, myqueue_entry);

typedef struct myqueue_head myqueue;

static void myqueue_init(myqueue* q) {
	STAILQ_INIT(q);
}

static bool myqueue_is_empty(myqueue* q) {
	return STAILQ_EMPTY(q);
}

static void myqueue_push(myqueue* q, int value) {
	struct myqueue_entry* entry = malloc(sizeof(struct myqueue_entry));
	entry->value = value;
	STAILQ_INSERT_TAIL(q, entry, entries);
}

static int myqueue_pop(myqueue* q) {
	assert(!myqueue_is_empty(q));
	struct myqueue_entry* entry = STAILQ_FIRST(q);
	const int value = entry->value;
	STAILQ_REMOVE_HEAD(q, entries);
	free(entry);
	return value;
}
// queue setup end

// creating atomic variable
atomic_int atomic = 0;

void my_mutex_lock(){
    atomic = 1;
}

void my_mutex_unlock(){
    atomic = 0;
}

// WORKS, DON'T TOUCH BELOW!!!!
struct myqueue_head queue;

long long *consumer()
{
    long long *ret = malloc(sizeof(long long));
    long long sum = 0;
    
    while (1)
    {
        while(atomic != 0){
            my_mutex_lock();
        }
        
        if (!myqueue_is_empty(&queue))
        {
            if (myqueue_pop(&queue) == 0)
            {
                my_mutex_unlock();
                break;
            }
            sum += 1;
        }
        my_mutex_unlock();
    }
    *ret = sum;
    pthread_exit(ret);
}

void *queue_writer(){
    for (int i = 0; i < 10000000; ++i){
        myqueue_push(&queue, 1);
    }

    myqueue_push(&queue, 0);

    return NULL;
}
// WORKS, DON'T TOUCH ABOVE!!!!


int main(void)
{
    pthread_t con[2];

    void *status = 0;
    int name[2] = {1, 2};

    myqueue_init(&queue);

    // create thread 0 that writes to queue
    pthread_create(&con[0], NULL, (void *)queue_writer, (void *)&name[0]);

    // wait for thread 0 to push 0 million 
    pthread_join(con[0], &status);

    long long sum_total = 0;
    
    // creating thread 1 to read 10 mil 1's
    pthread_create(&con[1], NULL, (void *)consumer, (void *)&name[1]);

    // wait for thread 1
    pthread_join(con[0], &status);
    sum_total += *(long long *)status;

    printf("Final sum: %lld\n", sum_total);

    return EXIT_SUCCESS;
}
