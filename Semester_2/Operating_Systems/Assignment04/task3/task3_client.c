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
      printf("Usage: ./task3_client NAME\n");
      return EXIT_FAILURE;
   }

   // opening fd in read only mode
   const int fd = open(argv[1], O_WRONLY);

   DO_OR_DIE(fd, "failed to create file descriptor");

   // creating buffer with BUFSIZE
   char buff[BUFSIZ] = {0};

   // creating endless loop

   while (1)
   {
      fgets(buff, BUFSIZ, stdin);

      // if the input is emty then break the loop and return success
      if (buff[0] == '\n')
         break;

      // else input must be not empty so we write in the file descriptor
      write(fd, buff, strlen(buff));
   }

   return EXIT_SUCCESS;
}
