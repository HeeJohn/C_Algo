#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// Global arrays to store distance and visited flags
int distance[MAX_VERTICES];
int visited[MAX_VERTICES];

typedef struct {
    int vertex;
    int weight;
} HeapNode;

typedef struct {
    HeapNode heap[MAX_VERTICES];
    int size;
} PriorityQueue;

// Function to initialize the priority queue
void init_priority_queue(PriorityQueue* pq) {
    pq->size = 0;
}

// Function to insert an element into the priority queue
void enqueue(PriorityQueue* pq, int vertex, int weight) {
    // Increment the size of the priority queue and start from the last element
    int i = ++(pq->size);
    // Move up the heap to find the correct position for the new element
    while (i != 1 && weight < pq->heap[i / 2].weight) {
        pq->heap[i] = pq->heap[i / 2];
        i /= 2;
    }
    // Insert the new element at the correct position
    pq->heap[i].vertex = vertex;
    pq->heap[i].weight = weight;
}

// Function to remove and return the element with the minimum weight from the priority queue
HeapNode dequeue(PriorityQueue* pq) {
    int parent, child;
    HeapNode item, temp;

    // Extract the root element (element with minimum weight) from the heap
    item = pq->heap[1];
    temp = pq->heap[(pq->size)--];
    parent = 1;
    child = 2;

    // Move down the heap to maintain the heap property after removing the root
    while (child <= pq->size) {
        if (child < pq->size && pq->heap[child].weight > pq->heap[child + 1].weight)
            child++;
        if (temp.weight <= pq->heap[child].weight)
            break;
        pq->heap[parent] = pq->heap[child];
        parent = child;
        child *= 2;
    }

    // Place the last element (heaviest weight) at the correct position
    pq->heap[parent] = temp;
    return item;
}

// Function to check if the priority queue is empty
int is_empty(PriorityQueue* pq) {
    return pq->size == 0;
}

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra_shortest_path(GraphType* g, int start) {
    int i, u, w;
    PriorityQueue pq;

    // Initialize the priority queue and distance/visited arrays
    init_priority_queue(&pq);
    for (i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        visited[i] = FALSE;
    }
    visited[start] = TRUE;
    distance[start] = 0;

    // Add all vertices to the priority queue with their initial distances
    for (i = 0; i < g->n; i++) {
        enqueue(&pq, i, distance[i]);
    }

    // Dijkstra's algorithm main loop
    while (!is_empty(&pq)) {
        // Extract the vertex with the minimum distance from the priority queue
        u = dequeue(&pq).vertex;
        printf("minimum vertext %d \n", u);
        // Mark the vertex as visited
        visited[u] = TRUE;

        // Relax edges: Update distances to neighbors if a shorter path is found
        for (w = 0; w < g->n; w++)
        {
            printf("distance[%d] + g->weight[%d][%d] : %d + %d = %d \n", u, u, w, distance[u], g->weight[u][w], (distance[u] + g->weight[u][w]));

            if (!visited[w] && distance[u] + g->weight[u][w] < distance[w])
            {
                printf("------true condition: g->weight[%d][%d] : %d \n", u, w, g->weight[u][w]);

                distance[w] = distance[u] + g->weight[u][w];
                // Enqueue the updated distance of the neighbor to the priority queue
                enqueue(&pq, w, distance[w]);
            }
        }
    }
}

// Function to print the graph as an adjacency matrix
void print_graph(GraphType* g) {
    printf("Graph (Adjacency Matrix):\n");
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (g->weight[i][j] == INF)
                printf(" * ");
            else
                printf("%2d ", g->weight[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    GraphType g = { 7,
                    {{ 0,  7,  INF, INF,   3,  10, INF },
                     { 7,  0,    4,  10,   2,   6, INF },
                     { INF,  4,    0,   2, INF, INF, INF },
                     { INF, 10,    2,   0,  11,   9,   4 },
                     { 3,  2,  INF,  11,   0, INF,   5 },
                     { 10,  6,  INF,   9, INF,   0, INF },
                     { INF, INF, INF,   4,   5, INF,   0 } }
    };

    // Print the graph before running Dijkstra's algorithm
    print_graph(&g);

    // Run Dijkstra's algorithm with the start vertex as 0
    dijkstra_shortest_path(&g, 0);

    // Print the shortest paths from the start vertex (Node 0)
    printf("Shortest Paths from Node 0:\n");
    for (int i = 0; i < g.n; i++) {
        printf("Node %d: Shortest Distance = %d\n", i, distance[i]);
    }

    return 0;
}
