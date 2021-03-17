#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int val;
	struct Node *parent;
} Node;

typedef struct {
	Node ver1, ver2;
	double cost;
} GraphEdge;

Node *
create_node(int v)
{
	Node *node = (Node*)malloc(sizeof(Node));
	node->val = v;
	node->parent = NULL;
	return node;
}

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

Node *
set_find(Node *node)
{
	if (node->parent == NULL) {
		return node;
	} else {
		Node *iter = node;
		while (iter->parent != NULL)
			iter = iter->parent;
		return iter;
	}
}

void
kruskals_algorith(GraphEdge **heap, int n)
{
	build_min_heap(heap, n);
	double mincost = 0;
	int i = 0;
	int heapsize = n;
	while (i < n-1 && heapsize != 0) {
		GraphEdge *tmp = heap[0];
		heap[0] = heap[heapsize-1];
		heap[heapsize-1] = tmp;
		for (int j = 0 ; j < 4 ; j++) printf("%.0lf ", heap[j]->cost);
		printf("\t");
		--heapsize;
		min_heapify(heap, n, 0);
		for (int j = 0 ; j < 4 ; j++) printf("%.0lf ", heap[j]->cost);
		printf("\n");
	}
}

int
main()
{
	GraphEdge e1 = { .ver1 = 1, .ver2 = 2, .cost = 12.0 };
	GraphEdge e2 = { .ver1 = 1, .ver2 = 2, .cost = 1.0 };
	GraphEdge e3 = { .ver1 = 1, .ver2 = 2, .cost = 112.0 };
	GraphEdge e4 = { .ver1 = 1, .ver2 = 2, .cost = 152.0 };
	GraphEdge *heap[] = {
		&e1,
		&e2,
		&e3,
		&e4,
	};
	kruskals_algorith(heap, 4);
	return 0;
}
