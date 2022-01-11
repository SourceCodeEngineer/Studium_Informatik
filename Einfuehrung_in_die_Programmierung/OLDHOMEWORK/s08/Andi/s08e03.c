#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_NAME 64

typedef struct person {
    char first_name[MAX_LEN_NAME + 1];
    char last_name[MAX_LEN_NAME + 1];
    unsigned char age;
} person_t;

void print_person(person_t *p){
    printf("%s %s %d", p->first_name, p->last_name, p->age);
}

int age_comparator(const void *pa, const void *pb){
    const person_t *x1 = pa;
    const person_t *x2 = pb;
    
    return x1->age - x2->age;
}

int first_name_comparator(const void *pa, const void *pb){
    const person_t *x1 = pa;
    const person_t *x2 = pb;

    return strcmp(x1->first_name, x2->first_name);
}

int last_name_comparator(const void *pa, const void *pb){
    const person_t *x1 = pa;
    const person_t *x2 = pb;

    return strlen(x1->last_name) - strlen(x2->last_name);    
}

int name_comparator(const void *pa, const void *pb){
    const person_t *x1 = pa;
    const person_t *x2 = pb;

    int cmp = strcmp(x1->last_name, x2->last_name);

    if(cmp < 0) {
        return -1;
    }
    if(cmp > 0) {
        return 1;
    }
    return first_name_comparator(pa,pb);
}

int person_comparator(const void *pa, const void *pb){
    int cmp = name_comparator(pa, pb);
    if (cmp == 0) {
        return age_comparator(pa, pb);
    }
    return name_comparator(pa, pb);
}

void sort_persons(person_t *persons, const int num_persons, int (*comparator)(const void *, const void *)){
    qsort(persons, num_persons, sizeof(person_t), comparator);
}

int main (void){return EXIT_SUCCESS;}
