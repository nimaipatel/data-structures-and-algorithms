#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    int priority;
    struct Node* link;
};

typedef struct Node Node;

Node* create_node(int value, int priority) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->priority = priority;
    node->link = NULL;
    return node;
}

void enqueue(Node** head_ref, Node** tail_ref, int value, int priority) {
    Node* node = create_node(value, priority);
    if (*head_ref == NULL && *tail_ref == NULL) {
        *head_ref = *tail_ref = node;
    } else if (node->priority < (**head_ref).priority) {
        node->link = *head_ref;
        *head_ref = node;
    } else if ((**tail_ref).priority <= node->priority) {
        (**tail_ref).link = node;
        *tail_ref = node;
    } else {
        Node* current = *head_ref;
        Node* previous;
        while (node->priority >= current->priority) {
            previous = current;
            current = current->link;
        }
        node->link = previous->link;
        previous->link = node;
    }
}

void dequeue(Node** head_ref, Node** tail_ref) {
    if (*head_ref == NULL) {
        printf("QUEUE IS EMPTY\n");
    } else if (*head_ref == *tail_ref) {
        Node* to_free = *head_ref;
        *head_ref = *tail_ref = NULL;
        free(to_free);
    } else {
        Node* to_free = *head_ref;
        *head_ref = (**head_ref).link;
        free(to_free);
    }
}

void print_queue(Node* head, Node* tail) {
    Node* iter = head;
    while (iter != tail) {
        printf("[V:%d P:%d]", iter->value, iter->priority);
        iter = iter->link;
    }
    printf("[V:%d P:%d]", iter->value, iter->priority);
    printf("\n");
}

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    int choice;
    do {
        printf("\n0 to enqueue\n1 to dequeue\nAny other number to exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("Enter value you want to enter and its priority:\n");
                int v;
                scanf("%d", &v);
                int p;
                scanf("%d", &p);
                enqueue(&head, &tail, v, p);
                print_queue(head, tail);
                break;
            case 1:
                printf("Dequeued from queue\n");
                dequeue(&head, &tail);
                print_queue(head, tail);
                break;
            default:
                printf("Exiting...\n");
                break;
        }
    } while (choice == 1 || choice == 0);
    return 0;
}
