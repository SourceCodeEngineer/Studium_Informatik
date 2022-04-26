// worked together with csaz7804, csaz7620

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <mqueue.h>
#include <errno.h>

// begin user defines
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

// begin main
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Usage ./task3_printer /abba 127 \"$(< test.txt)\"\n");
        return EXIT_FAILURE;
    }

    unsigned int priority = atoi(argv[2]);
    unlink(argv[1]);

    struct mq_attr attr = {
        .mq_maxmsg = MESSAGEQLENGTH,
        .mq_msgsize = BUFSIZ,
        .mq_curmsgs = 0, // elements in q
        .mq_flags = 0,

    };

    char buffer[BUFSIZ];

    mqd_t fd = mq_open(argv[1], O_CREAT | O_WRONLY, 0660, &attr);

    if (fd == -1)
    {
        printf("failed to mq\n");
        mq_close(fd);
        unlink(argv[1]);
        return errno;
    }

    strcpy(buffer, argv[3]);

    int send = mq_send(fd, buffer, strlen(buffer), priority);

    if (send == -1)
    {
        printf("failed to send mq\n");
        mq_close(fd);
        unlink(argv[1]);
        return errno;
    }

    mq_close(fd);
    unlink(argv[1]);

    return EXIT_SUCCESS;
}
// end main
