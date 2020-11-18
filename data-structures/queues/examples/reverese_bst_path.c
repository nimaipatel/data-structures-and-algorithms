#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
    int value;
    struct QueueNode* link;
} QueueNode;

QueueNode* create_queue_node(int value) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->value = value;
    node->link = NULL;
    return node;
}

void enqueue(QueueNode** head_ref, QueueNode** tail_ref, int value) {
    QueueNode* node = create_queue_node(value);
    if (*head_ref == NULL && *tail_ref == NULL) {
        *head_ref = *tail_ref = node;
    } else {
        (*tail_ref)->link = node;
        *tail_ref = node;
    }
}

void dequeue(QueueNode** head_ref, QueueNode** tail_ref) {
    if (*head_ref == NULL && *tail_ref == NULL) {
        printf("CAN'T DEQUEUE FROM EMPTY QUEUE\n");
    } else if (*head_ref == *tail_ref) {
        QueueNode* temp = *head_ref;
        *head_ref = *tail_ref = NULL;
        free(temp);
    } else {
        QueueNode* temp = *head_ref;
        *head_ref = (*head_ref)->link;
        free(temp);
    }
}

int queue_front(QueueNode* head) {
    if (head) {
        return head->value;
    } else {
        printf("QUEUE IS EMPTY\n");
        return 2147483647;
    }
}

typedef struct BSTNode {
    int value;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* create_BST_node(int value) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

BSTNode* insert_BST(BSTNode** root_ref, int value) {
    if (*root_ref == NULL) {
        *root_ref = create_BST_node(value);
    } else if (value < (**root_ref).value) {
        (**root_ref).left = insert_BST(&((**root_ref).left), value);
    } else {
        (**root_ref).right = insert_BST(&((**root_ref).right), value);
    }
    return *root_ref;
}

void __reverse_path(BSTNode** root_ref, int value, QueueNode** head_ref,
                    QueueNode** tail_ref) {
    if (*root_ref) {
        if (value < (*root_ref)->value) {
            enqueue(head_ref, tail_ref, (*root_ref)->value);
            __reverse_path(&((*root_ref)->left), value, head_ref, tail_ref);
            (*root_ref)->value = queue_front(*head_ref);
            dequeue(head_ref, tail_ref);
        } else if (value > (*root_ref)->value) {
            enqueue(head_ref, tail_ref, (*root_ref)->value);
            __reverse_path(&((*root_ref)->right), value, head_ref, tail_ref);
            (*root_ref)->value = queue_front(*head_ref);
            dequeue(head_ref, tail_ref);
        } else {
            enqueue(head_ref, tail_ref, (*root_ref)->value);
            (*root_ref)->value = queue_front(*head_ref);
            dequeue(head_ref, tail_ref);
        }
    }
}

void reverse_path(BSTNode** root_ref, int value) {
    QueueNode *head = NULL, *tail = NULL;
    __reverse_path(root_ref, value, &head, &tail);
}

void inorder_traversal(BSTNode* node) {
    if (node != NULL) {
        inorder_traversal(node->left);
        printf("%d ", node->value);
        inorder_traversal(node->right);
    }
}

void preorder_traversal(BSTNode* node) {
    if (node != NULL) {
        printf("%d ", node->value);
        inorder_traversal(node->left);
        inorder_traversal(node->right);
    }
}

void postorder_traversal(BSTNode* node) {
    if (node != NULL) {
        inorder_traversal(node->left);
        inorder_traversal(node->right);
        printf("%d ", node->value);
    }
}

int main() {
    BSTNode* root = NULL;
    insert_BST(&root, 5);
    insert_BST(&root, 3);
    insert_BST(&root, 7);
    insert_BST(&root, 2);
    insert_BST(&root, 4);
    insert_BST(&root, 6);
    insert_BST(&root, 8);
    reverse_path(&root, 7);
    inorder_traversal(root);
    return 0;
}
