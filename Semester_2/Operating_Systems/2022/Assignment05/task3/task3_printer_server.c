#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> // for semathore obviously
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h> // for INT_MAX, INT_MIN
#include <stdlib.h> // for strtol
#include <stdint.h> // for uint64_t
#include <errno.h>
#include <time.h>
#include <stdbool.h>

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

#define SLEEPTIMER 200000 // 200 milliseconds sleep timer for usleep

#define MESSAGESIZE 1024 // messagesize for files
// defines end

// checks if pq is empty
int isempty()
{
    if (rear == -1)
    {
        return true;
    }
    return false;
}

// check if pq is full
int isfull()
{
    // change the length of the pq up in the DEFINE!
    if (rear == PRIORITYQUEUE_LENGTH - 1)
    {
        return true;
    }
    return false;
}

// inserts element to next position
void insert(char *element, int p)
{
    rear += 1;
    pq[rear].element = element;
    pq[rear].priority = p;
}

// get highes prio
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

// delete element with highest prio
int delementteHighestPriority()
{
    int i, j, p, element;
    p = getHighestPriority();
    for (i = 0; i <= rear; ++i)
    {
        if (pq[i].priority == p)
        {
            element = *pq[i].element;
            break;
        }
    }
    if (i < rear)
    {
        for (j = i; j < rear; ++j)
        {
            pq[j].element = pq[j + 1].element;
            pq[j].priority = pq[j + 1].priority;
        }
    }
    rear = rear - 1;
    return element;
}

// displays message of server with prio
void display()
{
    int i = getHighestPriority;
    printf("Server print job with priority %d:\n", pq[i].priority);
}

// global variable start
struct priorityqueue
{
    char *element;
    int priority;
} pq[PRIORITYQUEUE_LENGTH];

int rear = -1;
// global variable end

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./task3_printer_server /YOUR_NAME!\n");
        return EXIT_FAILURE;
    }

    // todo implement shared memory buffer and add context to pq

    while(1){
        // do stuff with pq

        // if the file is closed we break the loop
        // break;
    }

    return EXIT_SUCCESS;
}
