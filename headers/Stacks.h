typedef struct Stack_Node 
{          
    int data;
    struct Stack_Node *below;    
}Stack_Node;

typedef struct Stack
{
    int count;
    Stack_Node* top;
}Stack;

typedef Stack* Stack_Link;
typedef Stack_Node* Stack_Node_Link;
typedef int* Array_Int;

Stack_Link stack_initialize(Stack_Link p);
void stack_push(Stack_Link p, int value);
int stack_pop(Stack_Link S);
Array_Int stack_to_array(Stack_Link pointer);
Stack_Link stack_copy(Stack_Link pointer);
void stack_clear(Stack_Link pointer);
void stack_print(Stack_Link S ); 
