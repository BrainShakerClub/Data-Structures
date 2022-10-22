#pragma once

typedef struct Stack* StackLink;
typedef struct StackNode* StackNodeLink;
typedef int* Array_Int;

StackLink stack_initialize();
void stack_push(StackLink p, int value);
int stack_pop(StackLink S);
Array_Int stack_to_array(StackLink pointer);
StackLink stack_copy(StackLink pointer);
void stack_clear(StackLink pointer);
void stack_print(StackLink S ); 