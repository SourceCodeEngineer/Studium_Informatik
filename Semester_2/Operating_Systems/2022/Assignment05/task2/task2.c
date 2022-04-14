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

#define RINGBUFFER 50


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
    uint64_t *sharedmemory = mmap(NULL, (RINGBUFFER + 1) * sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // share memory

    if (sharedmemory == MAP_FAILED)
    {
        perror("mmap failed at sharedmemory array\n");
        exit(EXIT_FAILURE);
    }

    uint64_t *array = sharedmemory;

    // creating bool check array to see if we can read or write
    uint64_t *sharedmemoryCHECK = mmap(NULL, (RINGBUFFER + 1) * sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // share memory

    if (sharedmemoryCHECK == MAP_FAILED)
    {
        perror("mmap failed at sharedmemory array\n");
        exit(EXIT_FAILURE);
    }

    uint64_t *arrayCHECK = sharedmemoryCHECK;

    for (int i = 0; i < RINGBUFFER; ++i)
    {
        // 0 is for writing
        arrayCHECK[i] = 0;
    }

    // creating sem array with every element being a sem to check if it is used or not.
    sem_t *sema = mmap(NULL, sizeof(sema) * RINGBUFFER, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (sema == MAP_FAILED)
    {
        perror("mmap failed at sema array\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < RINGBUFFER; ++i)
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
        int temp, count = 1;
        
        if (producer > consumer){
            temp = consumer;
        }else{
            temp = producer;
        }

        while (temp > 0)
        {
            for (int i = 0; i < RINGBUFFER; ++i)
            {
                if (arrayCHECK[i] == 2 || arrayCHECK[i] == 0)
                {
                    sem_wait(&sema[i]);
                    array[i] = count;
                    ++count;
                    arrayCHECK[i] = 1;
                    --temp;
                    sem_post(&sema[i]);
                }
            }
        }

        /*for (int i = 0; i < producer; ++i)
        {
            sem_wait(&sema[i]);
            // wrap around in ring buffer (i % buffer)
            array[i % RINGBUFFER] = i + 1;
            sem_post(&sema[i]);
        }*/
        munmap(sharedmemory, (RINGBUFFER + 1) * sizeof(uint64_t));
        munmap(sharedmemoryCHECK, (RINGBUFFER + 1) * sizeof(uint64_t));
    }

    pid = fork();
    DO_OR_DIE(pid, "fork2 failed!\n");

    if (pid == 0)
    {
        // child process 2
        unsigned long long result = 0;

        int temp;
        
        if (producer > consumer){
            temp = consumer;
        }else{
            temp = producer;
        }

        while (temp > 0)
        {
            for (int i = 0; i < RINGBUFFER; ++i)
            {
                if (arrayCHECK[i] == 1)
                {
                    sem_wait(&sema[i]);
                    result += array[i];
                    --temp;
                    arrayCHECK[i] = 0;
                    sem_post(&sema[i]);
                }
            }
        }

        /*for (int i = 0; i < producer; ++i)
        {
            sem_wait(&sema[i]);
            // read from shared memory
            result += array[i];
            sem_post(&sema[i]);
        }*/
        array[RINGBUFFER + 1] = result;
        munmap(sharedmemory, (RINGBUFFER + 1) * sizeof(uint64_t)); // sets the memory free (mmap)
        munmap(sharedmemoryCHECK, (RINGBUFFER + 1) * sizeof(uint64_t));
    }

    // waiting for children
    while ((pid = wait(NULL)) != -1);

    // printing the result
    printf("%ld\n", array[RINGBUFFER + 1]);

    // cleanup
    munmap(sharedmemory, (RINGBUFFER + 1) * sizeof(uint64_t));

    for (int i = 0; i < RINGBUFFER; ++i)
    {
        // creating sem entry for every array element
        sem_destroy(&sema[i]);
    }

    return EXIT_SUCCESS;
}
