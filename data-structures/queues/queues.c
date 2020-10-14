#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* link;
};

// craete new node and return address
struct node* create_node(int value) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = value;
    new_node->link = NULL;
    return new_node;
}

// traverse to end and insert node
void enqueue(struct node** ptr_to_head, int value) {
    struct node* temp = create_node(value);
    struct node* ptr;
    if (*ptr_to_head == NULL) {
        *ptr_to_head = temp;
    } else {
        ptr = *ptr_to_head;
        while (ptr->link != NULL) {
            ptr = ptr->link;
        }
        ptr->link = temp;
    }
}

// delete first node
void dequeue(struct node** ptr_to_head) {
    struct node* temp = *ptr_to_head;
    if (*ptr_to_head == NULL) {
        printf("List is empty, nothing to delete");
    } else if ((**ptr_to_head).link == NULL) {
        *ptr_to_head = NULL;
        free(temp);
    } else {
        *ptr_to_head = (**ptr_to_head).link;
        free(temp);
    }
}

// traverse and print all elements
void traverse(struct node* head) {
    struct node* temp;
    if (head == NULL) {
        printf("\nEmpty List: ");
    } else {
        printf("\nQueue: ");
        temp = head;
        while (temp != NULL) {
            printf("%d\t", temp->data);
            temp = temp->link;
        }
        printf("\n");
    }
}

int main() {
    struct node* head = NULL;
    int choice;
    do {
        printf("\n0 to enqueue\n1 to dequeue\nAny other number to exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("Enter value you want to enter:\n");
                int v;
                scanf("%d", &v);
                enqueue(&head, v);
                traverse(head);
                break;
            case 1:
                printf("Dequeued from queue\n");
                dequeue(&head);
                traverse(head);
                break;
            default:
                printf("Exiting...\n");
                break;
        }
    } while (choice == 1 || choice == 0);
    traverse(head);
    return 0;
}
