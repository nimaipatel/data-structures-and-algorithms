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
    int key_l = strlen(key);
    int value_l = strlen(value);
    char* _key = (char*)malloc(sizeof(char) * key_l);
    char* _value = (char*)malloc(sizeof(char) * value_l);
    strcpy(_key, key);
    strcpy(_value, value);
    node->key = _key;
    node->value = _value;
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

void delete (HashTable* hash_table, char* key) {
    int hashed_key = hash(key) % hash_table->size;
    if (hash_table->pointer_array[hashed_key]) {
        if (hash_table->pointer_array[hashed_key]->key == key) {
            Node* temp = hash_table->pointer_array[hashed_key];
            hash_table->pointer_array[hashed_key] =
                hash_table->pointer_array[hashed_key]->link;
            free(temp);
        } else {
            Node* iter = hash_table->pointer_array[hashed_key];
            Node* prev;
            while (iter->key != key) {
                if (iter->link) {
                    prev = iter;
                    iter = iter->link;
                } else {
                    printf("KEY NOT FOUND FOR DELETIOND\n");
                    return;
                }
            }
            prev->link = iter->link;
            free(iter);
        }
    } else {
        printf("KEY NOT FOUND FOR DELETION\n");
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
    int size, option;
    char key[100], value[100];
    printf("Enter size: ");
    scanf("%d", &size);
    HashTable* h = create_hash_table(size);
    do {
        printf("Enter 0 to insert value\nEnter 1 to delete value\n");
        scanf("%d *[^\n]", &option);
        if (option == 0) {
            printf("Enter key: ");
            fgets(key, 100, stdin);
            printf("Enter value: ");
            fgets(value, 100, stdin);
            insert(h, key, value);
        }

        if (option == 1) {
            printf("Enter key: ");
            fgets(key, 100, stdin);
            delete (h, key);
        }

        print_hash_table(h);

    } while (option == 0 || option == 1);
    return 0;
}
