#define __USE_POSIX199309

#include <bits/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>
#include <stddef.h>

#define NUMBER_OF_WOLFES 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var;

atomic_int barn = 0;
atomic_int sheep_id = 0;
atomic_int wolf_id = 0;

//sheeps
typedef struct
{   
    pthread_t thread;
    int current_meadow;
    int sleep;
    int killed;
} sheep_t;

//wolves
typedef struct
{
    int current_meadow;
} wolf_t;

//meadow
typedef struct
{   
    sheep_t *sheep;
    wolf_t *wolves;
    int number_of_sheeps;
    int number_of_meadows;
} meadow_t;

int random_meadow(int number_of_meadows)
{
    return rand() % (number_of_meadows + 1);
}

void init_wolfes(wolf_t *wolve_infos, int number_of_meadows)
{
    for (int i = 0; i < NUMBER_OF_WOLFES; i++)
    {
        wolve_infos[i].current_meadow = random_meadow(number_of_meadows);
    }
}

void init_sheepes(sheep_t *sheep_infos, int number_of_sheeps, pthread_t* sheep_thread)
{
    for (int i = 0; i < number_of_sheeps; i++)
    {
        sheep_infos[i].current_meadow = 0;
        sheep_infos[i].sleep = 0;
        sheep_infos[i].thread = sheep_thread[i];
        sheep_infos[i].killed = 0;
    }
}

void *wolf_func();
void *sheep_func();

int main(int argc, char **argv)
{   
    srand(time(NULL));

    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <use dog> <number of sheep> <number of meadows>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int number_of_sheeps = strtol(argv[2], NULL, 10);
    int number_of_meadows = strtol(argv[3], NULL, 10);

    pthread_t sheeps[number_of_sheeps];
    pthread_t wolfes[NUMBER_OF_WOLFES];

    sheep_t *sheep_infos = malloc(sizeof(sheep_t) * number_of_sheeps);
    wolf_t *wolf_infos = malloc(sizeof(wolf_t) * NUMBER_OF_WOLFES);

    meadow_t *meadows = malloc(sizeof(meadow_t));
    meadows->sheep = sheep_infos;
    meadows->wolves = wolf_infos;
    meadows->number_of_meadows = number_of_meadows;
    meadows->number_of_sheeps = number_of_sheeps;

    init_wolfes(wolf_infos, number_of_meadows);
    init_sheepes(sheep_infos, number_of_sheeps, sheeps);

    

    //Sheeps Threads
    for (int i = 0; i < number_of_sheeps; i++)
    {
        if ((pthread_create(&sheeps[i], NULL, sheep_func, (void *)meadows)) != 0)
        {
            fprintf(stderr, "ERROR: pthread create");
            return EXIT_FAILURE;
        }
        //Wolf Threads
        if (i < NUMBER_OF_WOLFES)
        {
            if ((pthread_create(&wolfes[i], NULL, wolf_func, (void *)meadows)) != 0)
            {
                fprintf(stderr, "ERROR: pthread create");
                return EXIT_FAILURE;
            }
        }
    }

    //JOIN
    for (int i = 0; i < number_of_sheeps; i++)
    {
        if ((pthread_join(sheeps[i], NULL)) != 0)
        {
            fprintf(stderr, "ERROR: pthread join");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUMBER_OF_WOLFES; i++)
    {
        if ((pthread_join(wolfes[i], NULL)) != 0)
        {
            fprintf(stderr, "ERROR: pthread join");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

void *wolf_func(void *arg)
{
    meadow_t *meadows = (meadow_t *)arg;
    int id = wolf_id++;

    //Observing
    usleep(500);
    for(int i = 0; i < meadows->number_of_sheeps; i++)
    {
        if(meadows->sheep[i].killed != 1 && meadows->sheep[i].current_meadow == meadows->wolves->current_meadow)
        {
            meadows->sheep[i].killed = 0;
            printf("Wolf has eaten sheep %d on meadow %d", i, meadows->wolves->current_meadow);
           // pthread_cancel(meadows->sheep[i].thread);
            break;
        }
    }
    printf("Wolves %d, Number of meadows %d Curr. m: %d \n",
     id, meadows->number_of_meadows, meadows->wolves->current_meadow);
    return NULL;
}

void *sheep_func(void *arg)
{
    meadow_t *meadows = (meadow_t *)arg;
    int id = sheep_id++;
    // printf("Sheep %d, Number of meadows %d, shap meadow %d\n", 
    // id, meadows->number_of_meadows, meadows->sheep->current_meadow);
    printf("Sheep %d is taking a nap on meadow %d\n", id, meadows->sheep->current_meadow);

    sleep(1);  
    // struct timespec ts;
    // clock_gettime(CLOCK_REALTIME, &ts);
    // ts.tv_sec += 1;
    // pthread_cond_timedwait(&cond_var, &mutex, &ts);


    return NULL;
}