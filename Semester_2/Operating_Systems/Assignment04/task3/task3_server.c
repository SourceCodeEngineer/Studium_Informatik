#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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
   char *myfifo = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "/tmp/server_to_client_fifo";

   char buf[BUFSIZ];

   /* create the FIFO (named pipe) */
   mkfifo(myfifo, 0666);
   mkfifo(myfifo2, 0666);

   /* open, read, and display the message from the FIFO */
   client_to_server = open(myfifo, O_RDONLY);
   server_to_client = open(myfifo2, O_WRONLY);

   printf("Server ON.\n");

   // execute client file with parameter argv[i]
   // write out message that client x has connected.

   

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
         printf("Sending back...\n");
         write(server_to_client,buf,BUFSIZ);
      }

      /* clean buf from any data */
      memset(buf, 0, sizeof(buf));
   }

   close(client_to_server);
   close(server_to_client);

   unlink(myfifo);
   unlink(myfifo2);
   return 0;
}
