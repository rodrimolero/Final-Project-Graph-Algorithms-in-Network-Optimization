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

void addEdge(int u, int v, int weight) {
    graph[u][v] = weight; // Add edge from u to v with given weight
    graph[v][u] = weight; // Add edge from v to u (undirected graph)
}

void createSample() {
    addEdge(0, 1, 5); // Stop A -> B (5 minutes)
    addEdge(0, 2, 10);
    addEdge(1, 3, 15);
    addEdge(2, 3, 20);
    addEdge(3, 4, 25);
    addEdge(4, 5, 30);
}

void createSample2() {
    addEdge(0, 3, 5);
    addEdge(0, 5, 10);
    addEdge(1, 2, 15);
    addEdge(2, 3, 20);
    addEdge(3, 6, 25);
    addEdge(4, 1, 30);
}

void BFS(int graph[V][V], int start) {
    int queue[V], front = 0, rear = 0; // Front is the index of the next item to be removed, rear is the index where the new item will be added
    int visited[V] = {0}; // Track visited nodes

    visited[start] = 1; // Mark the starting node as visited
    queue[rear++] = start; // Enqueue the starting node and increment rear
    while (front < rear) {
        int curr = queue[front++]; // Dequeue the front node and increment front
        printf("Visited node: %d\n", curr); // Process the current node
        for (int i = 0; i < V; i++) {
            if (graph[curr][i] != 0 && !visited[i]) { // Check for adjacent nodes that are not visited
                visited[i] = 1; // Mark the node as visited
                queue[rear++] = i; // Enqueue the adjacent node and increment rear
            }
        }
    }
}

void DFS(int graph[V][V], int visited[V], int curr) {
    visited[curr] = 1; // Mark the current node as visited
    printf("Visited node: %d\n", curr); // Process the current node
    for (int i = 0; i < V; i++) {
        if (graph[curr][i] != 0 && !visited[i]) { // Check for adjacent nodes that are not visited
            DFS(graph, visited, i); // Recursively visit the adjacent node
        }
    }
}

int main() {
    initGraph(); // Initialize the graph
    createSample(); // Create a sample graph with bus stops and travel times
    printf("Graph initialized and sample created.\n");

    printf("-------------------------------------\n");
    printf("BFS Traversal: \n");
    BFS(graph, 0); // Perform BFS starting from node 0 (Stop A)
    printf("-------------------------------------\n");

    printf("DFS Traversal: \n");
    int visitedDFS[V] = {0}; // Track visited nodes for DFS
    DFS(graph, visitedDFS, 0); // Perform DFS starting from node 0 (Stop A)
    printf("-------------------------------------\n");

    return 0;
}