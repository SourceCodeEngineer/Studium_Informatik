#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 128
#define LISTEN_BACKLOG 32

pthread_t listener;
pthread_t clients[32];
struct sockaddr_in addr, cli;
int sockfd, connfd, i, counter;
socklen_t len;
char buffer[BUF_SIZE];
char client_message[BUF_SIZE];
int listenerSocket;

void *clientThread(void *arg)
{
    int clientSocket = *((int *)arg);
    i++;
    counter++;
    char name[BUF_SIZE];
    if (recv(clientSocket, name, BUF_SIZE, 0) < 0)
    {
        perror("recv1 failed");
    }
    else
    {
        printf("%s connected.\n", name);
    }
    while (1)
    {

        if (recv(clientSocket, buffer, BUF_SIZE, 0) < 0)
        {
            perror("recv2 failed");
        }
        if (!strcmp(buffer, "/quit\n"))
        {
            printf("%s disconnected.\n", name);
            counter--;
            break;
        }
        if (!strcmp(buffer, "/shutdown\n"))
        {
            counter--;
            printf("%s disconnected.\n", name);
            printf("Server is shutting down. Waiting for %d client/s to disconnect.\n", counter);
            close(listenerSocket);
            break;
        }
        printf("%s: %s\n", name, buffer);
        memset(buffer, 0, BUF_SIZE);
    }
    if(counter == 0){
        pthread_cancel(listener);
    }

    close(clientSocket);
    return NULL;
}

void *listenerThread(void *arg)
{
    listenerSocket = *((int *)arg);

    while (1)
    {

        len = sizeof(cli);

        connfd = accept(listenerSocket, (struct sockaddr *)&cli, &len);
        if (connfd < 0)
        {
            printf("server acccept failed...\n");
            exit(0);
        }
        else
        {
            if (pthread_create(&clients[i], NULL, clientThread, (void *)&connfd) != 0)
                printf("Failed to create thread\n");
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("No argument passed through command line.\n");
    }

    int port;
    port = atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    bzero(&addr, sizeof(addr));

    memset(&addr, 0, sizeof(struct sockaddr_in));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // on server
    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // on client

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
        perror("socket failed...\n");
        exit(0);
    }
    if ((listen(sockfd, LISTEN_BACKLOG)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Listening on port %d.\n", port);
        if (pthread_create(&listener, NULL, listenerThread, (void *)&sockfd) != 0)
            printf("Failed to create thread\n");
    }
    sleep(2);
    for (i = 0; i < counter; i++)
    {
        if (pthread_join(clients[i], NULL) != 0)
        {
            perror("join failed");
            exit(0);
        }
    }

    if (pthread_join(listener, NULL) != 0)
    {
        perror("join failed");
        exit(0);
    }
    close(sockfd);
    close(connfd);
}