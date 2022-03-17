#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: ENVIRONMENT_VARIABLE");
        return EXIT_FAILURE;
    }

    // Make sure envar actually exists
    if(!getenv(argv[1])){
        printf("%s is not set\n", argv[1]);
        return EXIT_FAILURE;
    }else{
        printf("%s is set to %s\n", argv[1], getenv(argv[1]));
        return EXIT_SUCCESS;
    }
}
