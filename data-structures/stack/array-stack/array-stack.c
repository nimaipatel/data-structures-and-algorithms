#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct stack {
    int* values;
    int no_items;
};

struct stack* create_stack() {
    struct stack* new_stack = (struct stack*)malloc(sizeof(struct stack));
    new_stack->no_items = -1;
    return new_stack;
}

int main() {
    struct stack* stack1 = create_stack();

    push(stack1, 7);

    return 0;
}
