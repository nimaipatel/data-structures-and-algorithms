#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *values; // array of values stored in the queue
	int capacity; // capacity of array
	int head_index; // index of front of queue
	int tail_index; // index of rear of queue
} Queue;

Queue *
create_queue(int capacity)
{
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->capacity = capacity;
	queue->head_index = queue->tail_index = -1;
	queue->values = (int *)malloc(sizeof(int) * capacity);
	return queue;
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
enqueue_rear(Queue *queue, int value)
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
enqueue_front(Queue *queue, int value)
{
	if (is_full(queue)) {
		printf("QUEUE IS FULL\n");
	} else if (is_empty(queue)) {
		queue->head_index = queue->tail_index = 0;
		queue->values[0] = value;
	} else {
		queue->head_index--;
		queue->head_index += queue->capacity;
		queue->head_index %= queue->capacity;
		queue->values[queue->head_index] = value;
	}
}

void
dequeue_front(Queue *queue)
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

void
dequeue_rear(Queue *queue)
{
	if (is_empty(queue)) {
		printf("QUEUE IS EMPTY\n");
	} else if (queue->head_index == queue->tail_index) {
		queue->head_index = queue->tail_index = -1;
	} else {
		queue->tail_index--;
		queue->tail_index += queue->capacity;
		queue->tail_index %= queue->capacity;
	}
}

int
get_front(Queue *queue)
{
	return queue->values[queue->head_index];
}

int
get_rear(Queue *queue)
{
	return queue->values[queue->tail_index];
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
	printf("Enter capacity of DeQueue\n");
	int capacity;
	scanf("%d", &capacity);
	Queue *queue = create_queue(capacity);
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
			enqueue_rear(queue, value);
		} else if (option == 1) {
			printf("Enter value: ");
			int value;
			scanf("%d", &value);
			enqueue_front(queue, value);
		} else if (option == 2) {
			dequeue_front(queue);
		} else if (option == 3) {
			dequeue_rear(queue);
		}
		print_queue(queue);
	} while (option >= 0 && option <= 3);
	return 0;
}
