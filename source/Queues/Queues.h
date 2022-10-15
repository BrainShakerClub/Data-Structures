typedef struct Node {          
    int data;
    struct Node* next;    
}Node;

typedef struct Queue {
    int count;
    Node* first;
}Queue;

typedef int Bool;
#define true 1
#define false 0

typedef Queue* Queue_Link;
typedef Node* Node_Link; 

Queue_Link queue_initialize(Queue_Link pointer);
void queue_enqueue(Queue_Link pointer, int data);
void queue_print(Queue_Link pointer);
void queue_reverse(Queue_Link pointer);
int queue_dequeue(Queue_Link pointer);
void queue_destroy(Queue_Link pointer);
int queue_delete(Queue_Link pointer);

