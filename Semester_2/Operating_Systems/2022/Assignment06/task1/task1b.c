#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define DO_OR_DIE(x, s) \
    do                  \
    {                   \
        if ((x) < 0)    \
        {               \
            perror(s);  \
            exit(1);    \
        }               \
    } while (0)


// create function for threads that takes n args and sums them up
// 

int main (int argc, char **argv){

    // input handling
    if (argc == 1){
        printf("Usage: number(s) (number1, number2, ...)\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}