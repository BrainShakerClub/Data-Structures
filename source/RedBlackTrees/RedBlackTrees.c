#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTrees.h"

#define red 'R'
#define black 'B'

struct RBNode
{
    int item;
    RedBlackTreeLink l, r;
    char color;
};

static RedBlackTreeLink z;

// -----RBinitialize-----
RedBlackTreeLink red_black_tree_new(int item, RedBlackTreeLink l, RedBlackTreeLink r, char color)
{    // Create a new RedBlackTreeLink
    RedBlackTreeLink x = malloc(sizeof *x);
    x->item = item;
    x->l = l;
    x->r = r;
    x->color = color;
    return x;
}

RedBlackTreeLink red_black_tree_initialize()
{                           // Initialize a new red-black tree
    z = red_black_tree_new(NULLitem, NULL, NULL, black);       // Initialize the dummy node
    return z;                                   // Then, return it. This allows the user to create multiple red-black trees
}
// --------------------



// -----red_black_tree_insert_key-----
// rotation auxiliary functions
RedBlackTreeLink rotR(RedBlackTreeLink h)
{
    // Do rotation
    RedBlackTreeLink x = h->l;
    h->l = x->r;
    x->r = h;

    // Return x
    return x;
}

RedBlackTreeLink rotL(RedBlackTreeLink h)
{
    // Do rotation
    RedBlackTreeLink x = h->r;
    h->r = x->l;
    x->l = h;

    // Return x
    return x;
}

void insert_rotations(RedBlackTreeLink *head, RedBlackTreeLink ChildNode, RedBlackTreeLink ParentNode, RedBlackTreeLink GrandparentNode, RedBlackTreeLink Root)
{    // Solve using rotations
    if (GrandparentNode->item > ParentNode->item) {
        if (ParentNode->item < ChildNode->item) GrandparentNode->l = rotL(ParentNode);    // Case example: 30->10->20

        GrandparentNode->color = red;
        GrandparentNode->l->color = black;
        GrandparentNode->l->l->color = red;

        GrandparentNode = rotR(GrandparentNode);    // Case example: 30->20->10

        // Connect the rest of the tree with the rotated part
        if (Root == z) *head = GrandparentNode;
        else if (Root->item > GrandparentNode->item) Root->l = GrandparentNode;
        else Root->r = GrandparentNode;
    }
    else {
        if (ParentNode->item > ChildNode->item) GrandparentNode->r = rotR(ParentNode);    // Case example: 10->20->30

        GrandparentNode->color = red;
        GrandparentNode->r->color = black;
        GrandparentNode->r->r->color = red;

        GrandparentNode = rotL(GrandparentNode);    // Case example: 10->30->20

        // Connect the rest of the tree with the rotated part
        if (Root == z) *head = GrandparentNode;
        else if (Root->item > GrandparentNode->item) Root->l = GrandparentNode;
        else Root->r = GrandparentNode;
    }
}

RedBlackTreeLink red_black_parent_of(RedBlackTreeLink *head, RedBlackTreeLink goal)
{                                  // Find the parent of a given node
    RedBlackTreeLink ParentNode = z;                                                // Create a RedBlackTreeLink to save the parent node
    RedBlackTreeLink ChildNode = *head;                                             // Create a RedBlackTreeLink to save the child node

    while (ChildNode->item != goal->item) {                             // Repeat until you find the appropriate leaf node
        ParentNode = ChildNode;                                         // Save the current child

        if (ChildNode->item > goal->item) ChildNode = ChildNode->l;     // If the inserted item is less than the current node's item, go to left child
        else ChildNode = ChildNode->r;                                  // Else, go to right child
    }
    return ParentNode;                                                  // Return the parent
}

void check_for_double_red(RedBlackTreeLink *head, RedBlackTreeLink ChildNode, RedBlackTreeLink ParentNode, RedBlackTreeLink GrandparentNode, RedBlackTreeLink Root)
{    // Check for double-reds
    // Find the sibling of ParentNode
    RedBlackTreeLink SiblingNode;
    if (GrandparentNode->item < ParentNode->item) SiblingNode = GrandparentNode->l;
    else SiblingNode = GrandparentNode->r;

    // If parent is red and sibling is black, solve double-red using rotations (this is Case 1 according to the lectures)
    if (ParentNode->color == red && SiblingNode->color == black) {
        printf("Unfortunately, a double-red occurs so we need to do some rotations.\n");
        insert_rotations(head, ChildNode, ParentNode, GrandparentNode, Root);
    }

    // If both parent and sibling are red, solve double-red using recoloring (this is Case 2 according to the lectures)
    if (ParentNode->color == red && SiblingNode->color == red) {
        printf("Unfortunately, a double-red occurs so we need to do some recoloring.\n");
        ParentNode->color = black;
        SiblingNode->color = black;
        if (Root != z) GrandparentNode->color = red;

        // Check if another double red occured at GrandparentNode
        // NOTE: Only recolorings can create double-reds at GrandparentNode
        if (Root->color == red && (Root->l->color == red || Root->r->color == red)) {
            RedBlackTreeLink RootDad = red_black_parent_of(head, Root);
            RedBlackTreeLink DadOfRootDad = red_black_parent_of(head, RootDad);
            check_for_double_red(head, GrandparentNode, Root, RootDad, DadOfRootDad);
        }
    }
}

