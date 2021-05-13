#include <assert.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack[100];
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
	if (c >= '1' && c <= '9') {
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
push(int c)
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
int
peek()
{
	if (top == -1) {
		printf("Peeking empty stack!");
		return '\0';
	}
	return stack[top];
}

// append char ```c``` to string ```s```
void
append_char(char *s, char c)
{
	char *iter = s;
	while (*iter != '\0') {
		iter++;
	}
	*iter = c;
}

// perform operation ```oper```
// on ```a``` and ```b```
int
perform(char oper, int a, int b)
{
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

// return value of postfix expression
int
eval_postfix(char *postfix)
{
	char *iter = postfix;
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

// driver function
int
main()
{
	char postfix[100] = "";
	printf("Enter postfix expression: ");
	fgets(postfix, 100, stdin);
	int res = eval_postfix(postfix);
	printf("%d", res);
}
