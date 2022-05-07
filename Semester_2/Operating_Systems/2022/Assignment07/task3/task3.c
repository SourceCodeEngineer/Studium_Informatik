#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/queue.h>
#include <stdatomic.h>

#define THREAD_NUM 5

// rolled and saved
int dice_values[THREAD_NUM] = {0};

// if 0 then alive, if 1 just died, if 2 was dead
int alive[THREAD_NUM] = {0};

// checks for loser(s)
int status[THREAD_NUM] = {0};

int minrolled = 0;

pthread_barrier_t barrierRolledDice;
pthread_barrier_t barrierCalculated;

void kill(){
    for (int i = 0; i < THREAD_NUM; ++i){
        if(dice_values[i] == minrolled){
            alive[i] == 1;
            printf("Player %d was eliminated\n", i);
        }
    }
}

void makeDeadWasDead(){
    for (int i = 0; i < THREAD_NUM; ++i){
        if(alive[i] == 1){
            alive[i] == 2;
        }
    }
}

void calculateLoser(){
    pthread_barrier_wait(&barrierRolledDice);

    // Calculate loser
    int min = 6;
    for (int i = 0; i < THREAD_NUM; ++i)
    {
        if (dice_values[i] < min)
        {
            min = dice_values[i];
        }
    }

    for (int i = 0; i < THREAD_NUM; ++i)
    {
        if (dice_values[i] == min)
        {
            status[i] = 1;
            minrolled = min;
        }
    }
}

void *roll(void *args)
{
    while (1)
    {
        int index = *(int *)args;

        // rolling the dice for each thread individually
        if(alive[index] == 0){dice_values[index] = rand() % 6 + 1;}

        // waiting for the barriers
        pthread_barrier_wait(&barrierRolledDice);
        
        calculateLoser();

        if (index == 0)
        {
            int bc = 0;

            for (int i = 0; i < THREAD_NUM; ++i)
            {
                if (alive[i] == 1 || alive[i] == 2)
                {
                    ++bc;
                }
            }

            if (bc == 4)
            {
                for (int i = 0; i < THREAD_NUM; ++i)
                {
                    if (alive[i] == 0)
                    {
                        printf("Player %d has won the game!\n", i);
                        break;
                    }
                }
            }

            if (bc == 5)
            {
                printf("All players were eliminated!\n");
                break;
            }

            for (int i = 0; i < THREAD_NUM; ++i)
            {
                if (alive[i] == 0)
                {
                    printf("Player %d has rolled a %d\n", i, dice_values[i]);
                }
            }

            if (bc < 4)
            {
                kill();
                printf("---------------------\n");
                makeDeadWasDead();
                sleep(1);
            }
        } else {
            int bc = 0;

            for (int i = 0; i < THREAD_NUM; ++i)
            {
                if (alive[i] == 1 || alive[i] == 2)
                {
                    ++bc;
                }
            }

            if (bc > 3){
                break;
            }
        }
    }
    return NULL;
}

int main(void)
{

    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    int i;

    pthread_barrier_init(&barrierRolledDice, NULL, THREAD_NUM);
    pthread_barrier_init(&barrierCalculated, NULL, THREAD_NUM);

    for (i = 0; i < THREAD_NUM; ++i)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &roll, (void *)a) != 0)
        {
            perror("Failed to create thread");
        }
    }

    for (i = 0; i < THREAD_NUM; ++i)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }
    pthread_barrier_destroy(&barrierRolledDice);
    pthread_barrier_destroy(&barrierCalculated);
    return EXIT_SUCCESS;
}
