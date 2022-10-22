#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UndirectedGraphs.h" 

typedef struct edge* EdgePtr;

typedef struct edge 
{
    Vertex endpoint;
    EdgePtr nextedge;
} Edge;

struct graph 
{
    int n; //number of vertices in graph 
    EdgePtr firstedge[MAXVERTEX];
};

// -----Sperific stack for the undirected graph-----
typedef struct StackNodeTag 
{
    int Item;
    struct StackNodeTag *Link;
} StackNode;

struct Stack 
{
    StackNode* ItemList;
};

typedef struct Stack *StackPointer;

StackPointer undirected_stack_init() 
{                      // Create a stack and return it 
    StackPointer S = malloc(sizeof(*S));
    S->ItemList = NULL;
    return S;
}

int undirected_stack_empty(StackPointer S) 
{        // Check if the stack is empty 
    return (S->ItemList == NULL);
}

void undirected_stack_push(int Item, StackPointer S)
 {                     // Push an item to the stack 
    StackNode *Temp;                                                // Create a new node 
    Temp = malloc(sizeof(StackNode));

    if (Temp == NULL) printf("System storage is exhausted.\n");     // If malloc failed, print error message 
    else {                                                          // Else, 
        Temp->Item = Item;                                          // Initialize Temp 
        Temp->Link = S->ItemList;                                   
        S->ItemList = Temp;                                         // Temp is now the first node of the stack 
    }
}

int undirected_stack_pop(StackPointer S) 
{                                                     // Pop the first item from the stack 
    if (S->ItemList == NULL) {
        printf("Cannot pop an item from an empty stack.\n");       // If the stack is empty, print error message 
        return -1;
    }
    else {                                                                              // Else, 
        int Item = S->ItemList->Item;                                              // Save the item 
        
        StackNode *Temp;                                                                // Create a Temp node to save the address 
        Temp = S->ItemList;

        S->ItemList = Temp->Link;                                                       // Stack now points to second node 
        free(Temp);                                                                     // Free Temp 

        return Item;                                                                    // Return the item 
    }
}
// -----END----- 


// -----INITIALIZE----- 
EdgePtr undirected_graph_dummy(void)
{                   // Initializes and returns a dummy node 
    EdgePtr E = malloc(sizeof(*E));
    E->endpoint = -1;
    E->nextedge = NULL;
    return E;
}

UndirectedGraph undirected_graph_initialize(int size)
{    // Initializes a graph 
    UndirectedGraph G = malloc(sizeof(*G));               // Initialize the graph     
    G->n = size;
    for (int i = 0 ; i < MAXVERTEX ; i++) {     // Fill it with dummies 
        G->firstedge[i] = undirected_graph_dummy();
    }
    return G;                                   // And return it. This allows the user to create multiple graphs 
}
// -----END----- 


// -----INSERT EDGE----- 
EdgePtr undirected_graph_new(Vertex v, EdgePtr next)
{   // Returns an edge with v as its endpoint. It also points to next 
    EdgePtr E = malloc(sizeof(*E));
    E->endpoint = v;
    E->nextedge = next;
    return E;
}

void undirected_graph_insert(UndirectedGraph G, Vertex starting_vertex, Vertex ending_vertex)
{    // Same exact algorithm as seen in directed graphs 
    if (starting_vertex >= G->n || ending_vertex >= G->n) {
        printf("Cannot insert edge(either starting or ending vertex is greater than graph size)\n");
        return;
    }

    EdgePtr Current = G->firstedge[starting_vertex];        
    // If this is the first endpoint, insert it directly 
    if (Current->endpoint == -1) {          
        Current->endpoint = ending_vertex;
        Current->nextedge = undirected_graph_dummy();
        return;
    }

    // Else, for every endpoint don't forget to follow the natural order 
    while (Current->endpoint != -1) {
        if (Current->endpoint > ending_vertex) {
            EdgePtr New = undirected_graph_new(Current->endpoint, Current->nextedge);
            Current->endpoint = ending_vertex;
            Current->nextedge = New;
            return;
        }
        else Current = Current->nextedge;
    }
    Current->endpoint = ending_vertex;
    Current->nextedge = undirected_graph_dummy();
}

