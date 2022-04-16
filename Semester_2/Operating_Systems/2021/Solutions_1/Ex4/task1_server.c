#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h> 
#include <signal.h>
#include <poll.h>
#include <string.h>
#include <limits.h>

int TOTAL_CLIENTS = 0;


int main(int argc, char* argv[]){

for(int i = 1; i < argc; i++){
    if(mkfifo(argv[i],0660) == -1){
        if(errno != EEXIST){
            fprintf(stderr,"Fifo failed\n");
        }
    }
}


struct pollfd clients[argc-1];

for(int i =0; i < argc-1 ; i++){
    clients[i].fd = open(argv[i+1],O_RDONLY);
    clients[i].events = POLLIN;
    int comfirm_connection = 0;
    read(clients[i].fd,&comfirm_connection,sizeof(int));
    printf("%s connected\n",argv[i+1]);
    TOTAL_CLIENTS++;
}

while(1){
    char message[PIPE_BUF];
    int pollChecker = poll(clients,argc-1,-1);
    if(pollChecker < 0){
        printf("Polling failed\n");
        return EXIT_FAILURE;
    }
    for(int i = 0; i < argc-1; i++){
        if(clients[i].revents & POLLIN){
        read(clients[i].fd,message,sizeof(message));

        if(strlen(message) == 0){
            printf("%s has disconnected\n",argv[i+1]);
            close(clients[i].fd);
            TOTAL_CLIENTS--;
        }
        else{
            printf("%s : %s\n",argv[i+1], message);
            printf("\n");
        }

        if(TOTAL_CLIENTS == 0){
            execlp("find", "find", ".", "-maxdepth", "1", "-type", "p", "-delete",NULL);
        }
        
    }
    }
    


}
}




