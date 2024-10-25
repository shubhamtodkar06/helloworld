#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];

void BFS(int startVertex, int numVertices) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        for (int i = 0; i < numVertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

void DFS(int startVertex, int numVertices) {
    visited[startVertex] = 1;
    printf("%d ", startVertex);

    for (int i = 0; i < numVertices; i++) {
        if (graph[startVertex][i] == 1 && !visited[i]) {
            DFS(i, numVertices);
        }
    }
}

int main() {
    int numVertices, edges;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    if (numVertices <= 0 || numVertices > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    if (edges < 0 || edges > numVertices * (numVertices - 1) / 2) {
        printf("Invalid number of edges.\n");
        return 1;
    }

    for (int i = 0; i < edges; i++) {
        int u, v;
        printf("Enter edge endpoints (u, v): ");
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= numVertices || v < 0 || v >= numVertices) {
            printf("Invalid vertex indices.\n");
            return 1;
        }

        graph[u][v] = 1;
        graph[v][u] = 1; // For undirected graphs
    }

    printf("Enter the starting vertex for BFS: ");
    int startVertexBFS;
    scanf("%d", &startVertexBFS);

    if (startVertexBFS < 0 || startVertexBFS >= numVertices) {
        printf("Invalid starting vertex for BFS.\n");
        return 1;
    }

    printf("BFS Traversal: ");
    BFS(startVertexBFS, numVertices);
    printf("\n");

    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    printf("Enter the starting vertex for DFS: ");
    int startVertexDFS;
    scanf("%d", &startVertexDFS);

    if (startVertexDFS < 0 || startVertexDFS >= numVertices) {
        printf("Invalid starting vertex for DFS.\n");
        return 1;
    }

    printf("DFS Traversal: ");
    DFS(startVertexDFS, numVertices);
    printf("\n");

    return 0;
}
