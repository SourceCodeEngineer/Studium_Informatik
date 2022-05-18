#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAX 128
#define MAX_CLIENTS 32
#define SA struct sockaddr

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Usage: %s port uname", argv[0]);
		return EXIT_FAILURE;
	}
	
   int clientfd;
   struct sockaddr_in servaddr;
   memset(&servaddr, 0, sizeof(struct sockaddr_in));
   clientfd = socket(AF_INET, SOCK_STREAM, 0);
	char *edp;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(strtol(argv[1], &edp, 10));
    
    connect(clientfd, (struct sockaddr *) &servaddr, sizeof(servaddr)); 
   
   char buff[MAX];
   write(clientfd, argv[2], sizeof(argv[2])); 
   for(;;) {
   printf(">");
   bzero(buff, MAX);
   fgets(buff,MAX,stdin);
   if (strncmp("/quit", buff, 5) == 0) {
       write(clientfd, buff, sizeof(buff)); 
       break;
       } 
   if (strncmp("/shutdown", buff, 9) == 0) {
	 	write(clientfd, buff, sizeof(buff));
       	break;
    	 }
   
    write(clientfd, buff, sizeof(buff));
    
   }
	close(clientfd);
   return EXIT_SUCCESS;
  }

