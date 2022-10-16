#include <stdio.h>
#include <stdlib.h>
#include "Queues.h"
#include "Arrays.h"

Queue_Link queue_initialize(Queue_Link pointer) 
{
    pointer = malloc(sizeof(Queue));
    pointer->count = 0;
    pointer->first = NULL;
    return pointer;
}

void queue_enqueue(Queue_Link pointer, int data) //create 1 at start
{
    Queue_Node_Link temp;
    temp = malloc(sizeof(Queue_Node)); //Create a node as a "package"
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

int queue_dequeue(Queue_Link pointer) //delete 1 at end
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
        Queue_Node_Link cursor = pointer->first;
        for(int i = 2 ; i < pointer->count ; i++)
            cursor = cursor->next;

        int temp = cursor->next->data;
        free(cursor->next);
        cursor->next = NULL;
        pointer->count--;
        return temp;
    }
}

void queue_destroy(Queue_Link pointer)//delete all
{
    int loops = pointer->count;
    for(int i = 0 ; i < loops ; i++)
        queue_dequeue(pointer);
    free(pointer);
    pointer = NULL;
}

void queue_print(Queue_Link pointer)
{
    if ( !pointer )
    {
        printf("NULL\n");
    }
    else
    {
        Queue_Node_Link temp = pointer->first;
        for(int i=0 ; i < pointer->count ; i++)
        {
            printf("%d -> ",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void queue_reverse(Queue_Link pointer)
{
    Queue_Node_Link previous = NULL;
    Queue_Node_Link current = pointer->first;
    Queue_Node_Link next = NULL;
    while( current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    pointer->first = previous;
}

Queue_Link queue_copy(Queue_Link pointer)
{
    Queue_Link new = queue_initialize(new);
    for(int i = 0 ; i < pointer->count ; i++)
    {
        int temp = queue_dequeue(pointer);
        queue_enqueue(new,temp);
        queue_enqueue(pointer, temp);
    }
    return new;
}

Array_Int queue_to_array(Queue_Link pointer)
{
    int n = pointer->count;
    int* array = malloc(n*sizeof(int));
    for(int i = 0 ; i < n ; i++)
    {
        array[i] = queue_dequeue(pointer);
    }
    return array;
}

void queue_sort(Queue_Link pointer)
{
    int n = pointer->count;
    Array_Int array = queue_to_array(pointer);
    array_quicksort(array, 0, n-1);
    for(int i = 0 ; i < n ; i++)
    {
        queue_enqueue(pointer,array[i]);
    }
    queue_reverse(pointer); //reverse beacuse its in desceding order
}

int main()
{
    Queue_Link entrance = queue_initialize(entrance);

    queue_add(entrance, 1);
    queue_enqueue(entrance, 4);
    queue_add(entrance, 2);
    queue_enqueue(entrance, 3);
    queue_add(entrance, 8);
    queue_add(entrance, 6);
    queue_enqueue(entrance, 5);
    queue_add(entrance, 7); 
    
    queue_print(entrance);

    printf("Copying the  starting queue...\n");
    Queue_Link copy = queue_copy(entrance);
    

    printf("Sorting the queue:\n");
    queue_sort(entrance);
    queue_print(entrance);

    printf("Reversing the queue:\n");
    queue_reverse(entrance);
    queue_print(entrance);

    printf("The starting was:\n");
    queue_print(copy);
    queue_destroy(copy);

    queue_reverse(entrance);
    queue_print(entrance);

    queue_dequeue(entrance);
    queue_print(entrance);

    queue_delete(entrance);
    queue_print(entrance);

    queue_destroy(entrance);

    queue_print(entrance);

    return 0;
}
