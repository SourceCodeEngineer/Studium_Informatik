// worked in a colaboration with --

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

// start global variables
int my_global = 1;
// end global variables

#define DO_OR_DIE(x, s) \
    do                  \
    {                   \
        if ((x) < 0)    \
        {               \
            perror(s);  \
            exit(1);    \
        }               \
    } while (0)

// function for pthread_create
void *myThreadFun()
{
    ++my_global;
    return NULL;
}

int main(void)
{
    printf("%d\n", my_global);

    pid_t pid = fork();
    DO_OR_DIE(pid, "fork failed!");

    if (pid == 0)
    {
        // child process
        ++my_global;
        exit(1);
    }

    // parent
    // waiting for child
    while ((pid = wait(NULL)) != -1);

    printf("%d\n", my_global);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);

    printf("%d\n", my_global);
    return EXIT_SUCCESS;
}

// we do get the following sequence "1 \n 0 \0 1\n" because the child is a separat process!
