typedef struct Queue_Node {
    int data;
    struct Queue_Node* next;
}Queue_Node;

typedef struct Queue {
    int count;
    Queue_Node* first;
}Queue;

typedef int Bool;
#define true 1
#define false 0

typedef Queue* Queue_Link;
typedef Queue_Node* Queue_Node_Link; 

Queue_Link queue_initialize(Queue_Link pointer);
void queue_enqueue(Queue_Link pointer, int data);
int queue_dequeue(Queue_Link pointer);
void queue_destroy(Queue_Link pointer);
void queue_print(Queue_Link pointer);
void queue_reverse(Queue_Link pointer);
Queue_Link queue_copy(Queue_Link pointer);
int* queue_to_array(Queue_Link pointer);
void queue_sort(Queue_Link pointer);

