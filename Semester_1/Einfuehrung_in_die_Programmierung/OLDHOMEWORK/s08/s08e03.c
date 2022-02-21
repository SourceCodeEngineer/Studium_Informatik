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

int age_comparator(const void *value1, const void *value2){
    const person_t *ph1 = value1;
    const person_t *ph2 = value2;
    return ph1->age - ph2->age;
}

int first_name_comparator(const void *value1, const void *value2){
    const person_t *ph1 = value1;
    const person_t *ph2 = value2;
    return strcmp(ph1->first_name, ph2->first_name);
}

int last_name_comparator(const void *value1, const void *value2){
    const person_t *ph1 = value1;
    const person_t *ph2 = value2;
    return strlen(ph1->last_name) - strlen(ph2->last_name);    
}

int name_comparator(const void *value1, const void *value2){
    const person_t *ph1 = value1;
    const person_t *ph2 = value2;
    int compare = strcmp(ph1->last_name, ph2->last_name);

    if(compare < 0) return -1;
    if(compare > 0) return 1;
    return first_name_comparator(value1,value2);
}

int person_comparator(const void *value1, const void *value2){
    int compare = name_comparator(value1, value2);
    if (compare == 0) return age_comparator(value1, value2);
    return name_comparator(value1, value2);
}

void sort_persons(person_t *persons, const int num_persons, 
    int (*comparator)(const void *, const void *)){
    qsort(persons, num_persons, sizeof(person_t), comparator);
}

int main (void){return EXIT_SUCCESS;}
