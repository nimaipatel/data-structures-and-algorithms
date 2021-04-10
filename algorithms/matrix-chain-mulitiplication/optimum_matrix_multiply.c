#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
matrix_chain_mul(int *d, int n)
{
	double cost[n][n];
	for (int i = 1; i < n; ++i)
		cost[i][i] = 0;

	for (int l = 2; l < n; ++l) {
		for (int i = 1; i < n - l + 1; ++i) {
			int j = i + l - 1;
			cost[i][j] = INFINITY;
			for (int k = i; k <= j - 1; ++k) {
				int q = cost[i][k] + cost[k + 1][j]
				        + d[i - 1] * d[k] * d[j];
				if (q < cost[i][j])
					cost[i][j] = q;
			}
		}
	}
	return cost[1][n - 1];
}

int
main()
{
	int n;
	printf("Enter number of matrices: ");
	scanf("%d", &n);
	int d[n + 1];
	for (int i = 0; i < n + 1; ++i) {
		printf("Enter value for d%d: ", i);
		scanf("%d", d + i);
	}

	printf("Number of operations for optimum pairing: %d\n",
	        matrix_chain_mul(d, n + 1));
	return 0;
}
