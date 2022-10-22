#pragma once

#define MAXVERTEX 10

typedef int Vertex;
typedef struct graph* UndirectedGraph;

UndirectedGraph undirected_graph_initialize(int size);
void undirected_graph_insert_edge(UndirectedGraph G, char *Given_Edge);
void undirected_graph_show_graph(UndirectedGraph G);
void undirected_graph_simple_path_check(UndirectedGraph G, Vertex start, Vertex end);