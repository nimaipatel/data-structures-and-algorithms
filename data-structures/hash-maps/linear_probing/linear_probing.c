#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char *key;
	char *value;
} Node;

Node *
create_node(char *key, char *value)
{
	Node *node = (Node *)malloc(sizeof(Node));
	int key_l = strlen(key);
	int value_l = strlen(value);
	char *_key = (char *)malloc(sizeof(char) * key_l);
	char *_value = (char *)malloc(sizeof(char) * value_l);
	strcpy(_key, key);
	strcpy(_value, value);
	node->key = _key;
	node->value = _value;
	return node;
}

typedef struct HashTable {
	int size;
	struct Node **node_arr;
} HashTable;

int
hash(char *string)
{
	int hash = 0;
	for (char *iter = string; *iter != '\0'; ++iter) {
		hash += *iter;
	}
	return hash;
}

HashTable *
create_hash_table(int size)
{
	HashTable *hash_table = (HashTable *)malloc(sizeof(HashTable));
	hash_table->size = size;
	hash_table->node_arr = (Node **)malloc(sizeof(Node *) * size);
	for (int i = 0; i < size; ++i) {
		hash_table->node_arr[i] = NULL;
	}
	return hash_table;
}

void
insert(HashTable *hash_table, char *key, char *value)
{
	int hashed_key = hash(key) % hash_table->size;
	Node *node = create_node(key, value);
	int index = hashed_key;
	if (hash_table->node_arr[index] == NULL) {
		hash_table->node_arr[index] = node;
	} else {
		index = (index + 1) % hash_table->size;
		while (hash_table->node_arr[index] != NULL) {
			if (index == hashed_key) {
				printf("NO SPACE LEFT IN HASH TABLE\n");
				return;
			}
			index = (index + 1) % hash_table->size;
		}
		hash_table->node_arr[index] = node;
	}
}

void delete (HashTable *hash_table, char *key)
{
	int hashed_key = hash(key) % hash_table->size;
	if (hash_table->node_arr[hashed_key] &&
	    hash_table->node_arr[hashed_key]->key == key) {
		Node *temp = hash_table->node_arr[hashed_key];
		hash_table->node_arr[hashed_key] = NULL;
		free(temp);
	} else {
		int index = hashed_key + 1;
		while (hash_table->node_arr[index] &&
		       hash_table->node_arr[index]->key != key) {
			index = (index + 1) % hash_table->size;
			if (index == hashed_key) {
				printf("KEY FOR DELETION NOT FOUND\n");
				return;
			}
		}
		if (hash_table->node_arr[index]) {
			Node *temp = hash_table->node_arr[index];
			hash_table->node_arr[index] = NULL;
			free(temp);
		} else {
			printf("KEY FOR DELETION NOT FOUND\n");
		}
	}
}

void
print_hash_table(HashTable *hash_table)
{
	for (int i = 0; i < hash_table->size; ++i) {
		if (hash_table->node_arr[i]) {
			printf("%s : %s\n", hash_table->node_arr[i]->key,
			       hash_table->node_arr[i]->value);
		}
	}
}

int
main()
{
	int size, option;
	char key[100], value[100];
	printf("Enter size: ");
	scanf("%d", &size);
	HashTable *h = create_hash_table(size);
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
