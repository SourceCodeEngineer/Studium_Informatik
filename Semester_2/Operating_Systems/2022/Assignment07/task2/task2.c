// worked together in a colaboration with 

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "myqueue.h"
#include "usemymutex.h"

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
