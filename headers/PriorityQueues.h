#pragma once

#define MAXCOUNT 10
typedef struct PriorityQueue* PriorityQueuePointer;

PriorityQueuePointer priority_queue_init(void);
int priority_queue_empty(PriorityQueuePointer);
int priority_queue_full(PriorityQueuePointer);
void priority_queue_insert(int, PriorityQueuePointer);
int priority_queue_remove(PriorityQueuePointer);