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
	int *arr = start, n = end - start;
	for (int i = 1; i < n; ++i) {
		/*print_array(start, end);*/
		int key = arr[i], j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

int
main()
{
	int arr[] = { 12, 32, 9, 17, 8, 5 };
	sort(arr, arr + 6);
	print_array(arr, arr + 6);
	return 0;
}
