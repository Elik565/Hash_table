#include "hash_table.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

HTNode* create_node(const char* key, const char* value) {
    HTNode* node = malloc(sizeof(HTNode));
    node->key = malloc(strlen(key) + 1);  // don't forget about \0
    node->value = malloc(strlen(value) + 1);

    strcpy(node->key, key);
    strcpy(node->value, value);

    return node;
}

HashTable* create_table(const int size) {
    HashTable* hash_table = malloc(sizeof(HashTable));
    hash_table->size = size;
    hash_table->count = 0;  
    hash_table->node_array = calloc(size, sizeof(HTNode));

    for (size_t i = 0; i < size; ++i) {
        hash_table->node_array[i] = NULL;
    }

    return hash_table;
}