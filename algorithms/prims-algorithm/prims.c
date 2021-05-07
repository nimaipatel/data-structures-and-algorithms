#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
	int n_vertices;
	double *arr;
} Matrix;

typedef struct {
	int a, b;
} Pair;

double
cost(Matrix * matrix, int i, int j)
{
	return matrix->arr[i * matrix->n_vertices + j];
}

void
set_cost(Matrix *matrix, int i, int j, double cost)
{
	matrix->arr[i * matrix->n_vertices + j] =
		matrix->arr[j * matrix->n_vertices + i] = cost;
}

Matrix *
create_matrix(int n_vertices)
{
	Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
	matrix->n_vertices = n_vertices;
	matrix->arr = (double*)malloc(n_vertices * n_vertices * sizeof(double));
	for (int i = 0; i < matrix->n_vertices * matrix->n_vertices; ++i) {
		matrix->arr[i] = INFINITY;
	}
	return matrix;
}

void
destroy_matrix(Matrix *matrix)
{
	free(matrix->arr);
	free(matrix);
}

Pair
get_min_cost_edge(Matrix * matrix)
{
	Pair min;
	min.a = min.b = 0;
	for (int i = 0; i < matrix->n_vertices; ++i) {
		for (int j = 0; j < matrix->n_vertices; ++j) {
			if ( cost(matrix, i, j) < cost(matrix, min.a, min.b) ) {
				min.a = i;
				min.b = j;
			}
		}
	}
	return min;
}

void 
print_matrix(Matrix *matrix)
{
	for (int i = 0; i < matrix->n_vertices; ++i) {
		for (int j = 0; j < matrix->n_vertices; ++j) {
			printf("%.0lf\t", cost(matrix, i, j));
		}
		printf("\n");
	}
}

Matrix *
prims_algorithm(Matrix *matrix)
{
	Matrix *MST = create_matrix(matrix->n_vertices);
	Pair min = get_min_cost_edge(matrix);
	int k = min.a, l = min.b;
	set_cost(MST, k, l, cost(matrix, k, l));
	double min_cost = cost(matrix, k, l);
	int * near = (int*)malloc(matrix->n_vertices * sizeof(int));
	for (int i = 0; i < matrix->n_vertices; ++i) {
		if ( cost(matrix, i, l) < cost(matrix, i, k) )
			near[i] = l;
		else
			near[i] = k;
	}
	printf("\n");
	near[k] = near[l] = -1;
	for (int _ = 1; _ <= matrix->n_vertices - 2; ++_) {
		int index;
		double min_cost = INFINITY;
		for (int j = 0; j < matrix->n_vertices; ++j) {
			if (near[j] != -1 && cost(matrix, j , near[j]) < min_cost) {
				index = j;
				min_cost = cost(matrix, j, near[j]);
			}
		}
		set_cost( MST, index, near[index], cost(matrix, index, near[index]) );
		min_cost += cost(matrix, index, near[index]);
		near[index] = -1;
		for (int k = 0; k < matrix->n_vertices; ++k) {
			if ( near[k] != -1 && cost(matrix, k, near[k]) > cost(matrix, k, index) ) {
				near[k] = index;
			}
		}
	}
	return MST;
}

int 
main()
{
	Matrix * matrix = create_matrix(6);
	set_cost(matrix, 0, 1, 3);
	set_cost(matrix, 0, 3, 4);
	set_cost(matrix, 0, 2, 1);

	set_cost(matrix, 1, 3, 5);
	set_cost(matrix, 1, 4, 3);

	set_cost(matrix, 2, 3, 5);
	set_cost(matrix, 2, 5, 3);

	set_cost(matrix, 5, 3, 6);
	set_cost(matrix, 5, 4, 2);

	Matrix *MST = prims_algorithm(matrix);
	print_matrix(matrix);
	printf("\n");
	print_matrix(MST);
	destroy_matrix(matrix);
	destroy_matrix(MST);
	return 0;
}
