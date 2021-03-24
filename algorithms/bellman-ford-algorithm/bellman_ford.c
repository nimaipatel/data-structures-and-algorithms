#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct {
	int u, v;
	double weight;
} typedef Edge;

struct {
	double *dist;
	int *pred;
} typedef Pair;

Pair *
bellman_ford (int n_verts, int n_edges, Edge **edges, int source)
{
	double *dist = (double*)malloc(sizeof(double) * n_verts);
	int *pred = (int*)malloc(sizeof(int) * n_verts);

	for (int i = 0; i < n_verts; ++i) {
		dist[i] = INFINITY;
		pred[i] = -1;
	}

	dist[source] = 0;

	/* relax edges `n_verts - 1` times */
	for (int _ = 1; _ <= n_verts - 1; ++_)
	{
		for (int i = 0; i < n_edges; ++i) {
			int u = edges[i]->u;
			int v = edges[i]->v;
			double w = edges[i]->weight;
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pred[v] = u;
			}
		}
	}

	/* check for negative edge cycles */
	for (int i = 0; i < n_edges; ++i) {
		int u = edges[i]->u;
		int v = edges[i]->v;
		int w = edges[i]->weight;
		if (dist[u] + w < dist[v])
			return NULL;
	}

	Pair * ret = (Pair*)malloc(sizeof(Pair));
	ret->dist = dist;
	ret->pred = pred;
	return ret;
}

int 
main()
{
	int n_verts = 4, n_edges = 4, source = 0;

	Edge **edges = (Edge**)malloc(sizeof(Edge*) * n_edges);

	for (int i = 0; i < n_edges; ++i) {
		edges[i] = (Edge*)malloc(sizeof(Edge));
	}

	edges[0]->u = 0; edges[0]->v = 1; edges[0]->weight = 1;
	edges[1]->u = 0; edges[1]->v = 3; edges[1]->weight = -7;
	edges[2]->u = 1; edges[2]->v = 3; edges[2]->weight = 2;
	edges[3]->u = 0; edges[3]->v = 2; edges[3]->weight = 3;

	Pair *res = bellman_ford(n_verts, n_edges, edges, 0);

	if (res == NULL) {
		printf("Negative edge cycle detected in given graph!\n");
		return 1;
	}

	for (int i = 0; i < n_verts; ++i) {
		printf("%lf\n", res->dist[i]);
	}

	free(res->dist);
	free(res->pred);
	free(res);
	for (int i = 0; i < n_edges; ++i)
		free(edges[i]);
	free(edges);
	return 0;
}
