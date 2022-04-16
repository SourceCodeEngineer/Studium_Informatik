#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>

#define MAX_ARGS 8
#define SOCKET_NAME "/tmp/socket2client.socket"

int main() {
	
	int client_fd;
	struct sockaddr_un adress;
	char buffer[1024];
	int ret;
	
	if((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}
	
	memset(&adress, 0, sizeof(adress));
	
	adress.sun_family = AF_UNIX;
	strncpy(adress.sun_path, SOCKET_NAME, sizeof(adress.sun_path) - 1);
	ret = connect(client_fd, (const struct sockaddr *) &adress, sizeof(adress));
	if(ret == -1) {
		perror("bind failed\n");
		exit(EXIT_FAILURE);
	}
	
	
	
	while(1) {
   
   	printf("Command: ");
   		fgets(buffer, sizeof(buffer), stdin);
   		
   		if(buffer[0] == '\n'){
   			ret = write(client_fd, "exit", 6);
			if(ret == -1) {
				perror("read failed\n");
				exit(EXIT_FAILURE);
			}
		close(client_fd);
		exit(EXIT_SUCCESS);
   		
   		}
   		
   		buffer[strlen(buffer) - 1] = 0;
   		ret = write(client_fd, buffer, strlen(buffer) + 1);
		if(ret == -1) {
			perror("write failed\n");
			exit(EXIT_FAILURE);
		}
		
		ret = read(client_fd, buffer, sizeof(buffer));
		if(ret == -1) {
			perror("read failed\n");
			exit(EXIT_FAILURE);			
		}
		
		printf("%s\n", buffer);
		
   	} 
   	
   	ret = write(client_fd, "exit", 6);
		if(ret == -1) {
			perror("read failed\n");
			exit(EXIT_FAILURE);
		}
	close(client_fd);
	exit(EXIT_SUCCESS);
   	
	
}
