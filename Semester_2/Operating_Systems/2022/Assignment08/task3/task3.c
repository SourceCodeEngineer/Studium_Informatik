#include <stdio.h>     // perror, printf
#include <stdlib.h>    // exit, atoi
#include <unistd.h>    // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h>    // memset, strcmp
#include <pthread.h>

#define THREADS 2

void *listener(void *buffer)
{
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s PORT\n", argv[0]);
    }

    int port = atoi(argv[1]);

    int client_sock;

    socklen_t client_size;

    int listenfd;

    char buff[BUFSIZ];

    struct sockaddr_in serveraddr, client_addr;
    memset(&serveraddr, 0, sizeof(struct sockaddr_in));

    memset(buff, '\0', sizeof(buff));

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    DO_OR_DIE(listenfd, "FD LISTEN FAILED");

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Couldn't bind to the port\n");
        return -1;
    }

    pthread_t con[THREADS];

    if (pthread_create(&con[0], NULL, listener, NULL) != 0)
    {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }

    if (pthread_join(con[0], NULL) != 0)
    {
        perror("Failed to join thread");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
