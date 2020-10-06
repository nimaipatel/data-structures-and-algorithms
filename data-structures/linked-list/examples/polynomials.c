#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int power;
    struct Node* link;
};

void print_node(struct Node* node) {
    printf("(%d %d)", node->coeff, node->power);
}

struct Node* create_node(int coeff, int power) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->coeff = coeff;
    new_node->power = power;
    new_node->link = NULL;
    return new_node;
}

// traverse to end and insert node
void insert_end(struct Node** head_ref, int coeff, int power) {
    struct Node* new_node = create_node(coeff, power);
    struct Node* iter;
    if (*head_ref == NULL) {
        *head_ref = new_node;
    } else {
        iter = *head_ref;
        while (iter->link != NULL) {
            iter = iter->link;
        }
        iter->link = new_node;
    }
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;

    insert_end(&head1, 5, 2);
    insert_end(&head1, 3, 1);
    insert_end(&head1, 2, 0);

    insert_end(&head2, 2, 2);
    insert_end(&head2, 5, 0);

    return 0;
}
