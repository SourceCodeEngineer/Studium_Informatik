#include <stdlib.h>
#include <stdio.h>

size_t copy_distinct(int dst[], const int src[], size_t len)
{

    int isDuplicate = 0, pos = 0;
    int lenga = len;
    long unsigned int count = 1;

    for (int i = 0; i < lenga; i++){
        isDuplicate = 0;
        for (int j = 0; j < lenga; j++){
            if (src[i] == dst[j]){
                isDuplicate++; 
            }    
        }

        if (isDuplicate == 0){
            dst[pos] = src[i];
            pos++;
            count++;
        }
    }
    
    return count;
}

int main(void)
{

    const int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arrayB[10];

    size_t n = sizeof(array) / sizeof(int);

    copy_distinct(arrayB, array, n);

    return EXIT_SUCCESS;
}