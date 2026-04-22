#include <stdio.h>

#define V 15 // Number of bus stops

int graph[V][V]; // Adjacency matrix to represent the graph

void initGraph() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0; // Initialize all edges to 0 (no connection)
        }
    }
}
