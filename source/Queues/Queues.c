#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queues.h"
#include "Arrays.h"

typedef struct QueueNode 
{
    int data;
    struct QueueNode* next;
}QueueNode;

typedef struct Queue 
{
    int count;
    QueueNode* first;
}Queue;

QueueLink queue_initialize() 
{
    QueueLink pointer;
    pointer = malloc(sizeof(Queue));
    pointer->count = 0;
    pointer->first = NULL;
    return pointer;
}

void queue_enqueue(QueueLink pointer, int data) //create 1 at start
{
    QueueNodeLink temp;
    temp = malloc(sizeof(QueueNode)); //Create a node as a "package"
    temp->data = data;
    temp->next = NULL;

    if(pointer->count == 0)
    {
        pointer->first = temp;
        pointer->count++;
    } 
    else 
    {
        temp->next = pointer->first;
        pointer->first = temp; 
        pointer->count++;
    }
}

int queue_dequeue(QueueLink pointer) //delete 1 at end
{
    if(pointer->count == 0)
    {
        printf("ERROR. The queue is empty, cant dequeue a node\n");
        return -1;
    }
    else if(pointer->count == 1)
    {
        int temp = pointer->first->data;
        free(pointer->first);
        pointer->first = NULL;
        pointer->count--;
        return temp;
    }
    else
    {
        QueueNodeLink cursor = pointer->first;
        for(int i = 2 ; i < pointer->count ; i++)
            cursor = cursor->next;

        int temp = cursor->next->data;
        free(cursor->next);
        cursor->next = NULL;
        pointer->count--;
        return temp;
    }
}

QueueLink queue_destroy(QueueLink pointer)//delete all
{
    int loops = pointer->count;
    for(int i = 0 ; i < loops ; i++)
        queue_dequeue(pointer);
    free(pointer);
    pointer = NULL;
    return pointer;
}

void queue_print(QueueLink pointer)
{
    if ( !pointer || pointer->count == 0)
    {
        printf("NULL\n");
    }
    else
    {
        QueueNodeLink temp = pointer->first;
        for(int i=0 ; i < pointer->count ; i++)
        {
            printf("%d -> ",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void queue_reverse(QueueLink pointer)
{
    QueueNodeLink previous = NULL;
    QueueNodeLink current = pointer->first;
    QueueNodeLink next = NULL;
    while( current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    pointer->first = previous;
}

QueueLink queue_copy(QueueLink pointer)
{
    QueueLink new = queue_initialize();
    for(int i = 0 ; i < pointer->count ; i++)
    {
        int temp = queue_dequeue(pointer);
        queue_enqueue(new,temp);
        queue_enqueue(pointer, temp);
    }
    return new;
}

ArrayInt queue_to_array(QueueLink pointer)
{
    int n = pointer->count;
    int* array = malloc(n*sizeof(int));
    for(int i = 0 ; i < n ; i++)
    {
        array[i] = queue_dequeue(pointer);
    }
    return array;
}

void queue_sort(QueueLink pointer)
{
    int n = pointer->count;
    ArrayInt array = queue_to_array(pointer);
    array_quicksort(array, 0, n-1);
    for(int i = 0 ; i < n ; i++)
    {
        queue_enqueue(pointer,array[i]);
    }
    queue_reverse(pointer); //reverse beacuse its in desceding order
}