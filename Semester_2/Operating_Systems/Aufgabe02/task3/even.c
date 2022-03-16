#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>   // for errno
#include <limits.h>

bool isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

int main(int argc, char argv[]){
    if (argc > 2 || argc < 2){
        return -2; //wromg input
    }
    else {
        if (isNumber(argv[1])){
            return -3; //not a number
        }
        else{
            char *p;
            int num;

            errno = 0;

            long conv = strtol(argv[1], &p, 10);

            num = conv;

            if(num % 2 == 1){
                return -1; // odd number
            }
            else{
                return 0; // even number
            }
        }
    }
    return EXIT_SUCCESS;
}
