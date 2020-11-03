#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node** root_ref, int value) {
    if (*root_ref == NULL) {
        *root_ref = create_node(value);
    } else if (value < (**root_ref).value) {
        (**root_ref).left = insert(&((**root_ref).left), value);
    } else {
        (**root_ref).right = insert(&((**root_ref).right), value);
    }
    return *root_ref;
}

bool search(Node* root, int value) {
    if (!root) {
        return false;
    } else if (value == root->value) {
        return 1;
    } else if (value < root->value) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

Node* find_min(Node** root_ref) {
    if (*root_ref == NULL) {
        return NULL;
    } else if ((**root_ref).left == NULL) {
        return *root_ref;
    } else {
        return find_min(&((**root_ref).left));
    }
}

Node* find_max(Node** root_ref) {
    if (*root_ref == NULL) {
        return NULL;
    } else if ((**root_ref).right == NULL) {
        return *root_ref;
    } else {
        return find_max(&(**root_ref).right);
    }
}

Node* delete (Node** root_ref, int value) {
    if (*root_ref == NULL) {
        return *root_ref;
    } else if (value < (**root_ref).value) {
        (**root_ref).left = delete (&((**root_ref).left), value);
    } else if (value > (**root_ref).value) {
        (**root_ref).right = delete (&((**root_ref).right), value);
    } else {
        // CASE 1: no children node
        if ((**root_ref).left == NULL && (**root_ref).right == NULL) {
            Node* to_free = *root_ref;
            *root_ref = NULL;
            free(to_free);
        }
        // CASE 2: one child
        else if ((**root_ref).left == NULL) {
            Node* to_free = *root_ref;
            *root_ref = (**root_ref).right;
            free(to_free);
        } else if ((**root_ref).right == NULL) {
            Node* to_free = *root_ref;
            *root_ref = (**root_ref).left;
            free(to_free);
        }
        // CASE 3: two children
        else {
            Node* temp = find_min(&(**root_ref).right);
            (**root_ref).value = temp->value;
            (**root_ref).right = delete (&((**root_ref).right), temp->value);
        }
    }
    return *root_ref;
}

void inorder_traversal(Node* node) {
    if (node != NULL) {
        inorder_traversal(node->left);
        printf("%d ", node->value);
        inorder_traversal(node->right);
    }
}

void preorder_traversal(Node* node) {
    if (node != NULL) {
        printf("%d ", node->value);
        inorder_traversal(node->left);
        inorder_traversal(node->right);
    }
}

void postorder_traversal(Node* node) {
    if (node != NULL) {
        inorder_traversal(node->left);
        inorder_traversal(node->right);
        printf("%d ", node->value);
    }
}

int height(Node* node) {
    if (node == NULL) {
        return -1;
    } else {
        int left_height = height(node->left);
        int right_height = height(node->right);
        if (left_height > right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }
}

int count_nodes(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return count_nodes(root->left) + count_nodes(root->right) + 1;
    }
}

int count_internal_nodes(Node* root) {
    if (root == NULL) {
        return 0;
    } else if (root->left == NULL && root->right == NULL) {
        return 0;
    } else {
        return count_internal_nodes(root->left) +
               count_internal_nodes(root->right) + 1;
    }
}

int count_external_nodes(Node* root) {
    if (root == NULL) {
        return 0;
    } else if (root->left == NULL && root->right == NULL) {
        return 1;
    } else {
        return count_external_nodes(root->left) +
               count_external_nodes(root->right);
    }
}

void mirror(Node** root_ref) {
    if (*root_ref != NULL) {
        mirror(&((**root_ref).left));
        mirror(&((**root_ref).right));
        Node* temp = (**root_ref).left;
        (**root_ref).left = (**root_ref).right;
        (**root_ref).right = temp;
    }
}

int main() {
    Node* root = NULL;
    insert(&root, 3);
    insert(&root, 5);
    insert(&root, 4);
    insert(&root, 2);
    insert(&root, 7);
    insert(&root, -7);
    int choice;
    int v;
    inorder_traversal(root);
    printf("\n");
    do {
        printf("\n0 to insert\n1 to delete\nAny other number to exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("Enter value you want to insert:\n");
                scanf("%d", &v);
                insert(&root, v);
                inorder_traversal(root);
                printf("\n");
                break;
            case 1:
                printf("Enter value you want to delete\n");
                scanf("%d", &v);
                delete (&root, v);
                inorder_traversal(root);
                break;
            default:
                printf("Exiting...\n");
                break;
        }
    } while (choice == 1 || choice == 0);
    return 0;
}
