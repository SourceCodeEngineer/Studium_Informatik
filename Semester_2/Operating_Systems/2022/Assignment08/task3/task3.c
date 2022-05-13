#include <stdio.h>     // perror, printf
#include <stdlib.h>    // exit, atoi
#include <unistd.h>    // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h>    // memset, strcmp

int main(int argc, char **argv){
    if (argc != 2)
    {
        printf("Usage: %s PORT\n", argv[0]);
    }

    int port = atoi(argv[1]);
    
    return EXIT_SUCCESS;
}