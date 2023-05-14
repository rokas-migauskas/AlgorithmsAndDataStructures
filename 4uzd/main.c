#include "graph.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
    int num_courses, num_prerequisites;

    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error: Unable to open input.txt\n");
        return 1;
    }

    fscanf(file, "%d", &num_courses);

    Graph *graph = create_graph(num_courses);

    fscanf(file, "%d", &num_prerequisites);

    for (int i = 0; i < num_prerequisites; i++) {
        int course, prerequisite;
        fscanf(file, "%d%d", &course, &prerequisite);
        add_edge(graph, prerequisite, course);
    }

    fclose(file);

    bool success;
    int *ordering = topological_sort(graph, &success);

    if (success) {
        printf("One possible course order: ");
        for (int i = 0; i < num_courses; i++) {
            printf("%d ", ordering[i]);
        }
        printf("\n");
        free(ordering);
    } else {
        printf("No valid course order found.\n");
    }

    free_graph(graph);
    return 0;
}
