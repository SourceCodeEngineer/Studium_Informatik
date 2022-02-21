//Pointers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int foo(char *x, char *y){
    return (x[0] == y[1]) ? -10 : 20;
}

bool isPalindrome(int n){
    int r,temp = n;  
    unsigned long long sum=0;
    while(n>0)    
    {    
        r=n%10;    
        sum=(sum*10)+r;    
        n=n/10;    
    }   
    if(temp==sum){return true;}
    return false;
}

int main (void){

    char a[] = {7, 8, 9, 10};
    char b[] = {8, 7, 8, 8};

    int m = 5;
    int *pt = &m;
    int test[] = {1, 2, *pt, 3};

    int *testt[] = {pt};

    char *pa = a;
    char *pb = b;
    char **ppa = &pa;
    char **ppb = &pb;
    char ***pppa = &ppa;
    char ***pppb = &ppb;

    int result = foo(**pppa, **pppb);
    bool x = isPalindrome(-112211);
    printf("%d", x);

    printf("Adresse vom Pointer pa: %p\n", &pa);
    printf("Pointer ppa zeigt auf: %p\n", pa);
    printf("Adresse vom Pointer pb: %p\n", &pb);
    printf("Pointer ppa zeigt auf: %p\n", pb);

    printf("-----------------------------\n");

    printf("Adresse vom Pointer ppa: %p\n", &ppa);
    printf("Pointer ppa zeigt auf: %p\n", ppa);
    printf("Adresse vom Pointer ppb: %p\n", &ppb);
    printf("Pointer ppb zeigt auf: %p\n", ppb);
    printf("%d\n", **ppa);

    printf("Result: %d\n",result);

    return EXIT_SUCCESS;
}