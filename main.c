#include <stdio.h>
#include <stdlib.h>
#include "Arrays.h"
#include "Lists.h"
#include "Queues.h"
#include "Stacks.h"

int main()
{
printf("-----------LISTS--------------------\n");
    ListLink entrance = list_initialize();
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
    ListLink copy = list_copy(entrance);
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
    entrance = list_destroy(entrance);
    list_print(entrance);
printf("-----------STACKS--------------------\n");
    StackLink pointer = stack_initialize();
    stack_push(pointer, -1);
    stack_push(pointer, 2);
    stack_push(pointer, 8);
    stack_push(pointer, 4);
    stack_push(pointer, 5);
    stack_push(pointer, 6);
    stack_print(pointer);
    stack_clear(pointer);
    stack_print(pointer);
printf("-----------Queues--------------------\n");
    QueueLink p = queue_initialize();
    queue_enqueue(p, 13);
    queue_enqueue(p, 42);
    queue_enqueue(p, 24);
    queue_enqueue(p, 31);
    queue_enqueue(p, 18);
    queue_enqueue(p, 64);
    queue_enqueue(p, 75);
    queue_enqueue(p, 37);
    queue_print(p);
    printf("Copying the  starting queue...\n");
    QueueLink new = queue_copy(p);
    printf("Sorting the queue:\n");
    queue_sort(p);
    queue_print(p);
    printf("Reversing the queue:\n");
    queue_reverse(p);
    queue_print(p);
    printf("The starting was:\n");
    queue_print(new);
    queue_destroy(new);
    queue_reverse(p);
    queue_print(p);
    queue_dequeue(p);
    queue_print(p);
    
    p = queue_destroy(p);
    queue_print(p);

    return 0;
}


