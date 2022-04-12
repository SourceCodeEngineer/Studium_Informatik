#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>




static void sig_handler(){
    printf("Received SIGINT. Exiting.\n");
    exit(0);
}

int main(void) {

    struct sigaction psa;
    pid_t pid;
    sigset_t set;

    psa.sa_flags = SA_SIGINFO;
    psa.sa_sigaction = sig_handler;

    sigemptyset (&set);
    sigaddset(&set , SIGINT);

    sigaction(SIGINT, &psa, NULL);
    sigprocmask(SIG_BLOCK, &set, NULL);
    
    while(1){

    if ((pid = fork()) < 0){
        perror("Fork FAILED!!");
        abort();
    }
    else if(pid == 0){
        printf("Child %d started.\n",getpid());
            sleep(2);
        printf("Child %d done.\n", getpid());
            exit(0);
    }
    else {
        while(wait(NULL) > 0);
        sigprocmask(SIG_UNBLOCK, &set, NULL);
        printf("Did not receive SIGINT. Continuing.\n");
        sigprocmask(SIG_BLOCK, &set,NULL);
        }
    }
    return 0;
}