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

#define MAX 256
#define MAX_CLIENTS 32
#define SA struct sockaddr

pthread_t readThread;
pthread_t writeThread;

void *readFunc(void *x) {
	int ret;
     char buff[MAX];
     int clientfd = *(int*) x;
   while((ret = recv(clientfd, buff, MAX, 0)) > 0) {
   		printf("\b%s\n>", buff);
   		fflush(stdout);
   		memset(buff, '\0', MAX*sizeof(buff[0]));
   		}
   		return NULL;
}

void *writeFunc(void *x) {
	int clientfd = *(int*) x;
	for(;;) {
   printf(">");
   char buff[MAX];
   bzero(buff, MAX);
   fgets(buff,MAX,stdin);
   if (strncmp("/quit", buff, 5) == 0) {
       write(clientfd, buff, sizeof(buff)); 
       pthread_cancel(readThread);
       break;
       } 
   if (strncmp("/shutdown", buff, 9) == 0) {
	 	write(clientfd, buff, sizeof(buff));
	 	pthread_cancel(readThread);
       	break;
    	 }
    write(clientfd, buff, sizeof(buff));
   }
	return NULL;
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Usage: %s port uname", argv[0]);
		return EXIT_FAILURE;
	}

   struct sockaddr_in servaddr;
   memset(&servaddr, 0, sizeof(struct sockaddr_in));

	int clientfd;
   clientfd = socket(AF_INET, SOCK_STREAM, 0);
	char *edp;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(strtol(argv[1], &edp, 10));
    
    connect(clientfd, (struct sockaddr *) &servaddr, sizeof(servaddr)); 

   write(clientfd, argv[2], sizeof(argv[2]));
   pthread_create(&readThread, NULL, &readFunc, &clientfd);
   pthread_create(&writeThread, NULL, &writeFunc, &clientfd);
   
   int ret = 0;
   ret = pthread_join(readThread, NULL);
	if(ret != 0) {
		perror("join failed");
		return EXIT_FAILURE;
	}
	ret = pthread_join(writeThread, NULL);
	if(ret != 0) {
		perror("join failed");
		return EXIT_FAILURE;
	}
   
	close(clientfd);
   return EXIT_SUCCESS;
}
