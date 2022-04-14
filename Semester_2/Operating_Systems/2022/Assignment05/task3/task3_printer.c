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

#define USAGE   printf("priority fail\n"); \
                printf("Usage: ./task3_printer /YOURNAME PRIORITY(INT) FILE");

int main(int argc, char **argv)
{

    if (argc != 4)
    {
        printf("Usage: ./task3_printer /YOURNAME PRIORITY(INT) FILE");
        return EXIT_FAILURE;
    }

    char *p;

    errno = 0;
    long priority = strtol(argv[1], &p, 10);

    if (errno != 0 || *p != '\0' || priority > INT_MAX || priority < INT_MIN)
    {
        // error handling
        USAGE
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}