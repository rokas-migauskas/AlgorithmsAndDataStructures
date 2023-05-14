#include "graph.h"
#include <stdlib.h>
#include <string.h>

struct Graph {
    int vertices;
    int *adj_matrix;
};

Graph *create_graph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adj_matrix = (int *)calloc(vertices * vertices, sizeof(int));
    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    graph->adj_matrix[src * graph->vertices + dest] = 1;
}

int *topological_sort(Graph *graph, bool *success) {
    int *result = (int *)malloc(graph->vertices * sizeof(int));
    int *in_degree = (int *)calloc(graph->vertices, sizeof(int));

    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            in_degree[j] += graph->adj_matrix[i * graph->vertices + j];
        }
    }

    int next = 0;
    for (int i = 0; i < graph->vertices; i++) {
        int current = -1;
        for (int j = 0; j < graph->vertices; j++) {
            if (in_degree[j] == 0) {
                current = j;
                break;
            }
        }

        if (current == -1) {
            *success = false;
            free(result);
            return NULL;
        }

        result[next++] = current;
        in_degree[current] = -1;

        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adj_matrix[current * graph->vertices + j]) {
                in_degree[j]--;
            }
        }
    }

    *success = true;
    return result;
}

void free_graph(Graph *graph) {
    free(graph->adj_matrix);
    free(graph);
}
