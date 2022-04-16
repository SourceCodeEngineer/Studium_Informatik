#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>
#include <string.h>

int count_i = 10000000;
atomic_int count_a = 10000000;

pthread_mutex_t mutex;

void *consumer_int(void *cno) {
    for(int i = 0; i < 10000; i++) {
        pthread_mutex_lock(&mutex);
        --count_i;
        pthread_mutex_unlock(&mutex);
    }
   return NULL;
}

void *consumer_atm(void *cno) {
    for(int i = 0; i < 10000; i++) {
        --count_a;
    }
   return NULL;
}

int main(int argc, char *argv[]) {   
	
	if(argc != 2) {
		printf("USAGE: %s atm/int\n", argv[0]);
		return EXIT_FAILURE;
	}
	
    pthread_t con[1000];
    pthread_mutex_init(&mutex, NULL);
    
    if(!strcmp(argv[1], "atm")) {
    		for(int i = 0; i < 1000; i++) {
    	    pthread_create (&con[i], NULL, consumer_atm, NULL);
    	}
    } else {
    	for(int i = 0; i < 1000; i++) {
    	    pthread_create (&con[i], NULL, consumer_int, NULL);
    	}
    }
    for(int i = 0; i < 1000; i++) {
        pthread_join(con[i], NULL);
        printf("joined %d\n", i);
    }
	printf("Thread-Mutex-Count: %d\n", count_i);
	printf("Thread-Atomic-Count: %d\n", count_a);
    pthread_mutex_destroy(&mutex);
    return 0;
    
}
