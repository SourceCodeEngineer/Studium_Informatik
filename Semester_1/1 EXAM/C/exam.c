//Pointers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define square(x) x *x

int main (void){

    int x;
    x = 16/ square(4);
    printf("%d", x);

    return EXIT_SUCCESS;
}