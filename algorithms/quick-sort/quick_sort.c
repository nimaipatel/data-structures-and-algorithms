#include <stdio.h>
#include <stdlib.h>

void swap(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int hoare_partition(int * arr, int low, int high){
    int pivot = arr[low], i = low, j = high;
    while(i < j){
        do { ++i; } while(arr[i] <= pivot);
        do { --j; } while(arr[j] > pivot);
        if (i < j) {
            swap(&arr[i], &arr[j]);
        } else {
            break;
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quick_sort(int * arr, int low, int high){
    if (low < high){
        int j = hoare_partition(arr, low, high);
        quick_sort(arr, low, j);
        quick_sort(arr, j+1, high);
    }
}

int main(int argc, char ** argv) {
    int * arr = (int*)malloc(sizeof(int) * (argc-1));
    for (int i = 1; i < argc; ++i){
        arr[i-1] = atoi(argv[i]);
    }
    quick_sort(arr, 0, argc-1);
    for (int i = 0 ; i < argc-1; ++i){
        printf("%d ", arr[i]);
    }
    return 0;
}