void red_black_tree_insert_key(RedBlackTreeLink *head, int item)
{                      // Insert a new item
    if (*head == z) {                                           // If the tree is empty, insert it at root
        *head = red_black_tree_new(item, z, z, black);
        printf("This is the tree after correct insertion(printed in preorder): ");   // Finish by printing the tree
        red_black_tree_preorder(*head);
        return;
    }

    RedBlackTreeLink Root;                                                  // Else, get the root. This node will be used for RedBlackTreeLinking (root = great-grandparent)
    RedBlackTreeLink GrandparentNode = z;                                   // Get the grandparent (this node will be used for rotations)
    RedBlackTreeLink ParentNode = z;                                        // Get the parent
    RedBlackTreeLink ChildNode = *head;                                     // Get the child

    while (ChildNode != z) {                                    // Repeat until you find the appropriate leaf node
        Root = GrandparentNode;                                 // Cycle through the tree and update the family
        GrandparentNode = ParentNode;
        ParentNode = ChildNode;

        if (item < ChildNode->item) ChildNode = ChildNode->l;   // If the inserted item is less than the current node's item, go to left child
        else ChildNode = ChildNode->r;                          // Else, go to right child
    }

    if (item < ParentNode->item) {                              // If the inserted item is less than the leaf node's item, place item in left child
        ParentNode->l = red_black_tree_new(item, z, z, red);
        ChildNode = ParentNode->l;
    }
    else {                                                      // Else, save to right child
        ParentNode->r = red_black_tree_new(item, z, z, red);
        ChildNode = ParentNode->r;
    }

    // If the tree has height greater than 2, check for double-reds
    if (GrandparentNode != z) check_for_double_red(head, ChildNode, ParentNode, GrandparentNode, Root);

    // Finish by printing the tree
    printf("This is the tree after correct insertion(printed in preorder): ");
    red_black_tree_preorder(*head);
}
// --------------------



// -----red_black_tree_remove_key-----
RedBlackTreeLink remove_rotations(RedBlackTreeLink x, RedBlackTreeLink y, RedBlackTreeLink rchild)
{     // Do appropriate rotations to fix double-black
    if (y->item < x->item){
        if (rchild->item > y->item) x->l = rotL(y);

        x->color = black;
        x->l->color = red;
        x->l->l->color = black;
        return rotR(x);
    }
    else {
        if (rchild->item < y->item) x->r = rotR(y);

        x->color = black;
        x->r->color = red;
        x->r->r->color = black;
        return rotL(x);
    }
}

void fix_double_black(RedBlackTreeLink *head, RedBlackTreeLink r, RedBlackTreeLink x, RedBlackTreeLink GrandparentNode)
{       // Fix double-black
    // Find sibling y
    RedBlackTreeLink y;
    if (x->l == r) y = x->r;
    else y = x->l;

    // If y is black and has a red child, do trinode restructuring (this is Case 1 according to lectures)
    if (y->color == black && (y->l->color == red || y->r->color == red)) {
        printf("Unfortunately, a double-black occurs so we need to do some rotations.\n");
        // rchild is node z found in lectures, but I changed the name because we symbolize z with dummy node :)
        RedBlackTreeLink rchild;
        if (y->l->color == red) rchild = y->l;
        else rchild = y->r;

        // Connect the rest of the tree with the rotated part
        if (x-> item < GrandparentNode->item) GrandparentNode->l = remove_rotations(x, y, rchild);
        else GrandparentNode->r = remove_rotations(x, y, rchild);
    }

    // If y is black with black children, do recoloring (this is Case 2 according to lectures)
    else if (y->color == black && y->l->color != red && y->r->color != red) {
        printf("Unfortunately, a double-black occurs so we need to do some recoloring.\n");
        r->color = black;
        y->color = red;
        if (x->color == red) x->color = black;
        else fix_double_black(head, x, GrandparentNode, red_black_parent_of(head, GrandparentNode));     // If x was black, check again for double-black at node x
    }

    // If y is red, make y parent of x and repaint them (this is Case 3 according to lectures)
    else {
        printf("Unfortunately, a double-black occurs so we need to do some rotations.\n");
        if (x->r == y) {        // Case of y being right child of x
            if (GrandparentNode == *head) *head = rotL(*head);
            else if (x-> item < GrandparentNode->item) GrandparentNode->l = rotL(x);
            else GrandparentNode->r = rotL(x);

            // Repaint them
            y->color = black;
            x->color = red;

            fix_double_black(head, x->l, x, y);       // Check again for double-black
        }
        else {      // Case of y being left child of x
            if (GrandparentNode == *head) *head = rotR(*head);
            else if (x-> item < GrandparentNode->item) GrandparentNode->l = rotR(x);
            else GrandparentNode->r = rotR(x);

            // Repaint them
            y->color = black;
            x->color = red;

            fix_double_black(head, x->r, x, y);       // Check again for double-black
        }
    }
}

