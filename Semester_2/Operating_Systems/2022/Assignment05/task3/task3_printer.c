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

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        return EXIT_FAILURE;
    }

    int prio = atoi(argv[2]);
    unlink(argv[1]);
    struct mq_attr attr = {
        .mq_maxmsg = 10,
        .mq_msgsize = 256,
        .mq_curmsgs = 0,
        .mq_flags = 0,

    };
    char buffer[BUFSIZ];

    mqd_t fd = mq_open(argv[1], O_CREAT | O_WRONLY, 0660, &attr);
    if (fd == -1)
    {
        mq_close(fd);
        unlink(argv[1]);
        return errno;
    }
    
  
        read(STDIN_FILENO, buffer, sizeof(buffer));
        int send = mq_send(fd, buffer, strlen(buffer), prio);
        if (send == -1)
        {
            mq_close(fd);
            unlink(argv[1]);
            return errno;
        }
       
    

    mq_close(fd);
    unlink(argv[1]);

    return EXIT_SUCCESS;
}
