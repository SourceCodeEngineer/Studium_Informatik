#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_COND(cond)                                                       \
    printf("'" #cond "' evaluates to '%s'\n", (cond) ? "true" : "false")
#define CNT_COND(cond, y)                                                      \
    {PRINT_COND(cond);}                                                          \
    if (cond)                                                                  \
    y++

int main(int argc, char **argv) {
    int a = 0;
    size_t b = 4;
    if (argc > 1)
        CNT_COND(strlen(argv[1]) > b, a);
    else {
        PRINT_COND(strlen(argv[0]) > b);
        --a;
    }
    printf("a = %d\n", a);
    return EXIT_SUCCESS;
}