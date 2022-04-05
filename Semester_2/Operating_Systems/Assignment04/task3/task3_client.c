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

   // checking if user did correct input
   if (argc != 2)
   {
      printf("Usage: ./task3_client NAME\n");
      return EXIT_FAILURE;
   }

   // opening fd in read only mode
   const int fd = open(argv[1], O_WRONLY);

   // error handling
   DO_OR_DIE(fd, "failed to create file descriptor");

   // creating bufferer with BUFSIZE
   char buffer[BUFSIZ] = {0};

   // creating endless loop
   while (1)
   {
      // reading from stdin to buffer
      fgets(buffer, BUFSIZ, stdin);

      // if the input is emty then break the loop and return success
      if (buffer[0] == '\n')
         break;

      // else input must be not empty so we write in the file descriptor
      write(fd, buffer, strlen(buffer));
   }

   // if everything got done correctly, SUCCESS
   return EXIT_SUCCESS;
}
