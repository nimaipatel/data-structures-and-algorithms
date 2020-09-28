#include <bits/stdc++.h>

#define LEFT 0
#define RIGHT 199

int find_next(int head, std::list<int> requests) {
    std::list<int>::iterator iter = requests.begin();
    int next = *iter;
    for (; iter != requests.end(); iter++) {}
}

void scan(int head, std::list<int> requests) {
    int original_length = requests.size() + 1;  // including final positon
    int total_seek = 0;
    int current = *requests.begin();
    for (int i = 0; i < original_length; i++) {
        int next = find_next(head, requests);
        total_seek += abs(current - next);
        current = next;
        requests.remove(next);
    }
}

int main() {
    int head = 50;
    int array[] = {98, 183, 41, 122, 14, 124, 65, 67};
    std::list<int> requests(std::begin(array), std::end(array));
    scan(head, requests);
    return 0;
}
