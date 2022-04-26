// worked together with csaz7804

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> // for semathore obviously
#include <string.h>
#include <sys/types.h>
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
#include <stdint.h> // for uint64_t
#include <errno.h>
#include <time.h>

#define MAP_ANONYMOUS 0x20

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
        printf("Usage: ./task1 number buffer(number)\n");
        return EXIT_FAILURE;
    }

    char *p;

    errno = 0;
    long number = strtol(argv[1], &p, 10);

    if (errno != 0 || *p != '\0' || number > INT_MAX || number < INT_MIN)
    {
        // error handling
        printf("number fail\n");
        printf("Usage: ./task1 number(number) ringbuffer(number)\n");
        return EXIT_FAILURE;
    }

    long ringbuffer = strtol(argv[2], &p, 10);

    if (errno != 0 || *p != '\0' || ringbuffer > INT_MAX || ringbuffer < INT_MIN)
    {
        // error handling
        printf("ringbuffer fail\n");
        printf("Usage: ./task1 number(number) ringbuffer(number)\n");
        return EXIT_FAILURE;
    }

    if (ringbuffer < 1 || number < 1)
    {
        printf("number must be greater then 0!\n");
        return EXIT_FAILURE;
    }

    // input is correct and we can continue with the shared memory we need of size ringbuffer!
    uint64_t *sharedmemory = mmap(NULL, (ringbuffer + 1) * sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // share memory

    if (sharedmemory == MAP_FAILED)
    {
        perror("mmap failed at sharedmemory array\n");
        exit(EXIT_FAILURE);
    }

    uint64_t *array = sharedmemory;

    // creating sem array with every element being a sem to check if it is used or not.
    sem_t *sema = mmap(NULL, sizeof(sema) * 2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // 0 == read, 1 == write

    if (sema == MAP_FAILED)
    {
        perror("mmap failed at sema array\n");
        exit(EXIT_FAILURE);
    }

    uint64_t initVals[] = {0, ringbuffer};
    for (int i = 0; i < 2; ++i)
    {
        // creating sem entry for every array element
        if (sem_init(&sema[i], 1, initVals[i]) < 0)
        {
            perror("sem_init failed\n");
            exit(EXIT_FAILURE);
        }
    }

    // after creating shared memory fork 2 times
    pid_t pid = fork();
    DO_OR_DIE(pid, "fork1 failed!\n");

    if (pid == 0)
    {
        // child process 1
        for (int i = 0; i < number; ++i)
        {
            sem_wait(&sema[1]);
            sharedmemory[i%ringbuffer] = i + 1;
            sem_post(&sema[0]);
        }

        munmap(sharedmemory, (ringbuffer + 1) * sizeof(uint64_t));
    }
    else
    {

        pid = fork();
        DO_OR_DIE(pid, "fork2 failed!\n");

        if (pid == 0)
        {
            // child process 2
            for (int i = 0; i < number; ++i)
            {
                sem_wait(&sema[0]);
                sharedmemory[ringbuffer] += sharedmemory[i % ringbuffer];
                sem_post(&sema[1]);
            }

            munmap(sharedmemory, (ringbuffer + 1) * sizeof(uint64_t)); // sets the memory free (mmap)
        }
    }

    // waiting for children
    while ((pid = wait(NULL)) != -1);

    // printing the result
    printf("Result: %ld\n", array[ringbuffer]);

    // cleanup
    munmap(sharedmemory, (ringbuffer + 1) * sizeof(uint64_t));

    for (int i = 0; i < 2; ++i)
    {
        // destroying semaphore
        sem_destroy(&sema[i]);
    }

    return EXIT_SUCCESS;
}

// I did notice that task 1 is much faster then task 2 because task 2 requires to wait for the semaphores and task 1 doesn't use semaphores

/*
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> // for semathore obviously
#include <string.h>
#include <sys/types.h>
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
#include <stdint.h> // for uint64_t
#include <errno.h>
#include <time.h>

#define MAP_ANONYMOUS 0x20

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
        printf("Usage: ./task1 number buffer(number)\n");
        return EXIT_FAILURE;
    }

    char *p;

    errno = 0;
    long number = strtol(argv[1], &p, 10);

    if (errno != 0 || *p != '\0' || number > INT_MAX || number < INT_MIN)
    {
        // error handling
        printf("number fail\n");
        printf("Usage: ./task1 number(number) ringbuffer(number)\n");
        return EXIT_FAILURE;
    }

    long ringbuffer = strtol(argv[2], &p, 10);

    if (errno != 0 || *p != '\0' || ringbuffer > INT_MAX || ringbuffer < INT_MIN)
    {
        // error handling
        printf("ringbuffer fail\n");
        printf("Usage: ./task1 number(number) ringbuffer(number)\n");
        return EXIT_FAILURE;
    }

    if (ringbuffer < 1 || number < 1)
    {
        printf("number must be greater then 0!\n");
        return EXIT_FAILURE;
    }

    // input is correct and we can continue with the shared memory we need of size ringbuffer!
    uint64_t *sharedmemory = mmap(NULL, (ringbuffer + 1) * sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // share memory

    if (sharedmemory == MAP_FAILED)
    {
        perror("mmap failed at sharedmemory array\n");
        exit(EXIT_FAILURE);
    }

    uint64_t *array = sharedmemory;

    // creating bool check array to see if we can read or write
    uint64_t *sharedmemoryCHECK = mmap(NULL, (ringbuffer + 1) * sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // share memory

    if (sharedmemoryCHECK == MAP_FAILED)
    {
        perror("mmap failed at sharedmemoryCHECK array\n");
        exit(EXIT_FAILURE);
    }

    uint64_t *arrayCHECK = sharedmemoryCHECK;

    for (int i = 0; i < ringbuffer; ++i)
    {
        // 0 is for writing
        arrayCHECK[i] = 0;
    }

    // creating sem array with every element being a sem to check if it is used or not.
    sem_t *sema = mmap(NULL, sizeof(sema) * 2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // 0 == read, 1 == write

    if (sema == MAP_FAILED)
    {
        perror("mmap failed at sema array\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; ++i)
    {
        // creating sem entry for every array element
        if (sem_init(&sema[i], 1, 1) < 0)
        {
            perror("sem_init failed\n");
            exit(EXIT_FAILURE);
        }
    }

    // after creating shared memory fork 2 times
    pid_t pid = fork();
    DO_OR_DIE(pid, "fork1 failed!\n");

    if (pid == 0)
    {
        // child process 1
        int temp = number, count = 1;

        while (temp > 0)
        {
            sem_wait(&sema[0]); // reader

            for (int i = 0; i < ringbuffer; ++i)
            {
                if (arrayCHECK[i] == 0)
                {
                    arrayCHECK[i] = 1;
                    array[i] = count;
                    ++count;
                    --temp;
                }
                if (temp <= 0)
                {
                    break;
                }
            }
            sem_post(&sema[0]); // reader
        }

        munmap(sharedmemory, (ringbuffer + 1) * sizeof(uint64_t));
        munmap(sharedmemoryCHECK, (ringbuffer + 1) * sizeof(uint64_t));
    }

    pid = fork();
    DO_OR_DIE(pid, "fork2 failed!\n");

    if (pid == 0)
    {
        // child process 2
        int temp = number;

        while (temp > 0)
        {
            sem_wait(&sema[0]); // reader

            for (int i = 0; i < ringbuffer; ++i)
            {
                if (arrayCHECK[i] == 1)
                {
                    arrayCHECK[i] = 0;
                    array[ringbuffer] += array[i];
                    array[i] = 0;
                    --temp;
                }
                if (temp <= 0)
                {
                    break;
                }
            }

            sem_post(&sema[0]); // reader
        }

        munmap(sharedmemory, (ringbuffer + 1) * sizeof(uint64_t)); // sets the memory free (mmap)
        munmap(sharedmemoryCHECK, (ringbuffer + 1) * sizeof(uint64_t));
    }

    // waiting for children
    while ((pid = wait(NULL)) != -1)
        ;

    // printing the result
    printf("Result: %ld\n", array[ringbuffer]);

    // cleanup
    munmap(sharedmemory, (ringbuffer + 1) * sizeof(uint64_t));

    for (int i = 0; i < 2; ++i)
    {
        // destroying semaphore
        sem_destroy(&sema[i]);
    }

    return EXIT_SUCCESS;
}

*/

// I did notice that task 1 is much faster then task 2 because task 2 requires to wait for the semaphores and task 1 doesn't use semaphores
