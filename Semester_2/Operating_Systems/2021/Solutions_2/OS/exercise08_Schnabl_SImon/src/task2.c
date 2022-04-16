#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdatomic.h>

#include "myqueue.h"

#define MAX_PRODUCE 100000
#define NUM_THREADS 50

#ifdef MY_MUTEX
    atomic_flag flag = ATOMIC_FLAG_INIT;

    #define MUTEX_LOCK my_mutex_lock()
    #define MUTEX_UNLOCK my_mutex_unlock()

    void my_mutex_lock(){
	while(atomic_flag_test_and_set(&flag)) {
    	}
    }

    void my_mutex_unlock(){
       atomic_flag_clear(&flag);
    }
#else
    pthread_mutex_t mutex;
    #define MUTEX_LOCK pthread_mutex_lock(&mutex)
    #define MUTEX_UNLOCK pthread_mutex_unlock(&mutex)
#endif

void *consumer(void *q);


int main() {   
    #ifndef MY_MUTEX
    pthread_mutex_init(&mutex, NULL);
    #endif
    
	myqueue* queue = malloc(sizeof(myqueue));
    myqueue_init(queue);
    
    pthread_t con[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&(con[i]), NULL, consumer, queue);
    }
    
     for(int i = 0; i < MAX_PRODUCE; i++) {
       MUTEX_LOCK;
       myqueue_push(queue, 1);
       MUTEX_UNLOCK;
    }
    
    for(int i = 0; i < NUM_THREADS; i++) {
	   MUTEX_LOCK;
       myqueue_push(queue, 0);
       MUTEX_UNLOCK;
    }
    
	int sum_total = 0;
	void *status = 0;
    for(int i = 0; i < NUM_THREADS; i++) {
    	
        pthread_join(con[i], &status);
        sum_total += *((int *)status);
       *((int *)status) = 0;
    }
    printf("Consumer sum total: %d\n", sum_total);
	
	#ifndef MY_MUTEX
    pthread_mutex_destroy(&mutex);
    #endif
    free(queue);
    
    return EXIT_SUCCESS;
}

void* consumer(void *q) {
	int *ret = malloc(sizeof(int));
	int sum = 0;
	*ret = 0;
	myqueue* queue = (myqueue*) q;
	
    while(1) {
    	MUTEX_LOCK;
        if(myqueue_is_empty(queue)) {
        	MUTEX_UNLOCK;
        	continue; 
        }
        sum=myqueue_pop(queue);
        MUTEX_UNLOCK;
        if(sum == 0) {
         	break;
         }
         *ret += sum;
    }
    printf("Consumer %ld sum: %d\n", syscall(__NR_gettid), *ret);
   return ret;
}


