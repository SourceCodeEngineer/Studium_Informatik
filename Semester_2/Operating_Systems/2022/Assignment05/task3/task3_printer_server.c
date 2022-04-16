#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <errno.h>
#include <time.h>

#define SLEEPER usleep(200000)

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        return EXIT_FAILURE;
    }

    unlink(argv[1]);
    struct mq_attr attr = {
        .mq_maxmsg = 10,
        .mq_msgsize = BUFSIZ,
        .mq_curmsgs = 0,
        .mq_flags = 0,

    };
    char buffer[BUFSIZ] = "\0";
    char temp[BUFSIZ] = "0";

    mqd_t fd = mq_open(argv[1], O_CREAT | O_RDONLY, 0660, &attr);

    struct timespec tm;
    int prio = 0;

    clock_gettime(CLOCK_REALTIME, &tm);
    tm.tv_sec += 20; // Set for 20 seconds
    if (fd == -1)
    {
        mq_close(fd);
        unlink(argv[1]);
        return errno;
    }
    ssize_t recieve;
    while (0 < (recieve = mq_timedreceive(fd, buffer, sizeof(buffer) + 1, &prio, &tm)))
    {
        if (recieve == -1)
        {
            mq_close(fd);
            unlink(argv[1]);
            return errno;
        }
        pid_t pid = fork();
        if (pid == 0)
        {
            if (buffer[0] != '\0')
            {
                printf("Serving print job with priority %d:\n", prio);
                for (int i = 0; i < strlen(buffer); i++)
                {
                    temp[0] = buffer[i];
                    temp[1] = ' ';
                    write(STDOUT_FILENO, temp, 1);
                    SLEEPER;
                }

                exit(0);
            }
        }
        else
        {
            waitpid(pid, NULL, 0);
            printf("\n");
            strcpy(buffer, "0");
        }
    }

    mq_close(fd);
    unlink(argv[1]);
    return EXIT_SUCCESS;
}
