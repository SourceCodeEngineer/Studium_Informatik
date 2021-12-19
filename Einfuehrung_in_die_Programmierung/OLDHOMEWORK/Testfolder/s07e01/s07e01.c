#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char values[] = "abcdefg";
    char *p1 = values;
    char *p2 = values + strlen(values);
    char c1 = *(p1 + 2);
    char c2 = *p2;
    printf("1) %c\n", c1);
    printf("2) %c\n", c2);
    printf("3) %d\n", p1 < p2);
    printf("4) %d\n", (p1 + 4) < p2);
    printf("5) %d\n", (((int32_t *)p1) + 4) < (int32_t *)p2);
    return EXIT_SUCCESS;
}