#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int array[] = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;
    int* next = array;
    int total_seek = 0;
    printf("Order:\n");
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        printf("%d\t", head);
        total_seek += abs(head - *next);
        head = *next;
        next++;
    }
    printf("\nTotal Seek: %d", total_seek);
}

