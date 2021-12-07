#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int length_longest_palindrome(char str[])
{
    int len = 0, pos = 0;

    while (str[pos] != '\0')
    {
        pos++;
        len++;
    }

    if (len == 0){
        return 0;
    }

    int counter = 1;
    int b = len - 1;
    int f = 0;
    int counter_tmp;

    for (int i=0; i<len; i++){
        for (int k = 0; k < len; k++){
            if (str[f] != str[b]){
                break;
            }
        }
    }
    return counter;
}

int main(void)
{
    char a[] = "aba";
    int x = length_longest_palindrome(a);
    printf("%d", x);
    return EXIT_SUCCESS;
}