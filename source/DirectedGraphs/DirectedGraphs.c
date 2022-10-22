#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DirectedGraphs.h"
#include "PriorityQueues.h"

typedef struct edge  *EdgePtr;

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


// -----directed_graph_initialize----- 
EdgePtr directed_graph_dummy(void)
{                   // Returns a dummy edge. Dummy edges are noted by endpoint=-1 and nextedge=NULL 
    EdgePtr E = malloc(sizeof(*E));
    E->endpoint = -1;
    E->nextedge = NULL;
    return E;
}

DirectedGraph directed_graph_initialize(int size)
{            // Initialize a graph by filling it with dummy edges 
    DirectedGraph G = malloc(sizeof(*G));
    G->n = size;
    for (int i = 0 ; i < MAXVERTEX ; i++) {
        G->firstedge[i] = directed_graph_dummy();
    }
    return G;
}
// -----END----- 


// -----directed_graph_insert_edge----- 
EdgePtr directed_graph_new(Vertex v, EdgePtr next)
{   // Returns an edge with edgepoint=v and nextedge=next 
    EdgePtr E = malloc(sizeof(*E));
    E->endpoint = v;
    E->nextedge = next;
    return E;
}

void directed_graph_insert_edge(DirectedGraph G, char *Given_Edge)
{    // Inserts an edge to the graph 
    char temp_given_edge[4];                            // Create a temp string in order to use strtok later 
    strcpy(temp_given_edge, Given_Edge);                // Copy the given string to the temp string 
    const char s[2] = "-";                              // Strings used by strtok 
    char *token;

    token = strtok(temp_given_edge, s);                 // Do strtok to get starting and ending vertex 
    Vertex starting_vertex = atoi(token);
    token = strtok(NULL, s);
    Vertex ending_vertex = atoi(token);

    // If starting or ending vertex is out of bounds, print error 
    if (starting_vertex >= G->n || ending_vertex >= G->n) {
        printf("Cannot insert edge(either starting or ending vertex is greater than graph size)\n");
        return;
    }

    EdgePtr Current = G->firstedge[starting_vertex];
    // If this is the first endpoint, insert it directly 
    if (Current->endpoint == -1) {
        Current->endpoint = ending_vertex;
        Current->nextedge = directed_graph_dummy();
        return;
    }

    // Else, for every endpoint don't forget to follow the natural order 
    while (Current->endpoint != -1) {
        if (Current->endpoint > ending_vertex) {
            EdgePtr New = directed_graph_new(Current->endpoint, Current->nextedge);
            Current->endpoint = ending_vertex;
            Current->nextedge = New;
            return;
        }
        else Current = Current->nextedge;
    }
    Current->endpoint = ending_vertex;
    Current->nextedge = directed_graph_dummy();
}
// -----END----- 


// -----directed_graph_show_graph----- 
void directed_graph_show_graph(DirectedGraph G)
{               // Prints the graph 
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


// -----directed_graph_depth_first----- 
void directed_graph_vertex_show(Vertex x)
{
    printf("%d ", x);
}

void traverse(DirectedGraph G, Vertex v, int visited[], void (*Visit)(Vertex x))
{
    Vertex w;
    Edge *curedge;
    visited[v]=1;
    Visit(v);
    curedge=G->firstedge[v]; // curedge is a pointer to the first edge (v,_) of V 
    while (curedge->endpoint != -1){
        w=curedge->endpoint; // w is a successor of v and (v,w) is the current edge 
        if (!visited[w]) traverse(G, w, visited, Visit);
        curedge=curedge->nextedge; //curedge is a pointer to the next edge (v,_) of V 
    }
}

void directed_graph_depth_first(DirectedGraph G, void (*Visit)(Vertex x))
{  // Searches a graph according to the recursive DFS algorithm found in Lecture 16 
    int visited[MAXVERTEX];
    Vertex v;

    for (v=0; v < G->n; v++)
        visited[v]=0;
    for (v=0; v < G->n; v++)
        if (!visited[v]) traverse(G, v, visited, Visit);
    printf("\n");
}
// -----END----- 


// -----directed_graph_breadth_top_sort----- 
typedef Vertex Toporder[MAXVERTEX];

void directed_graph_breadth_top_sort(DirectedGraph G)
{  // Prints a topological sort of graph G according to the algorithm found in Lecture 16 
    Toporder T;
    int predecessorcount[MAXVERTEX]; // number of predecessors of each vertex 
                                    // (the array D of the previous algorithm) 
    // initialize a queue 
    PriorityQueuePointer Q = priority_queue_init();
    Vertex v, succ;
    Edge *curedge;
    int place;

    // initialize all the predecessor counts to 0 
    for (v=0; v < G->n; v++)
        predecessorcount[v]=0;

    // increase the predecessor count for each vertex that is a successor of another one 
    for (v=0; v < G->n; v++)
        for (curedge=G->firstedge[v]; curedge->endpoint != -1; curedge=curedge->nextedge)
            predecessorcount[curedge->endpoint]++;

    // place all vertices with no predecessors into the queue 
    for (v=0; v < G->n; v++)
        if (predecessorcount[v]==0) {
            priority_queue_insert(v, Q);
        }

    // start the breadth-first traversal 
    place=-1;

    while (!priority_queue_empty(Q)) {
        // visit v by placing it into the topological order 
        v = priority_queue_remove(Q);
        place++;
        T[place]=v;
        // traverse the list of successors of v 

        for (curedge=G->firstedge[v]; curedge->endpoint != -1; curedge=curedge->nextedge){
            // reduce the predecessor count for each successor 
            succ=curedge->endpoint;
            predecessorcount[succ]--;
            if (predecessorcount[succ]==0)
                // succ has no further predecessors, so it is ready to process 
                priority_queue_insert(succ, Q);
        }
    }

    // Lastly, print the Topological Sort 
    for (int i = 0 ; i < G->n ; i++) {
        printf("%d ", T[i]);
    }
    printf("\n");
}
// -----END----- 


// -----GRAPH REVERSE----- 
DirectedGraph directed_graph_reverse(DirectedGraph G)
{       // Returns a reversed graph 
    DirectedGraph K = directed_graph_initialize(G->n);    // Initialize a new graph K. This will be returned 
    char reversed_edge[4] = "0-0";
    EdgePtr Temp;

    for (int i = 0 ; i < G->n ; i++) {  // Reverse G by inserting the reversed edges to K 
        Temp = G->firstedge[i];
        reversed_edge[2] = i + '0';
        while (Temp->endpoint != -1) {
            reversed_edge[0] = Temp->endpoint + '0';
            directed_graph_insert_edge(K, reversed_edge);
            Temp = Temp->nextedge;
        }
    }
    return K;   // Return K 
}
// -----END----- 
