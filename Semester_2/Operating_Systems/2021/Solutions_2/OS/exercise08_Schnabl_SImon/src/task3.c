#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdatomic.h>

#include "myqueue.h"

#define MAX_PRODUCE 100000
#define NUM_THREADS 500

void *consumer(void *q);

pthread_mutex_t mutex;
pthread_cond_t cv;
int main() {   
    pthread_mutex_init(&mutex, NULL);
    
	myqueue* queue = malloc(sizeof(myqueue));
    myqueue_init(queue);
    
    pthread_t con[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&(con[i]), NULL, consumer, queue);
    }
    
     for(int i = 0; i < MAX_PRODUCE; i++) {
       	 pthread_mutex_lock(&mutex);
       myqueue_push(queue, 1);
       pthread_cond_signal(&cv);
       pthread_mutex_unlock(&mutex);
    }
    
    for(int i = 0; i < NUM_THREADS; i++) {
	 pthread_mutex_lock(&mutex);
       myqueue_push(queue, 0);
       pthread_cond_signal(&cv);
       pthread_mutex_unlock(&mutex);
    }
    
	int sum_total = 0;
	void *status = 0;
    for(int i = 0; i < NUM_THREADS; i++) {
    	
        pthread_join(con[i], &status);
        sum_total += *((int *)status);
       *((int *)status) = 0;
    }
    printf("Consumer sum total: %d\n", sum_total);
	
    pthread_mutex_destroy(&mutex);
    free(queue);
    
    return EXIT_SUCCESS;
}

void* consumer(void *q) {
	int *ret = malloc(sizeof(int));
	int sum = 0;
	*ret = 0;
	myqueue* queue = (myqueue*) q;
	
    while(1) {
    	pthread_mutex_lock(&mutex);
    	pthread_cond_wait(&cv,&mutex);
        if(myqueue_is_empty(queue)) {
        	pthread_mutex_unlock(&mutex);
        	continue; 
        }
        sum=myqueue_pop(queue);
        pthread_mutex_unlock(&mutex);
        if(sum == 0) {
         	break;
         }
         *ret += sum;
    }
    printf("Consumer %ld sum: %d\n", syscall(__NR_gettid), *ret);
   return ret;
}


