#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct Graph Graph;

Graph *create_graph(int vertices);
void add_edge(Graph *graph, int src, int dest);
int *topological_sort(Graph *graph, bool *success);
void free_graph(Graph *graph);

#endif
