#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void
__sum_of_sub(int size, bool *sol, int *set,
           int acc_sum, int curr, int rem, int aim)
{
	sol[curr] = true;
	if (acc_sum + set[curr] == aim) {
		for (int i = 0; i < curr + 1; ++i) {
			if (sol[i]) {
				printf("%d ", set[i]);
			}
		}
		printf("\n");
	} else {
		if (acc_sum + set[curr] + set[curr + 1] <= aim) {
			__sum_of_sub(size, sol, set,
			           acc_sum + set[curr],
			           curr + 1,
			           rem - set[curr],
			           aim);
		}
		if (acc_sum + rem - set[curr] >= aim &&
		    acc_sum + set[curr + 1] <= aim) {
			sol[curr] = false;
			__sum_of_sub(size, sol, set,
			           acc_sum,
			           curr + 1,
			           rem - set[curr],
			           aim);
		}
	}
}

void
sum_of_sub(int size, int *set, int aim)
{
	bool *sol = malloc(sizeof(bool) * size);

	int sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += set[i];
	}

	__sum_of_sub(size, sol, set, 0, 0, sum, aim);
}

int
main(int argc, char **argv) {
	/* last argument is M (target sum) and all arguments 
	 * before it are part of the set */
	int size = argc - 2;
	int *set = malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i) {
		set[i] = atoi(argv[i + 1]);
	}
	int aim = atoi(argv[argc - 1]);

	sum_of_sub(size, set, aim);
	return 0;
}
