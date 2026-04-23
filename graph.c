#include <stdio.h>
#include <time.h>

// Number of bus stops
#define V 16

// Adjacency matrix to represent the graph of bus stops and travel times
int mainGraph[V][V];
int smallSparseGraph[V][V];
int largeSparseGraph[V][V];

// Array of bus stop names for reference
char *stops[V] = {
    "Downtown","University","Airport","Mall","Hospital","Stadium",
    "Library","Police","Museum","Bank",
    "Post Office","Beach","Port","School","Market","Park"
};

// Function to initialize the graph with no edges
void initGraph(int graph[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0; // Initialize all edges to 0 (no connection)
        }
    }
}

// Function to add an edge between two bus stops with a given weight (travel time)
void addEdge(int graph[V][V], int u, int v, int weight) {
    graph[u][v] = weight; // Add edge from u to v with given weight
    graph[v][u] = weight; // Add edge from v to u (undirected graph)
}

// Function to create a bus network with specific connections and travel times
void createBusNetwork(int graph[V][V]) {
    // Core city connections
    addEdge(graph, 0, 1, 5); // Downtown -> University (5 minutes)
    addEdge(graph, 0, 2, 12); // Downtown -> Airport (12 minutes)
    addEdge(graph, 0, 4, 8); // Downtown -> Hospital (8 minutes)
    addEdge(graph, 0, 7, 6); // Downtown -> Police Station (6 minutes)

    // University connections
    addEdge(graph, 1, 3, 10); // University -> Mall (10 minutes)
    addEdge(graph, 1, 5, 15); // University -> Stadium (15 minutes)
    addEdge(graph, 1, 6, 7); // University -> Library (7 minutes)

    // Airport connections
    addEdge(graph, 2, 8, 20); // Airport -> Museum (20 minutes)
    addEdge(graph, 2, 9, 18); // Airport -> Bank (18 minutes)

    // Mall connections
    addEdge(graph, 3, 10, 5); // Mall -> Post Office (5 minutes)
    addEdge(graph, 3, 11, 17); // Mall -> Beach (17 minutes)

    // Hospital connections
    addEdge(graph, 4, 7, 10); // Hospital -> Police Station (10 minutes)
    addEdge(graph, 4, 13, 12); // Hospital -> School (12 minutes)

    // Stadium connections
    addEdge(graph, 5, 12, 25); // Stadium -> Port (25 minutes)
    addEdge(graph, 5, 14, 10); // Stadium -> Market (10 minutes)

    // Library connections
    addEdge(graph, 6, 15, 8); // Library -> Park (8 minutes)

    // Police Station connections
    addEdge(graph, 7, 8, 9); // Police Station -> Museum (9 minutes)
    addEdge(graph, 7, 9, 11); // Police Station -> Bank (11 minutes)

    // School connections   
    addEdge(graph, 13, 14, 6); // School -> Market (6 minutes)
    addEdge(graph, 13, 15, 8); // School -> Park (8 minutes)
}

// Function to create a small sparse graph for testing
void createSmallSparseGraph(int graph[V][V]) {
    addEdge(graph, 0, 1, 5); // Downtown -> University (5 minutes)
    addEdge(graph, 0, 2, 12); // Downtown -> Airport (12 minutes)
    addEdge(graph, 1, 3, 10); // University -> Mall (10 minutes)
    addEdge(graph, 4, 5, 10); // Hospital -> Stadium (10 minutes)
}

// Function to create a large sparse graph for testing
void createLargeSparseGraph(int graph[V][V]) {
    addEdge(graph, 0, 1, 5); // Downtown -> University (5 minutes)
    addEdge(graph, 0, 2, 12); // Downtown -> Airport (12 minutes)
    addEdge(graph, 1, 3, 10); // University -> Mall (10 minutes)
    addEdge(graph, 3, 7, 10); // Mall -> Police Station (10 minutes)
    addEdge(graph, 4, 12, 25); // Hospital -> Port (25 minutes)
    addEdge(graph, 4, 7, 13); // Hospital -> Police Station (13 minutes)
    addEdge(graph, 7, 15, 8); // Police Station -> Park (8 minutes)
    addEdge(graph, 8, 12, 20); // Museum -> Port (20 minutes)
}

// Function to print the adjacency matrix of the graph
void printGraph(int graph[V][V]) {
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
    initGraph(mainGraph); // Initialize the main graph
    createBusNetwork(mainGraph); // Create the main bus network with specific connections and travel times
    printStops(); // Print the list of bus stops with their corresponding indices
    printf("-------------------------------------\n");
    printf("Main graph adjacency matrix (travel times in minutes):\n");
    printGraph(mainGraph); // Print the adjacency matrix of the main graph
    printf("-------------------------------------\n");

    initGraph(smallSparseGraph); // Initialize the small sparse graph
    createSmallSparseGraph(smallSparseGraph); // Create the small sparse graph with specific connections and travel times
    printf("Small sparse graph adjacency matrix (travel times in minutes):\n");
    printGraph(smallSparseGraph); // Print the adjacency matrix of the small sparse graph
    printf("-------------------------------------\n");

    initGraph(largeSparseGraph); // Initialize the large sparse graph
    createLargeSparseGraph(largeSparseGraph); // Create the large sparse graph with specific connections and travel times
    printf("Large sparse graph adjacency matrix (travel times in minutes):\n");
    printGraph(largeSparseGraph); // Print the adjacency matrix of the large sparse graph
    printf("-------------------------------------\n");

    clock_t start, end;
    double cpu_time;

    printf("-------------------------------------\n");
    printf("BFS Traversal of main graph: \n");
    start = clock();
    BFS(mainGraph, 0); // Perform BFS starting from node 0 (Stop A)
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("BFS Time for main graph: %f seconds\n", cpu_time);
    printf("-------------------------------------\n");

    printf("BFS Traversal of small sparse graph: \n");
    start = clock();
    BFS(smallSparseGraph, 0); // Perform BFS starting from node 0 (Stop A)
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("BFS Time for small sparse graph: %f seconds\n", cpu_time);
    printf("-------------------------------------\n");

    printf("BFS Traversal of large sparse graph: \n");
    start = clock();
    BFS(largeSparseGraph, 0); // Perform BFS starting from node 0 (Stop A)
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("BFS Time for large sparse graph: %f seconds\n", cpu_time);
    printf("-------------------------------------\n");

    printf("DFS Traversal of main graph: \n");
    int visitedDFSMainGraph[V] = {0}; // Track visited nodes for DFS
    start = clock();
    DFS(mainGraph, visitedDFSMainGraph, 0); // Perform DFS starting from node 0 (Stop A)
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("DFS Time for main graph: %f seconds\n", cpu_time);
    printf("-------------------------------------\n");

    printf("DFS Traversal of small sparse graph: \n");
    int visitedDFSSmallSparseGraph[V] = {0}; // Track visited nodes for DFS
    start = clock();
    DFS(smallSparseGraph, visitedDFSSmallSparseGraph, 0); // Perform DFS starting from node 0 (Stop A)
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("DFS Time for small sparse graph: %f seconds\n", cpu_time);
    printf("-------------------------------------\n");

    printf("DFS Traversal of large sparse graph: \n");
    int visitedDFSLargeSparseGraph[V] = {0}; // Track visited nodes for DFS
    start = clock();
    DFS(largeSparseGraph, visitedDFSLargeSparseGraph, 0); // Perform DFS starting from node 0 (Stop A)
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("DFS Time for large sparse graph: %f seconds\n", cpu_time);
    printf("-------------------------------------\n");


    return 0;
}