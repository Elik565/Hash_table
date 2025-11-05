#include "hash_table.h"
#include <string.h>
#include <stdio.h>

HTNode* create_node(const char* key, const char* value) {
    HTNode* node = malloc(sizeof(HTNode));
    node->key = malloc(strlen(key) + 1);  // don't forget about \0
    node->value = malloc(strlen(value) + 1);

    strcpy(node->key, key);
    strcpy(node->value, value);

    return node;
}

HashTable* create_table(const size_t size) {
    HashTable* table = malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;  
    table->node_array = calloc(size, sizeof(HTNode));

    for (size_t i = 0; i < size; ++i) {
        table->node_array[i] = NULL;
    }

    return table;
}

void free_node(HTNode* node) {
    free(node->key);
    free(node->value);
    free(node);
}

void free_table(HashTable* table) {
    for (size_t i = 0; i < table->size; ++i) {
        if (table->node_array[i] != NULL) {
            free_node(table->node_array[i]);
        }
    }

    free(table->node_array);
    free(table);
}