void red_black_tree_remove_key(RedBlackTreeLink *head, int item)
{          // Remove an item from a tree
    RedBlackTreeLink GrandparentNode = *head;                   // Get the grandparent (this node will be used for RedBlackTreeLinking)
    RedBlackTreeLink x = *head;                                 // Get the parent
    RedBlackTreeLink v = *head;                                 // Get the child

    while (v->item != item) {                       // Repeat until you find the item
        GrandparentNode = x;                        // Cycle through the tree and update the family
        x = v;

        if (item < v->item) v = v->l;               // If the item we are looking for is less than the current node's item, go to left child
        else v = v->r;                              // Else, go to right child
    }

    if (v->l != z && v->r != z) {                   // If both of v's children are not leaf nodes, find the following node in the inorder traversal
        RedBlackTreeLink root = v;                              // Save the current node
        v = v->r;                                   // Go to right subtree
        while (v->l != z) {                         // Repeat until you find the smallest item
            GrandparentNode = x;                    // Update the family
            x = v;

            v = v->l;                               // Go to leftmost node
        }
        root->item = v->item;                       // Swap labels and perform removal at node v
    }

    RedBlackTreeLink r;                                         // Find r (sibling) and RedBlackTreeLink it with x (parent)
    if (v->r == z) r = v->l;
    else r = v->r;

    if (x->item > v->item) x->l = r;                // RedBlackTreeLink x and r appropriately
    else x->r = r;

    char v_color = v->color;                        // Save color of v before freeing
    free(v);                                        // Free v

    if (v_color == red) {                           // If v was red, we end the removal without violating any properties
        printf("This is the tree after deletion(printed in preorder): ");
        red_black_tree_preorder(*head);
        return;
    }
    else if (r->color == red) r->color = black;     // Else if r is red, color it black
    else if (r->color == black && v_color == black) fix_double_black(head, r, x, GrandparentNode);      // Else if r and v are black, fix double-black

    // Finish by printing the tree
    printf("This is the tree after deletion(printed in preorder): ");
    red_black_tree_preorder(*head);
}



// -----red_black_tree_search-----
int searchR(RedBlackTreeLink h, int item)
{
    if (h == z) return NULLitem;                        // If item was not found, return NULLitem
    if (item == h->item) return h->item;                // If item was found, return it

    if (item < h->item) return searchR(h->l, item);     // If item < h->item, go to left child
    else return searchR(h->r, item);                    // Else, go to right child
}

int red_black_tree_search(RedBlackTreeLink head, int item) {                   // Search for a key using searchR
    return searchR(head, item);
}
// --------------------



// -----red_black_tree_print_elements-----
void inorder(RedBlackTreeLink head)
{
    if (head!=z) {
        inorder(head->l);
        printf("%5d%c ", head->item, head->color);
        inorder(head->r);
    }
}

void red_black_tree_print_elements(RedBlackTreeLink head)
{   // Print all items in ascending order using inorder
    inorder(head);
    printf("\n\n");
}
// --------------------



// -----Helpful function for demonstration purposes in client program-----
void preoder(RedBlackTreeLink head)
{
    if (head!=z) {
        printf("%5d%c ", head->item, head->color);
        preoder(head->l);
        preoder(head->r);
    }
}

void red_black_tree_preorder(RedBlackTreeLink head)
{   // Print all items using preoder
    preoder(head);
    printf("\n\n");
}
// --------------------
