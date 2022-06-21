#define _DEFAULT_SOURCE

#include "myqueue.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct RestaurantInfo
{
    pthread_mutex_t *approachCounter;
    pthread_mutex_t *queueMutex;
    sem_t *queueSemaphore;
    int *foodOnCounter;
    myqueue *orderQueue;
    atomic_int *currentNumberOfGuests;
    int isNotificationAppEnabled;
    pthread_cond_t *guestConditionVariables;
} RestaurantInfo;

typedef struct CookInfo
{
    int cookID;
    struct RestaurantInfo *restaurantInfo;
} CookInfo;

typedef struct GuestInfo
{
    int guestID;
    const int totalNumberOfGuests;
    struct RestaurantInfo *restaurantInfo;
} GuestInfo;

static void *ThreadCook(void *arg)
{
    srand((unsigned)time(NULL));

    CookInfo *const cookInfo = arg;
    RestaurantInfo *const restaurantInfo = cookInfo->restaurantInfo;
    const int myID = cookInfo->cookID;
    int *const foodOnCounter = restaurantInfo->foodOnCounter;
    pthread_mutex_t *const approachCounter = restaurantInfo->approachCounter;
    pthread_mutex_t *const queueMutex = restaurantInfo->queueMutex;
    sem_t *const queueSemaphore = restaurantInfo->queueSemaphore;
    myqueue *const orderQueue = restaurantInfo->orderQueue;
    atomic_int *const currentNumberOfGuests = restaurantInfo->currentNumberOfGuests;
    pthread_cond_t *const guestConditionVariables = restaurantInfo->guestConditionVariables;
    const int isNotificationAppEnabled = restaurantInfo->isNotificationAppEnabled;

    while (*currentNumberOfGuests > 0)
    {
        struct order order = {.guestID = -1, .foodID = -1};
        sem_wait(queueSemaphore);
        pthread_mutex_lock(queueMutex);
        // kind of busy waiting, not ideal, might fix it later
        if (!myqueue_is_empty(orderQueue))
        {
            order = myqueue_pop(orderQueue);
        }
        pthread_mutex_unlock(queueMutex);

        if (order.foodID != -1)
        {
            printf("Cook %d is preparing order %d\n", myID, order.foodID);
            const unsigned timeToWait = (unsigned)rand() % 400 + 100;
            usleep(timeToWait * 1000);
            printf("Cook %d has finished order %d\n", myID, order.foodID);
            while (1)
            {
                pthread_mutex_lock(approachCounter);
                if (*foodOnCounter != -1)
                {
                    pthread_mutex_unlock(approachCounter);
                    continue;
                }
                *foodOnCounter = order.foodID;
                printf("Cook %d has placed order %d on counter\n", myID, order.foodID);
                if (isNotificationAppEnabled)
                {
                    pthread_cond_signal(&guestConditionVariables[order.guestID]);
                }
                pthread_mutex_unlock(approachCounter);
                break;
            }
        }
    }

    printf("Cook %d is leaving the restaurant.\n", myID);
    return NULL;
}

