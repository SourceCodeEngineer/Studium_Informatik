#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_palindrome(char str[], int len)
{
    int l = 0;
    int h = len;

    // Keep comparing characters while they are the same
    while (h > l)
    {
        if (str[l++] != str[h--]) // wenn ungleich false
        {
            return false;
        }
    }
    return true; // wenn gleich true
}

void creat_array_up_to(char dst[], char src[], int upto, int from)
{
    int i = 0;
    int pos = 0;
    while (i <= upto)
    {
        dst[pos] = src[from];
        pos++;
        i++;
        from++;
    }
}

int length_longest_palindrome(char str[])
{
    int len = 0, pos = 0;
    // len of the array
    while (str[pos] != '\0')
    {
        pos++;
        len++;
    }

    // if the len is 0 then returning 0
    if (len == 0)
    {
        return 0;
    }

    int counter = -1;
    // creating empty char array
    char testingpurpose[len];

    // if the len is greater than 0 --> loop with function call
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            creat_array_up_to(testingpurpose, str, j, i);
            bool pal = is_palindrome(testingpurpose, j);
            if (pal && j >= counter)
            {
                counter = j+1;
            }
        }
    }
    return counter;
}

int main(void)
{
    char a[] = "ll";
    int x = length_longest_palindrome(a);
    printf("%d",x);
    return EXIT_SUCCESS;
}