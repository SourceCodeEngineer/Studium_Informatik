#include <stdio.h>     // perror, printf
#include <stdlib.h>    // exit, atoi
#include <unistd.h>    // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h>    // memset, strcmp

/* DO NOT TOUCH BELOW!
TELNET SCRIPT
for i in $(seq 1 10); \
        do sleep 1; \
        telnet localhost 1337 & \
done

DO NOT TOUCH ABOVE! */

#define DO_OR_DIE(x, s) \
    do                  \
    {                   \
        if ((x) < 0)    \
        {               \
            perror(s);  \
            exit(1);    \
        }               \
    } while (0)

// server program, client program can be found at my Github Repo
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s PORT\n", argv[0]);
    }

    int client_sock;
    socklen_t client_size;
    int listenfd;

    char buff[BUFSIZ];

    int port = atoi(argv[1]);

    printf("Listening on port %d\n", port);

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

    if (listen(listenfd, 1) < 0)
    {
        printf("Error while listening\n");
        return -1;
    }

    int tmp = 0;

    int accepter = 0;

    client_size = sizeof(client_addr);
    client_sock = accept(listenfd, (struct sockaddr *)&client_addr, &client_size);

    if (client_sock < 0)
    {
        printf("Can't accept\n");
        return -1;
    }

    while (1)
    {
        if (accepter)
        {
            client_size = sizeof(client_addr);
            client_sock = accept(listenfd, (struct sockaddr *)&client_addr, &client_size);

            if (client_sock < 0)
            {
                printf("Can't accept\n");
                return -1;
            }
            --accepter;
        }

        tmp = recv(client_sock, buff, sizeof(buff), 0);

        if (tmp < 0)
        {
            printf("Couldn't receive\n");
            --accepter;
        }

        if (tmp == 0)
        {
            ++accepter;
        }

        if (strcmp(buff, "/shutdown\r\n") == 0)
        {
            printf("Shutting down!\n");
            close(listenfd);
            break;
        }
        else
        {
            printf("Echo: %s", buff);
            memset(buff, '\0', sizeof(buff));
        }
    }

    return EXIT_SUCCESS;
}
