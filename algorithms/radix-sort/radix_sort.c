#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* values;
    int capacity;
    int head_index;
    int tail_index;
} Queue;

// function to create circular queue
// of size `capacity`
Queue* create_queue(int capacity) {
    Queue* new_queue = (Queue*)malloc(sizeof(Queue));
    new_queue->capacity = capacity;
    int* values = (int*)malloc(sizeof(int) * capacity);
    new_queue->values = values;
    new_queue->head_index = new_queue->tail_index = -1;
    return new_queue;
}

bool is_full(Queue* queue) {
    if ((queue->tail_index + 1) % queue->capacity == queue->head_index) {
        return true;
    }
    return false;
}

bool is_empty(Queue* queue) {
    if (queue->head_index == -1 && queue->tail_index == -1) {
        return true;
    }
    return false;
}

void enqueue(Queue* queue, int value) {
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

void dequeue(Queue* queue) {
    if (is_empty(queue)) {
        printf("QUEUE IS EMPTY\n");
    } else if (queue->head_index == queue->tail_index) {
        queue->head_index = queue->tail_index = -1;
    } else {
        queue->head_index++;
        queue->head_index %= queue->capacity;
    }
}

int front(Queue* queue) {
    if (is_empty(queue)) {
        printf("QUEUE IS EMPTY\n");
        return -1;
    } else {
        return queue->values[queue->head_index];
    }
}

void sort(int n, int arr[n], int d) {
    Queue* Q[10];
    for (int p = 0; p < 10; ++p) {
        Q[p] = create_queue(10);
    }
    int D = 1;
    for (int k = 0; k < d; ++k) {
        D *= 10;
        for (int i = 0; i <= n; ++i) {
            int t = (arr[i] % D) / (D / 10);
            enqueue(Q[t], arr[i]);
        }
        int j = 0;
        for (int p = 0; p < 10; ++p) {
            while (!is_empty(Q[p])) {
                arr[j] = front(Q[p]);
                dequeue(Q[p]);
                ++j;
            }
        }
    }
}

void print_array(int n, int arr[n]) {
    for (int i = 1; i < n + 1; ++i) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int l;
    printf("Enter length of array: ");
    scanf("%d", &l);
    int* arr = (int*)malloc(sizeof(int) * l);
    for (int i = 0; i < l; ++i) {
        scanf("%d", arr + i);
    }
    // setting max digits to 5
    sort(l, arr, 5);
    print_array(l, arr);
    return 0;
}
