#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>

void closePipe(char *filename, int fd)
{
   close(fd);
   unlink(filename);
}

char *removeNewLine(char *input)
{
   input[strlen(input) - 1] = '\0';
   return input;
}

void parseInput(char *name, char *input)
{
   double n1, n2, result;
   char operator;

   if (sscanf(input, "%lf %c %lf", &n1, &operator, & n2) != 3)
   {
      printf("%s: %s is malformed.\n", name, input);
   }

   if (operator== '+')
   {
      result = n1 + n2;
   }
   else if (operator== '-')
   {
      result = n1 - n2;
   }
   else if (operator== '/')
   {
      result = n1 / n2;
   }
   else if (operator== '*')
   {
      result = n1 * n2;
   }
   else
      printf("%s: %s is malformed.\n", name, input);
}

void waitForInput(int *fds, int size, char **names)
{
   int closed = 0;
   struct pollfd polls[size];
   for (int i = 0; i < size; ++i)
   {
      polls[i] = (struct pollfd){.fd = fds[i], .events = POLLIN};
   }

   while (1)
   {
      if (poll(polls, size, -1) > 0)
      {
         for (int i = 0; i < size; ++i)
         {
            if (polls[i].revents & POLLIN)
            {
               char buff[BUFSIZ] = {0};
               read(polls[i].fd, &buff, sizeof(buff));
               parseInput(names[i], removeNewLine(buff));
            }
            else if (polls[i].revents & POLLHUP)
            {
               closePipe(names[i], fds[i]);
               printf("%s disconnected!\n", names[i]);
               polls[i].fd = -1;
               if (++closed == size)
                  return;
            }
         }
      }
   }
}

int main(int argc, char **argv)
{
   if (argc < 2)
   {
      printf("usage: execute the server and give it a parameter of clients (e.g.: ./task3_server euler gaus ...)!\n");
      return EXIT_FAILURE;
   }

   const int size = argc - 1;
   char *names[size];
   int fds[size];

   for (int i = 0; i < size; ++i)
   {
      names[i] = argv[i + 1];
      if (i > 0)
      {
         printf("%s connected\n", names[i - 1]);
      }

      const mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
      mkfifo(names[i], permissions);
      fds[i] = open(names[i], O_RDONLY);
   }
   printf("%s connected!\n", names[size - 1]);

   waitForInput(fds, size, names);

   return EXIT_SUCCESS;
}
