#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

double mc_pi(int64_t S) {
    int64_t in_count = 0;
    for(int64_t i = 0; i < S; ++i) {
        const double x = rand() / (double)RAND_MAX;
        const double y = rand() / (double)RAND_MAX;
        if(x*x + y*y <= 1.f) {
            in_count++;
        }
    }
    return 4 * in_count / (double)S;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: Number of child processes (N), Number of simulations (S)");
        return EXIT_FAILURE;
    }

    int children = atoi(argv[1]);
    int simulations = atoi(argv[2]);

    if(children == 0 || simulations == 0) return EXIT_FAILURE;

    int status = 0;

    // forking in a for loop to create N child processes
    for (int i = 0; i < children; ++i){
        pid_t pid = fork();
        if(pid < 0) return EXIT_FAILURE;
        srand(getpid());
        if (pid == 0)
        {            
            double result = mc_pi(simulations);
            printf("Child %d PID = %d. mc_pi(%d) = %.6f\n", i , getpid(), simulations, result);
            exit(0);
        }
    }

    for(int i=0; i < children; ++i) {// loop will run n times to wait for the child processes
        wait(&status);
    }

    printf("Done.\n");

    return EXIT_SUCCESS;
}
