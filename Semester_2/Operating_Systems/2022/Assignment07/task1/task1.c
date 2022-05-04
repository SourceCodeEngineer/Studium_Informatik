#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t threadMutex;

#define THREADS 1000

void* threadFunction(){

}

int main (void){

    int x = 100000;

    for (int i = 0; i < THREADS; ++i){
        // create 1000 thrads
    }


    for (int i = 0; i < THREADS; ++i){
        // join 1000 thrads
    }


    // cleanup
    pthread_mutex_destroy(&threadMutex);

    return EXIT_SUCCESS;
}