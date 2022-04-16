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
#include <limits.h>
#include <string.h>

int RUNNING = 1;


int main(int argc , char* argv[]){
    if(argc != 2){
        fprintf(stderr,"Please enter a name for you client\n");
        return EXIT_FAILURE;
    }

   int fd =  open(argv[1],O_WRONLY);
   int confirm = 1;
   write(fd,&confirm,sizeof(int));


   while(RUNNING == 1){
       char message[PIPE_BUF];
       printf("Message:..\n");
       fgets(message,PIPE_BUF,stdin);
       int length = strlen(message);
       if( length == 1){
           message[strlen(message)-1] = '\0';
           write(fd,message,sizeof(message));
           close(fd);
           RUNNING = 0;
       }
       else{
            message[strlen(message)-1] = '\0';
            write(fd,message,sizeof(message));
       }
      
   }


}