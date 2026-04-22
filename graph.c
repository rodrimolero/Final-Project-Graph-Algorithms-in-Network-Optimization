#include <stdio.h>

// Number of bus stops
#define V 16

// Adjacency matrix to represent the graph
int graph[V][V];

// Array of bus stop names for reference
char *stops[V] = {
    "Downtown","University","Airport","Mall","Hospital","Stadium",
    "Library","Police","Museum","Bank",
    "Post Office","Beach","Port","School","Market","Park"
};

// Function to initialize the graph with no edges
void initGraph() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0; // Initialize all edges to 0 (no connection)
        }
    }
}

// Function to add an edge between two bus stops with a given weight (travel time)
void addEdge(int u, int v, int weight) {
    graph[u][v] = weight; // Add edge from u to v with given weight
    graph[v][u] = weight; // Add edge from v to u (undirected graph)
}

// Function to create a bus network with specific connections and travel times
void createBusNetwork() {
    // Core city connections
    addEdge(0, 1, 5); // Downtown -> University (5 minutes)
    addEdge(0, 2, 12); // Downtown -> Airport (12 minutes)
    addEdge(0, 4, 8); // Downtown -> Hospital (8 minutes)
    addEdge(0, 7, 6); // Downtown -> Police Station (6 minutes)

    // University connections
    addEdge(1, 3, 10); // University -> Mall (10 minutes)
    addEdge(1, 5, 15); // University -> Stadium (15 minutes)
    addEdge(1, 6, 7); // University -> Library (7 minutes)

    // Airport connections
    addEdge(2, 8, 20); // Airport -> Museum (20 minutes)
    addEdge(2, 9, 18); // Airport -> Bank (18 minutes)

    // Mall connections
    addEdge(3, 10, 5); // Mall -> Post Office (5 minutes)
    addEdge(3, 11, 17); // Mall -> Beach (17 minutes)

    // Hospital connections
    addEdge(4, 7, 10); // Hospital -> Police Station (10 minutes)
    addEdge(4, 13, 12); // Hospital -> School (12 minutes)

    // Stadium connections
    addEdge(5, 12, 25); // Stadium -> Port (25 minutes)
    addEdge(5, 14, 10); // Stadium -> Market (10 minutes)

    // Library connections
    addEdge(6, 15, 8); // Library -> Park (8 minutes)

    // Police Station connections
    addEdge(7, 8, 9); // Police Station -> Museum (9 minutes)
    addEdge(7, 9, 11); // Police Station -> Bank (11 minutes)

    // School connections   
    addEdge(13, 14, 6); // School -> Market (6 minutes)
    addEdge(13, 15, 8); // School -> Park (8 minutes)
}

// Function to print the adjacency matrix of the graph
void printGraph() {
    printf("Graph adjacency matrix (travel times in minutes):\n");
    for (int i = 0; i < V; i++) {
        printf("%-11s", stops[i]);
    }
    printf("\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%-11d", graph[i][j]);
        }
        printf("\n");
    }
}

// Function to print the list of bus stops
void printStops() {
    printf("\nBus Stops:\n");
    for (int i = 0; i < V; i++) {
        printf("%d -> %s\n", i, stops[i]);
    }
}

// Function to perform Breadth-First Search (BFS) on the graph starting from a given node
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

// Function to perform Depth-First Search (DFS) on the graph starting from a given node
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
    createBusNetwork(); // Create the bus network with specific connections and travel times
    printGraph(); // Print the adjacency matrix of the graph
    printStops(); // Print the list of bus stops

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