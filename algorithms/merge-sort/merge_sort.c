#include <stdio.h>
#include <stdlib.h>

void merge(int * arr, int low, int mid, int high){
    int h = low, i = low, j = mid + 1;
    int * temp_arr = (int*)malloc(sizeof(int) * (high+1));
    while (h <= mid && j <= high){
        if (arr[h] <= arr[j]){
            temp_arr[i++] = arr[h++];
        } else {
            temp_arr[i++] = arr[j++];
        }
    }
    if (h > mid) {
        for (int k = j; k < high+1; ++k){
            temp_arr[i++] = arr[k];
        }
    } else {
        for (int k = h; k < mid+1; ++k){
            temp_arr[i++] = arr[k];
        }
    }
    for (int k = low; k < high+1; ++k){
        arr[k] = temp_arr[k];
    }
    free(temp_arr);
}

void merge_sort(int * arr, int low, int high){
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}

int main(int argc, char ** argv) {
    int * arr = (int*)malloc(sizeof(int) * (argc-1));
    for (int i = 1; i < argc; ++i){
        arr[i-1] = atoi(argv[i]);
    }
    merge_sort(arr, 0, argc-1);
    for (int i = 0 ; i < argc-1; ++i){
        printf("%d ", arr[i]);
    }
    return 0;
}
