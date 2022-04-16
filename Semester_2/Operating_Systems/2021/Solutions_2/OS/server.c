#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <malloc.h>
#include <stdlib.h>

#define PIPE_BUF 200

int main (int argc, char *argv[]) {
if(argc != 1) {

	char locations[argc-1][20];
	int cclients = argc - 1;
	
	
	
	for(int i = 1; i < argc; i++) {
		char temp[20] = "/tmp/";
		strcat(temp, argv[i]); 
		strcpy(locations[i],temp);
	}
	
	for(int i = 1; i < argc; i++) {
		unlink(locations[i]);
	}
	
	for(int i = 1; i < argc; i++) {
	
    	if(mkfifo(locations[i], 0666) != 0) {
    		fprintf(stderr, "ERROR: FIFO failed for %s\n", argv[i]);
    		return EXIT_FAILURE;
    	}
    	
	}
	
	int fds_arr[argc-1];
	for(int i = 0; i < argc - 1; i++) {
		char temp[20] = "/tmp/";
		strcat(temp, argv[i+1]); 
		strcpy(locations[i],temp);
		printf("%s\n", locations[i]);
		const char* client = argv[i+1];
		if((fds_arr[i] = open(locations[i], O_RDONLY)) == -1) {
			fprintf(stderr, "ERROR: Couldn't open pipe for %s @:%s\n", client, locations[i]);
			return EXIT_FAILURE;
		}
    	else {
    		printf("%s connected\n", client);
    		cclients++;
    	}
	}
	
	
	char buf[PIPE_BUF];
	
    struct pollfd polls[argc-1];
    for(int i = 0; i < argc - 1; i++) {
	polls[i].fd = fds_arr[i];
    polls[i].events = POLLIN;
    }
    
    printf("Server ON.\n");
	
    while (cclients > 0) {
    	if (poll(polls, argc, 100) == -1) {
   			fprintf(stderr, "ERROR: polling failed\n");
   		}
    	for(int i = 0; i < argc - 1; i++) {
			const char* client = argv[i];
			if(polls[i].revents & POLLIN) {
				read(fds_arr[i], buf, PIPE_BUF);
				printf("%s: %s\n", client,buf);
			}
			if(polls[i].revents & POLLHUP) {
				printf("%s: disconnected\n", client);
				close(polls[i].fd);
				remove(locations[i]);
				polls[i].fd *= -1;
				cclients--;
			}
			
    	}
    
    }
	printf("All clients disconnected\n");
    return 0;
  }

}