static void *ThreadGuest(void *arg)
{
    srand((unsigned)time(NULL));

    GuestInfo *const guestInfo = arg;
    RestaurantInfo *const restaurantInfo = guestInfo->restaurantInfo;
    const int myID = guestInfo->guestID;
    int *const foodOnCounter = restaurantInfo->foodOnCounter;
    pthread_mutex_t *const approachCounter = restaurantInfo->approachCounter;
    pthread_mutex_t *const queueMutex = restaurantInfo->queueMutex;
    sem_t *const queueSemaphore = restaurantInfo->queueSemaphore;
    myqueue *const orderQueue = restaurantInfo->orderQueue;
    atomic_int *const currentNumberOfGuests = restaurantInfo->currentNumberOfGuests;
    const int totalNumberOfGuests = guestInfo->totalNumberOfGuests;
    pthread_cond_t *const guestConditionVariables = restaurantInfo->guestConditionVariables;
    const int isNotificationAppEnabled = restaurantInfo->isNotificationAppEnabled;

    const int myFoodID = rand() % 10;
    const struct order order = {.guestID = myID, .foodID = myFoodID};
    pthread_mutex_lock(queueMutex);
    myqueue_push(orderQueue, order);
    pthread_mutex_unlock(queueMutex);
    sem_post(queueSemaphore);
    printf("Guest %d has made meal order %d\n", myID, myFoodID);

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    const uint64_t orderTime = (uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);

    while (1)
    {
        pthread_mutex_lock(approachCounter);
        if (isNotificationAppEnabled)
        {
            while (*foodOnCounter != myFoodID)
            {
                pthread_cond_wait(&guestConditionVariables[myID], approachCounter);
            }
        }
        usleep(100 * 1000);
        if (*foodOnCounter == myFoodID)
        {
            *foodOnCounter = -1;
            pthread_mutex_unlock(approachCounter);
            break;
        }
        pthread_mutex_unlock(approachCounter);

        usleep(100 * 1000);
    }

    clock_gettime(CLOCK_MONOTONIC, &ts);
    const uint64_t getTime = (uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    printf("Guest %d has picked up order %d after %lu ms\n", myID, myFoodID, getTime - orderTime);
    --*currentNumberOfGuests;

    if (*currentNumberOfGuests == 0)
    {
        for (int i = 0; i < totalNumberOfGuests; ++i)
        {
            sem_post(queueSemaphore);
        }
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        fprintf(
            stderr,
            "Invalid number of arguments. Usage: ./restaurant <enable notifications> <number of guests> <number of cooks>\n");
        return EXIT_FAILURE;
    }

    char *endptr;

    const int isNotificationAppEnabled = (int)strtol(argv[1], &endptr, 10);
    if (endptr != argv[1] && *endptr != '\0')
    {
        fprintf(stderr, "Failed to parse notification enabled parameter. Aborting...\n");
        return EXIT_FAILURE;
    }
    if (isNotificationAppEnabled != 0 && isNotificationAppEnabled != 1)
    {
        fprintf(stderr, "Notification enabling may only be 0 or 1. Aborting...\n");
        return EXIT_FAILURE;
    }

    const int numberOfGuests = (int)strtol(argv[2], &endptr, 10);
    if (endptr != argv[1] && *endptr != '\0')
    {
        fprintf(stderr, "Failed to parse notification enabled parameter. Aborting...\n");
        return EXIT_FAILURE;
    }
    if (numberOfGuests <= 0)
    {
        fprintf(stderr, "Number of guests must be positive. Aborting...\n");
        return EXIT_FAILURE;
    }

    const int numberOfCooks = (int)strtol(argv[3], &endptr, 10);
    if (endptr != argv[1] && *endptr != '\0')
    {
        fprintf(stderr, "Failed to parse notification enabled parameter. Aborting...\n");
        return EXIT_FAILURE;
    }
    if (numberOfCooks <= 0)
    {
        fprintf(stderr, "Number of cooks must be positive. Aborting...\n");
        return EXIT_FAILURE;
    }

    myqueue orderQueue;
    myqueue_init(&orderQueue);

    pthread_mutex_t approachCounter;
    pthread_mutex_t queueMutex;
    sem_t queueSemaphore;
    pthread_mutex_init(&approachCounter, NULL);
    pthread_mutex_init(&queueMutex, NULL);
    sem_init(&queueSemaphore, 0, 0);

    pthread_cond_t *const guestConditionVariables =
        malloc(sizeof(*guestConditionVariables) * (unsigned)numberOfGuests);
    for (int i = 0; i < numberOfGuests; ++i)
    {
        pthread_cond_init(&guestConditionVariables[i], NULL);
    }

    int foodOnCounter = -1;
    atomic_int currentNumberOfGuests = numberOfGuests;

    RestaurantInfo restaurantInfo = {.approachCounter = &approachCounter,
                                     .queueMutex = &queueMutex,
                                     .queueSemaphore = &queueSemaphore,
                                     .foodOnCounter = &foodOnCounter,
                                     .orderQueue = &orderQueue,
                                     .currentNumberOfGuests = &currentNumberOfGuests,
                                     .isNotificationAppEnabled = isNotificationAppEnabled,
                                     .guestConditionVariables = guestConditionVariables};

    CookInfo cookInfos[numberOfCooks];
    pthread_t cooks[numberOfCooks];
    for (int i = 0; i < numberOfCooks; ++i)
    {
        cookInfos[i].cookID = i;
        cookInfos[i].restaurantInfo = &restaurantInfo;
        pthread_create(&cooks[i], NULL, ThreadCook, (void *)&cookInfos[i]);
    }

    GuestInfo guestInfos[numberOfGuests];
    pthread_t guests[numberOfGuests];
    for (int i = 0; i < numberOfGuests; ++i)
    {
        guestInfos[i].guestID = i;
        *(int *)&guestInfos[i].totalNumberOfGuests = numberOfGuests;
        guestInfos[i].restaurantInfo = &restaurantInfo;
        pthread_create(&guests[i], NULL, ThreadGuest, (void *)&guestInfos[i]);
    }

    for (int i = 0; i < numberOfGuests; ++i)
    {
        pthread_join(guests[i], NULL);
    }
    for (int i = 0; i < numberOfCooks; ++i)
    {
        pthread_join(cooks[i], NULL);
    }

    pthread_mutex_destroy(&approachCounter);
    pthread_mutex_destroy(&queueMutex);
    sem_destroy(&queueSemaphore);
    for (int i = 0; i < numberOfGuests; ++i)
    {
        pthread_cond_destroy(&guestConditionVariables[i]);
    }
    free(guestConditionVariables);

    return EXIT_SUCCESS;
}
