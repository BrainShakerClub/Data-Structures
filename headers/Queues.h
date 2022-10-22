#pragma once

typedef struct Queue* QueueLink;
typedef struct QueueNode* QueueNodeLink; 

QueueLink queue_initialize();
void queue_enqueue(QueueLink pointer, int data);
int queue_dequeue(QueueLink pointer);
QueueLink queue_destroy(QueueLink pointer);
void queue_print(QueueLink pointer);
void queue_reverse(QueueLink pointer);
QueueLink queue_copy(QueueLink pointer);
int* queue_to_array(QueueLink pointer);
void queue_sort(QueueLink pointer);