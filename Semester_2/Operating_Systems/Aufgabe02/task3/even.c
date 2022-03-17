#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h> // for errno
#include <limits.h>
#include <ctype.h>
#include <string.h>

int checkForMinus(char argv[])
{
    if (argv[0] == '-')
    {
        return 1;
    }
    return 0;
}

int checkForChar(char array[], int length)
{
    for (int i = 0; i < length; ++i)
    {
        if ((array[i] > 47 && array[i] < 58))
        {
            continue;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 2 || argc < 2)
    {
        return 2; // wrong input
    }
    else
    {
        int returnValue = checkForMinus(argv[1]); // returns 1 if string starts with a '-'

        if (returnValue)
        {
            // negative number
            int stringLen = strlen(argv[1]);
            char array[stringLen];
            strcpy(array, argv[1]);

            array[0] = '0';

            int checkedForChar = checkForChar(array, stringLen);

            if (checkedForChar == 1)
            {
                return 3;
            }

            int numberToCompare = atoi(array);

            switch (numberToCompare % 2)
            {
            case 1:
                return 1;

            default:
                return 0;
            }
        }
        else
        {
            // check if a char is in the string
            int stringLen = strlen(argv[1]);
            char array[stringLen];
            strcpy(array, argv[1]);

            int checkedForChar = checkForChar(array, stringLen);

            if (checkedForChar == 1)
            {
                return 3;
            }

            int numberToCompare = atoi(argv[1]);
            switch (numberToCompare % 2)
            {
            case 1:
                return 1;

            default:
                return 0;
            }
        }
    }
    return EXIT_SUCCESS;
}
