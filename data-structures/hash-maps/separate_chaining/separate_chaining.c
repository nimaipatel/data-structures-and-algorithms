#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* key;
    char* value;
    struct Node* link;
} Node;

Node* create_node(char* key, char* value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->link = NULL;
    return node;
}

typedef struct HashTable {
    int size;
    struct Node** pointer_array;
} HashTable;

int hash(char* string) {
    int hash = 0;
    for (char* iter = string; *iter != '\0'; ++iter) {
        hash += *iter;
    }
    return hash;
}

HashTable* create_hash_table(int size) {
    HashTable* hash_table = (HashTable*)malloc(sizeof(hash_table));
    hash_table->size = size;
    hash_table->pointer_array = (Node**)malloc(sizeof(Node*) * size);
    for (int i = 0; i < size; ++i) {
        hash_table->pointer_array[i] = NULL;
    }
    return hash_table;
}

void insert(HashTable* hash_table, char* key, char* value) {
    int hashed_key = hash(key) % hash_table->size;
    Node* node = create_node(key, value);
    if (!hash_table->pointer_array[hashed_key]) {
        hash_table->pointer_array[hashed_key] = node;
    } else {
        node->link = hash_table->pointer_array[hashed_key];
        hash_table->pointer_array[hashed_key] = node;
    }
}

char* get_value(HashTable* hash_table, char* key) {
    int hashed_key = hash(key) % hash_table->size;
    Node* iter = hash_table->pointer_array[hashed_key];
    while (iter != NULL) {
        if (iter->key == key) {
            return iter->value;
        }
        iter = iter->link;
    }
    return "\0";
}

void print_hash_table(HashTable* hash_table) {
    for (int i = 0; i < hash_table->size; ++i) {
        if (hash_table->pointer_array[i]) {
            Node* iter = hash_table->pointer_array[i];
            while (iter != NULL) {
                printf("%s : %s\n", iter->key, iter->value);
                iter = iter->link;
            }
        }
    }
}

int main() {
    HashTable* hash_table = create_hash_table(2);
    insert(hash_table, "dog", "barks");
    insert(hash_table, "cat", "meows");
    insert(hash_table, "mouse", "squeaks");
    char* value = get_value(hash_table, "mouse");
    printf("%s", value);
    return 0;
}
