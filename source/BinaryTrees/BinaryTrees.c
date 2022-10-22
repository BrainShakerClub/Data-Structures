#include <stdio.h>
#include <stdlib.h>
#include "BinaryTrees.h"

void item_show(int x) {    // Print the item 
    printf("%d ", x);
}

// Definition of a Binary Tree 
struct BinaryTree {
            int item;
            BinaryTreeLink left;
            BinaryTreeLink right;
            int N;
        };

BinaryTreeLink binary_tree_make_tree(int item)
{                        // Make a binary tree 
    BinaryTreeLink BinaryTree = malloc(sizeof(*BinaryTree));

    BinaryTree->item = item;
    BinaryTree->left = NULL;
    BinaryTree->right = NULL;
    BinaryTree->N = 1;

    return BinaryTree;                              // Then return it. This allows the user to create multiple binary trees 
}



int binary_tree_root(BinaryTreeLink root)
{      // Return the item at the root of the tree 
    return root->item;
}



BinaryTreeLink binary_tree_parent_of(BinaryTreeLink tree, BinaryTreeLink node)
{                                       // Returns the parent node of a given node 
    BinaryTreeLink ParentNode;                                                        // Get the parent 
    BinaryTreeLink ChildNode = tree;                                                  // Get the child 

    while (ChildNode->item != node->item) {                                 // Repeat until you find the item 
        ParentNode = ChildNode;                                             // Cycle through the tree and update the family 

        if (node->item < ChildNode->item) ChildNode = ChildNode->left;      // If the node item is less than the ChildNode's item, go to left child 
        else ChildNode = ChildNode->right;                                  // Else, go to right child 

        if (ChildNode == NULL) return NULL;                                 // If the item doesn't exist, return NULLitem 
    }

    return ParentNode;                                                      // Return the ParentNode 
}

int binary_tree_parent(BinaryTreeLink tree, BinaryTreeLink node)
{                       // Returns the element at the parent of a node
    if (tree == node) return NULLitem;                      // If inserted root, return NULLitem 

    BinaryTreeLink ParentNode = binary_tree_parent_of(tree, node);                 // Get the parent 
    if (ParentNode != NULL) return ParentNode->item;        // If Parent isn't NULL, return the item at the ParentNode 
    else return NULLitem;                                   // Else, return NULLitem 
}



int binary_tree_sibling(BinaryTreeLink tree, BinaryTreeLink node)
{                                                                  // Returns the element at the sibling of a node
    if (tree == node) return NULLitem;                                                                  // If inserted root, return NULLitem 

    BinaryTreeLink ParentNode = binary_tree_parent_of(tree, node);                                                             // Get the parent 
    if (node == ParentNode->right && ParentNode->left != NULL) return ParentNode->left->item;           // If the sibling is not NULL, return its item 
    else if (node == ParentNode->left && ParentNode->right != NULL) return ParentNode->right->item;
    else return NULLitem;                                                                               // Else, rerturn NULLitem 
}



int binary_tree_is_internal(BinaryTreeLink node)
{                                   // Returns true if a node is an internal node 
    if (node->left == NULL && node->right == NULL) return 0;    // If it has no children, return false 
    else return 1;                                              // Else, return true 
}



int binary_tree_is_external(BinaryTreeLink node)
{                                   // Returns true if a node is an external node 
    if (node->left == NULL && node->right == NULL) return 1;    // If it has no children, return true 
    else return 0;                                              // Else, return false 
}



BinaryTreeLink binary_tree_insert_left(BinaryTreeLink node, int item)
{       // Insert a left child at a given node 
    if (node->left != NULL) {                   // If an old child exists, 
        free(node->left);                       // Free it 
        (node->N)--;                            // Reduce the N value by 1 
    }

    node->left = binary_tree_make_tree(item);              // Add the left child 
    (node->N)++;                                // Increase the N value by 1 
    return node->left;                          // Return the child 
}



BinaryTreeLink binary_tree_insert_right(BinaryTreeLink node, int item)
{      // Insert a right child at a given node 
    if (node->right != NULL) {                  // If an old child exists, 
        free(node->right);                      // Free it 
        (node->N)--;                            // Reduce the N value by 1 
    }

    node->right = binary_tree_make_tree(item);             // Add the right child 
    (node->N)++;                                // Increase the N value by 1 
    return node->right;                         // Return the child 
}



