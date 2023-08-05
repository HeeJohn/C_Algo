/*
    program : dijkstra_normal
    name : HuiJun Seo
    last_edit: 23.08.05
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
    int n; // Number of vertices in the graph
    int weight[MAX_VERTICES][MAX_VERTICES]; // Weighted adjacency matrix
} GraphType;

int distance[MAX_VERTICES]; // Array to store the shortest distance from the starting vertex to each vertex
int visited[MAX_VERTICES]; // Array to keep track of visited vertices

// Function to find the index of the minimum distance node among the unvisited nodes
int findMin(int distance[], int n, int visited[]) {
    int i, min, minpos;

    min = INF;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !visited[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra_shortest_path(GraphType* g, int start) {
    int i, u, w;

    // Initialize distance array with the weights of edges from start to all other vertices
    for (i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        visited[i] = FALSE; // Mark all vertices as not visited
    }
    visited[start] = TRUE; // Mark the starting vertex as visited
    distance[start] = 0; // Distance from start to start is 0

    // Main loop to find the shortest path to all vertices
    for (i = 0; i < g->n - 1; i++) {
        // Find the vertex with the minimum distance among the unvisited vertices
        u = findMin(distance, g->n, visited);
        visited[u] = TRUE; // Mark the selected vertex as visited

        // Update the distances of adjacent vertices from the selected vertex
        for (w = 0; w < g->n; w++) {
            if (!visited[w] && distance[u] + g->weight[u][w] < distance[w]) {
                // If the new path is shorter than the current shortest path, update the distance
                distance[w] = distance[u] + g->weight[u][w];
            }
        }
    }
}

int main(void) {
    // Define the graph with its weighted adjacency matrix
    GraphType g = { 7,
                    {{ 0,  7,  INF, INF,   3,  10, INF },
                     { 7,  0,    4,  10,   2,   6, INF },
                     { INF,  4,    0,   2, INF, INF, INF },
                     { INF, 10,    2,   0,  11,   9,   4 },
                     { 3,  2,  INF,  11,   0, INF,   5 },
                     { 10,  6,  INF,   9, INF,   0, INF },
                     { INF, INF, INF,   4,   5, INF,   0 } }
    };

    // Find the shortest paths from Node 0 using Dijkstra's algorithm
    dijkstra_shortest_path(&g, 0);

    // Print the shortest distances to all vertices from Node 0
    printf("Shortest Paths from Node 0:\n");
    for (int i = 0; i < g.n; i++) {
        printf("Node %d: Shortest Distance = %d\n", i, distance[i]);
    }

    return 0;
}
