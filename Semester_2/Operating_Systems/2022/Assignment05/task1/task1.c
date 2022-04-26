// worked together with csaz7804

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
#include <limits.h> // for INT_MAX, INT_MIN
#include <stdlib.h> // for strtol
#include <stdint.h>

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
    if (argc != 3)
    {
        printf("Usage: ./task1 producer(number) consumer(number)\n");
        return EXIT_FAILURE;
    }

    char *p;

    errno = 0;
    long producer = strtol(argv[1], &p, 10);

    if (errno != 0 || *p != '\0' || producer > INT_MAX || producer < INT_MIN)
    {
        // error handling
        printf("producer fail\n");
        printf("Usage: ./task1 producer(number) consumer(number)\n");
        return EXIT_FAILURE;
    }

    long consumer = strtol(argv[2], &p, 10);

    if (errno != 0 || *p != '\0' || consumer > INT_MAX || consumer < INT_MIN)
    {
        // error handling
        printf("consumer fail\n");
        printf("Usage: ./task1 producer(number) consumer(number)\n");
        return EXIT_FAILURE;
    }

    if (consumer < 1 || producer < 1)
    {
        printf("number must be greater then 0!\n");
        return EXIT_FAILURE;
    }

    // input is correct and we can continue with the shared memory we need of size consumer!
    uint64_t *shm = mmap(NULL, (consumer + 1) * sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // share memory
    uint64_t *array = shm;

    // after creating shared memory fork 2 times
    pid_t pid = fork();
    DO_OR_DIE(pid, "fork1 failed!\n");

    if (pid == 0)
    {
        // child process 1

        for (int i = 0; i < producer; ++i)
        {
            // wrap around in ring buffer (i % buffer)
            array[i % consumer] = i + 1;
        }

        // cleanup
        munmap(shm, (consumer + 1) * sizeof(uint64_t));
    }

    // *********************************
    // while ((pid = wait(NULL)) != -1); 
    // if we would wait for the child 1 we would get the same result 
    // every run but we dont because of the scheduling
    // *********************************

    pid = fork();
    DO_OR_DIE(pid, "fork2 failed!\n");

    if (pid == 0)
    {
        // child process 2
        unsigned long long result = 0;

        for (int i = 0; i < producer; ++i)
        {
            // read from shared memory
            result += array[i];
        }

        // write result to last position in array
        array[consumer + 1] = result;

        // cleanup
        munmap(shm, (consumer + 1) * sizeof(uint64_t));
    }

    // waiting for children
    while ((pid = wait(NULL)) != -1);

    // printing the result
    printf("Result: %ld\n", array[consumer + 1]);

    // cleanup
    munmap(shm, (consumer + 1) * sizeof(uint64_t));

    return EXIT_SUCCESS;
}

/*
    Analyze the obtained output. 
    
    Is the computed result the expected value?
        For low numbers yes and for higher numbers (on my mashine more than 3000) the result changes every run.

    Does the computed value change across different runs? 
        On low numbers, no. If the numbers are high enough, yes.

    What happens when you try different and larger values for N and B, for example 10,000 or 100,000?
        The number changes on every run.

    Try to explain the behavior.
        See comment in line 87.
*/
