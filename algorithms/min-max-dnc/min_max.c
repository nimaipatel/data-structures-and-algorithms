#include <stdio.h>
#include <stdlib.h>

struct pair {
	int max;
	int min;
};

struct pair *
__find_max_min(int *arr, int low, int high)
{
	int max, min;
	if (low == high) {
		max = arr[low];
		min = arr[low];
	} else if (low == high - 1) {
		if (arr[low] < arr[high]) {
			max = arr[high];
			min = arr[low];
		} else {
			max = arr[low];
			min = arr[high];
		}
	} else {
		int mid = (high + low) / 2;
		struct pair *l_pair = __find_max_min(arr, low, mid);
		struct pair *h_pair = __find_max_min(arr, mid + 1, high);
		if (l_pair->max > h_pair->max) {
			max = l_pair->max;
		} else {
			max = h_pair->max;
		}
		if (l_pair->min < h_pair->min) {
			min = l_pair->min;
		} else {
			min = h_pair->min;
		}
	}
	struct pair *max_min = malloc(sizeof(struct pair));
	max_min->max = max;
	max_min->min = min;
	return max_min;
}

struct pair *
find_max_min(int *arr, int length)
{
	return __find_max_min(arr, 0, length);
}

int
main(int argc, char *argv[])
{
	int arr[] = { 1, 7, 9, 11, 4, 5, 12, 13, 11, 12, -1 };
	struct pair *max_min_pair = find_max_min(arr, 10);
	printf("%d %d", max_min_pair->max, max_min_pair->min);
	free(max_min_pair);
	return 0;
}
