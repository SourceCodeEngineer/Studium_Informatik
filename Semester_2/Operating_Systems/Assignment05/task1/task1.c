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

#define SHM_ID "/mmap-test"
#define BUFFER_SIZE 4096
#define SLEEP_NANOS 1000   // 1 micro

/*
 * pvtmMmapAlloc - creates a memory mapped file area.
 * The return value is a page-aligned memory value, or NULL if there is a failure.
 * Here's the list of arguments:
 * @mmapFileName - the name of the memory mapped file
 * @size - the size of the memory mapped file (should be a multiple of the system page for best performance)
 * @create - determines whether or not the area should be created.
 */
/*
void *pvtmMmapAlloc(char *mmapFileName, size_t size, char create)
{
    void *retv = NULL;
    if (create)
    {
        mode_t origMask = umask(0);
        int mmapFd = open(mmapFileName, O_CREAT | O_RDWR, 00666);
        umask(origMask);
        if (mmapFd < 0)
        {
            perror("open mmapFd failed");
            return NULL;
        }
        if ((ftruncate(mmapFd, size) == 0))
        {
            int result = lseek(mmapFd, size - 1, SEEK_SET);
            if (result == -1)
            {
                perror("lseek mmapFd failed");
                close(mmapFd);
                return NULL;
            }

             * Something needs to be written at the end of the file to
             * have the file actually have the new size.
             * Just writing an empty string at the current file position will do.
             * Note:
             *  - The current position in the file is at the end of the stretched
             *    file due to the call to lseek().
             *  - The current position in the file is at the end of the stretched
             *    file due to the call to lseek().
             *  - An empty string is actually a single '\0' character, so a zero-byte
             *    will be written at the last byte of the file.
             *
            result = write(mmapFd, "", 1);
            if (result != 1)
            {
                perror("write mmapFd failed");
                close(mmapFd);
                return NULL;
            }
            retv = mmap(NULL, size,
                        PROT_READ | PROT_WRITE, MAP_SHARED, mmapFd, 0);

            if (retv == MAP_FAILED || retv == NULL)
            {
                perror("mmap");
                close(mmapFd);
                return NULL;
            }
        }
    }
    else
    {
        int mmapFd = open(mmapFileName, O_RDWR, 00666);
        if (mmapFd < 0)
        {
            return NULL;
        }
        int result = lseek(mmapFd, 0, SEEK_END);
        if (result == -1)
        {
            perror("lseek mmapFd failed");
            close(mmapFd);
            return NULL;
        }
        if (result == 0)
        {
            perror("The file has 0 bytes");
            close(mmapFd);
            return NULL;
        }
        retv = mmap(NULL, size,
                    PROT_READ | PROT_WRITE, MAP_SHARED, mmapFd, 0);

        if (retv == MAP_FAILED || retv == NULL)
        {
            perror("mmap");
            close(mmapFd);
            return NULL;
        }

        close(mmapFd);
    }
    return retv;
}
*/

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