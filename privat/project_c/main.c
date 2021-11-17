#include <stdio.h>
#include <stdlib.h>

// Task: Get an user input and output the all numbers from 0 up to the users number.
// Hint: You must be carefull, because the inputtype can be any positive / negative integer!

int main (void){
    int number, counter = 0;
    scanf("%d\n", &number);

    if (number == 0){
        printf("Nothing to do, You chose 0!\n");
    } else if (number > 0){
        printf("You have chosen %d\n", number);
        while (counter < number){
            counter++;

            if (number % 2){
                printf("%d\n", number);
            }
            
        }
    }
}