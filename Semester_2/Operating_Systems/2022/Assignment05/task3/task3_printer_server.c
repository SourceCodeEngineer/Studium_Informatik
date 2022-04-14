#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// defines start
#define DO_OR_DIE(x, s) \
    do                  \
    {                   \
        if ((x) < 0)    \
        {               \
            perror(s);  \
            exit(1);    \
        }               \
    } while (0)

#define PRIORITYQUEUE_LENGTH 5
// defines end

// function prototype start
int isempty();
int isfull();
void insert(char*, int);
int getHighestPriority();
int delementteHighestPriority();
void display();
// function prototype end

// global variable start
struct priorityqueue
{
    char* element;
    int priority;
} pq[PRIORITYQUEUE_LENGTH];

int rear = -1;
// global variable end

int main(void)
{

    // todo implement shared memory buffer and add context to pq

    return EXIT_SUCCESS;
}

// user defined function start
int isempty()
{
    if (rear == -1)
    {
        return true;
    }
    return false;
}

int isfull()
{
    // change the length of the pq and here the value
    if (rear == PRIORITYQUEUE_LENGTH - 1)
    {
        return true;
    }
    return false;
}

void insert(char *element, int p)
{
    rear += 1;
    pq[rear].element = element;
    pq[rear].priority = p;
}

int getHighestPriority()
{
    int i, p = -1;
    if (!isempty())
    {
        for (i = 0; i <= rear; ++i)
        {
            if (pq[i].priority > p)
            {
                p = pq[i].priority;
            }
        }
    }
    return p;
}

int delementteHighestPriority(){
    int i, j, p, element;
    p = getHighestPriority();
    for (i = 0; i <= rear; ++i){
        if (pq[i].priority == p){
            element = *pq[i].element;
            break;
        }
    }
    if (i < rear){
        for (j = i; j < rear; ++j){
            pq[j].element = pq[j+1].element;
            pq[j].priority = pq[j+1].priority;
        }
    }
    rear = rear-1;
    return element;
}

void display(){
    int i;
    printf("\n    Priority Queue = ");
    for (i = 0; i <= rear; ++i){
        printf("| element = %s - priority = %d |", pq[i].element, pq[i].priority);
    }
}

// user defined function end
