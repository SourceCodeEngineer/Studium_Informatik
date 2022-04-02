#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>

#define DO_OR_DIE(x, s) \
   do                   \
   {                    \
      if ((x) < 0)      \
      {                 \
         perror(s);     \
         exit(1);       \
      }                 \
   } while (0)

int main(int argc, char **argv)
{
   if(argc < 2){
      printf("usage: execute the server and give it a parameter of clients (e.g.: ./task3_server euler gaus)!");
      return EXIT_FAILURE;
   }

   int client_to_server;
   char *fifo_location_CtS = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *fifo_location_StC = "/tmp/server_to_client_fifo";

   char buf[BUFSIZ];

   /* create the FIFO (named pipe) */
   mkfifo(fifo_location_CtS, 0777);
   mkfifo(fifo_location_StC, 0777);

   /* open, read, and display the message from the FIFO */
   client_to_server = open(fifo_location_CtS, O_RDONLY);
   server_to_client = open(fifo_location_StC, O_WRONLY);

   printf("Server ON for test results.\n"); // can delete afterwards!

   while (1)
   {
      read(client_to_server, buf, BUFSIZ);

      if (strcmp("exit",buf)==0)
      {
         printf("Server OFF.\n");
         break;
      }

      else if (strcmp("",buf)!=0)
      {
         printf("Received: %s\n", buf);
      }

      /* clean buf from any data */
      memset(buf, 0, sizeof(buf));
   }

   close(client_to_server);
   close(server_to_client);

   unlink(fifo_location_CtS);
   unlink(fifo_location_StC);
   return 0;
}
