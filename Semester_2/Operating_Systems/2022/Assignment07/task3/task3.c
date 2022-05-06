#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define NUMBER_OF_PLAYERS 5

// creating double linked list (may be overkill but first thaought). Might change that later! DO NOT TOUCH!!!
struct Player {
    int threadNumber;
    int diceRoll;
    int rollCounter;
    struct Player* next;
    struct Player* prev;
};

void push(struct Player** head_ref, int threadNumber, int diceRoll, int rollCounter)
{
    /* 1. allocate Player */
    struct Player* new_Player
        = (struct Player*)malloc(sizeof(struct Player));
 
    /* 2. put in the data  */
    new_Player->threadNumber = threadNumber;
    new_Player->diceRoll = diceRoll;
    new_Player->rollCounter = rollCounter;
 
    new_Player->next = (*head_ref);
    new_Player->prev = NULL;
 
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_Player;
 
    (*head_ref) = new_Player;
}
 
/* Given a Player as prev_Player, insert a new Player after the
 * given Player */
void insertAfter(struct Player* prev_Player, int threadNumber, int diceRoll, int rollCounter)
{
    /*1. check if the given prev_Player is NULL */
    if (prev_Player == NULL) {
        printf("the given previous Player cannot be NULL");
        return;
    }
 
    /* 2. allocate new Player */
    struct Player* new_Player
        = (struct Player*)malloc(sizeof(struct Player));
 
    /* 3. put in the data  */
    new_Player->threadNumber = threadNumber;
    new_Player->diceRoll = diceRoll;
    new_Player->rollCounter = rollCounter;
 
    /* 4. Make next of new Player as next of prev_Player */
    new_Player->next = prev_Player->next;
 
    /* 5. Make the next of prev_Player as new_Player */
    prev_Player->next = new_Player;
 
    /* 6. Make prev_Player as previous of new_Player */
    new_Player->prev = prev_Player;
 
    /* 7. Change previous of new_Player's next Player */
    if (new_Player->next != NULL)
        new_Player->next->prev = new_Player;
}
 
/* Given a reference (pointer to pointer) to the head
   of a DLL and an int, appends a new Player at the end  */
void append(struct Player** head_ref, int threadNumber, int diceRoll, int rollCounter)
{
    /* 1. allocate Player */
    struct Player* new_Player
        = (struct Player*)malloc(sizeof(struct Player));
 
    struct Player* last = *head_ref; /* used in step 5*/
 
    /* 2. put in the data  */
    new_Player->threadNumber = threadNumber;
    new_Player->diceRoll = diceRoll;
    new_Player->rollCounter = rollCounter;
 
    /* 3. This new Player is going to be the last Player, so
          make next of it as NULL*/
    new_Player->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new
          Player as head */
    if (*head_ref == NULL) {
        new_Player->prev = NULL;
        *head_ref = new_Player;
        return;
    }
 
    /* 5. Else traverse till the last Player */
    while (last->next != NULL)
        last = last->next;
 
    /* 6. Change the next of last Player */
    last->next = new_Player;
 
    /* 7. Make last Player as previous of new Player */
    new_Player->prev = last;
 
    return;
}

// DO NOT TOUCH ABOVE!!!!!!!

int main(void){



    return EXIT_SUCCESS;
}