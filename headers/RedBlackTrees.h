#pragma once

#define NULLitem -1

typedef struct RBNode* RedBlackTreeLink;

RedBlackTreeLink red_black_tree_initialize();
void red_black_tree_insert_key(RedBlackTreeLink*, int);
void red_black_tree_remove_key(RedBlackTreeLink*, int);
int red_black_tree_search(RedBlackTreeLink, int);
void red_black_tree_print_elements(RedBlackTreeLink);
void red_black_tree_preorder(RedBlackTreeLink);