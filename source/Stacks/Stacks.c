#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Stacks.h"

Stack_Link stack_initialize(Stack_Link pointer)
{
    pointer = malloc(sizeof(Stack_Link));
    pointer->count = 0;   
    pointer->top = NULL; 
} 

void stack_push(Stack_Link pointer, int value)
{
    Stack_Node_Link temp;
    temp = malloc(sizeof(Stack_Node));
    temp->data = value;

    temp->below = pointer->top; // Making the previous top the below
    pointer->top = temp;
    pointer->count++;
}

int stack_pop(Stack_Link pointer)
{
    if(pointer->count != 0) 
    {
        Stack_Node_Link temp;
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

Array_Int stack_to_array(Stack_Link pointer)
{
    int* arr = malloc(pointer->count * sizeof(int*) );
    Stack_Node_Link temp = pointer->top;
    int n = pointer->count - 1;
    while ( temp != NULL )
    {
        arr[n] = temp->data;
        temp = temp->below;
        n--;
    }
    return arr;
}

Stack_Link stack_copy(Stack_Link pointer)
{  
    Array_Int array = stack_to_array(pointer);
    Stack_Link new = stack_initialize(new);
    for(int i = 0 ; i < pointer->count ; i++)
    {
        stack_push(new, array[i]);
    }
    free(array);
    return new;
}

void stack_clear(Stack_Link pointer)
{
    printf("Clearing the stack:\n");
    int i = pointer->count;
    while(i > 0) 
    {
        printf("Poping -> ( %d )\n", stack_pop(pointer));
        i--;
    }
}

void stack_print(Stack_Link pointer)
{
    printf("The stack is:\n");
    Stack_Link new = stack_copy(pointer);
    int i = pointer->count;
    while(i > 0) 
    {
        printf("( %d )\n", stack_pop(new));
        i--;
    }
}

int main()
{
    Stack_Link pointer = stack_initialize(pointer);
    stack_push(pointer, -1);
    stack_push(pointer, 2);
    stack_push(pointer, 8);
    stack_push(pointer, 4);
    stack_push(pointer, 5);
    stack_push(pointer, 6);
    
    stack_print(pointer);
    stack_clear(pointer);

}