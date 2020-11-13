#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int order;
    int* values;
    struct Node** links;
};

typedef struct Node Node;

// function for printing nodes
void print_node(Node* node) {
    printf("[");
    for (int i = 0; i < node->order - 1; i++) {
        if (i == node->order - 2) {
            printf("%d", node->values[i]);
        } else {
            printf("%d ", node->values[i]);
        }
    }
    printf("]");
}

// function for creating nodes
Node* create_node(int* values, int order) {
    // Number of values in each node = (order - 1)
    // Number of pointers in each node = order
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->order = order;
    new_node->values = values;
    new_node->links = (Node**)malloc(sizeof(Node*) * order);
    for (int i = 0; i < order; ++i) {
        new_node->links[i] = NULL;
    }
    return new_node;
}

Node* create_tree(int order) {
    Node* root = create_node(NULL, 3);
    return root;
}

bool node_empty(Node* node) {
    if (node == NULL || node->values == NULL) {
        return true;
    }
    for (int i = 0; i < node->order - 1; ++i) {
        if (node->values[i] == 0) {
            return true;
        }
    }
    return false;
}

void insert(int value, Node* root) {
    if (root->values == NULL) {
        // root is initialized with NULL for `values`
        // we can access order of overall tree from here
        int* values = (int*)malloc(sizeof(int) * root->order - 1);
        root->values = values;
        root->values[0] = value;
    } else {
        Node* iter = root;
        Node* parent;
        while (!node_empty(iter)) {
            parent = iter;
            // find next node based on `value`
            int i;
            for (i = 0; i < root->order - 1; ++i) {
                if (value < iter->values[i]) {
                    break;
                }
            }
            iter = iter->links[i];
        }
        if (iter == NULL) {
            for (int i = 0; i < root->order - 1; ++i) {
                if (value < parent->values[i]) {
                    int* values = (int*)malloc(sizeof(int) * root->order - 1);
                    Node* node = create_node(values, root->order);
                    node->values[0] = value;
                    parent->links[i] = node;
                    break;
                }
            }
        } else {
            for (int i = 0; i < iter->order - 1; ++i) {
                if (iter->values[i] == 0) {
                    iter->values[i] = value;
                }
            }
        }
    }
}

int main() {
    Node* root = create_tree(3);
    insert(3, root);
    insert(5, root);
    insert(4, root);
    printf("%d", root->links[1]->values[0]);
    return 0;
}
