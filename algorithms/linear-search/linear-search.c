#include <stdio.h>

int search(int *first, int *last, int term) {
    for (int *iter = first; iter != last; iter++) {
        if (*iter == term) { return (iter - first); }
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 4, 5, 3, 7};
    int index = search(arr, arr + 5, 4);
    printf("%d", index);
}
