#include <stdlib.h>

struct my_array {
    int *array;
    int len;
};

int main(void) {
    int len = 10;
    struct my_array *arr = malloc(sizeof(*arr));
    arr->len = len;
    arr->array = malloc(sizeof(*arr->array * len));
    free(arr);
    return EXIT_SUCCESS;
}