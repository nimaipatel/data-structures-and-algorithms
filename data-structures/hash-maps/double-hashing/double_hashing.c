#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    int value;
} Node;

typedef struct HashTable {
    Node** node_arr;
    int size;
    int R;
} HashTable;

Node* create_node(int key, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    return node;
}

bool is_prime(int n) {
    for (int i = 2; i < n / 2; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

HashTable* create_hash_table(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->node_arr = (Node**)malloc(sizeof(Node*) * size);

    for (int i = size; i > 0; --i) {
        if (is_prime(i)) {
            ht->R = i;
            break;
        }
    }

    return ht;
}

void insert(HashTable* ht, int key, int value) {
    int h_key = key % ht->size, R = ht->R, index = 0;
    for (int i = 0; i < ht->size; ++i) {
        if (!ht->node_arr[index]) {
            ht->node_arr[index] = create_node(key, value);
            return;
        }
        index = (h_key + i * (R - (key % R))) % ht->size;
    }
}

void print_hash_table(HashTable* hash_table) {
    for (int i = 0; i < hash_table->size; ++i) {
        if (hash_table->node_arr[i]) {
            printf("%d : %d \n", hash_table->node_arr[i]->key,
                   hash_table->node_arr[i]->value);
        }
    }
}

int main() {
    int size, option;
    printf("Enter size of hash table: ");
    scanf("%d", &size);
    HashTable* h = create_hash_table(size);
    do {
        printf("Enter 0 to insert\nEnter any other number to exit\n");
        scanf("%d", &option);
        if (option == 0) {
            int key, value;
            printf("Enter key: ");
            scanf("%d", &key);
            printf("Enter value: ");
            scanf("%d", &value);
            insert(h, key, value);
            print_hash_table(h);
        }
    } while (option == 0);
    return 0;
}
