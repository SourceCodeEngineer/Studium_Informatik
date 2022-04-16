#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdatomic.h> //module load gcc/9.2.0

#define BUF_SIZE 128
#define LISTEN_BACKLOG 32

int sockfd;
char buffer[BUF_SIZE];
pthread_t readerThread;
pthread_t writerThread;
atomic_int destroy = 0;

void* writer(){
    while(1) {
        printf("\n> ");
        fgets(buffer, sizeof(buffer), stdin);

        if(write(sockfd, buffer, BUF_SIZE) == -1)
        {
            perror("write failed\n");
            return NULL;
        }

        if((strcmp(buffer, "/quit\n") == 0) || strcmp(buffer, "/shutdown\n") == 0)
        {
            destroy = 1;
            
            break;

        }
    }
    pthread_cancel(readerThread);
    return NULL;
}

void* reader() 
{
    while(1)
    {
        if(read(sockfd, buffer, BUF_SIZE) == -1)
        {
            perror("read failed\n");
            return NULL;
        }
        if(!destroy)
        {
            printf("%s\n", buffer);
        }
    }
    return NULL;
}



int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Pass 2 arguments through command line.\n");
    }

    struct sockaddr_in addr;
    int port;
    port = atoi(argv[1]);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            perror("socket failed!\n");
        }

    memset(&addr, 0, sizeof(struct sockaddr_in));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // on client

    char *clientname = argv[2];

    

    if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
        perror("connection with the server failed...\n");
        return EXIT_FAILURE;
    }
    if (write(sockfd, clientname, BUF_SIZE) == -1)
    {
        perror("write failed\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&writerThread, NULL, writer, (void *)clientname) != 0)
    {
        perror("Failed to create thread\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&readerThread, NULL, reader, NULL) != 0)
    {
        perror("Failed to create thread\n");
    }

    if (pthread_join(writerThread, NULL) != 0)
    {
        perror("join failed");
        return EXIT_FAILURE;
    }
    if (pthread_join(readerThread, NULL) != 0)
    {
        perror("join failed");
        return EXIT_FAILURE;
    }
    close(sockfd);

    return EXIT_SUCCESS;
}
