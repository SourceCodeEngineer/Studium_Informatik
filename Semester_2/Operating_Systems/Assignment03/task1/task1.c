#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

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
    }

    int children = atoi(argv[1]);
    int simulations = atoi(argv[2]);

    int status = 0;

    // forking in a for loop to create N child processes
    for (int i = 0; i < children; ++i){
        pid_t pid = fork();

        if (pid == 0) /* only execute this if child */
        {
            // do something with the command line arguments
            // eg. execlp with argv[i]
            double result = mc_pi(simulations);
            printf("Child %d PID = %d. mc_pi(%d) = %f.", i , getpid(), simulations, result);
            exit(0);
        }
        wait(&status);  /* only the parent waits */
    }
    printf("Done.");

    return EXIT_SUCCESS;
}
