#pragma once

typedef struct List* ListLink;
typedef struct ListNode* ListNodeLink;

ListLink list_initialize();
void list_enlist(ListLink pointer, int data);
int list_delist(ListLink pointer);
void list_append(ListLink pointer, int data);
int list_delete(ListLink pointer);
ListLink list_destroy(ListLink pointer);
void list_print(ListLink pointer);
void list_reverse(ListLink pointer);
ListLink list_copy(ListLink pointer);
int* list_to_array(ListLink pointer);
void list_sort(ListLink pointer);