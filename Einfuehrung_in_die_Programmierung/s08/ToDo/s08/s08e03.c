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

void age_comparator(const void *pa, const void *pb){
    const int *p1 = pa;
    const int *p2 = pb;
    return *p2 - *p1;
}
/*
void first_name_comparator(const void *pa, const void *pb){
    
}

void last_name_comparator(const void *pa, const void *pb){
    
}

void name_comparator(person_t *pa){
    
}

void person_comparator(person_t *pa){
    
}
*/
int main (void){

    int nums[] = {0,7,6,5,8,15};
    int n = sizeof(nums)/sizeof(int);

    qsort(nums, n, sizeof(int), age_comparator);

    for (int i = 0; i<n; i++){
        printf(" %d", nums[i]);
    }

    return EXIT_SUCCESS;
}