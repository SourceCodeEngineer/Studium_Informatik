#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG 1

#ifdef DEBUG
#define PRINT_VAR(file, line, x)                                               \
    do {                                                                       \
        printf("%s:%d: ", file, line);                                         \
        printf(#x " = %d\n", x);                                               \
    } while (0)
#else
#define PRINT_VAR(file, line, x) printf(#x " = %d\n", x)
#endif

int main(int argc, char **argv) {
    PRINT_VAR(__FILE__, __LINE__, argc);
    if (argc > 1)
        PRINT_VAR(__FILE__, __LINE__, strcmp(argv[0], argv[1]));
    return EXIT_SUCCESS;
}
