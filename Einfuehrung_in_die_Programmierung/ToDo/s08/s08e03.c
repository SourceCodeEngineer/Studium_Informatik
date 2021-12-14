#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_NAME 64

typedef struct person {
    char first_name[MAX_LEN_NAME + 1];
    char last_name[MAX_LEN_NAME + 1];
    unsigned char age;
} person_t;

void print_person(struct person var){
    int i = 0;
    while (var.first_name[i] != '\0'){printf("%c", var.first_name[i]); i++;}
    printf("%s ", var.first_name);
    printf("%s ", var.last_name);
    printf("%d ", var.age);
}

int main(void){
    struct person Book2;
    strcpy( Book2.first_name, "C Programming\0");
    print_person(Book2);
    return EXIT_SUCCESS;
}