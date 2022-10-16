#include <stdio.h>
#include <stdlib.h>
#include "Lists.h"
#include "Arrays.h"

List_Link list_initialize(List_Link pointer) 
{
    pointer = malloc(sizeof(List));
    pointer->count = 0;
    pointer->first = NULL;
    return pointer;
}

void list_enlist(List_Link pointer, int data) //create 1 at start
{
    List_Node_Link temp;
    temp = malloc(sizeof(List_Node)); //Create a node as a "package"
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

int list_delist(List_Link pointer) //delete 1 at end
{
    if(pointer->count == 0)
    {
        printf("ERROR. The List is empty, cant deList a node\n");
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
        List_Node_Link cursor = pointer->first;
        for(int i = 2 ; i < pointer->count ; i++)
            cursor = cursor->next;

        int temp = cursor->next->data;
        free(cursor->next);
        cursor->next = NULL;
        pointer->count--;
        return temp;
    }
}

void list_append(List_Link pointer, int data)//create 1 at end
{
    List_Node_Link temp;
    temp = malloc(sizeof(List_Node)); //Create a node as a "package"
    temp->data = data;
    temp->next = NULL;

    if(pointer->count == 0)
    {
        pointer->first = temp;
        pointer->count++;
    }
    else
    {
        List_Node_Link cursor = pointer->first;
        while(cursor->next != NULL)
            cursor = cursor->next;
        cursor->next = temp;
        pointer->count++;
    }
}

int list_delete(List_Link pointer)//delete 1 at start
{
    if(pointer == NULL) 
    {
        printf("ERROR. The list is empty, cant delete a node\n");
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
        List_Node_Link temp = pointer->first->next;
        int data = pointer->first->data;
        free(pointer->first);
        pointer->first = temp; 
        pointer->count--; 
        return data;
    }
}

void list_destroy(List_Link pointer)//delete all
{
    int loops = pointer->count;
    for(int i = 0 ; i < loops ; i++)
        list_delist(pointer);
    free(pointer);
    pointer = NULL;
}

void list_print(List_Link pointer)
{
    if ( !pointer )
    {
        printf("NULL\n");
    }
    else
    {
        List_Node_Link temp = pointer->first;
        for(int i=0 ; i < pointer->count ; i++)
        {
            printf("%d -> ",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void list_reverse(List_Link pointer)
{
    List_Node_Link previous = NULL;
    List_Node_Link current = pointer->first;
    List_Node_Link next = NULL;
    while( current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    pointer->first = previous;
}

List_Link list_copy(List_Link pointer)
{
    List_Link new = list_initialize(new);
    for(int i = 0 ; i < pointer->count ; i++)
    {
        int temp = list_delist(pointer);
        list_enlist(new,temp);
        list_enlist(pointer, temp);
    }
    return new;
}

Array_Int list_to_array(List_Link pointer)
{
    int n = pointer->count;
    int* array = malloc(n*sizeof(int));
    for(int i = 0 ; i < n ; i++)
    {
        array[i] = list_delist(pointer);
    }
    return array;
}

void list_sort(List_Link pointer)
{
    int n = pointer->count;
    Array_Int array = list_to_array(pointer);
    array_bubblesortarray(pointer, n);
    for(int i = 0 ; i < n ; i++)
    {
        list_enlist(pointer,array[i]);
    }
    list_reverse(pointer); //reverse beacuse its in desceding order
}

int main()
{
    List_Link entrance = list_initialize(entrance);

    list_append(entrance, 1);
    list_enlist(entrance, 4);
    list_append(entrance, 2);
    list_enlist(entrance, 3);
    list_append(entrance, 8);
    list_append(entrance, 6);
    list_enlist(entrance, 5);
    list_append(entrance, 7); 
    
    list_print(entrance);

    printf("Copying the  starting list...\n");
    List_Link copy = list_copy(entrance);
    

    printf("Sorting the list:\n");
    list_sort(entrance);
    list_print(entrance);

    printf("Reversing the list:\n");
    list_reverse(entrance);
    list_print(entrance);

    printf("The starting was:\n");
    list_print(copy);
    list_destroy(copy);

    list_reverse(entrance);
    list_print(entrance);

    list_delist(entrance);
    list_print(entrance);

    list_delete(entrance);
    list_print(entrance);

    list_destroy(entrance);

    list_print(entrance);

    return 0;
}
