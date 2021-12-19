#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_NAME 64

typedef struct person {
    char first_name[MAX_LEN_NAME + 1];
    char last_name[MAX_LEN_NAME + 1];
    unsigned char age;
} person_t;

void print_person(struct person p){
    printf("%s %s %d", p.first_name, p.last_name, p.age);
}

void age_comparator(const void *, const void *){
    
}

void first_name_comparator(const void *, const void *){
    
}

void last_name_comparator(const void *, const void *){
    
}

void name_comparator(person_t *){
    
}

void person_comparator(person_t *){
    
}

int main (void){
    return EXIT_SUCCESS;
}