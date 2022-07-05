#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

// very nice do or die macro :D
#define DO_OR_DIE(x, s) \
   do                   \
   {                    \
      if ((x) < 0)      \
      {                 \
         perror(s);     \
         exit(1);       \
      }                 \
   } while (0)

typedef struct {
    int doornobs;
    int doors;
    int frames;
}my_struct;

void* consumerfunc(void *args){
    return NULL;
}

void* producer(void *args){
    return NULL;
}

int main(void){
    pthread_t producer[5]; 
    pthread_t consumer[5];

    int f = fork();
    
    DO_OR_DIE(f, "fork failed");

    if (f){
        // consumer
        for (size_t i = 0; i < 5; ++i)
        {
            pthread_create();
        }
        

    } else {
        f = fork();
        DO_OR_DIE(f, "fork 2 failed!");
        if (f)
        {
            // producer
        }
        
        // pthread join for consumer and producer
        
    }


    return EXIT_SUCCESS;
}