#pragma once

#define MAXVERTEX 10

typedef int Vertex;
typedef struct graph *DirectedGraph;

DirectedGraph directed_graph_initialize(int size);
void directed_graph_insert_edge(DirectedGraph G, char *Given_Edge);
void directed_graph_show_graph(DirectedGraph G);
void directed_graph_depth_first(DirectedGraph G, void (*Visit)(Vertex x));
void directed_graph_breadth_top_sort(DirectedGraph G);
DirectedGraph directed_graph_reverse(DirectedGraph G);
void directed_graph_vertex_show(Vertex x);