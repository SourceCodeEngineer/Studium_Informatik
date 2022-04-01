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

int main(int arc, char **argc)
{

    for (int i = 0; i < argc-1; ++i){
        // calling the client by forking n times!
        
    }

   return EXIT_SUCCESS;
}
