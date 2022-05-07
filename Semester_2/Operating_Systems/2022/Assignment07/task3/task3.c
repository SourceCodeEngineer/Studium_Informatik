#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>

#define THREAD_NUM 5

// rolled and saved
int dice_values[THREAD_NUM] = {0};

// if 0 then alive, if -1 dead
int alive[THREAD_NUM] = {0};

int loopAlive = THREAD_NUM;

pthread_barrier_t barrierRolledDice;
pthread_barrier_t barrierCalculated;

void *roll(void *args)
{
    int index = *(int *)args;

    while (loopAlive)
    {
        // rolling the dice for each thread individually
        if (alive[index] == 0)
        {
            dice_values[index] = rand() % 6 + 1;
        }

        // waiting for the barriers
        pthread_barrier_wait(&barrierRolledDice);

        if (index == 0)
        {

            // check how many are alive
            int deadCounter = 0;

            for (int i = 0; i < THREAD_NUM; ++i)
            {
                if (alive[i] == -1)
                {
                    ++deadCounter;
                }
            }

            if (deadCounter < 4)
            {
                for (int i = 0; i < THREAD_NUM; ++i)
                {
                    if (alive[i] == 0)
                    {
                        printf("Player %d rolled a %d\n", i, dice_values[i]);
                    }
                }

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
                    if (dice_values[i] == min && alive[i] >= 0)
                    {
                        printf("%d eliminated\n", i);
                        alive[i] = -1;
                        --loopAlive;
                    }
                }
            }

            if (deadCounter < 4)
            {
                printf("---------------------\n");
            }

            if (deadCounter == (THREAD_NUM - 1))
            {
                for (int i = 0; i < THREAD_NUM; ++i)
                {
                    if (alive[i] == 0)
                    {
                        printf("Player %d won the game!\n", i);
                    }
                }
                loopAlive = 0;
            }

            if (deadCounter == THREAD_NUM)
            {
                printf("All players were eliminated!\n");
                loopAlive = 0;
            }
        } 

        pthread_barrier_wait(&barrierCalculated);
    }

    free(args);

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
