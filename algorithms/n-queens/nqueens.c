#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool
place(int size, int *sol, int row, int col)
{
	for (int i = 0; i < row; ++i) {
		if (sol[i] == col || abs(sol[i] - col) == abs(i - row)) {
			return false;
		}
	}
	return true;
}

void
n_queens(int size, int *sol, int row) {
	for (int col = 0; col < size; ++col) {
		if (place(size, sol, row, col)) {
			sol[row] = col;
			if (row == size - 1) {
				for (int i = 0; i < size; ++i)
					printf("%d\t", sol[i]);
				printf("\n");
			} else {
				n_queens(size, sol, row + 1);
			}
		}
	}
}

int
main(int argc, char **argv) {
	int size = atoi(argv[1]);
	int *sol = malloc(sizeof(int) * size); 
	n_queens(size, sol, 0);
	free(sol);
	return 0;
}
