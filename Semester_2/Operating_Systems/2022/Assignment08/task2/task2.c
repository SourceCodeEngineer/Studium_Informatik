#include <stdio.h>     // perror, printf
#include <stdlib.h>    // exit, atoi
#include <unistd.h>    // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h>    // memset


// server program, client program can be found at my Github Repo
int main(int argc, char const *argv[])
{

    

    int serverFd, clientFd;
    struct sockaddr_in server, client;
    socklen_t len;

    // default port if no port is given to listen on!
    int port = 1337;

    // buffer 
    char buffer[BUFSIZ];

    if (argc == 2)
    {
        port = atoi(argv[1]);
    }

    serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if (serverFd < 0)
    {
        perror("Cannot create socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    len = sizeof(server);

    if (bind(serverFd, (struct sockaddr *)&server, len) < 0)
    {
        perror("Cannot bind socket");
        exit(2);
    }

    if (listen(serverFd, 10) < 0)
    {
        perror("Listen error");
        exit(3);
    } else {
        printf("Listening on port %d.\n", port);
    }
    
    while (1)
    {
        len = sizeof(client);

        if ((clientFd = accept(serverFd, (struct sockaddr *)&client, &len)) < 0)
        {
            perror("accept error");
            exit(4);
        }

        memset(buffer, 0, sizeof(buffer));

        int size = read(clientFd, buffer, sizeof(buffer));

        if (size < 0)
        {
            perror("read error");
            exit(5);
        }

        if (strcmp(buffer, "/shutdown")){
            printf("Shutting down\n");
            close(clientFd);
            break;
        } else {
            printf("Echo: %s\n", buffer);
        }
        
    }

    close(serverFd);

    return EXIT_SUCCESS;
}
