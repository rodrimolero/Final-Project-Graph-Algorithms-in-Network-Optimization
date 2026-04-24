#include <stdio.h>
#include <time.h>
#include <windows.h>

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
    addEdge(graph, 2, 4, 10); // Airport -> Hospital (10 minutes)
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

// Helper function to find the index of the smallest edge weight that is not yet included in the MST
int minMSTEdge(int smallestEdges[V], int isinMST[V]) {
    int minWeight = 9999999;
    int minIndex = -1;
    for (int i = 0; i < V; i++) {
        // If the node has not been visited before and it has a smaller edge weight than any other edge
        if (!isinMST[i] && smallestEdges[i] < minWeight) {
            minWeight = smallestEdges[i]; // Then set it to be the new smallest edge
            minIndex = i; // And the new smallest index
        }
    }
    return minIndex; // Return the index to be used as the new current node
}

// Function to perform Prim's algorithm to find the Minimum Spanning Tree (MST) of the graph starting from a given node
void MST(int graph[V][V], int start) {
    int smallestEdges[V];
    int isinMST[V];

    for (int i = 0; i < V; i++){
        smallestEdges[i] = 9999999; // Initialize smallest edge for each node to be a very big number
        isinMST[i] = 0; // Initialize each node to not be in the MST
    }
    
    smallestEdges[start] = 0; // To go from node 0 to node 0 will cost nothing

    for (int i = 0; i < V - 1; i++) {
        int curr = minMSTEdge(smallestEdges, isinMST); // Current node will be the smallest one in the MST

        // If no smallest edge is found but there are still nodes in the graph then those nodes are disconnected from the network of the starting node.
        if (curr == -1) {
            printf("ERROR: graph may be disconnected\n");
            break;
        }

        isinMST[curr] = 1; // Make sure the current node is in the MST
        
        printf("Visited Node: %d\n", curr); // Output that we have visited the current node

        // For all nodes in the graph
        for (int neighbor = 0; neighbor < V; neighbor++) {
            // If the node is a neighbor, that has not been visited, and has a smaller edge weight than any other edge
            if (graph[curr][neighbor] && !isinMST[neighbor] && graph[curr][neighbor] < smallestEdges[neighbor]) {
                smallestEdges[neighbor] = graph[curr][neighbor]; // Then set this neighbor to be the new smallest edge
            }
        }
    }
}

// Wrapper function for DFS to handle the visited array and call the recursive DFS function
void DFSContainer(int graph[V][V], int start) {
    int visitedDFS[V] = {0}; // Track visited nodes for DFS
    DFS(graph, visitedDFS, 0); // Call DFS with the provided graph, visited array, and starting node
}


//Bellman-Ford algorithm using the bus network adjacency matrix.
//Finds shortest travel times from a source stop to all other stops.
void bellmanFord(int graph[V][V], int source) 
{
    int distance[V];
    int predecessor[V];
    //Initialize distances to 9999999, predecessors to -1
    for (int i = 0; i < V; i++) {    
        distance[i] = 9999999;
        predecessor[i] = -1;
    }
    distance[source] = 0;
 
    //Relax all edges V-1 times.
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != 0 && distance[u] != 9999999 && distance[u] + graph[u][v] < distance[v]) //If 
                {
                    distance[v] = distance[u] + graph[u][v];
                    predecessor[v] = u;
                }
            }
        }
    }
 
    //Check for negative-weight cycles
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) 
        {
            if (graph[u][v] != 0 && distance[u] != 9999999
                && distance[u] + graph[u][v] < distance[v]) 
            {
                printf("Negative cycle detected!\n");
                return;
            }
        }
    }
 
    //Print shortest travel times from the source stop
    printf("\nShortest travel times from %s:\n", stops[source]);
    printf("%-15s %-10s %s\n", "Stop", "Time", "Path");
    printf("----------------------------------------------\n");
 
    for (int i = 0; i < V; i++) 
    {
        printf("%-15s ", stops[i]);
        if (distance[i] == 9999999) 
        {
            printf("No route\n");
        } 
        else 
        {
            printf("%-10d ", distance[i]);
            //Print the path
            int path[V];
            int pathLen = 0;
            int current = i;
            while (current != -1) {
                path[pathLen++] = current;
                current = predecessor[current];
            }
            for (int p = pathLen - 1; p >= 0; p--) {
                printf("%s", stops[path[p]]);
                if (p > 0) printf(" -> ");
            }
            printf("\n");
        }
    }
}

// Function to display the results of a graph algorithm and measure its execution time
void displayFunct(char funct_name[], char graph_name[], void (*funct)(int graph[V][V], int), int graph[V][V], int start_node) {
    LARGE_INTEGER frequency, start, end;
    
    printf("%s Traversal of %s graph: \n", funct_name, graph_name);
    QueryPerformanceCounter(&frequency);
    QueryPerformanceCounter(&start);
    funct(graph, start_node);
    QueryPerformanceCounter(&end);
    double cpu_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%s Time for %s: %.10f seconds\n", funct_name, graph_name, cpu_time);
    printf("-------------------------------------\n");
}
// Function to display the graph and its properties, including the adjacency matrix and bus stops
void displayGraphs(char graph_name[], int graph[V][V], int has_stops, void (*createFn)(int g[V][V])) {
    initGraph(graph); // Initialize the graph
    createBusNetwork(graph); // Create the bus network with specific connections and travel times
    if (has_stops) printStops(); // Print the list of bus stops with their corresponding indices
    printf("%s graph adjacency matrix (travel times in minutes):\n", graph_name);
    printGraph(graph); // Print the adjacency matrix
    printf("-------------------------------------\n");
}

int main() {
    displayGraphs("Main", mainGraph, 1, createBusNetwork); //Function arg added.
    displayGraphs("Small sparse", smallSparseGraph, 0, createSmallSparseGraph); //Function arg added.
    displayGraphs("Large sparse", largeSparseGraph, 0, createLargeSparseGraph); //Function arg added.

    displayFunct("BFS", "main", BFS, mainGraph, 0);
    displayFunct("BFS", "small sparse", BFS, smallSparseGraph, 0);
    displayFunct("BFS", "large sparse", BFS, largeSparseGraph, 0);

    displayFunct("DFS", "main", DFSContainer, mainGraph, 0);
    displayFunct("DFS", "small sparse", DFSContainer, smallSparseGraph, 0);
    displayFunct("DFS", "large sparse", DFSContainer, largeSparseGraph, 0);

    displayFunct("MST", "main graph", MST, mainGraph, 0);
    displayFunct("MST", "small sparse", MST, smallSparseGraph, 0);
    displayFunct("MST", "large sparse", MST, largeSparseGraph, 0);
    

    return 0;
}