#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int v1, v2;
	double cost;
} GraphEdge;

/*
 * heapify `heap` represented by array of
 * length `n` starting at index `i`
 */
void
min_heapify(GraphEdge **heap, int n, int i)
{
	int min = i;
	int left  = 2*i + 1;
	int right = 2*i + 2;

	if (left < n && heap[left]->cost < heap[min]->cost) {
		min = left;
	}
	if (right < n && heap[right]->cost < heap[min]->cost) {
		min = right;
	}
	/* if `min` is not minimum swap and recurse to check for child nodes */
	if (min != i) {
		GraphEdge *tmp = heap[i];
		heap[i] = heap[min];
		heap[min] = tmp;
		min_heapify(heap, n, min);
	}
}

void
build_min_heap(GraphEdge **heap, int n)
{
	for (int i = n / 2; i >= 0; --i) {
		min_heapify(heap, n, i);
	}
}

int
main()
{
	GraphEdge e1 = { .v1 = 1, .v2 = 2, .cost = 12.0 };
	GraphEdge e2 = { .v1 = 1, .v2 = 2, .cost = 1.0 };
	GraphEdge e3 = { .v1 = 1, .v2 = 2, .cost = 112.0 };
	GraphEdge e4 = { .v1 = 1, .v2 = 2, .cost = 152.0 };
	GraphEdge *heap[] = {
		&e1,
		&e2,
		&e3,
		&e4,
	};
	build_min_heap(heap, 4);
	return 0;
}
