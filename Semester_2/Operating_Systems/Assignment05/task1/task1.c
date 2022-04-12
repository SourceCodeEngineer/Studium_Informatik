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

#define DO_OR_DIE(x, s) \
    do                  \
    {                   \
        if ((x) < 0)    \
        {               \
            perror(s);  \
            exit(1);    \
        }               \
    } while (0)

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

    // todo: input is correct and we can continue with the shared memory we need of size consumer!

    // after creating shared memory fork 2 times

    pid_t pid = fork();
    DO_OR_DIE(pid, "fork1 failed!\n");

    if (pid == 0){
        // child process 1

        // if Producer > Consumer then wrap around the ring buffer
        for (int i = 1; i <= producer; ++i){
            // write to shared memory
            if (producer > consumer){
                // wrap around in ring buffer (i % buffer)
            }
            // normal writing to shared memory at position i
        }
    }

    pid = fork();
    DO_OR_DIE(pid, "fork2 failed!\n");

    if (pid == 0){
        // child process 2
        long result;

        for (int i = 0; i < producer; ++i){
            // read from shared memory
        }

        // write result to shared memory at position 1
    }

    // waiting for children
    while ((pid = wait(NULL)) != -1);

    // read from shared memory position 1 and print the result


    return EXIT_SUCCESS;
}
