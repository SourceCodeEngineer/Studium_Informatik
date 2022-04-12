// Execute ls | wc -l 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/wait.h>

// creating pipe function 
static void xpipe(int *fd)
{
   // checking if pipe is created successfully
   if (pipe(fd) == -1)
   {
      err(1, "pipe failed");
   }
}

// creating a dup2 function
static void xdup2(int a, int b)
{
   // dup2ing the values a and b and check if they got created without error
   if (dup2(a, b) == -1)
   {
      err(1, "dup2 failed");
   }
}

// closing file descriptor function
static void xclose(int fd)
{
   // checking for error
   if (close(fd) == -1)
   {
      err(1, "closing the file failed");
   }
}

// executing function
static void
execute(int *fd, char **cmd, int w)
{
   // check with switch case if fork failed
   switch (fork())
   {
   
   // error handling
   case -1:
      err(EXIT_FAILURE, "fork failed");
   
   // if no error do execution
   case 0:
      // fupingh the fd
      xdup2(fd[w], w);

      // closing fd because of dup2
      xclose(fd[0]);
      xclose(fd[1]);

      // executing command
      execvp(cmd[0], cmd);

      // if we reach here we had a problem in the execv
      err(EXIT_FAILURE, "execv failed");
   }
}

int main(void)
{
   // creating array with ls
   char *ls[] = {"ls", NULL};

   // creating array with wordcount
   char *wordcount[] = {"wc", "-l", NULL};

   // creating a fd
   int fd[2];

   // piping the fd via function
   xpipe(fd);

   // executing function with fd, ls array and write 
   execute(fd, ls, 1);

   // executing function with fd, wc array and reading 
   execute(fd, wordcount, 0);

   // closing fd
   xclose(fd[0]);

   // closing fd
   xclose(fd[1]);

   for (int i = 0; i < 2; ++i)
   {
      // creating status variable
      int status;

      // waiting for child
      wait(&status);

      // checking if status returned with error
      if (!WIFEXITED(status) || WEXITSTATUS(status))
      {
         return EXIT_FAILURE;
      }
   }

   // return SUCCESS if everything got done correctly
   return EXIT_SUCCESS;
}
