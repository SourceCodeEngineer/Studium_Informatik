#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include "myqueue.h"

//cook
typedef struct
{
    int id;
    int current_order;
    int working;
} cook_t;

//guest
typedef struct
{
    int id;
    int current_order;
} guest_t;

pthread_mutex_t mutex_lock;

void *cooking()
{

    int *sum_of_orders = (int *)malloc(sizeof(int *));
    void *orders;
    int temp;
    int order = 0;
    *sum_of_orders = 0;
    myqueue *queue = orders;
    while (1)
    {
        pthread_mutex_lock(&mutex_lock);

        if (!myqueue_is_empty(queue))
        {
            temp = myqueue_pop(orders); //to get the orders out for the cook
            *sum_of_orders += temp;

            if (sum_of_orders != 0)
            {
                printf("Cook %ld is preparing order %d!\n", pthread_self(), order); //the id of the cook and what order he is making.
                usleep(500);                                                   //cook prepares the order should be random but i had no time for that
                order++;                                                       // next order will be 1
                sum_of_orders--;                                                      //if the cook is finished i gives out 1 order
                pthread_mutex_unlock(&mutex_lock);
            }
            if (orders == 0)
            {
                pthread_mutex_unlock(&mutex_lock);
                pthread_exit(orders);
            }
        }
    }
}

void *ordering()
{
int *sum_of_orders = (int *)malloc(sizeof(int *));
    void *orders;
    int temp;
    int order = 0;
    *sum_of_orders = 0;
    myqueue *queue = orders;
    while (1)
    {
        pthread_mutex_lock(&mutex_lock);

        if (!myqueue_is_empty(queue))
        {
            temp = myqueue_pop(orders); //to get the orders out for the cook
            *sum_of_orders += temp;
    

            if (sum_of_orders != 0)
            {
                printf("Guest %ld has made meal order %d", pthread_self(), order); //the id of the cook and what order he is making.
                order++;                                                       // next order will be 1
                sum_of_orders--;                                                      //if the cook is finished i gives out 1 order
                pthread_mutex_unlock(&mutex_lock);
            }
            if (sum_of_orders == 0)
            {
                pthread_mutex_unlock(&mutex_lock);
                pthread_exit(orders);
            }
        }
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    pthread_mutex_init(&mutex_lock, NULL);
    myqueue *orders = malloc(sizeof(myqueue));
    myqueue_init(orders); //queue for the orders

    if (argc != 4)
    {
        perror("give me more Arguements!\n");
    }
    //int notifications = strtol(argv[1], NULL, 10);
    int number_of_guests = strtol(argv[2], NULL, 10);
    int number_of_cooks = strtol(argv[3], NULL, 10);

    pthread_t cooks[number_of_cooks];
    pthread_t guests[number_of_guests];

    for (int i = 0; i < number_of_guests; i++)
    {
        if (pthread_create(&guests[i], NULL, &ordering, NULL) != 0)
        {
            perror("Failed to creat Thread/s!\n");
        }
    }
    for (int i = 0; i < number_of_cooks; i++)
    {
        if (pthread_create(&cooks[i], NULL, &cooking, NULL) != 0)
        {
            perror("Failed to creat Thread/s!\n");
        }
    }

    for (int i = 0; i < number_of_guests; i++)
    {
        pthread_mutex_lock(&mutex_lock);
        myqueue_push(orders, 1);
        pthread_mutex_unlock(&mutex_lock);
    }
    for (int i = 0; i < number_of_guests; i++)
    {
        if (pthread_join(guests[i], NULL) != 0)
        {
            perror("Failed to join threads!\n");
        }
    }
    for (int i = 0; i < number_of_cooks; i++)
    {
        if (pthread_join(cooks[i], NULL) != 0)
        {
            perror("Failed to join threads!\n");
        }
    }

    pthread_mutex_destroy(&mutex_lock);
    return EXIT_SUCCESS;
}
/*
Meine Hauptidee war dass ich 2 Threads mache wo dann eine queue die orders rein pusht,
aber das Problem war hauptsächlich, dass es zu wenig zeit war, ich wollte noch die ids machen aber hatte dafür zuwenig zeit die structs die ich oben
verwenden wollte habe ich letztendlich auch nimmer verwendet weil wie gesagt zu wenig Zeit für mich war. Nach der Cook dann die Orders 
bekommen hat wollte ich ihn sleepen lassen es hat aber nit funktioniert mit dieser random zeit weil dieses CLOCK_MONOTONIC als nicht definiert ist obwohl ich die ganzen
includiert habe.
nachdem dieser cook fertig hat und keine anderen orders mehr sind wird er returned und dann kann er "feierabend machen"
die guests sollten warten bis sie die mitteilung bekommen hatte dafür aber zu wenig zeit es sollte eigenlich recht easy sein, man könnte mit sigaction ein signal an den Kunden schicken dass er das abholt
oder ein fach ein printf machen und dies dann returnen und am anfang einfach if(notification == 1) soll man immer die die Nachricht schicken wenn er == 0 ist nicht.
ich habe die Header datei vom Sheet7 genommen und so die queue gemacht aber mit der zeit um es auf 2 Threads anzuwenden war es doch zu wenig meiner Meinung nach, vielleicht dachte ich auf zu kompliziert.
nachdem der Kunde was zu essen bekommen hat wird er dann essen und dann gehen sprich wird er returned und dann wartet der pthread im join auf die anderene Threads.
zu synchronisieren habe ich mutex verwendet weil es meiner meinung nach besser da ich selbst konntrollieren kann was von einem Thread verwendet wird, man hätte auch die orders atomic machen können das hätte glaubich auch gereicht.

Die Datei Compiliert leider nicht obwohl es weil meine queue nicht richtig verwendet wird weil ich ja Teile nicht gemacht habe, ich hoffe ich bekomme trotzdem paar Punkte bekomme weil mir nicht viel fehlt um zu bestehen, 
ich habe ja Makefiles und meine Ideen gemacht, mein hauptproblem war hauptsächlich dass ich zu wenig zeit hatte, sonst wäre es glaubich möglich gewesen nur in der Zeit für mich nit.

myqueue.h ist von der WEEK7 Exercise2 glaube ich.
*/