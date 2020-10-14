#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* link;
};

struct node* create_node(int value) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = value;
    new_node->link = NULL;
    return new_node;
}

bool is_empty(struct node** ptr_to_top) {
    if (*ptr_to_top == NULL) {
        return true;
    }
    return false;
}

void push(struct node** ptr_to_top, int value) {
    struct node* new_node = create_node(value);
    if (*ptr_to_top == NULL) {
        *ptr_to_top = new_node;
    } else {
        new_node->link = *ptr_to_top;
        *ptr_to_top = new_node;
    }
}

void pop(struct node** ptr_to_top) {
    if (*ptr_to_top == NULL) {
        printf("\nStack is empty, nothing to pop");
    } else if ((**ptr_to_top).link == NULL) {
        // only one item in stack
        free(*ptr_to_top);
        *ptr_to_top = NULL;
    } else {
        struct node* temp = *ptr_to_top;
        *ptr_to_top = (**ptr_to_top).link;
        free(temp);
    }
}

int peek(struct node** ptr_to_top) {
    if (*ptr_to_top == NULL) {
        printf("\nStack is empty, returning garbage value!");
        return -1;
    }
    return (*ptr_to_top)->data;
}

void traverse(struct node* top) {
    if (top == NULL) {
        printf("\nStack is empty, noting to traverse");
    } else {
        printf("\nStack: ");
        struct node* temp = top;
        printf("\n");
        while (temp != NULL) {
            printf("%d\t", temp->data);
            temp = temp->link;
        }
    }
    printf("\n");
}

int main() {
    struct node* head = NULL;
    int choice;
    do {
        printf("\n0 to push\n1 to pop\nAny other number to exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("Enter value you want to push:\n");
                int v;
                scanf("%d", &v);
                push(&head, v);
                traverse(head);
                break;
            case 1:
                printf("Popping from stack\n");
                pop(&head);
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
