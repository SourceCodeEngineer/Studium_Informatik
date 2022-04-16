#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MAX_ARGS 8
#define SOCKET_NAME "/tmp/socket2client.socket"

void parse_args(char* str, char* (*result)[MAX_ARGS]) {
	memset(*result, 0, sizeof(char*) * MAX_ARGS);
	for(int i = 0; i < MAX_ARGS - 1; ++i, str = NULL) {
		(*result)[i] = strtok(str," ");
	}
}

int main () {

int server_fd, client_fd;
struct sockaddr_un adress;
char buffer[32] = {0};
char* args[MAX_ARGS];
int ret;
unlink(SOCKET_NAME);

	if((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}
	memset(&adress, 0, sizeof(adress));
	
	adress.sun_family = AF_UNIX;
	strncpy(adress.sun_path, SOCKET_NAME, sizeof(adress.sun_path) - 1);
	ret = bind(server_fd, (const struct sockaddr *) &adress, sizeof(adress));
	if(ret == -1) {
		perror("bind failed\n");
		exit(EXIT_FAILURE);
	}
	
	ret = listen(server_fd, 1);
	if(ret == -1) {
		perror("listen failed\n");
		exit(EXIT_FAILURE);
	}
pid_t pid;
	for(;;) {
		client_fd = accept(server_fd, NULL ,NULL);
		if(client_fd == -1) {
			perror("client accept failed\n");
			exit(EXIT_FAILURE);
		}
		
		while(1) {
		
			ret = read(client_fd, buffer, sizeof(buffer));
			if(ret == -1) {
				perror("read failed\n");
				unlink(SOCKET_NAME);
				exit(EXIT_FAILURE);
			}
			if(strcmp(buffer,"exit") == 0) {
			printf("%s\n", buffer);
			close(server_fd);
			unlink(SOCKET_NAME);
			exit(EXIT_SUCCESS);
			}
			
			else{
				if((pid = fork()) == -1) {
					perror("fork failed\n");
					unlink(SOCKET_NAME);
					exit(EXIT_FAILURE);
					} 
				else if(pid == 0) {
				buffer[sizeof(buffer) - 1] = 0;
				parse_args(buffer, &args);
				dup2(client_fd, STDOUT_FILENO);
				execvp(args[0],args);	
				}
				else {
					wait(NULL);
				}
			}
		}
		
	}
	
	
	

}
