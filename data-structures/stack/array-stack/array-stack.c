#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct stack {
    int* values;
    int array_capacity;
    int top;
};

struct stack* create_stack() {
    struct stack* new_stack = (struct stack*)malloc(sizeof(struct stack));
    // initialize top to -1 since stack is empty
    new_stack->top = -1;
    // initialize array of size 1
    new_stack->array_capacity = 1;
    new_stack->values = (int*)malloc(new_stack->array_capacity * sizeof(int));
    return new_stack;
}

bool is_full(struct stack* stack_ptr) {
    if (stack_ptr->array_capacity - 1 == stack_ptr->top) {
        return true;
    }
    return false;
}

bool is_empty(struct stack* stack_ptr) {
    if (stack_ptr->top == -1) {
        return true;
    }
    return false;
}

void pop(struct stack* stack_ptr) {
    if (stack_ptr->top == -1) {
        printf("Stack is empty!");
    }
    stack_ptr->top--;
}

void push(struct stack* stack_ptr, int value) {
    if (is_full(stack_ptr)) {
        // double the array capacity and reallocate memory
        stack_ptr->array_capacity *= 2;
        stack_ptr->values = realloc(stack_ptr->values, sizeof(int) * stack_ptr->array_capacity);
    }
    stack_ptr->values[++stack_ptr->top] = value;
}

int peek(struct stack* stack_ptr) {
    if (is_empty(stack_ptr)) {
        printf("stack is empty, throwing garbage!");
    }
    return stack_ptr->values[stack_ptr->top];
}

int main() {
    struct stack* stack1 = create_stack();

    return 0;
}
