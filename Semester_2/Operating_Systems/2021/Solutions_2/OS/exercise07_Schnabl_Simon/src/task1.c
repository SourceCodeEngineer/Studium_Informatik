#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>


int my_global = 1;

void *t_inc(void *vargp) {
	++my_global;
	return NULL;
}

int main() {

	pid_t pid;
	pthread_t tid;
	
	printf("Pre-Fork: %d\n", my_global);
	
	if((pid = fork()) == -1) {
		perror("fork failed");
		return EXIT_FAILURE;
	}
	else if(pid == 0) {
		my_global += 1;
	}
	else {
		wait(NULL);
		printf("Post-Fork: %d\n", my_global);
	
		pthread_create(&tid, NULL, t_inc, NULL);	
		pthread_join(tid, NULL);
	
		printf("Post-Thread: %d\n", my_global);
	
		return EXIT_SUCCESS;
}
}
