#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdint.h>

#include "myqueue.h"

int cookID = 0;
int guestID = 0;
int guests_total = 0;
int orders = 0;
uint64_t totalms = 0;

pthread_mutex_t mutex;
struct myqueue_head order_queue;
struct myqueue_head counter;

void *cook()
{
    pthread_mutex_lock(&mutex);
    int id = cookID;
    ++cookID;
    pthread_mutex_unlock(&mutex);

    int val;
    unsigned int seed = (unsigned)pthread_self();
    int rand_time = (rand_r(&seed) % 500 + 100);
    while (guests_total > 0)
    {
        pthread_mutex_lock(&mutex);
        if (!myqueue_is_empty(&order_queue))
        {
            val = myqueue_pop(&order_queue);
            pthread_mutex_unlock(&mutex);
            printf("Cook %d is preparing order %d\n", id, val);
            usleep(rand_time * 1000);
            myqueue_push(&counter, val);
            printf("Cook %d has placed order %d on counter\n", id, val);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(0);
}

void *guest()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    pthread_mutex_lock(&mutex);
    int id = guestID;
    ++guestID;
    int order = orders;
    int val;
    printf("Guest %d has made meal order %d\n", id, orders);
    ++orders;
    myqueue_push(&order_queue, id);
    pthread_mutex_unlock(&mutex);

    while (1)
    {
        usleep(100 * 1000);
        pthread_mutex_lock(&mutex);
        if (!myqueue_is_empty(&counter))
        {
            usleep(100 * 1000);
            val = myqueue_pop(&counter);
            if (val == order)
            {
                uint64_t ms = ts.tv_sec * 1e3 + ts.tv_nsec / 1e6;
                printf("Guest %d has picked up order %d after %ld ms\n", id, order, ms);
                --guests_total;
                totalms = totalms + ms;
                pthread_mutex_unlock(&mutex);
                pthread_exit(0);
            }
            else if (!myqueue_is_empty(&counter))
            {
                int tmp = myqueue_pop(&counter);
                if (tmp == order)
                {
                    myqueue_push(&counter, val);
                    uint64_t ms = ts.tv_sec * 1e3 + ts.tv_nsec / 1e6;
                    printf("Guest %d has picked up order %d after %ld ms\n", id, order, ms);
                    --guests_total;
                    totalms = totalms + ms;
                    pthread_mutex_unlock(&mutex);
                    pthread_exit(0);
                }
                myqueue_push(&counter, tmp);
            }
            myqueue_push(&counter, val);
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(0);
}

int main(int argc, char **argv)
{

    if (argc != 4)
    {
        perror("Usage: <enable notifications> <number of guests> <number of cooks>");
        return EXIT_FAILURE;
    }

    pthread_mutex_init(&mutex, NULL);
    myqueue_init(&order_queue);
    myqueue_init(&counter);

    int COOKS = atoi(argv[3]);
    int GUESTS = atoi(argv[2]);
    guests_total = GUESTS;

    pthread_t cooks[COOKS];
    pthread_t guests[GUESTS];

    for (int i = 0; i < COOKS; ++i)
    {
        pthread_create(&cooks[i], NULL, cook, NULL);
    }

    for (int i = 0; i < GUESTS; ++i)
    {
        pthread_create(&guests[i], NULL, guest, NULL);
    }

    // if( atoi(argv[1]) == 1 ) {

    // would have been for notification

    //}

    for (int i = 0; i < COOKS; ++i)
    {
        pthread_join(cooks[i], NULL);
    }

    for (int i = 0; i < GUESTS; ++i)
    {
        pthread_join(guests[i], NULL);
    }

    printf("All guests have been served with an average waiting time of %ld ms\n", totalms / GUESTS);

    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}
