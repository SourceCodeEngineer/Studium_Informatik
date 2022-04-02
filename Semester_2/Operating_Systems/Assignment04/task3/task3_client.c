#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
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

   if (argc != 2){
      printf("Usage: ./task3_client NAME");
      return EXIT_FAILURE;
   }

   int client_to_server;
   char *myfifo = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "/tmp/server_to_client_fifo";

   char str[BUFSIZ];

   client_to_server = open(myfifo, O_WRONLY);
   server_to_client = open(myfifo2, O_RDONLY);

   write(client_to_server, argv[1], sizeof(argv[1]));

   while(1){

      printf("Expression:\n");
      scanf("%s", str);

      if (strlen(str) == 0){
         write(client_to_server, argv[1], sizeof(argv[1]));
         write(client_to_server, "disconnect", sizeof("disconnect"));
         break;
      }

      /* write str to the FIFO */
      write(client_to_server, argv[1], sizeof(argv[1]));
      write(client_to_server, str, sizeof(str));
   }

   /* remove the FIFO */
   close(client_to_server);
   close(server_to_client);

   return EXIT_SUCCESS;
}
