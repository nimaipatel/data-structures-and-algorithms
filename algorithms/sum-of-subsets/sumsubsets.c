#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void
sum_of_sub(int size, bool *sol, int *W, int s, int k, int r, int M)
{
	sol[k] = true;
	if (s + W[k] == M) {
		for (int i = 0; i < k + 1; ++i) {
			if (sol[i]) {
				printf("%d ", W[i]);
			}
		}
		printf("\n");
	} else {
		if (s + W[k] + W[k + 1] <= M) {
			sum_of_sub(size, sol, W, s + W[k], k + 1, r - W[k], M);
		}
		if (s + r - W[k] >= M && s + W[k + 1] <= M) {
			sol[k] = false;
			sum_of_sub(size, sol, W, s, k + 1, r - W[k], M);
		}
	}
}

int
main(int argc, char **argv) {
	/* last argument is M and all before it are part of the set */
	int size = argc - 2;
	int *W = malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i) {
		W[i] = atoi(argv[i + 1]);
	}
	int M = atoi(argv[argc - 1]);

	bool *sol = malloc(sizeof(bool) * size);

	int sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += W[i];
	}

	sum_of_sub(size, sol, W, 0, 0, sum, M);

	return 0;
}
