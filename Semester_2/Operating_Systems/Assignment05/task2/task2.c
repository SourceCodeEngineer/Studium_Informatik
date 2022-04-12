#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>  // for INT_MAX, INT_MIN
#include <stdlib.h>  // for strtol

int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("Usage: ./task1 producer(number) consumer(number)\n");
        return EXIT_FAILURE;
    }

    char *p;

    errno = 0;
    long producer = strtol(argv[1], &p, 10);

    if (errno != 0 || *p != '\0' || producer > INT_MAX || producer < INT_MIN) {
        // Put here the handling of the error, like exiting the program with
        // an error message
        printf("producer fail\n");
        printf("Usage: ./task1 producer(number) consumer(number)\n");
        return EXIT_FAILURE;
    }

    long consumer = strtol(argv[2], &p, 10);

    if (errno != 0 || *p != '\0' || consumer > INT_MAX || consumer < INT_MIN) {
        // Put here the handling of the error, like exiting the program with
        // an error message
        printf("consumer fail\n");
        printf("Usage: ./task1 producer(number) consumer(number)\n");
        return EXIT_FAILURE;
    }

    // input is correct and we can continue with the shared memory we need!

    return EXIT_SUCCESS;
}