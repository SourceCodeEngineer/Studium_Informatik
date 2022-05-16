#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s PORT\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int port = atoi(argv[1]);

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    //    char *hello = "Hello from server";
    const char *hello = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello world!";
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );

    // Forcefully attaching socket to the port from argv
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        read( new_socket , buffer, 1024);
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("Hello message sent\n");
    }

    return 0;
}
