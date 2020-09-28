#include <bits/stdc++.h>

int shortest_dist(int head, std::list<int> requests) {
    std::list<int>::iterator iter = requests.begin();
    int shortest_dist = *iter;
    for (; iter != requests.end(); iter++) {
        if (abs(*iter - head) < abs(shortest_dist - head)) {
            shortest_dist = *iter;
        }
    }
    return shortest_dist;
}

void sstf(int head, std::list<int> requests) {
    int current = head;
    int total_seek = 0;
    int original_size = requests.size();
    for (int i = 0; i < original_size; i++) {
        int next = shortest_dist(current, requests);
        total_seek += abs(current - next);
        current = next;
        requests.remove(next);
    }
    printf("\n%d", total_seek);
}

int main() {
    int head = 53;
    int array[] = {98, 183, 41, 122, 14, 124, 65, 67};
    std::list<int> requests(std::begin(array), std::end(array));
    sstf(head, requests);
    return 0;
}
