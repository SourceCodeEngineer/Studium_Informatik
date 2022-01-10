#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void printBinary(int n, int mant){
    for (int i = 0; i >= 0; i--){
        if (n >> i & 1) printf("1");
        else printf("0");
    }
}

typedef union {
    float fl;
    struct{
        unsigned int m : 23;
        unsigned int e : 8;
        unsigned int s : 1;
    } temp;
} un;

void convertToBinary(un n){
    printf("    %d  ", n.temp.s);
    printBinary(n.temp.e, 8);
    printf("  ");
    printBinary(n.temp.m, 23);
    printf("\n");
}

int main(int argc, char *argv[]){
    char *text;
    if(argc == 2){
        int mybool = true;
        unsigned long int i = 0;
        while(i < strlen(*(argv + 1))){
            if (mybool == true){
                if (isalpha(argv[1][i])){
                    mybool = false;
                    i++;
                    break;
                }
                else{
                    i++;
                }
            }
        }
        if (mybool){
            un n;
            n.fl = strtof(*(argv + 1),&text);
            printf("Number: %f\n",n.fl);
            printf("Binary representation:\n");
            convertToBinary(n);
            printf("sign  exponent                 mantissa");
            return EXIT_SUCCESS;
        }
        else{
            fprintf(stderr,"ERROR: %s is not a valid float!\n", argv[1]);
            fprintf(stderr,"Extracted float component: %f\n",strtof(*(argv+1), &text));
            fprintf(stderr, "Remaining: %s", text);
            return EXIT_FAILURE;
        }
    }
}