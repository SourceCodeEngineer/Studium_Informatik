#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "You have to give 2 Arguments");
        return EXIT_FAILURE;
    }
    int N = atoi(argv[1]); // input N from command line
    int B = atoi(argv[2]); // input B from command line
    
    uint64_t *sharedmemory = mmap(NULL, (B + 1) * sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //share memory
    
    uint64_t *array = sharedmemory;


    pid_t pid1 = fork();


    
    if (pid1 < 0)
    {
        fprintf(stderr, "fork failed");
        return EXIT_FAILURE;
    }
    else if (pid1 == 0)
    { // first child process


        for (int i = 0; i < N; i++){

            array[i % B] = (i + 1);

        }
        munmap(sharedmemory,(B+1)*sizeof(uint64_t));

    }
    else
    { //parent
        pid_t pid2 = fork();

        if (pid2 < 0)
        {
            fprintf(stderr, "fork failed");
            return EXIT_FAILURE;
        }
        else if (pid2 == 0)
        { // second child process
            
            int result=0;
            for (int i = 0; i < N; i++)
            {
                result += array[i % B];
            }
            array[B + 1] = result;
            munmap(sharedmemory,(B+1)*sizeof(uint64_t)); //sets the memory free (mmap)
        }
        else
        { //parent
            wait(NULL);
            wait(NULL);
            printf("%ld\n", array[B + 1]);

            munmap(sharedmemory,(B+1)*sizeof(uint64_t));
        }
    }
}

/*Is the computed result the expected value?
Its not anytime the same. 
Does the computed value change across different runs?
Yes sometimes. but if u have B bigger than N its always the same output 
What happens when you try different and larger values for N and B, for example 10,000 or 100,000?
when the values are diffrent like B > N it will not change anything but when N is equal or bigger B its a "random" 
value because sometimes its 0 or minus or the wanted value, 
and if u make bigger values its like the same but it has a much more wrong outputs than ones with smaller numbers.*/