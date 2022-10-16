typedef struct List_Node {
    int data;
    struct List_Node* next;
}List_Node;

typedef struct List {
    int count;
    List_Node* first;
}List;

typedef int Bool;
#define true 1
#define false 0

typedef List* List_Link;
typedef List_Node* List_Node_Link;

List_Link list_initialize(List_Link pointer);
void list_enlist(List_Link pointer, int data);
int list_delist(List_Link pointer);
void list_destroy(List_Link pointer);
void list_print(List_Link pointer);
void list_reverse(List_Link pointer);
List_Link list_copy(List_Link pointer);
int* list_to_array(List_Link pointer);
void list_sort(List_Link pointer);
