#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Lists.h"
#include "Arrays.h"

typedef struct ListNode
{
    int data;
    struct ListNode* next;
}ListNode;

typedef struct List
{
    int count;
    ListNode* first;
}List;

ListLink list_initialize()
{
    ListLink pointer = malloc(sizeof(List));
    pointer->count = 0;
    pointer->first = NULL;
    return pointer;
}

void list_enlist(ListLink pointer, int data) //create 1 at start
{
    ListNodeLink temp;
    temp = malloc(sizeof(ListNode)); //Create a node as a "package"
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

int list_delist(ListLink pointer) //delete 1 at end
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
        ListNodeLink cursor = pointer->first;
        for(int i = 2 ; i < pointer->count ; i++)
            cursor = cursor->next;

        int temp = cursor->next->data;
        free(cursor->next);
        cursor->next = NULL;
        pointer->count--;
        return temp;
    }
}

void list_append(ListLink pointer, int data)//create 1 at end
{
    ListNodeLink temp;
    temp = malloc(sizeof(ListNode)); //Create a node as a "package"
    temp->data = data;
    temp->next = NULL;

    if(pointer->count == 0)
    {
        pointer->first = temp;
        pointer->count++;
    }
    else
    {
        ListNodeLink cursor = pointer->first;
        while(cursor->next != NULL)
            cursor = cursor->next;
        cursor->next = temp;
        pointer->count++;
    }
}

int list_delete(ListLink pointer)//delete 1 at start
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
        ListNodeLink temp = pointer->first->next;
        int data = pointer->first->data;
        free(pointer->first);
        pointer->first = temp;
        pointer->count--;
        return data;
    }
}

ListLink list_destroy(ListLink pointer)//delete all
{
    int loops = pointer->count;
    for(int i = 0 ; i < loops ; i++)
        list_delist(pointer);
    free(pointer);
    pointer = NULL;
    return pointer;
}

void list_print(ListLink pointer)
{
    if ( !pointer )
    {
        printf("NULL\n");
    }
    else
    {
        ListNodeLink temp = pointer->first;
        for(int i=0 ; i < pointer->count ; i++)
        {
            printf("%d -> ",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void list_reverse(ListLink pointer)
{
    ListNodeLink previous = NULL;
    ListNodeLink current = pointer->first;
    ListNodeLink next = NULL;
    while( current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    pointer->first = previous;
}

ListLink list_copy(ListLink pointer)
{
    ListLink new = list_initialize();

    for(int i = 0 ; i < pointer->count ; i++)
    {
        int temp = list_delist(pointer);
        list_enlist(new,temp);
        list_enlist(pointer, temp);
    }
    return new;
}

ArrayInt list_to_array(ListLink pointer)
{
    int n = pointer->count;
    int* array = malloc(n*sizeof(int));
    for(int i = 0 ; i < n ; i++)
    {
        array[i] = list_delist(pointer);
    }
    return array;
}

void list_sort(ListLink pointer)
{
    int n = pointer->count;
    int* array = list_to_array(pointer);
    array_bubblesort(array, n);
    for(int i = 0 ; i < n ; i++)
    {
        list_enlist(pointer,array[i]);
    }
    list_reverse(pointer); //reverse because its in desceding order
}