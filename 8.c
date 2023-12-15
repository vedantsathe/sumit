#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node* adjacencyList[MAX_VERTICES];
};

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    int i; // move the variable declaration outside the loop
    for (i = 0; i < numVertices; ++i) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = src;
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

void DFS(struct Graph* graph, int startVertex, int visited[]) {
    visited[startVertex] = 1;
    printf("%d ", startVertex);

    struct Node* temp = graph->adjacencyList[startVertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void BFS(struct Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = -1, rear = -1;

    visited[startVertex] = 1;
    queue[++rear] = startVertex;

    while (front != rear) {
        startVertex = queue[++front];
        printf("%d ", startVertex);

        struct Node* temp = graph->adjacencyList[startVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[++rear] = adjVertex;
            }
            temp = temp->next;
        }
    }
}

void printGraph(struct Graph* graph) {
    int i;
    for (i = 0; i < graph->numVertices; ++i) {
        printf("Adjacency list of vertex %d:\n", i);
        struct Node* temp = graph->adjacencyList[i];
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int numVertices = 6;
    struct Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    printf("Adjacency List Representation:\n");
    printGraph(graph);

    printf("\nDepth First Search (DFS): ");
    int visitedDFS[MAX_VERTICES] = {0};
    DFS(graph, 0, visitedDFS);

    printf("\nBreadth First Search (BFS): ");
    BFS(graph, 0);

    free(graph);

    return 0;
}

