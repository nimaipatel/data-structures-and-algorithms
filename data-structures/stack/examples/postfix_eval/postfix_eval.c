#include <assert.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack[100];
int top = -1;

bool is_empty() {
    if (top == -1) {
        return true;
    }
    return false;
}

bool is_operator(char c) {
    if (c == '^' || c == '+' || c == '*' || c == '-' || c == '/') {
        return true;
    }
    return false;
}

bool is_operand(char c) {
    if (c >= '1' && c <= '9') {
        return true;
    }
    return false;
}

int pres(char c) {
    assert(is_operator(c));
    if (c == '^') {
        return 2;
    } else if (c == '/' || c == '*') {
        return 1;
    } else {
        return 0;
    }
}

void push(int c) {
    stack[++top] = c;
}

void pop() {
    if (top == -1) {
        printf("Popping from empty stack!");
        return;
    } else {
        top--;
    }
}

int peek() {
    if (top == -1) {
        printf("Peeking empty stack!");
        return '\0';
    }
    return stack[top];
}

void append_char(char* s, char c) {
    char* iter = s;
    while (*iter != '\0') {
        iter++;
    }
    *iter = c;
}

int perform(char oper, int a, int b) {
    assert(is_operator(oper));
    switch (oper) {
        case '^':
            return pow(b, a);
            break;
        case '*':
            return b * a;
            break;
        case '/':
            return b / a;
            break;
        case '+':
            return b + a;
            break;
        case '-':
            return b - a;
            break;
    }
    return 0;
}

int eval_postfix(char* postfix) {
    char* iter = postfix;
    while (*iter != '\0') {
        if (is_operand(*iter)) {
            char substring[10] = "";
            while (*iter != ' ') {
                append_char(substring, *iter);
                iter++;
            }
            push(atoi(substring));
        } else if (is_operator(*iter)) {
            int operand1 = peek();
            pop();
            int operand2 = peek();
            pop();
            int result = perform(*iter, operand1, operand2);
            push(result);
        }
        iter++;
    }
    return peek();
}

int main() {
    char postfix[100] = "";
    printf("Enter postfix expression: ");
    fgets(postfix, 100, stdin);
    int res = eval_postfix(postfix);
    printf("%d", res);
}
