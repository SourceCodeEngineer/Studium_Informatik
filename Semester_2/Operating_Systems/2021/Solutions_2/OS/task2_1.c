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
  	pipe(fd);
	pid_t pid1;
	char path[MAXpath];
  	char* args1[MAX_ARGS];
  	char* args2[MAX_ARGS];
  	if((pid1 = fork()) == 0) {
  		
  		close(fd[1]);
  		dup2(fd[0], STDIN_FILENO);
  		parse_args(argv[2], &args1);
  		strcpy(path, args1[0]);
		if(execvp(path,args1) == -1) {fprintf(stderr, "ERROR: exec failed");}
		close(fd[0]);
		exit(0);
  	}
	else {
  		close(fd[0]);
  		dup2(fd[1], STDOUT_FILENO);
  		parse_args(argv[1], &args2);
 		strcpy(path, args2[0]); 
  		if(execvp(path,args2) == -1) {fprintf(stderr, "ERROR: exec failed");}
  		close(fd[1]);
  		wait(NULL);
  		return EXIT_SUCCESS;
  		}
  	  	
  	return EXIT_SUCCESS;
  }
