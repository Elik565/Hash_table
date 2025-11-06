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
    table->count_nodes = 0;  
    table->node_array = calloc(size, sizeof(HTNode));

    for (size_t i = 0; i < size; ++i) {
        table->node_array[i] = NULL;
    }

    return table;
}

size_t hash_djb2(const char* key) {
    size_t hash = 5381;
    int c;

    while ((c = (unsigned char)*key++)) {
        // hash = hash * 33 + c;
        // We can use << 5 like 2^5
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

void insert(HashTable* table, const char* key, const char* value) {
    HTNode* node = create_node(key, value);
    size_t id = hash_djb2(key) % table->size;
    
    HTNode* current_node = table->node_array[id];
    if (current_node == NULL) {  // there is no collision
        if (table->count_nodes >= table->size) {  // table is full
            printf("ERROR: when inserting, there was no place in the hash table\n");
            free_node(node);
            return;
        }

        // Regular insert
        table->node_array[id] = node;
        table->count_nodes++;
    }    
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