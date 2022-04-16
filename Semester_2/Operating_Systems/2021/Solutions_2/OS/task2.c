#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>

#define MAX_ARGS 8
#define MAXpath 255

void parse_args(char* str, char* (*result)[MAX_ARGS]) {
	memset(*result, 0, sizeof(char*) * MAX_ARGS);
	for(int i = 0; i < MAX_ARGS - 1; ++i, str = NULL) {
		(*result)[i] = strtok(str," ");
	}
}

int main(int argc, char *argv[]) {
	
  	
  	
  if(argc != 3) { printf("Arguments!\n"); 
  		return EXIT_FAILURE;}

 	int fd[2];
  	if(pipe(fd) == -1) {
  		fprintf(stderr, "ERROR: Pipe failed");
  	}
	pid_t pid1, pid2;
	char path[MAXpath];
  	char* args1[MAX_ARGS];
  	char* args2[MAX_ARGS];
  	switch( fork()) {
  		case -1: 
  			fprintf(stderr, "ERROR: Fork1 failed");
  			exit(1);
  		case 0: 
  			dup2(fd[1], STDOUT_FILENO);
  			close(fd[0]);
  			parse_args(argv[1], &args1);
  			strcpy(path, args1[0]);
			execvp(path,args1);
  			printf("test\n");
  			_exit(EXIT_SUCCESS);
  		default:
  			break;
  		}
  	switch( fork()) {
  		case -1: 
  			fprintf(stderr, "ERROR: Fork2 failed");
  			exit(1);
  		case 0:
  			dup2(fd[0], STDIN_FILENO);
  			close(fd[1]);
  			parse_args(argv[2], &args2);
  			strcpy(path, args2[0]); 
  			execvp(path,args2);
  			_exit(EXIT_SUCCESS);
  		default:
  			break;
  		}
  		
/*
  	    	if(wait(NULL) == -1) {
  	    		fprintf(stderr, "ERROR: waiting failed");
  	    		return EXIT_FAILURE;
  	    	}
  	    	if(wait(NULL) == -1) {
  	    		fprintf(stderr, "ERROR: waiting failed");
  	    		return EXIT_FAILURE;
  	    	}
  	    	*/
  	   
  		
  	  	
  	return EXIT_SUCCESS;
  }
