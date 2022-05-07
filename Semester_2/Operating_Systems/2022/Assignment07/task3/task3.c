#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>
#include <stdatomic.h>

#define NUMBER_OF_PLAYERS 5

pthread_mutex_t mutex;
atomic_int atomic = 0;

// creating double linked list (may be overkill but first thaought). Might change that later! DO NOT TOUCH!!!
struct Player {
    int threadNumber;
    int diceRoll;
    int rollCounter;
    bool hasRolled;
    int deletedPlayer;
    struct Player* next;
    struct Player* prev;
};

void push(struct Player** head_ref, int threadNumber, int diceRoll, int rollCounter, bool hasRolled, int deletedPlayer)
{
    /* 1. allocate Player */
    struct Player* new_Player
        = (struct Player*)malloc(sizeof(struct Player));
 
    /* 2. put in the data  */
    new_Player->threadNumber = threadNumber;
    new_Player->diceRoll = diceRoll;
    new_Player->rollCounter = rollCounter;
    new_Player->hasRolled = hasRolled;
    new_Player->deletedPlayer = deletedPlayer;
 
    new_Player->next = (*head_ref);
    new_Player->prev = NULL;
 
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_Player;
 
    (*head_ref) = new_Player;
}
 
/* Given a Player as prev_Player, insert a new Player after the
 * given Player */
void insertAfter(struct Player* prev_Player, int threadNumber, int diceRoll, int rollCounter, bool hasRolled, int deletedPlayer)
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
    new_Player->hasRolled = hasRolled;
    new_Player->deletedPlayer = deletedPlayer;
 
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
void append(struct Player** head_ref, int threadNumber, int diceRoll, int rollCounter, bool hasRolled, int deletedPalyer)
{
    /* 1. allocate Player */
    struct Player* new_Player
        = (struct Player*)malloc(sizeof(struct Player));
 
    struct Player* last = *head_ref; /* used in step 5*/
 
    /* 2. put in the data  */
    new_Player->threadNumber = threadNumber;
    new_Player->diceRoll = diceRoll;
    new_Player->rollCounter = rollCounter;
    new_Player->hasRolled = hasRolled;
    new_Player->deletedPlayer = deletedPalyer;
 
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

void deleteNode(struct Player** head_ref, struct Player* del)
{
    /* base case */
    if (*head_ref == NULL || del == NULL)
        return;
 
    /* If node to be deleted is head node */
    if (*head_ref == del)
        *head_ref = del->next;
 
    /* Change next only if node to be deleted is NOT the last node */
    if (del->next != NULL)
        del->next->prev = del->prev;
 
    /* Change prev only if node to be deleted is NOT the first node */
    if (del->prev != NULL)
        del->prev->next = del->next;
 
    /* Finally, free the memory occupied by del*/
    free(del);
    return;
}
// DO NOT TOUCH ABOVE EVER!!!!!!!

int rollDice(){
    srand(time(NULL));
    return rand() % 6;
}

int search(struct Player** head_ref, int x)
{
 
    // Stores head Node
    struct Player* temp = *head_ref;
 
    // Stores position of the integer
    // in the doubly linked list
    int pos = 0;
 
    // Traverse the doubly linked list
    while (temp->hasRolled != x
           && temp->next != NULL) {
 
        // Update pos
        pos++;
 
        // Update temp
        temp = temp->next;
    }
 
    // If the integer not present
    // in the doubly linked list
    if (temp->hasRolled != x)
        return -1;
 
    // If the integer present in
    // the doubly linked list
    return (pos + 1);
}

bool checkIfDiceRolled(struct Player** head_ref){
    pthread_mutex_lock(&mutex);

    bool rv = true;

    for (int i = 0; i < NUMBER_OF_PLAYERS; ++i){
        // check every player if the dices have rolled
        if(search(*(&head_ref), false) == -1) rv = false;
    }

    pthread_mutex_unlock(&mutex);
    return rv;
}

int findSize(struct Player** node)
{
   int res = 0;
   while (node != NULL)
   {
       ++res;
       *node = (*node)->next;
   }
   return res;
}

void searchAndUpdate(struct Player** head_ref, int x, int roll)
{
 
    // Stores head Node
    struct Player* temp = *head_ref;
 
    // Stores position of the integer
    // in the doubly linked list
 
    // go through every element and if found then update entry
    while (temp->next != NULL){
        if (temp->threadNumber == x){
            // update the entry
            (*head_ref)->diceRoll = roll;
            (*head_ref)->hasRolled = true;
            (*head_ref)->rollCounter += 1;
            break;
        }
        temp = temp->next;
    }
}

void printFunctionBeforeElimination(struct Player** player, int x){
    pthread_mutex_lock(&mutex);

    //int size = findSize(&player);

    struct Player* temp = *player;

    for (int i = 0; i < 5; ++i){
        // do printing
        if(x != 0){break;}

        printf("Player %d rolled a %d\n", temp->threadNumber, temp->diceRoll);
        //temp = temp->next;
    }

    pthread_mutex_unlock(&mutex);
}

void printFunctionAfterElimination(struct Player** player){
    pthread_mutex_lock(&mutex);

    // check wich player got eliminated

    pthread_mutex_unlock(&mutex);
}

void defaultFunction(struct Player** player, int threadnumber)
{
    while (true)
    {
        // rolling dice + 1 because of range 0-5 and we want 1 - 6:
        int roll = rollDice() + 1;

        // find element in DLL and edit note
        int position = search(player, threadnumber); 
        searchAndUpdate(player, threadnumber, roll);     
        
        // print DLL before player(s) got eliminated
        printFunctionBeforeElimination(player, threadnumber);

        // access DLL and add the roll to the correct field

        // set roundnumber in DLL +1

        // determine loser (multiple possible!)

        // exit if we are a loser! else wait for others and play again!

        // reset hasrolled counter in node to false!

        // check if eliminated then break
        if (1 != 0){
            break;
        }
    }
}

void* threadRoutine(struct Player** player){
    pthread_mutex_lock(&mutex);
    int x = atomic;
    ++atomic;
    pthread_mutex_unlock(&mutex);

    // default function
    defaultFunction(player, x);

    return NULL;
}

int main(void){

    // initing mutex
    pthread_mutex_init(&mutex, NULL);
    
    // creating starting point of DLL
    struct Player* head = NULL;

    // Adding 5 players to the DLL and setting starter parameters.
    push(&head, 0, 0, 0, false, -1);
    push(&head, 1, 0, 0, false, -1);
    push(&head, 2, 0, 0, false, -1);
    push(&head, 3, 0, 0, false, -1);
    push(&head, 4, 0, 0, false, -1);

    pthread_t con[NUMBER_OF_PLAYERS];
    int name[NUMBER_OF_PLAYERS] = {0};

    for (int i = 0; i < NUMBER_OF_PLAYERS; ++i)
    {
        name[i] = i;
    }

    // creating 5 threads for 5 players
    for (int i = 0; i < NUMBER_OF_PLAYERS; ++i){
        pthread_create(&con[i], NULL, (void *)threadRoutine, head);
    }

    // waiting for 5 threads for 5 players
    for (int i = 0; i < NUMBER_OF_PLAYERS; ++i){
        pthread_join(con[i], NULL);
    }

    return EXIT_SUCCESS;
}
