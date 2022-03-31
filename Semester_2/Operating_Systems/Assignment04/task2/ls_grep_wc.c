#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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

int main(void)
{

   // creating pipes
   int fd1[2], fd2[2], ret;
   pid_t pid = 0;

   ret = pipe(fd1);
   DO_OR_DIE(ret, "pipe failed");
   ret = pipe(fd2);
   DO_OR_DIE(ret, "pipe failed");

   pid = fork();
   DO_OR_DIE(pid, "fork failed");

   if (pid == 0)
   {  
      // child process 1

      //closing fd
      close(fd1[0]);
      // duping fd1 to 1
      dup2(fd1[1], 1);
      //closing fd1
      close(fd1[1]);

      //executing command that gets piped to the parent process
      execlp("ls", "ls", NULL);

      //If we reach here, we have a problem
      return EXIT_FAILURE;
   }

   pid = fork();
   if (pid == 0)
   { 
      //child process 2

      // closing pipe
      close(fd1[1]);
      // duping pipe
      dup2(fd1[0], 0);
      // closing pipe
      close(fd1[0]);

      //closing second pipe
      close(fd2[0]);
      // duping second pipe
      dup2(fd2[1], 1);
      // closing second pipe
      close(fd2[1]);

      // executing command
      execlp("grep", "grep", "-v", "lab", NULL);

      //If we reach here, we have a problem
      return EXIT_FAILURE;
   }

   // forking again
   pid = fork();
   DO_OR_DIE(pid, "fork error");

   if (pid == 0)
   {
      // child process 3

      // closing pipe 1 and 2
      close(fd1[0]);
      close(fd1[1]);
      close(fd2[1]);
      // duping pipe 2 
      dup2(fd2[0], 0);
      // closing pipe 2
      close(fd2[0]);

      // executing command
      execlp("wc", "wc", "-l", NULL);

      //If we reach here, we have a problem
      return EXIT_FAILURE;
   }

   // closing all pipes
   close(fd1[0]);
   close(fd1[1]);
   close(fd2[0]);
   close(fd2[1]);

   // waiting for childs
   while ((pid = wait(NULL)) != -1);

   return EXIT_SUCCESS;
}
