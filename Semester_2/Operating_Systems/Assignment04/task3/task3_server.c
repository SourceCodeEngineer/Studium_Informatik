#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>

// for error handling
#define DO_OR_DIE(x, s) \
   do                   \
   {                    \
      if ((x) < 0)      \
      {                 \
         perror(s);     \
         exit(1);       \
      }                 \
   } while (0)


// for closing the pipe 
void pipeCloser(char *filename, int fd)
{
   close(fd);
   unlink(filename);
}

// for removing the newline
char *rpNLtoNULL(char *input)
{
   // changing the last charactere of the given input to a \0 because we don't want newlines here
   input[strlen(input) - 1] = '\0';

   // after replacing the newline with \0 we return the input
   return input;
}

// parser
void parseInput(char *name, char *input)
{
   char operator;
   double numberLeftOfOperator, numberRightOfOperator, result;
   
   if (sscanf(input, "%lf %c %lf", &numberLeftOfOperator, &operator, &numberRightOfOperator) != 3)
   {
      printf("%s: %s is malformed.\n", name, input);
      return;
   }

   // parse input for operator +
   if (operator == '+')
   {
      result = numberLeftOfOperator + numberRightOfOperator;
      printf("%s: %g %c %g = %g\n", name, numberLeftOfOperator, operator, numberRightOfOperator, result);
   }
   // parse input for operator -
   else if (operator == '-')
   {
      result = numberLeftOfOperator - numberRightOfOperator;
      printf("%s: %g %c %g = %g\n", name, numberLeftOfOperator, operator, numberRightOfOperator, result);
   }
   // parse input for operator /
   else if (operator == '/')
   {
      result = numberLeftOfOperator / numberRightOfOperator;
      printf("%s: %g %c %g = %g\n", name, numberLeftOfOperator, operator, numberRightOfOperator, result);
   }
   // parse input for operator *
   else 
   {
      result = numberLeftOfOperator * numberRightOfOperator;
      printf("%s: %g %c %g = %g\n", name, numberLeftOfOperator, operator, numberRightOfOperator, result);
   }
}


// input waiting function
void waitingForInput(int *filedescriptores, int clients, char **clientNames)
{
   // creating a struct of polls with size of clients
   struct pollfd polls[clients];

   // creating a variable isClosed and initialise it with 0
   int isClosed = 0;

   // for every client we do the for loop
   for (int i = 0; i < clients; ++i)
   {
      polls[i] = (struct pollfd){.fd = filedescriptores[i], .events = POLLIN};
   }

   // endless loop
   while (1)
   {
      if (poll(polls, clients, -1) > 0)
      {
         for (int i = 0; i < clients; ++i)
         {
            if (polls[i].revents & POLLIN)
            {
               char buff[BUFSIZ] = {0};

               read(polls[i].fd, &buff, sizeof(buff));

               parseInput(clientNames[i], rpNLtoNULL(buff));
            }
            else if (polls[i].revents & POLLHUP)
            {
               pipeCloser(clientNames[i], filedescriptores[i]);

               printf("%s disconnected!\n", clientNames[i]);

               polls[i].fd = -1;

               if (++isClosed == clients)
                  return;
            }
         }
      }
   }
}

int main(int argc, char **argv)
{

   // checking if input is correct else print usage
   if (argc < 2)
   {
      printf("usage: execute the server and give it a parameter of clients (e.g.: ./task3_server euler gaus ...)!\n");
      return EXIT_FAILURE;
   }

   // creating clients so we know how many clients we are awaiting
   const int clients = argc - 1;

   // creating an array of size clients
   char *clientNames[clients];

   // creating fd array of size clients
   int filedescriptores[clients];

   for (int i = 0; i < clients; ++i)
   {
      clientNames[i] = argv[i + 1];

      if (i > 0)
      {
         printf("%s connected!\n", clientNames[i - 1]);
      }

      // setting the permissions
      const mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

      // creating fifo with permissions
      int fifoCheck = mkfifo(clientNames[i], permissions);

      // error handling
      DO_OR_DIE(fifoCheck, "FIFO FAILED!");

      // opening fd on position i with read only permissions
      filedescriptores[i] = open(clientNames[i], O_RDONLY);
   }

   // if successfull, print connected
   printf("%s connected!\n", clientNames[clients - 1]);

   // executing inputwaiting
   waitingForInput(filedescriptores, clients, clientNames);

   // if everything is successfull return SUCCESS
   return EXIT_SUCCESS;
}
