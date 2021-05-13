#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int *values;
	int capacity;
	int head_index;
	int tail_index;
} Queue;

// function to create circular queue
// of size `capacity`
Queue *
create_queue(int capacity)
{
	Queue *new_queue = (Queue *)malloc(sizeof(Queue));
	new_queue->capacity = capacity;
	int *values = (int *)malloc(sizeof(int) * capacity);
	new_queue->values = values;
	new_queue->head_index = new_queue->tail_index = -1;
	return new_queue;
}

bool
is_full(Queue *queue)
{
	if ((queue->tail_index + 1) % queue->capacity == queue->head_index) {
		return true;
	}
	return false;
}

bool
is_empty(Queue *queue)
{
	if (queue->head_index == -1 && queue->tail_index == -1) {
		return true;
	}
	return false;
}

void
enqueue(Queue *queue, int value)
{
	if (is_full(queue)) {
		printf("QUEUE IS FULL\n");
	} else if (is_empty(queue)) {
		queue->head_index = queue->tail_index = 0;
		queue->values[0] = value;
	} else {
		queue->tail_index++;
		queue->tail_index %= queue->capacity;
		queue->values[queue->tail_index] = value;
	}
}

void
dequeue(Queue *queue)
{
	if (is_empty(queue)) {
		printf("QUEUE IS EMPTY\n");
	} else if (queue->head_index == queue->tail_index) {
		queue->head_index = queue->tail_index = -1;
	} else {
		queue->head_index++;
		queue->head_index %= queue->capacity;
	}
}

int
front(Queue *queue)
{
	if (is_empty(queue)) {
		printf("QUEUE IS EMPTY\n");
		return -1;
	} else {
		return queue->values[queue->head_index];
	}
}

void
print_queue(Queue *queue)
{
	printf("Queue: ");
	for (int i = queue->head_index; i != queue->tail_index;
	     i++, i %= queue->capacity) {
		printf("%d ", queue->values[i]);
	}
	printf("%d ", queue->values[queue->tail_index]);
	printf("\n");
}

int
main()
{
	printf("Enter capacity of circular queue: ");
	int capacity;
	scanf("%d", &capacity);
	Queue *queue = create_queue(capacity);
	int option;
	do {
		printf("> Enter 1 to enqueue\n");
		printf("> Enter 0 to dequeue\n");
		printf("> Enter any other number to exit\n");
		scanf("%d", &option);
		if (option == 1) {
			printf("Enter number to enqueue: ");
			int value;
			scanf("%d", &value);
			enqueue(queue, value);
		} else if (option == 0) {
			dequeue(queue);
		}
		print_queue(queue);
	} while (option == 1 || option == 0);
	return 0;
}
