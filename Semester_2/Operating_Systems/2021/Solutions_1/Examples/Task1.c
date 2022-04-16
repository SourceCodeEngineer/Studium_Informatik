#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>

#define TRAINS 7

typedef struct
{
    atomic_int id;
    int arival_time;
    int stop_time;
    atomic_int inactive;
    pthread_t *thread;
} train_info;

//platforms initialized with zero
//if trains is in platform value is 1
int platform[3];

atomic_int status = 0;

//Start counting
time_t start;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void handler()
{
    status = 1;
}

bool check_platform_available(int i, int train_id)
{
    pthread_mutex_lock(&lock);
    if (platform[i] == 0)
    {
        platform[i] = train_id;
        pthread_mutex_unlock(&lock);
        return true;
    }
    pthread_mutex_unlock(&lock);
    //mutex unlock
    return false;
}

void *train_func(void *arg)
{   
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    train_info *train = (train_info *)arg;
    int flag_platform_available = 0;
    int sec;

    sleep(train->arival_time);

    while (!flag_platform_available)
    {
        for (int i = 0; i < 3; i++)
        {

            if (check_platform_available(i, train->id))
            {
                
                sec = (time(NULL) - start);
                printf("%d seconds after the start: train %d moves into the station at platform %d.\n",
                       sec, train->id, i + 1);
                sleep(train->stop_time);
                //platform is free again
                platform[i] = 0;
                flag_platform_available = 1;
                sec = (time(NULL) - start);

                printf("%d seconds after the start: train %d leaves the station at platform %d.\n",
                       sec, train->id, i + 1);

                break;
            }
        }
    }       
     
    pthread_exit(0);
}

void *interrupt_func(void *arg)
{   
    train_info **trains = (train_info**) arg;
    
    while (1)
    {
        if (status == 1)
        {   
            printf("\n");
            for (int i = 0; i < 3; i++)
            {
                if (platform == 0)
                {
                    printf("Platform %d: empty\n", i + 1);
                }
                else
                {
                    printf("Platform %d: Train %d\n", i + 1, platform[i]);
                }
            }
  
            for(int i = 0; i < TRAINS; i++)
            {   
                pthread_cancel(*trains[i]->thread);
            }
           
            break;
        }
        else if (status == 2)
        {
            break;
        }
    }
   
    pthread_exit(0);
}

void init_train_infos(train_info *train_infos)
{
    train_infos[0].id = 1;
    train_infos[0].arival_time = 0;
    train_infos[0].stop_time = 8;

    train_infos[1].id = 2;
    train_infos[1].arival_time = 0;
    train_infos[1].stop_time = 4;

    train_infos[2].id = 3;
    train_infos[2].arival_time = 2;
    train_infos[2].stop_time = 3;

    train_infos[3].id = 4;
    train_infos[3].arival_time = 3;
    train_infos[3].stop_time = 7;

    train_infos[4].id = 5;
    train_infos[4].arival_time = 5;
    train_infos[4].stop_time = 3;

    train_infos[5].id = 6;
    train_infos[5].arival_time = 5;
    train_infos[5].stop_time = 5;

    train_infos[6].id = 7;
    train_infos[6].arival_time = 6;
    train_infos[6].stop_time = 2;

    for(int i = 0; i < TRAINS; i++)
        train_infos[i].inactive = 0;
}

int main(void)
{
    pthread_t trains[TRAINS];
    pthread_t interrupt_handler;
    start = time(NULL);

    train_info *train_infos;
    train_infos = malloc(sizeof(train_info) * TRAINS);
    init_train_infos(train_infos);

    for (int i = 0; i < TRAINS; i++)
    {
        train_infos[i].thread = &trains[i];
        if ((pthread_create(&trains[i], NULL, train_func, (void *)&train_infos[i])) != 0)
        {   
            fprintf(stderr, "ERROR: pthread create");
            return EXIT_FAILURE;
        }
    }

    if ((pthread_create(&interrupt_handler, NULL, interrupt_func, (void *)&trains)) != 0)
    {
        return EXIT_FAILURE;
    }

    struct sigaction sa = {0};
    sa.sa_handler = &handler;     //Pointer to our function
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL); //signal, reference to struct, NULL (no use of old sigaction)

    for (int i = 0; i < TRAINS; i++)
    {
        if ((pthread_join(trains[i], NULL)) != 0)
        {
            fprintf(stderr, "Error: Pthread Join");
            return EXIT_FAILURE;
        } 
    }

    status = 2;

    if ((pthread_join(interrupt_handler, NULL)) != 0)
    {
        fprintf(stderr, "Error: Pthread Join");
        return EXIT_FAILURE;
    }

    free(train_infos);
    return EXIT_SUCCESS;
}