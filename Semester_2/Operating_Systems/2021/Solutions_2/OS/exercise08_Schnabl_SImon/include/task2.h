#ifndef _TASK_2_H
#define _TASK_2_H

#include <stdatomic.h>
#include <stdbool.h>

#include "myqueue.h"

#define MAX_PRODUCE 100000
#define NUM_THREADS 50

typedef struct args_t args_t;
typedef struct my_mutex my_mutex;

int my_mutex_lock(my_mutex* my_mutex);
int my_mutex_unlock(my_mutex* my_mutex);

#endif