void binary_tree_attach(BinaryTreeLink node, BinaryTreeLink left, BinaryTreeLink right)
{   // Attaches two trees to be subtrees of an external node 
    node->left = left;
    node->right = right;
    node->N = left->N + right->N + 1;               // Don't forget to update N value 
}


void binary_tree_remove(BinaryTreeLink tree, BinaryTreeLink node)
{                                       // Removes a node with zero or one child which is an external node 
    BinaryTreeLink ParentNode = binary_tree_parent_of(tree, node);                                 // Get the parent 
    
    if (node->item < ParentNode->item) {                                    // If the node is the left child of ParentNode, 
        if (binary_tree_is_external(node)) ParentNode->left = NULL;                    // If node is external, make ParentNode pointer NULL 
        else if (node->left != NULL) ParentNode->left = node->left;         // Else if node has a left child, ParentNode now points to left child 
        else ParentNode->left = node->right;                                // Else, ParentNode now points to right child 
    }
    else {                                                                  // Else, 
        if (binary_tree_is_external(node)) ParentNode->right = NULL;                   // If node is external, make ParentNode pointer NULL 
        else if (node->left != NULL) ParentNode->right = node->left;        // Else if node has a left child, ParentNode now points to left child 
        else ParentNode->right = node->right;                               // Else, ParentNode now points to right child 
    }

    free(node);                                                        // In any case, free the node 
}



void binary_tree_destroy(BinaryTreeLink tree)
{     // Free all the nodes of the tree. Do this by visiting them in PostOrder 
    if (tree != NULL) {
        binary_tree_destroy(tree->left);
        binary_tree_destroy(tree->right);
        free(tree);
    }
}



void binary_tree_preorder(BinaryTreeLink tree, void (*visit)(int))
{   // Traverse the tree in PreOrder 
    if (tree != NULL) {
        visit(tree->item);
        binary_tree_preorder(tree->left, visit);
        binary_tree_preorder(tree->right, visit);
    }
}



void binary_tree_inorder(BinaryTreeLink tree, void (*visit)(int))
{    // Traverse the tree in InOrder 
    if (tree != NULL) {
        binary_tree_inorder(tree->left, visit);
        visit(tree->item);
        binary_tree_inorder(tree->right, visit);
    }
}



void binary_tree_postorder(BinaryTreeLink tree, void (*visit)(int))
{  // Traverse the tree in PostOrder 
    if (tree != NULL) {
        binary_tree_postorder(tree->left, visit);
        binary_tree_postorder(tree->right, visit);
        visit(tree->item);
    }
}



// -----Traverse the tree in LevelOrder----- 
void row_print(BinaryTreeLink node, int row, void (*visit)(int))
{        // Visits items in a row starting from left to right 
    if (node == NULL) return;                                   // If the node is NULL, return 

    if (row == 0) visit(node->item);                            // If at the first row, only visit the root 
    else {                                                      // Else, 
        row_print(node->left, row-1, visit);                     // Visit left child 
        row_print(node->right, row-1, visit);                    // Visit right child 
    }
}

void binary_tree_levelorder(BinaryTreeLink tree, void (*visit)(int))
{
    int height = binary_tree_height(tree);        // Get the height of the tree 
    int i;
    for (i = 0; i <= height; i++) {     // Repeat until you reach the last row 
        row_print(tree, i, visit);       // Visit the row 
    }
}
// ----------- 



int binary_tree_height(BinaryTreeLink tree)
{                                   // Returns the height of the tree 
    if (tree == NULL) return NULLitem;                      // If the tree is NULL, return NULLitem 

    int LeftHeight = binary_tree_height(tree->left);                  // Calculate the height of the left sub-tree 
    int RightHeight = binary_tree_height(tree->right);                // Calculate the height of the right sub-tree 

    int max;                                                // Find which one of the sub-trees has the biggest height and add 1 to it 
    if (LeftHeight > RightHeight) max = LeftHeight+1;      
    else max = RightHeight+1;

    return max;                                             // Return the max value 
}



int binary_tree_size(BinaryTreeLink tree)
{     // Returns the number of elements in the tree 
    return tree->N;
}



BinaryTreeLink binary_tree_search(BinaryTreeLink tree, int key)
{                     // Returns the node(pointer) in the tree of a given item 
    BinaryTreeLink node = tree;
    while (node->item != key) {                         // Cycle through the tree 
        if (key < node->item) node = node->left;        // If key is smaller than the node item, go to left child 
        else node = node->right;                        // Else, go to right child 

        if (node == NULL) return NULL;                  // If the item was not found, return NULL 
    }

    return node;                                        // Return the node 
}
