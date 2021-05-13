#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int *
find_min(int *start, int *end)
{
	int *min = start;
	for (int *iter = start; iter != end; iter++) {
		if (*min > *iter) {
			min = iter;
		}
	}
	return min;
}

void
swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void
print_array(int *arr, int n)
{
	for (int i = 0; i < 7; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void
sort(int *start, int *end)
{
	for (int i = 0; i < end - start; i++) {
		print_array(start, end - start);
		swap(start + i, find_min(start + i, end));
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
	print_array(arr, l);
	return 0;
}
