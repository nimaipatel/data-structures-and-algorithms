#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *next;
};

typedef struct Node Node;

Node *
create_node(int value)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = value;
	node->next = NULL;
	return node;
}

void
enqueue_rear(Node **head_ref, Node **tail_ref, int value)
{
	Node *node = create_node(value);
	if (*head_ref == NULL && *tail_ref == NULL) {
		*head_ref = *tail_ref = node;
	} else {
		(*tail_ref)->next = node;
		*tail_ref = node;
	}
}

void
enqueue_front(Node **head_ref, Node **tail_ref, int value)
{
	Node *node = create_node(value);
	if (*head_ref == NULL && *tail_ref == NULL) {
		*head_ref = *tail_ref = node;
	} else {
		node->next = *head_ref;
		*head_ref = node;
	}
}

void
dequeue_front(Node **head_ref, Node **tail_ref)
{
	Node *to_remove = *head_ref;
	if (*head_ref == NULL) {
		printf("QUEUE IS EMPTY\n");
	} else if (*head_ref == *tail_ref) {
		*head_ref = *tail_ref = NULL;
	} else {
		*head_ref = (*head_ref)->next;
	}
	free(to_remove);
}

void
dequeue_rear(Node **head_ref, Node **tail_ref)
{
	Node *to_remove = *tail_ref;
	if (*head_ref == NULL) {
		printf("QUEUE IS EMPTY\n");
	} else if (*head_ref == *tail_ref) {
		*head_ref = *tail_ref = NULL;
	} else {
		Node *iter = *head_ref;
		while (iter->next != to_remove) {
			iter = iter->next;
		}
		*tail_ref = iter;
		iter->next = NULL;
	}
	free(to_remove);
}

void
traverse(Node **head_ref, Node **tail_ref)
{
	printf("QUEUE: ");
	Node *iter = *head_ref;
	while (iter != NULL) {
		printf("%d ", iter->value);
		iter = iter->next;
	}
	printf("\n");
}

int
main()
{
	Node *head = NULL;
	Node *tail = NULL;
	int option;
	do {
		printf("> Enter 0 to enqueue at rear\n");
		printf("> Enter 1 to enqueue at front\n");
		printf("> Enter 2 to dequeue at front\n");
		printf("> Enter 3 to dequeue at rear\n");
		scanf("%d", &option);
		if (option == 0) {
			printf("Enter value: ");
			int value;
			scanf("%d", &value);
			enqueue_rear(&head, &tail, value);
		} else if (option == 1) {
			printf("Enter value: ");
			int value;
			scanf("%d", &value);
			enqueue_front(&head, &tail, value);
		} else if (option == 2) {
			dequeue_front(&head, &tail);
		} else if (option == 3) {
			dequeue_rear(&head, &tail);
		}
		traverse(&head, &tail);
	} while (option >= 0 && option <= 3);
	return 0;
}
