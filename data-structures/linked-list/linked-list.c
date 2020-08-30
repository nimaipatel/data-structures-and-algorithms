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

void insert_end(struct node** ptr_to_head, int value) {
    struct node* temp = create_node(value);
    struct node* ptr;
    if (*ptr_to_head == NULL) {
        *ptr_to_head = temp;
    } else {
        ptr = *ptr_to_head;
        while (ptr->link != NULL) { ptr = ptr->link; }
        ptr->link = temp;
    }
}

// insert node at start of list
void insert_start(struct node** ptr_to_head, int value) {
    struct node* new_node = create_node(value);
    if (*ptr_to_head == NULL) {
        *ptr_to_head = new_node;
    } else {
        new_node->link = *ptr_to_head;
        *ptr_to_head = new_node;
    }
}

void insert_in_sorted(struct node** ptr_to_head, int value) {
    struct node* new_node = create_node(value);
    if (*ptr_to_head == NULL) {
        *ptr_to_head = new_node;

    } else if (value < (**ptr_to_head).data) {
        new_node->link = *ptr_to_head;
        *ptr_to_head = new_node;
    } else {
        struct node* ptr = *ptr_to_head;
        struct node* prev;
        while (value >= ptr->data) {
            /*printf("\n %d %p", ptr->data, ptr->link);*/
            if (ptr->link == NULL) { break; }
            prev = ptr;
            ptr = ptr->link;
        }
        // condition if element is larger than all:
        if (ptr->link == NULL) {
            ptr->link = new_node;
        } else {
            new_node->link = ptr;
            prev->link = new_node;
        }
    }
}

void delete_first(struct node** ptr_to_head) {
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

int count_nodes(struct node* head) {
    struct node* temp;
    temp = head;
    if (temp == NULL) { return 0; }
    int counter = 0;
    for (temp = head; temp->link != NULL; temp = temp->link) { counter++; }
    return counter + 1;
}

void traverse(struct node* head) {
    struct node* temp;
    if (head == NULL) {
        printf("\nEmpty List: ");
    } else {
        printf("\nList: ");
        temp = head;
        while (temp != NULL) {
            if (temp->link == NULL) {
                printf("%d, %p", temp->data, temp->link);
            } else {
                printf("%d, %p --> ", temp->data, temp->link);
            }
            temp = temp->link;
        }
    }
}

void concat(struct node** ptr_to_head1, struct node** ptr_to_head2) {
    struct node* ptr = *ptr_to_head1;
    while (ptr->link != NULL) { ptr = ptr->link; }
    ptr->link = *ptr_to_head2;
}

int main() {
    struct node* head = NULL;

    return 0;
}
