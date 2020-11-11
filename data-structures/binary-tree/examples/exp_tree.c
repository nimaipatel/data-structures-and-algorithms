#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    char value;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

Node* stack[100];
int top = -1;

Node* root = NULL;

bool is_operator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        return true;
    }
    return false;
}

bool is_operand(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    return false;
}

void push(Node* node) {
    stack[++top] = node;
}

Node* pop() {
    return stack[top--];
}

Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

void preorder(Node* node) {
    if (node != NULL) {
        printf("%c", node->value);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(Node* node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%c", node->value);
        inorder(node->right);
    }
}

void postorder(Node* node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        printf("%c", node->value);
    }
}

void display() {
    printf("Preorder: ");
    preorder(stack[top]);
    printf("\n");
    printf("inorder: ");
    inorder(stack[top]);
    printf("\n");
    printf("postorder: ");
    postorder(stack[top]);
    printf("\n");
}

void evalaute(char* expression) {
    char* iter = expression;

    while (*iter != '\0') {
        if (is_operand(*iter)) {
            Node* node = create_node(*iter);
            push(node);
        } else if (is_operator(*iter)) {
            Node* node = create_node(*iter);
            node->right = pop();
            node->left = pop();
            push(node);
        }
        iter++;
    }

    display();
}

int main() {
    char postfix[100];
    printf("Enter postfix expression: ");
    fgets(postfix, 100, stdin);
    evalaute(postfix);
    return 0;
}
