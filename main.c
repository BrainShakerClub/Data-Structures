#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Arrays.h"
#include "Lists.h"
#include "Queues.h"
#include "Stacks.h"
#include "BinaryTrees.h"
#include "RedBlackTrees.h"
#include "PriorityQueues.h"
#include "DirectedGraphs.h"
#include "UndirectedGraphs.h"
#include "HashTable.h"

// THIS IS AN EXAMPLE ON HOW TO USE AND COMPILE THE LIBRARY

int main(void)
{
printf("-----------LISTS--------------------\n");
    ListLink entrance = list_initialize();
    list_append(entrance, 1);
    list_enlist(entrance, 4);
    list_append(entrance, 2);
    list_enlist(entrance, 3);
    list_append(entrance, 8);
    list_append(entrance, 6);
    list_enlist(entrance, 5);
    list_append(entrance, 7);
    list_print(entrance);
    printf("Copying the  starting list...\n");
    ListLink copy = list_copy(entrance);
    printf("Sorting the list:\n");
    list_sort(entrance);
    list_print(entrance);
    printf("Reversing the list:\n");
    list_reverse(entrance);
    list_print(entrance);
    printf("The starting was:\n");
    list_print(copy);
    list_destroy(copy);
    list_reverse(entrance);
    list_print(entrance);
    list_delist(entrance);
    list_print(entrance);
    list_delete(entrance);
    list_print(entrance);
    entrance = list_destroy(entrance);
    list_print(entrance);
printf("-----------STACKS--------------------\n");
    StackLink pointer = stack_initialize();
    stack_push(pointer, -1);
    stack_push(pointer, 2);
    stack_push(pointer, 8);
    stack_push(pointer, 4);
    stack_push(pointer, 5);
    stack_push(pointer, 6);
    stack_print(pointer);
    stack_clear(pointer);
    stack_print(pointer);
printf("-----------Queues--------------------\n");
    QueueLink p = queue_initialize();
    queue_enqueue(p, 13);
    queue_enqueue(p, 42);
    queue_enqueue(p, 24);
    queue_enqueue(p, 31);
    queue_enqueue(p, 18);
    queue_enqueue(p, 64);
    queue_enqueue(p, 75);
    queue_enqueue(p, 37);
    queue_print(p);
    printf("Copying the  starting queue...\n");
    QueueLink new = queue_copy(p);
    printf("Sorting the queue:\n");
    queue_sort(p);
    queue_print(p);
    printf("Reversing the queue:\n");
    queue_reverse(p);
    queue_print(p);
    printf("The starting was:\n");
    queue_print(new);
    queue_destroy(new);
    queue_reverse(p);
    queue_print(p);
    queue_dequeue(p);
    queue_print(p);

    p = queue_destroy(p);
    queue_print(p);

printf("-----------BINARY TREES--------------------\n");
    BinaryTreeLink TreeA = binary_tree_make_tree(2);
    printf("Initializing TreeA. The root item of TreeA is: %d\n", binary_tree_root(TreeA));

    printf("Inserting item 1 in TreeA as left child\n");
    BinaryTreeLink TreeA_One = binary_tree_insert_left(TreeA, 1);
    printf("Inserting item 3 in TreeA as right child\n");
    binary_tree_insert_right(TreeA, 3);

    printf("The parent item of item 1 in TreeA is %d and its sibling is %d\n", binary_tree_parent(TreeA, TreeA_One), binary_tree_sibling(TreeA, TreeA_One));
    printf("Height and size of TreeA are %d and %d respectively\n", binary_tree_height(TreeA), binary_tree_size(TreeA));

    printf("PreOrder of TreeA is: ");
    binary_tree_preorder(TreeA, item_show); printf("\n");
    printf("InOrder of TreeA is: ");
    binary_tree_inorder(TreeA, item_show); printf("\n");
    printf("PostOrder of TreeA is: ");
    binary_tree_postorder(TreeA, item_show); printf("\n");
    printf("LevelOrder of TreeA is: ");
    binary_tree_levelorder(TreeA, item_show); printf("\n");


    printf("\n\n");


    BinaryTreeLink TreeB = binary_tree_make_tree(6);
    printf("Initializing TreeB. The root item of TreeB is: %d\n", binary_tree_root(TreeB));

    printf("Inserting item 5 in TreeB as left child\n");
    binary_tree_insert_left(TreeB, 5);
    printf("Inserting item 7 in TreeB as right child\n");
    BinaryTreeLink TreeB_Seven = binary_tree_insert_right(TreeB, 7);

    printf("The parent of item 7 in TreeB is %d and its sibling is %d\n", binary_tree_parent(TreeB, TreeB_Seven), binary_tree_sibling(TreeB, TreeB_Seven));
    printf("Height and size of TreeB are %d and %d respectively\n", binary_tree_height(TreeB), binary_tree_size(TreeB));

    printf("PreOrder of TreeB is: ");
    binary_tree_preorder(TreeB, item_show); printf("\n");
    printf("InOrder of TreeB is: ");
    binary_tree_inorder(TreeB, item_show); printf("\n");
    printf("PostOrder of TreeB is: ");
    binary_tree_postorder(TreeB, item_show); printf("\n");
    printf("LevelOrder of TreeB is: ");
    binary_tree_levelorder(TreeB, item_show); printf("\n");


    printf("\n\n");


    BinaryTreeLink TreeC = binary_tree_make_tree(4);
    printf("Initializing TreeC. The root item of TreeC is: %d\n", binary_tree_root(TreeC));

    printf("Attaching TreeA and TreeB to be left and right children of TreeC\n");
    binary_tree_attach(TreeC, TreeA, TreeB);

    printf("Height and size of TreeC are %d and %d respectively\n", binary_tree_height(TreeC), binary_tree_size(TreeC));

    printf("PreOrder of TreeC is: ");
    binary_tree_preorder(TreeC, item_show); printf("\n");
    printf("InOrder of TreeC is: ");
    binary_tree_inorder(TreeC, item_show); printf("\n");
    printf("PostOrder of TreeC is: ");
    binary_tree_postorder(TreeC, item_show); printf("\n");
    printf("LevelOrder of TreeC is: ");
    binary_tree_levelorder(TreeC, item_show); printf("\n\n");

    printf("Searching for item 6 in TreeC... ");
    if (binary_tree_search(TreeC, 6) != NULL) printf("Found!\n\n");
    else printf("Not found.\n\n");

    printf("Now removing 7 from TreeC\n");
    binary_tree_remove(TreeC, TreeB_Seven);
    printf("PreOrder of TreeC is: ");
    binary_tree_preorder(TreeC, item_show); printf("\n");
    printf("InOrder of TreeC is: ");
    binary_tree_inorder(TreeC, item_show); printf("\n");
    printf("PostOrder of TreeC is: ");
    binary_tree_postorder(TreeC, item_show); printf("\n");
    printf("LevelOrder of TreeC is: ");
    binary_tree_levelorder(TreeC, item_show); printf("\n\n");

    printf("Now removing 6 from TreeC\n");
    binary_tree_remove(TreeC, TreeB);
    printf("PreOrder of TreeC is: ");
    binary_tree_preorder(TreeC, item_show); printf("\n");
    printf("InOrder of TreeC is: ");
    binary_tree_inorder(TreeC, item_show); printf("\n");
    printf("PostOrder of TreeC is: ");
    binary_tree_postorder(TreeC, item_show); printf("\n");
    printf("LevelOrder of TreeC is: ");
    binary_tree_levelorder(TreeC, item_show); printf("\n\n");

    printf("Searching for item 6 in TreeC... ");
    if (binary_tree_search(TreeC, 6) != NULL) printf("Found!\n");
    else printf("Not found.\n");

    printf("Destroying TreeC by freeing all of its nodes\n");
    binary_tree_destroy(TreeC);


printf("-----------RED BLACK TREES--------------------\n");
    printf("Initializing empty tree\n");
    RedBlackTreeLink RB = red_black_tree_initialize();

    printf("Inserting item 4\n");
    red_black_tree_insert_key(&RB, 4);

    printf("Inserting item 7\n");
    red_black_tree_insert_key(&RB, 7);

    printf("Inserting item 12\n");
    red_black_tree_insert_key(&RB, 12);

    printf("Inserting item 15\n");
    red_black_tree_insert_key(&RB, 15);

    printf("Inserting item 3\n");
    red_black_tree_insert_key(&RB, 3);

    printf("Inserting item 5\n");
    red_black_tree_insert_key(&RB, 5);

    printf("Inserting item 14\n");
    red_black_tree_insert_key(&RB, 14);

    printf("Inserting item 18\n");
    red_black_tree_insert_key(&RB, 18);

    printf("Inserting item 16\n");
    red_black_tree_insert_key(&RB, 16);

    printf("Inserting item 17\n");
    red_black_tree_insert_key(&RB, 17);

    printf("Item 12 was%sfound in tree\n", (red_black_tree_search(RB, 12) == NULLitem) ? " not " : " ");
    printf("Item 33 was%sfound in tree\n", (red_black_tree_search(RB, 33) == NULLitem) ? " not " : " ");
    printf("Now printing keys in ascending order using red_black_tree_print_elements: ");
    red_black_tree_print_elements(RB);

    printf("Removing item 3\n");
    red_black_tree_remove_key(&RB, 3);

    printf("Removing item 12\n");
    red_black_tree_remove_key(&RB, 12);

    printf("Removing item 17\n");
    red_black_tree_remove_key(&RB, 17);

    printf("Removing item 18\n");
    red_black_tree_remove_key(&RB, 18);

    printf("Removing item 15\n");
    red_black_tree_remove_key(&RB, 15);

    printf("Removing item 16\n");
    red_black_tree_remove_key(&RB, 16);

    printf("Item 12 was%sfound in tree\n", (red_black_tree_search(RB, 12) == NULLitem) ? " not " : " ");
    printf("Item 33 was%sfound in tree\n", (red_black_tree_search(RB, 33) == NULLitem) ? " not " : " ");
    printf("Now printing keys in ascending order using red_black_tree_print_elements: ");
    red_black_tree_print_elements(RB);


printf("-----------DIRECTED GRAPHS--------------------\n");
    FILE* file1;
    file1 = fopen("./assets/graph_examples/DirectedGraph.txt", "r");
    if (file1 == NULL) {
        printf("File can't be opened. Exiting...\n");
        return 1;
    }

    char line[100];
    fgets(line,sizeof line, file1);
    int size = atoi(line);
    if (size > MAXVERTEX) {
        printf("Sorry, max amount of vertices is %d. Exiting...\n", MAXVERTEX);
        return -1;
    }
    DirectedGraph G = directed_graph_initialize(size);

    while(fgets(line,sizeof line, file1)!= NULL) {
        line[strcspn(line, "\n")] = 0;
        printf("Now inserting %s\n", line);
        directed_graph_insert_edge(G, line);
        printf("The graph is:\n");
        directed_graph_show_graph(G); printf("\n");
    }

    printf("\nNow reversing the graph. The reversed graph is:\n");
    DirectedGraph K = directed_graph_reverse(G);
    directed_graph_show_graph(K);

    printf("DFS Traversal of G is: ");
    directed_graph_depth_first(G, directed_graph_vertex_show);

    printf("Topological sort of G is: ");
    directed_graph_breadth_top_sort(G);

    fclose(file1);

printf("-----------UNDIRECTED GRAPHS--------------------\n");
    FILE* file2;
    file2 = fopen("./assets/graph_examples/UndirectedGraph.txt", "r");
    if (file2 == NULL) {
        printf("File can't be opened. Exiting...\n");
        return 1;
    }

    fgets(line,sizeof line, file2);
    size = atoi(line);
    if (size > MAXVERTEX) {
        printf("Sorry, max amount of vertices is %d. Exiting...\n", MAXVERTEX);
        return -1;
    }

    UndirectedGraph UG = undirected_graph_initialize(size);

    while(fgets(line,sizeof line,file2)!= NULL) {
        line[strcspn(line, "\n")] = 0;
        printf("Now inserting %s\n", line);
        undirected_graph_insert_edge(UG, line);
        printf("The graph is:\n");
        undirected_graph_show_graph(UG); printf("\n");
    }

    printf("Let's see if a simple path exists from 1 to 6\n");
    undirected_graph_simple_path_check(UG, 1, 6);
    printf("\nLet's see if a simple path exists from 1 to 0\n");
    undirected_graph_simple_path_check(UG, 1, 0);
    printf("\nLet's see if a simple path exists from 2 to 7\n");
    undirected_graph_simple_path_check(UG, 2, 7);
    fclose(file1);

printf("\n-----------HASH TABLE(linear probing)--------------------\n");
    HashTable ht = hash_initialize();

    // test insert
    srand(time(NULL));
    for (int i = 0; i < 1000; i++)
        hash_insert(ht, i);

    // test search
    if (!hash_search(ht, 0))
        printf("ERROR\n");

    // test size
    if (hash_size(ht) != 1000)
        printf("ERROR\n");

    // test remove
    for (int i = 0; i < 1000; i++)
        if (!hash_remove(ht, i))
            printf("ERROR\n");

    if (hash_size(ht) > 0)
        printf("ERROR\n");

    hash_destroy(ht);
    printf("Hash Table passed all tests!\n");

    return 0;
}


