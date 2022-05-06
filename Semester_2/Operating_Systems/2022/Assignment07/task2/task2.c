// worked together in a colaboration with 

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/queue.h>

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

int mutex;

struct myqueue_head queue;

long long *consumer(void *cno)
{
    long long *ret = malloc(sizeof(long long));
    long long sum = 0;
    
    while (1)
    {
        use_my_mutex_lock(&mutex);
        if (!myqueue_is_empty(&queue))
        {
            if (myqueue_pop(&queue) == 0)
            {
                pthread_mutex_unlock(&mutex);
                break;
            }
            sum += 1;
        }
        pthread_mutex_unlock(&mutex);
    }
    *ret = sum;
    pthread_exit(ret);
}

void *queue_writer(){
    for (int i = 0; i < 10000000; ++i){
        myqueue_push(&queue, 1);
    }

    return NULL;
}

int main(void)
{
    pthread_t con[2];
    use_my_mutex_init(&mutex, NULL);
    void *status = 0;
    int name[2] = {1, 2};

    myqueue_init(&queue);

    // create thread 0 that writes to queue
    pthread_create(&con[0], NULL, (void *)consumer, (void *)&name[0]);

    long long sum_total = 0;
    
    for (int i = 0; i < 5; ++i)
    {
        pthread_join(con[i], &status);
        sum_total += *(long long *)status;
    }

    printf("Final sum: %lld\n", sum_total);

    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}
