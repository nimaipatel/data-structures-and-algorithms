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

Pair *
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
	Pair *ret = (Pair*)malloc(sizeof(Pair));
	ret->mincost = mincost;
	ret->edges = mst_edges;
	return ret;
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
	int n_verts, n_edges;
	printf("Enter number of vertices in graph: ");
	scanf("%d", &n_verts);
	printf("Enter number of edges in graph: ");
	scanf("%d", &n_edges);
	Edge **edges = (Edge**)malloc(sizeof(Edge*) * n_edges);
	for (int i = 0; i < n_edges; ++i) {
		int v1, v2;
		double cost;
		printf("Enter first vertex: ");
		scanf("%d",&v1);
		printf("Enter second vertex: ");
		scanf("%d",&v2);
		printf("Enter cost of this edge: ");
		scanf("%lf",&cost);
		edges[i] = (Edge*)malloc(sizeof(Edge));
		edges[i]->ver1 = v1;
		edges[i]->ver2 = v2;
		edges[i]->cost = cost;
	}

	Pair *mst = kruskals_algorithm(edges, n_edges, n_verts);
	printf("Adjacency matrix of MST is: \n");
	print_adj_matrix(mst->edges, n_verts - 1);

	for (int i = 0; i < n_edges; ++i) {
		free(edges[i]);
	}
	free(edges);
	free(mst->edges);
	free(mst);
	return 0;
}
