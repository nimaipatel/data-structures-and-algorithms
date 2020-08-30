#include <iostream>

int search(int* first, int* last, int term) {
    int* low = first;
    int* high = last;
    while (low <= high) {
        int* mid = low + (high - low) / 2;
        // std::cout << *low << " " << *mid << " " << *high << std::endl;

        if (*mid == term) {
            // std::cout << *first << " " << *mid << std::endl;
            return mid - first;
        } else if (*mid < term) {
            return search(mid + 1, last, term);
        } else {
            return search(first, mid - 1, term);
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 54, 76, 81};
    std::cout << search(arr, arr + 8, 5);
    return 0;
}
