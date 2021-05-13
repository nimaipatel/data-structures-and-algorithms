#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[100];
int top = -1;

// check if stack is empty
bool
is_empty()
{
	if (top == -1) {
		return true;
	}
	return false;
}

// check if character is an operator
bool
is_operator(char c)
{
	if (c == '^' || c == '+' || c == '*' || c == '-' || c == '/') {
		return true;
	}
	return false;
}

// check if character is an operand
bool
is_operand(char c)
{
	if (c >= 'a' && c <= 'z') {
		return true;
	}
	if (c >= 'A' && c <= 'Z') {
		return true;
	}
	return false;
}

// assign precedence to every operator
// use to compare precedence
int
pres(char c)
{
	assert(is_operator(c));
	if (c == '^') {
		return 2;
	} else if (c == '/' || c == '*') {
		return 1;
	} else {
		return 0;
	}
}

// push to stack
void
push(char c)
{
	stack[++top] = c;
}

// pop from stack
// DOESN'T return, so peek first
void
pop()
{
	if (top == -1) {
		printf("Popping from empty stack!");
		return;
	} else {
		top--;
	}
}

// return values at top of stack
char
peek()
{
	if (top == -1) {
		printf("Peeking empty stack!");
		return '\0';
	}
	return stack[top];
}

// print postfix expression
void
print_postfix(char *infix)
{
	int l = 0;
	char *c = infix;
	while (*c != '\0') {
		l++;
		c++;
	}
	printf("Postfix expression is: ");
	for (int i = 0; i < l; i++) {
		if (is_operand(infix[i])) {
			printf("%c", infix[i]);
		} else if (is_operator(infix[i])) {
			while (!is_empty() && peek() != '(' &&
			       pres(peek()) >= pres(infix[i])) {
				printf("%c", peek());
				pop();
			}
			push(infix[i]);
		} else if (infix[i] == '(') {
			push(infix[i]);
		} else if (infix[i] == ')') {
			while (!is_empty() && peek() != '(') {
				printf("%c", peek());
				pop();
			}
			pop();
		}
	}
	while (!is_empty()) {
		printf("%c", peek());
		pop();
	}
	printf("\n");
}

// driver function
int
main()
{
	char infix[100];
	printf("Enter infix expression: ");
	fgets(infix, 100, stdin);
	print_postfix(infix);
	return 0;
}
