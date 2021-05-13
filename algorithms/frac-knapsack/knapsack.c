#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* return type of `solve_knapsack` */
typedef struct {
	double *fractions, profit;
} Pair;

void
swap(double *a, double *b)
{
	/* swap two doubles by reference */
	double temp = *a;
	*a = *b;
	*b = temp;
}

void
sort(unsigned int n_items, double *profits, double *weights)
{
	/* function to sort array of profits and weights in increasing order of profit/weight */
	for (int i = 0; i < n_items; ++i) {
		for (int j = 0; j < n_items - 1; ++j) {
			if ((profits[j] / weights[j]) <
			    (profits[j + 1] / weights[j + 1])) {
				swap(profits + j, profits + j + 1);
				swap(weights + j, weights + j + 1);
			}
		}
	}
}

Pair *
solve_knapsack(unsigned int n_items, double *profits, double *weights,
	       double max_weight)
{
	sort(n_items, profits, weights);
	/* array to store faction of each item selected */
	double *fractions = (double *)malloc(n_items * sizeof(double));
	/* initialize all fractions to 0 */
	memset(fractions, 0, n_items);
	double space_left = max_weight, cuml_profit = 0;
	int i = 0;
	for (; i < n_items; ++i) {
		if (weights[i] > space_left)
			break;
		fractions[i] = 1;
		space_left -= weights[i];
		cuml_profit += profits[i];
	}
	if (i <= n_items) {
		fractions[i] = space_left / weights[i];
		cuml_profit += profits[i] * fractions[i];
	}
	Pair *answer = (Pair *)malloc(sizeof(Pair));
	answer->fractions = fractions;
	answer->profit = cuml_profit;
	return answer;
}

int
main()
{
	unsigned int n_items;
	printf("Enter number of items: ");
	scanf("%d", &n_items);
	double profits[n_items], weights[n_items], max_weight;
	printf("Enter capacity of knapsack: ");
	scanf("%lf", &max_weight);
	printf("Enter profits: ");
	for (int i = 0; i < n_items; ++i)
		scanf("%lf", profits + i);
	printf("Enter weights: ");
	for (int i = 0; i < n_items; ++i)
		scanf("%lf", weights + i);
	Pair *answer = solve_knapsack(n_items, profits, weights, 16);
	printf("Answer vector is: ");
	for (int i = 0; i < 6; ++i)
		printf("%.2f ", answer->fractions[i]);
	printf("\nProfit is: %.2f\n", answer->profit);
	return 0;
}
