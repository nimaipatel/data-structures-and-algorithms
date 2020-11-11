#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void max_heapify(int* arr, int n, int i) {
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[max]) {
        max = left;
    }
    if (right < n && arr[right] > arr[max]) {
        max = right;
    }
    if (max != i) {
        int temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;
        max_heapify(arr, n, max);
    }
}

void build_max_heap(int* arr, int n) {
    for (int i = n / 2; i >= 0; --i) {
        max_heapify(arr, n, i);
    }
}

void sort(int* start, int* end) {
    int n = end - start;
    build_max_heap(start, n);

    for (int i = n - 1; i >= 0; --i) {
        int temp = start[0];
        start[0] = start[i];
        start[i] = temp;
        max_heapify(start, i, 0);
    }
}

int main() {
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
