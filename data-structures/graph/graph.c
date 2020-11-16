#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Queue functions are defined first.
  Since we need queue for BFT and stack for DFT
  we use an output restricted dequeue

  Output restricted dequeue provides regular enqueue
  and dequeue operations, but we can also enqueue at the front
  of the queue which can be treated like pushing onto stack
*/

// Node definition for linked list implementation of queue
typedef struct Node {
    int value;
    struct Node* link;
} Node;

// function to return if queue is empty
bool is_empty(Node* head, Node* tail) {
    if (!head && !tail) {
        return true;
    }
    return false;
}

// function for creating new node and returning its address
Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->link = NULL;
    return node;
}

// enqueue `value` into queue defined by `head_ref` and `tail_ref`
void enqueue(Node** head_ref, Node** tail_ref, int value) {
    if (*head_ref == NULL && *tail_ref == NULL) {
        *head_ref = *tail_ref = create_node(value);
    } else {
        Node* node = create_node(value);
        (*tail_ref)->link = node;
        *tail_ref = node;
    }
}

// dequeue from queue defined by `head_ref` and `tail_ref`
void dequeue(Node** head_ref, Node** tail_ref) {
    if (*head_ref == NULL && *tail_ref == NULL) {
        printf("QUEUE IS EMPTY\n");
    } else if (*head_ref == *tail_ref) {
        Node* to_delete = *head_ref;
        *head_ref = *tail_ref = NULL;
        free(to_delete);
    } else {
        Node* to_delete = *head_ref;
        *head_ref = (*head_ref)->link;
        free(to_delete);
    }
}

// function for returning integer at front of queue with `head`
int front(Node* head) {
    if (!head) {
        printf("QUEUE IS EMPTY\n");
        return -1;
    }
    return head->value;
}

// push into dequeue defined by `head_ref` and `tail_ref`
void push(Node** head_ref, Node** tail_ref, int value) {
    if (*head_ref == NULL && *tail_ref == NULL) {
        *head_ref = *tail_ref = create_node(value);
    } else {
        Node* node = create_node(value);
        node->link = *head_ref;
        *head_ref = node;
    }
}

// wrapper around dequeue to use as stack
void pop(Node** head_ref, Node** tail_ref) {
    dequeue(head_ref, tail_ref);
}

// wrapper around front to use as stack
int peek(Node* head) {
    return front(head);
}

void print_queue(Node* head, Node* tail) {
    if (head == NULL && tail == NULL) {
        printf("[]\n");
        return;
    }
    printf("[");
    Node* iter = head;
    for (; iter != tail; iter = iter->link) {
        printf("%d,", iter->value);
    }
    printf("%d]\n", iter->value);
}

/*
  Functions for graph

  We use queue operations for BFS and BFT
  and stack operations for DFS and DFT
*/

// graph defined by adjacency matrix
typedef struct Graph {
    int n_edges;
    int** matrix;
} Graph;

// function for creating graph using adjacency matrix and edges
Graph* create_graph(int n_edges, int matrix[n_edges][n_edges]) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n_edges = n_edges;
    graph->matrix = (int**)malloc(sizeof(int*) * n_edges);
    for (int i = 0; i < n_edges; ++i) {
        graph->matrix[i] = matrix[i];
    }
    return graph;
}

// Breadth first search of graph
void BFS(Graph* graph, bool* visited, int start) {
    Node *head = NULL, *tail = NULL;
    if (!visited) {
        visited = (bool*)malloc(sizeof(bool) * graph->n_edges);
        memset(visited, false, graph->n_edges);
    }
    enqueue(&head, &tail, start);
    visited[start] = true;
    printf("%d ", start);
    while (!is_empty(head, tail)) {
        int v = front(head);
        dequeue(&head, &tail);
        for (int u = 0; u < graph->n_edges; ++u) {
            if (graph->matrix[v][u] == 1 && !visited[u]) {
                enqueue(&head, &tail, u);
                visited[u] = true;
                printf("%d ", u);
            }
        }
    }
}

// Breadth first traversal of graph
void BFT(Graph* graph) {
    bool* visited = (bool*)malloc(sizeof(bool) * graph->n_edges);
    memset(visited, false, graph->n_edges);
    for (int i = 0; i < graph->n_edges; ++i) {
        if (!visited[i]) {
            BFS(graph, visited, i);
        }
    }
}

// Depth first search of graph
void DFS(Graph* graph, bool* visited, int start) {
    Node *head = NULL, *tail = NULL;
    if (!visited) {
        visited = (bool*)malloc(sizeof(bool) * graph->n_edges);
        memset(visited, false, graph->n_edges);
    }
    push(&head, &tail, start);
    visited[start] = true;
    /*printf("%d ", start);*/
    while (!is_empty(head, tail)) {
        int v = peek(head);
        pop(&head, &tail);
        printf("%d ", v);
        for (int u = 0; u < graph->n_edges; ++u) {
            if (graph->matrix[v][u] == 1 && !visited[u]) {
                push(&head, &tail, u);
                visited[u] = true;
            }
        }
    }
}

// Depth first traversal of graph
void DFT(Graph* graph) {
    bool* visited = (bool*)malloc(sizeof(bool) * graph->n_edges);
    memset(visited, false, graph->n_edges);
    for (int i = 0; i < graph->n_edges; ++i) {
        if (!visited[i]) {
            DFS(graph, visited, i);
        }
    }
}

int main() {
    return 0;
}
