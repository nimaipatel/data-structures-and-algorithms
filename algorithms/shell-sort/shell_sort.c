#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void
print_array(int *start, int *end)
{
	printf("[");
	int *iter = start;
	for (; iter != end - 1; ++iter) {
		printf("%d, ", *iter);
	}
	printf("%d]\n", *iter);
}

void
sort(int *start, int *end)
{
	int n = end - start, *arr = start, interval = 1;
	while (interval < n / 3) {
		interval = interval * 3 + 1;
	}
	while (interval > 0) {
		printf("Interval size: %d\n", interval);
		for (int outter = interval; outter < n; ++outter) {
			print_array(start, end);
			int key = arr[outter];
			int inner = outter;
			while (inner > interval - 1 &&
			       arr[inner - interval] >= key) {
				arr[inner] = arr[inner - interval];
				inner -= interval;
			}
			arr[inner] = key;
		}
		--interval;
		interval /= 3;
	}
}

int
main()
{
	int l;
	int arr[100];
	printf("Enter length of array: ");
	scanf("%d", &l);
	for (int i = 0; i < l; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + l);
	print_array(arr, arr + l);
	return 0;
}
