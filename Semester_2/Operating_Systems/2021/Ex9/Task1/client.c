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

pthread_t client;
struct sockaddr_in addr, cli;
int sockfd, connfd, len, i;

char buffer[BUF_SIZE];
char *clientname;
void *clientThread(void *arg)
{
    int clientSocket = *(int *)arg;
    //argvname = clientname; 
    if (write(clientSocket, clientname, BUF_SIZE) == -1)
    {
        printf("Send failed\n");
    }    
    while(1){
    fgets(buffer,BUF_SIZE,stdin);
    
    //strcpy(client_message,clientmessage);
    if (write(clientSocket, buffer, BUF_SIZE) == -1)
    {
        printf("Send failed\n");
    }
    if (!strcmp(buffer,"/quit\n")){
            break;
        }
    if (!strcmp(buffer,"/shutdown\n")){
        break;
    }
    memset(buffer, 0, BUF_SIZE);
}
close(sockfd);
return NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Pass 2 arguments through command line.\n");
    }

    memset(&addr, 0, sizeof(struct sockaddr_in));

    clientname = argv[2];

    int port;
    port = atoi(argv[1]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);      // on server
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // on client

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
    {
        if (pthread_create(&client, NULL, clientThread, (void *)&sockfd) != 0)
            perror("Failed to create thread\n");
    }
    if (pthread_join(client, NULL) != 0)
    {
        perror("join failed");
    }
}
