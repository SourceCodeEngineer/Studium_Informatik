#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <malloc.h>
#include <stdlib.h>

#define PIPE_BUF 200

int main(int argc, char *argv[]) {
if(argc == 2) {
   int c2s;
   char cfifo[20] = "/tmp/";
   strcat(cfifo, argv[1]);

   c2s = open(cfifo, O_WRONLY);
   char str[PIPE_BUF];
   
   do {
   
   printf("Message: ");
   
   if (fgets(str,200,stdin)) {
   	write(c2s, str, sizeof(str));
   }
   } while(getchar() != '\n');
   close(c2s);

   return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
  
}

