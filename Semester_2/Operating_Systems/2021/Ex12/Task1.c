#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <stdatomic.h> //module load gcc/9.2.0

#define WORKERS 20

typedef struct _worker_
{
    atomic_int worker;
    double lazyness;
} worker_struct;

atomic_size_t knobs = 0;
atomic_size_t doors = 0;

size_t doors_to_produce;

void redestributeTo(int add_worker, worker_struct worker_info[])
{
    for (int i = 0; i < WORKERS; i++)
    {
        if (worker_info[i].worker != add_worker)
        {
            worker_info[i].worker = add_worker;
            return;
        }
    }
}

void *sleepWorker(void *received_info)
{
    worker_struct *worker_info = (worker_struct *)received_info;
    unsigned seed = (unsigned)pthread_self();
    worker_info->lazyness = rand_r(&seed) / (double)RAND_MAX;

    while (doors < doors_to_produce || knobs < doors_to_produce)
    {
        if (worker_info->worker == 0)
        {
            usleep((10 + worker_info->lazyness * 30) * 1000);
            knobs++;
        }
        if (worker_info->worker == 1)
        {
            usleep((10 + worker_info->lazyness * 90) * 1000);
            doors++;
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{

    if (argc != 3)
    {
        perror("give me more Arguements!\n");
    }

    bool with_redist = atoi(argv[1]);
    doors_to_produce = atoi(argv[2]);

    pthread_t worker_ids[WORKERS];
    worker_struct worker_info[WORKERS];

    size_t num_knob_worker = WORKERS / 2;
    size_t second_counter = 0;
    double door_rate;
    double knob_rate;

    for (int i = 0; i < WORKERS; i++)
    {
        worker_info[i].worker = i < WORKERS / 2 ? 0 : 1;
        pthread_create(&worker_ids[i], NULL, sleepWorker, &worker_info[i]);
    }

    while (doors < doors_to_produce || knobs < doors_to_produce)
    {
        sleep(1);
        second_counter++;
        door_rate = doors / second_counter;
        knob_rate = knobs / second_counter;
        printf("Producing %.2f knobs/s, %.2f doors/s\n", knob_rate, door_rate);
        if (with_redist)
        {
            if ((door_rate / (knob_rate + door_rate)) * 100 > 60)
            {
                num_knob_worker++;
                redestributeTo(0, worker_info);
            }
            if ((knob_rate / (door_rate + knob_rate)) * 100 > 60)
            {
                num_knob_worker--;
                redestributeTo(1, worker_info);
            }
            printf("\t Workers reassigned: %ld making knobs, %ld making doors\n", num_knob_worker, WORKERS - num_knob_worker);
        }
    }

    printf("%ld doors produced in %ld.00s (%.2f doors/s)\n", doors, second_counter, door_rate);
    printf("%ld knobs produced\n", knobs);

    for (int i = 0; i < WORKERS; i++)
    {
        pthread_join(worker_ids[i], NULL);
    }
}