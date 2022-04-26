// worked together with csaz7804, csaz7620

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

// begin user defines
#define SLEEPER usleep(200000)

#define MESSAGEQLENGTH 10

#define DO_OR_DIE(x, s) \
    do                  \
    {                   \
        if ((x) < 0)    \
        {               \
            perror(s);  \
            exit(1);    \
        }               \
    } while (0)
// end user defines

// global var for SIGINT catch
mqd_t fd;
char buffer2[BUFSIZ];
// end

// begin global structs
struct mq_attr attr = {
    .mq_maxmsg = MESSAGEQLENGTH,
    .mq_msgsize = BUFSIZ,
    .mq_curmsgs = 0, // elements in q
    .mq_flags = 0,
};
// end global structs

// signal handler
void handlerSIGINT()
{
    write(STDOUT_FILENO, "Signal SIGINT received, shutting down\n", 38);
    mq_close(fd);
    unlink(buffer2);
    exit(0);
}
// end signal handler

// begin main function
int main(int argc, char **argv)
{
    // error handling for input
    if (argc != 2)
    {
        printf("Usage ./task3_printer_server NAME\n");
        return EXIT_FAILURE;
    }

    // unlink argv[1]
    unlink(argv[1]);

    // copy argv1 to global
    strcpy(buffer2, argv[1]);

    // creating buffer
    char buffer[BUFSIZ] = "\0";
    char tmp[2] = "";

    // open msq
    fd = mq_open(argv[1], O_CREAT | O_RDONLY, 0660, &attr);

    // error handling for mq
    if (fd == -1)
    {
        printf("failed to open mq");
        mq_close(fd);
        unlink(argv[1]);
        return errno;
    }

    // timehandling of idle time
    struct timespec tm;

    // creating priority of type unsigned int because of reference
    unsigned int priority = 0;

    // timehandling of idle time
    clock_gettime(CLOCK_REALTIME, &tm);
    tm.tv_sec += 30; // set runtime, if idle for 30 sec -> shutdown

    // creating received variable
    ssize_t recieve;

    // loop untill we receive nothing or timeout
    while ((recieve = mq_timedreceive(fd, buffer, sizeof(buffer) + 1, &priority, &tm)) > 0)
    {
        // error handling
        if (recieve == -1)
        {
            printf("receive failed");
            mq_close(fd);
            unlink(argv[1]);
            return errno;
        }

        pid_t pid = fork();
        DO_OR_DIE(pid, "fork failed!\n");

        if (pid == 0)
        {
            // child process

            // sigint catch
            struct sigaction sa;
            sa.sa_handler = &handlerSIGINT;
            sa.sa_flags = SA_RESTART;
            sigaction(SIGINT, &sa, NULL);

            if (buffer[0] != '\0')
            {
                printf("Serving print job with priorityrity %d:\n", priority);

                clock_gettime(CLOCK_REALTIME, &tm);
                tm.tv_sec += 30; // set timer again up to 30 sec, if idle -> shutdown

                for (int i = 0; i < (int)strlen(buffer); ++i)
                {
                    tmp[0] = buffer[i];
                    tmp[1] = '\0';
                    write(STDOUT_FILENO, tmp, 1);
                    SLEEPER; // for printing each char into stdout with x delay
                }
                write(STDOUT_FILENO, "\n", 1);
                exit(0);
            }
        }
        else
        {
            // parent process

            // waiting for child
            waitpid(pid, NULL, 0);
            strcpy(buffer, "\0");
        }
    }

    mq_close(fd);
    unlink(argv[1]);

    return EXIT_SUCCESS;
}
// end main
