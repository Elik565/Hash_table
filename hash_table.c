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

void handle_collision(HTNode* current_node, HTNode* node) {
    // Moving to the last node in the chain
    while (current_node->next_node != NULL) {
        current_node = current_node->next_node;
    }

    current_node->next_node = node;
}

void insert(HashTable* table, const char* key, char* value) {
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
    } else {  // There is collision
        if (strcmp(current_node->key, key) == 0) {  // we only need to update value
            strcpy(current_node->value, value);
        } else {
            handle_collision(current_node, node);
            table->count_nodes++;
        }
    }
}

void print_ht(const HashTable* table, const size_t node_limit) {
    for (size_t i = 0; i < table->size && i < node_limit; ++i) {
        printf("[%zu]: ", i);

        HTNode* node = table->node_array[i];
        if (node == NULL) {
            printf("NULL\n");
            continue;
        }

        while (node->next_node != NULL) {
            printf("%s (%s) -> ", node->key, node->value);
            node = node->next_node;
        }

        printf("%s (%s)\n", node->key, node->value);
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