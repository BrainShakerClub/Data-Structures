#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Stacks.h"

typedef struct StackNode
{
    int data;
    struct StackNode *below;
}StackNode;

typedef struct Stack
{
    int count;
    StackNode* top;
}Stack;

StackLink stack_initialize()
{
    StackLink pointer;
    pointer = malloc(sizeof(StackLink));
    pointer->count = 0;
    pointer->top = NULL;
    return pointer;
}

void stack_push(StackLink pointer, int value)
{
    StackNodeLink temp;
    temp = malloc(sizeof(StackNode));
    temp->data = value;

    temp->below = pointer->top; // Making the previous top the below
    pointer->top = temp;
    pointer->count++;
}

int stack_pop(StackLink pointer)
{
    if(pointer->count != 0)
    {
        StackNodeLink temp;
        temp = pointer->top;
        int n = pointer->top->data;
        pointer->top = pointer->top->below;
        free(temp);
        pointer->count--;
        return n;
    } else
    {
        printf("The Stack is empty.\n");
        return -1;
    }
}

Array_Int stack_to_array(StackLink pointer)
{
    int* arr = malloc(pointer->count * sizeof(int*) );
    StackNodeLink temp = pointer->top;
    int n = pointer->count - 1;
    while ( temp != NULL )
    {
        arr[n] = temp->data;
        temp = temp->below;
        n--;
    }
    return arr;
}

StackLink stack_copy(StackLink pointer)
{
    Array_Int array = stack_to_array(pointer);
    StackLink new = stack_initialize();
    for(int i = 0 ; i < pointer->count ; i++)
    {
        stack_push(new, array[i]);
    }
    free(array);
    return new;
}

void stack_clear(StackLink pointer)
{
    printf("Clearing the stack:\n");
    int i = pointer->count;
    while(i > 0)
    {
        printf("Poping -> ( %d )\n", stack_pop(pointer));
        i--;
    }
}

void stack_print(StackLink pointer)
{
    printf("The stack is:\n");
    StackLink new = stack_copy(pointer);
    int i = pointer->count;
    while(i > 0)
    {
        printf("( %d )\n", stack_pop(new));
        i--;
    }
}