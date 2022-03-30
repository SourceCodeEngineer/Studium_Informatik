#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{

   int fd1[2]; // Used to store two ends of first pipe
   int fd2[2]; // Used to store two ends of second pipe

   pid_t p;

   if (pipe(fd1) == -1) // check if pipe failed
   {
      fprintf(stderr, "Pipe Failed");
      return 1;
   }
   if (pipe(fd2) == -1) // check if pipe failed
   {
      fprintf(stderr, "Pipe Failed");
      return 1;
   }

   p = fork(); // Now forking to create a child

   if (p < 0) // Check if fork failed
   {
      fprintf(stderr, "fork Failed");
      return 1;
   }
   // Parent process
   else if (p > 0)
   {
      char concat_str[100];

      close(fd1[0]); // Close reading end of first pipe

      // Wait for child to send a string
      wait(NULL);

      close(fd2[1]); // Close writing end of second pipe

      // Read string from child, print it and close
      // reading end.
      read(fd2[0], concat_str, 100);
      close(fd2[0]);
   }
   // Child process
   else
   {
      close(fd1[1]); // Close writing end of first pipe

      // Read a string using first pipe
      
      read(fd1[0], "", 100);
      
      // Close both reading ends
      close(fd1[0]);
      close(fd2[0]);

      // Write concatenated string and close writing end
      write(fd2[1], "", strlen("") + 1);
      close(fd2[1]);

      exit(0);
   }

   return EXIT_SUCCESS;
}