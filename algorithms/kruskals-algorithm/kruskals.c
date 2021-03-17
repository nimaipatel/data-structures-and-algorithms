#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int ver1, ver2;
	double cost;
} Edge;

typedef struct {
	Edge **edges;
	double mincost;
} Pair;

void
sort(Edge **edges, int n)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (edges[j]->cost > edges[j+1]->cost) {
				Edge *tmp = edges[j];
				edges[j] = edges[j+1];
				edges[j+1] = tmp;
			}
		}
	}
}

Edge **
kruskals_algorithm(Edge **edges, int n_edges, int n_verts)
{
	int *find = (int*)malloc(sizeof(int) * n_verts);
	Edge **mst_edges = (Edge**)malloc(sizeof(Edge*) * (n_verts - 1));
	double mincost = 0.0;
	for (int i = 0; i < n_verts; ++i)
		find[i] = i;
	sort(edges, n_edges);
	for (int i = 0; i < n_verts - 1; ++i) {
		int closest = -1;
		for (int j = 0; j < n_edges && closest == -1; ++j) {
			if (find[edges[j]->ver1] != find[edges[j]->ver2])
				closest = j;
		}
		mst_edges[i] = edges[closest];
		for (int j = 0; j < n_verts; ++j) {
			if (find[j] == edges[closest]->ver2)
				find[j] = edges[closest]->ver1;
		}
		mincost += edges[closest]->cost;
	}
	free(find);
	return mst_edges;
}

void
print_adj_matrix(Edge **edges, int n)
{
	for (int i = 0; i < n; ++i) {
		printf("%d -- %.0lf --> %d\n",
		       edges[i]->ver1, edges[i]->cost, edges[i]->ver2);
	}
}

int
main()
{
	Edge e0 = { .ver1 = 0, .ver2 = 1, .cost = 4 };
	Edge e1 = { .ver1 = 0, .ver2 = 3, .cost = 8 };
	Edge e2 = { .ver1 = 2, .ver2 = 3, .cost = 1 };
	Edge e3 = { .ver1 = 2, .ver2 = 1, .cost = 3 };
	Edge e4 = { .ver1 = 1, .ver2 = 3, .cost = 5 };
	Edge *edges[] = {
		&e0,
		&e1,
		&e2,
		&e3,
		&e4,
	};
	Edge **mst_edges = kruskals_algorithm(edges, 5, 4);
	print_adj_matrix(mst_edges, 3);
}
