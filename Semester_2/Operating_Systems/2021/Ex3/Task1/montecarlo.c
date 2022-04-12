#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdint.h> 
#include <sys/types.h>
#include <sys/wait.h>

double mc_pi(int64_t S) {
    int64_t in_count = 0;
    for(int64_t i = 0; i < S; ++i) {
        const double x = rand() / (double)RAND_MAX; //montecarlo calculation
        const double y = rand() / (double)RAND_MAX;
        if(x*x + y*y <= 1.f) {
            in_count++;
        }
    }
    return 4 * in_count / (double)S;
}

int main(int argc, char* argv[]) {
(void)argc;

int64_t S = atoi(argv[2]); //input from the user -> S for the calculation in the function mc_pi
int n = atoi(argv[1]);//input from the user -> how many forks should be generated


for(int i = 0; i < n;i++){

        pid_t pid = fork();
        srand(getpid()); //randomizes the values of all forks
    if(pid == 0){//child process
   
        printf("Child %d PID = %d. mc_pi(%ld) = %lf.\n",i, getpid(), S, mc_pi(S));
        return 0;   
    }  
    else
        wait(&pid); // parent waits for the execution of all childs.
    }
    printf("Done.\n");
    
}

// the position of the srand is important because it gets first randomized and then it gets split by the forks, 
//if you place it after the usage of fork u "randomize" every value.