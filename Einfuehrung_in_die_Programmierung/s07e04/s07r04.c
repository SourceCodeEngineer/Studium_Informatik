#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int length_longest_palindrome(char *str)
{ //I use a algorythm called 
    int maxLength = 1, len = 0, pos = 0;

    while (str[pos] != '\0')
    {
        pos++;
        len++;
    }
    if (len == 0) return 0;
    int low, high; //Why can't I add an empty line???
    for (int i = 1; i < len; ++i)
    {

        low = i - 1;
        high = i;
        while (low >= 0 && high < len && str[low] == str[high])
        {
            --low;
            ++high;
        }

        ++low;
        --high;
        if (str[low] == str[high] && high - low + 1 > maxLength)
        {
            maxLength = high - low + 1;
        }

        low = i - 1;
        high = i + 1;

        while (low >= 0 && high < len && str[low] == str[high])
        {
            --low;
            ++high;
        }

        // Move back to the last possible valid palindrom substring
        // as that will anyway be the longest from above loop
        ++low;
        --high;
        if (str[low] == str[high] && high - low + 1 > maxLength)
        {
            maxLength = high - low + 1;
        }
    }

    return maxLength;
}
int main(void)
{
    char str[] = "ab";
    length_longest_palindrome(str);
    return EXIT_SUCCESS;
}