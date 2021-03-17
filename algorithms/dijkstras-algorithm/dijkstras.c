#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
        unsigned int n_verts;
        double *arr;
} Matrix;

double
min(double a, double b)
{
        return a < b ? a : b;
}

void
set_edge(Matrix *matrix, unsigned int v1, unsigned int v2, double cost)
{
        matrix->arr[v1 * matrix->n_verts + v2] = cost;
}

double
cost(Matrix *matrix, unsigned int v1, unsigned int v2)
{
        return matrix->arr[v1 * matrix->n_verts + v2];
}

Matrix *
create_matrix(unsigned int n_verts)
{
        Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
        matrix->n_verts = n_verts;
        matrix->arr = (double*)malloc(sizeof(double) * n_verts * n_verts);
        for (unsigned int i = 0; i < n_verts; ++i) {
                for (unsigned int j = 0; j < n_verts; ++j) {
                        if (i == j)
                                set_edge(matrix, i, j, 0);
                        else
                                set_edge(matrix, i, j, INFINITY);
                }
        }
        return matrix;
}

void
destroy_matrix(Matrix *matrix)
{
        free(matrix->arr);
        free(matrix);
}

void
print_matrix(Matrix *matrix)
{
        for (int i = 0; i < matrix->n_verts; ++i) {
                for (int j = 0; j < matrix->n_verts; ++j) {
                        printf("%.0lf\t", cost(matrix, i,j));
                }
                printf("\n");
        }
}

unsigned int
min_cost_unvisited(Matrix *matrix, bool *visited, double *dist)
{
        int min;
        for (unsigned int i = 0; i < matrix->n_verts; ++i) {
                if (visited[i] == false)
                        min = i;
        }
        for (unsigned int i = 0; i < matrix->n_verts; ++i) {
                if (visited[i] == false && dist[i] < dist[min]) {
                        min = i;
                }
        }
        return min;
}

double *
dijkstras_algo(Matrix *matrix, unsigned int s)
{
        double *dist = (double*)malloc(sizeof(double) * matrix->n_verts);
        bool *visited = (bool*)malloc(sizeof(bool) * matrix->n_verts);
        for (unsigned int i = 0; i < matrix->n_verts; ++i)
        {
                visited[i] = false;
                dist[i] = cost(matrix, s, i);
        }
        visited[s] = true;
        dist[s] = 0;
        for (unsigned int _ = 2; _ < matrix->n_verts - 1; ++_){
                unsigned int u = min_cost_unvisited(matrix, visited, dist);
                visited[u] = true;
                for (unsigned int v = 0; v < matrix->n_verts; ++v) {
                        if (visited[v] == false) {
                                dist[v] = min(dist[v], 
                                              dist[u] + cost(matrix, u, v));
                        }
                }
        }
        free(visited);
        return dist;
}

int
main()
{
        Matrix *matrix = create_matrix(8);
        set_edge(matrix, 0, 1, 5);
        set_edge(matrix, 0, 7, 8);
        set_edge(matrix, 0, 4, 9);
        set_edge(matrix, 1, 3, 15);
        set_edge(matrix, 1, 2, 12);
        set_edge(matrix, 1, 7, 4);
        set_edge(matrix, 2, 6, 11);
        set_edge(matrix, 2, 3, 3);
        set_edge(matrix, 3, 6, 9);
        set_edge(matrix, 4, 7, 5);
        set_edge(matrix, 4, 5, 4);
        set_edge(matrix, 4, 6, 20);
        set_edge(matrix, 5, 2, 1);
        set_edge(matrix, 5, 6, 13);
        set_edge(matrix, 7, 2, 7);
        set_edge(matrix, 7, 5, 6);
        double *dist = dijkstras_algo(matrix, 0);
        for (int i = 0; i < matrix->n_verts; ++i)
                printf("%.0lf\t", dist[i]);
        free(matrix);
        free(dist);
        return 0;
}
