#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
merge(int *arr, int low, int mid, int high)
{
	// declare an array of half the size of original array
	int *aux_array = (int *)malloc(sizeof(int) * (mid + 1));
	memcpy(aux_array, arr, (mid + 1) * sizeof(arr[0]));
	int i = low, j = mid + 1, k = low;
	while (i <= mid && j <= high) {
		if (aux_array[i] <= arr[j])
			arr[k++] = aux_array[i++];
		else
			arr[k++] = arr[j++];
	}
	if (i > mid) {
		// copy rest of arr to arr
		for (int m = j; m < high + 1; ++m)
			arr[k++] = arr[m];
	} else {
		// copy rest of aux_array to arr
		for (int m = i; m < mid + 1; ++m)
			arr[k++] = aux_array[m];
	}
	free(aux_array);
}

void
__merge_sort(int *arr, int low, int high)
{
	// internal function which is called by `merge_sort`
	if (low < high) {
		int mid = (low + high) / 2;
		__merge_sort(arr, low, mid);
		__merge_sort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

void
merge_sort(int *arr, int length)
{
	__merge_sort(arr, 0, length - 1);
}

int
main(int argc, char **argv)
{
	int length = argc - 1;
	int *arr = (int *)malloc(sizeof(int) * length);
	for (int i = 0; i < length; ++i)
		arr[i] = atoi(argv[i + 1]);
	merge_sort(arr, length);
	for (int i = 0; i < length; ++i)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}
