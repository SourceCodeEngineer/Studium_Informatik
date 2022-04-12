#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/wait.h>

#define DO_OR_DIE(x, s) \
   do                   \
   {                    \
      if ((x) < 0)      \
      {                 \
         perror(s);     \
         exit(1);       \
      }                 \
   } while (0)

#define SHMSIZE 101

int main(int argc, char* argv[]){

    if (argc != 3) {
        printf("Usage: ./task1 PARAMETER1 PARAMETER2!\n");
        return EXIT_FAILURE;
    }

    // creating shared memory
    int shmid;
    key_t key = 1337;
    char* shm;

    shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);

    DO_OR_DIE(shmid, "memory create failure!\n");

    shm = shmat(shmid, NULL, 0);

    if (shm == (char *) -1){
        perror("shmat error!\n");
        exit(1);
    }

    // todo: fork, create loops to write and then finish task

    return EXIT_SUCCESS;
}