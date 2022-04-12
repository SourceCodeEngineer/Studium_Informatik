#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

int my_global = 1;

void *execute()
{

    my_global++;
    return 0;
}

int main(void)
{

    pid_t pid1;
    pthread_t thread;

    printf("First Output: %d \n", my_global);

    pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork failed!\n");
        return EXIT_FAILURE;
    }
    else if (pid1 == 0)
    {
        my_global++;
        return 0;
    }
    else
    {
        wait(NULL);
    }

    printf("Second Output: %d \n", my_global);

    if (pthread_create(&thread, NULL, &execute, NULL) != 0)
    {
        perror("Failed to create Thread!\n");
    }

    if (pthread_join(thread, NULL) != 0)
    {
        perror("Failed to wait!\n");
    }

    printf("Third Output: %d\n", my_global);
}