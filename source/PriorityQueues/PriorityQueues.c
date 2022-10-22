#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueues.h"

// Do appropiate typedefs and structs
typedef struct PQNodeTag
{
    int Item;
    struct PQNodeTag* Link;
} PQNode;

struct PriorityQueue
{
    int Count;
    PQNode* ItemList;
};

PriorityQueuePointer priority_queue_init(void)
{                    // Create a node that contains the item count and ItemList of the priority queue
    PriorityQueuePointer PQ = malloc(sizeof(*PQ));

    PQ->Count = 0;
    PQ->ItemList = NULL;
    return PQ;                              // Then, return it. This allows the user to create multiple priority queues
}

int priority_queue_empty(PriorityQueuePointer PQ)
{     // Check if priority queue is empty
    return (PQ->Count == 0);
}

int priority_queue_full(PriorityQueuePointer PQ)
{              // Check if priority queue is full
    return (PQ->Count == MAXCOUNT);
}

PQNode* priority_queue_sorted_insert(int Item, PQNode *P)
{        // Add the item to the correct position
    if ((P == NULL) || (Item >= P->Item)) {             // If the ItemList is empty or the inserted Item is greater than current Item,
        PQNode *N;                                      // Create a new node N and initialize it
        N = malloc(sizeof(PQNode));
        N->Item = Item;
        N->Link = P;                                    // N points to P because it is greater than P
        return N;                                       // Return N
    }
    else {                                              // Else,
        P->Link = priority_queue_sorted_insert(Item, P->Link);          // Call priority_queue_sorted_insert with the next node instead
        return P;                                       // Return P
    }
}

void priority_queue_insert(int Item, PriorityQueuePointer PQ)
{                            // Insert an item to the priority queue
    if (priority_queue_full(PQ)) printf("Cannot add item(Queue is full).\n");        // If the queue is full, print error message
    else {                                                              // Else,
        ++(PQ->Count);                                                  // Raise the item counter
        PQ->ItemList = priority_queue_sorted_insert(Item, PQ->ItemList);                // Add the item to the correct position
    }
}

int priority_queue_remove(PriorityQueuePointer PQ)
{                                                   // Remove the first item
    if (priority_queue_empty(PQ)) {
        printf("Cannot remove item from empty priority queue.\n");     // If the priority queue is empty, print error message
        return -1;
    }
    else {
        int Item;                                                              // Save the item
        Item = PQ->ItemList->Item;

        PQNode *Temp;                                                               // Create a Temp node to save the memory address
        Temp = PQ->ItemList;

        PQ->ItemList = Temp->Link;                                                  // ItemList now starts at the second item
        free(Temp);                                                                 // Free Temp

        --(PQ->Count);                                                              // Lower the item counter
        return Item;                                                                // Return the item
    }
}
