#pragma once
#define NULLitem -1

typedef struct BinaryTree* BinaryTreeLink;

void item_show(int x);

BinaryTreeLink binary_tree_make_tree(int item);
int binary_tree_root(BinaryTreeLink root);
int binary_tree_parent(BinaryTreeLink tree, BinaryTreeLink node);
int binary_tree_sibling(BinaryTreeLink tree, BinaryTreeLink node);
int binary_tree_is_internal(BinaryTreeLink node);
int binary_tree_is_external(BinaryTreeLink node);
BinaryTreeLink binary_tree_insert_left(BinaryTreeLink node, int item);
BinaryTreeLink binary_tree_insert_right(BinaryTreeLink node, int item);
void binary_tree_attach(BinaryTreeLink node, BinaryTreeLink left, BinaryTreeLink right);
void binary_tree_remove(BinaryTreeLink tree, BinaryTreeLink node);
void binary_tree_destroy(BinaryTreeLink tree);
void binary_tree_preorder(BinaryTreeLink tree, void (*visit)(int));
void binary_tree_inorder(BinaryTreeLink tree, void (*visit)(int));
void binary_tree_postorder(BinaryTreeLink tree, void (*visit)(int));
void binary_tree_levelorder(BinaryTreeLink tree, void (*visit)(int));
int binary_tree_height(BinaryTreeLink tree);
int binary_tree_size(BinaryTreeLink tree);
BinaryTreeLink binary_tree_search(BinaryTreeLink tree, int key);