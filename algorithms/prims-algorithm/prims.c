#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int n_vertices;
    double *arr;
} AdjacencyMatrix;

typedef struct {
    int a, b;
} Pair;

/* returns cost of edge formed by vertices `i` and `j` in
 * graph represented by adjacency matrix `matrix` */
double
cost(AdjacencyMatrix * matrix, int i, int j)
{
    return matrix->arr[i * matrix->n_vertices + j];
}

/* sets cost to `cost` between vertices `i` and `j` of
 * graph `matrix` */
void
set_cost(AdjacencyMatrix *matrix, int i, int j, double cost)
{
    matrix->arr[i * matrix->n_vertices + j] = matrix->arr[j * matrix->n_vertices + i] = cost;
}

/* creates matrix with `n` rows and columns to represent graph with
 * `n` nodes and initializes all edges to infinity i.e. not edges */
AdjacencyMatrix *
create_matrix(int n_vertices)
{
    AdjacencyMatrix *matrix = (AdjacencyMatrix*)malloc(sizeof(AdjacencyMatrix));
    matrix->n_vertices = n_vertices;
    matrix->arr = (double*)malloc(n_vertices * n_vertices * sizeof(double));
    for (int i = 0; i < matrix->n_vertices * matrix->n_vertices; ++i) {
        matrix->arr[i] = INFINITY;
    }
    return matrix;
}

/* destructor for matrix created with `create_matrix` */
void
destroy_matrix(AdjacencyMatrix *matrix)
{
    free(matrix->arr);
    free(matrix);
}

/* gets edge with minimum cost from the graph */
Pair
get_min_cost_edge(AdjacencyMatrix * matrix)
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

/* function to print square matrix */
void 
print_matrix(AdjacencyMatrix *matrix)
{
    for (int i = 0; i < matrix->n_vertices; ++i) {
        for (int j = 0; j < matrix->n_vertices; ++j) {
            printf("%.0lf\t", cost(matrix, i, j));
        }
        printf("\n");
    }
}

/* function accepts a graph represented by adjacency matrix `matrix`
 * and returns its MST's adjacency matrix */
AdjacencyMatrix *
prims_algorithm(AdjacencyMatrix *matrix)
{
    AdjacencyMatrix *MST = create_matrix(matrix->n_vertices);
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
    /* we represent including `k` and `l` in MST by
     * setting their keys in `near` to -1 */
    near[k] = near[l] = -1;
    /* adjaceny matrix will have `n_vertices - 1` edges
     * we have filled one edge so loop has to run 
     * `n_vertices - 2` times */
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
    AdjacencyMatrix * matrix = create_matrix(6);
    set_cost(matrix, 0, 1, 8);
    set_cost(matrix, 0, 2, 1);
    set_cost(matrix, 1, 2, 5);
    set_cost(matrix, 1, 3, 2);
    set_cost(matrix, 2, 4, 7);
    set_cost(matrix, 3, 4, 2);
    set_cost(matrix, 3, 5, 3);
    set_cost(matrix, 4, 5, 15);
    AdjacencyMatrix *MST = prims_algorithm(matrix);
    print_matrix(matrix);
    printf("\n");
    print_matrix(MST);
    destroy_matrix(matrix);
    destroy_matrix(MST);
    return 0;
}