void undirected_graph_insert_edge(UndirectedGraph G, char *Given_Edge)
{    // Insert both the given edge and the reverse edge to the graph  
    const char s[2] = "-";  // Strings used by strtok 
    char *token;

    token = strtok(Given_Edge, s);
    Vertex start = atoi(token);
    token = strtok(NULL, s);
    Vertex end = atoi(token);

    undirected_graph_insert(G, start, end);
    undirected_graph_insert(G, end, start);
}
// -----END----- 


// -----SHOW GRAPH----- 
void undirected_graph_show_graph(UndirectedGraph G)
{       // Same exact algorithm as seen in question 1 
    printf("Vertex | Adjacency List\n");
    EdgePtr Temp;

    for (int i = 0 ; i < G->n ; i++) {
        printf("  %d   ->  ", i);
        Temp = G->firstedge[i];
        while (Temp->endpoint != -1) {
            printf("%d ", Temp->endpoint);
            Temp = Temp->nextedge;
        }
        printf("\n");
    }
}
// -----END----- 


// -----SIMPLE PATH CHECK----- 
int undirected_graph_path_rec(UndirectedGraph G, Vertex v, Vertex end, Vertex visited[], StackPointer S)
{  // Checks if a simple path exists recursively 
    EdgePtr Current = G->firstedge[v];
    visited[v] = 1;                                                             // Mark the vertex you visit each time 
    undirected_stack_push(v, S);                                                            // Add it to the stack 

    while (Current->endpoint != -1) {                                           // Repeat until you have checked all edges 
        if (Current->endpoint == end) {                                         // If the endpoint was reached, 
            undirected_stack_push(Current->endpoint, S);                                    // add it to the stack 
            return 1;                                                           // and return success code 
        }

        while (visited[Current->endpoint]) {                                    // Search for the next unvisited vertex 
            Current = Current->nextedge;
            if (Current->endpoint == -1) {                                      // If none were found, 
                undirected_stack_pop(S);                                                    // remove the current endpoint from the stack 
                return 0;                                                       // and return failure code 
            }
            if (Current->endpoint == end) {                                     // Check again for endpoint 
                undirected_stack_push(Current->endpoint, S);
                return 1;
            }
        }

        int flag = undirected_graph_path_rec(G, Current->endpoint, end, visited, S);              // Repeat the process for the next edge 
        
        if (flag) return 1;                                                     // If search was successful, return success code 
        else Current = Current->nextedge;                                       // Else, go to next vertex 
    }
    undirected_stack_pop(S);                                                                // If none of the above worked, remove the vertex from the stack 
    return 0;                                                                   // and return failure code 
}

void undirected_graph_simple_path_check(UndirectedGraph G, Vertex start, Vertex end)
{   // Checks if the simple path exists 
    if (start == end) {
        printf("Cannot calculate simple path(vertices must be different)\n");
        return;
    }
    if (start >= G->n || end >= G->n) {
        printf("Cannot calculate simple path(either starting or ending vertex is greater than graph size)\n");
        return;
    }

    // Initialize a boolean array to check if a vertex is visited or not 
    Vertex visited[G->n];
    for (int i = 0 ; i < G->n ; i++) {
        visited[i] = 0;
    }

    StackPointer S = undirected_stack_init();                                   // Initialize a stack to save the simple path 
    int found = undirected_graph_path_rec(G, start, end, visited, S);                 // Check for path recursively 
    if (found) {                                                    // If the path was found, 
        Vertex temp[G->n];
        int i;
        for (i = G->n - 1 ; i >= 0 ; i--) {                         // Initialize an array. This is used to reverse the stack 
            temp[i] = -1;
            if (!undirected_stack_empty(S)) temp[i] = undirected_stack_pop(S);
        }
        printf("The simple path from %d to %d is: ", start, end);   // Print the path normally 
        for (i = 0 ; i < G->n ; i++) {
            if (temp[i] != -1) printf("%d ", temp[i]);
        }
        printf("\n");
    }
    else printf("No simple path was found\n");                      // Else, state that no simple path was found 
}
// -----END----- 
