#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

struct sigaction psa;

static void pSigHandler(int signo){
    switch(signo){
        case SIGCHLD:
            printf("Parent done.\n");
            exit(0);
    }
}

int main(int argc, char* argv[]) {
    (void)argc;
    
    memset(&psa, 0, sizeof(psa));
    psa.sa_handler = pSigHandler;
    sigaction(SIGCHLD, &psa, NULL);

int T = atoi(argv[1]);
pid_t pid = fork();
    if (pid == 0){
        
        printf("Child %d sleeping for %d seconds...\n",getpid(), T);
        sleep(T);
        printf("Child done.\n");
    }
    else {
        while(1);
        sigaction(SIGCHLD, &psa, NULL);  
    }
}