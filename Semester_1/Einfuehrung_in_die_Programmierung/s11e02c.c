#include <stdio.h>
#include <stdlib.h>

#define BASIC_DATATYPE_NAME(x)                                                 \
    _Generic((x), char                                                         \
             : "char", signed char                                             \
             : "signed char", unsigned char                                    \
             : "unsigned char", short                                          \
             : "short", unsigned short                                         \
             : "unsigned short", int                                           \
             : "int", unsigned int                                             \
             : "unsigned int", long                                            \
             : "long", unsigned long                                           \
             : "unsigned long", long long                                      \
             : "long long", unsigned long long                                 \
             : "unsigned long long", float                                     \
             : "float", double                                                 \
             : "double", long double                                           \
             : "long double", default                                          \
             : "other")

#define PRINT_EXPRESSION(exp)                                                  \
    printf(#exp " is of datatype \"%s\"\n", BASIC_DATATYPE_NAME(exp))

int main(void) {
    unsigned int a = 5;
    PRINT_EXPRESSION(a);
    PRINT_EXPRESSION('A' + 'B');
    PRINT_EXPRESSION((7.4 > 4.2) && (3.0 == 4.5f));
    PRINT_EXPRESSION(1ull);
    PRINT_EXPRESSION(2147483648);
    PRINT_EXPRESSION(0.34f - 0.022 + 0.252f);
    PRINT_EXPRESSION(0xB4D / 3.f);
    PRINT_EXPRESSION(&a);
    return EXIT_SUCCESS;
}