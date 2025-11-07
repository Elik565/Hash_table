#include "hash_table.h"
#include <string.h>
#include <stdio.h>

HTNode* create_node(const char* key, const char* value) {
    HTNode* node = malloc(sizeof(HTNode));
    node->key = malloc(strlen(key) + 1);  // don't forget about \0
    node->value = malloc(strlen(value) + 1);

    strcpy(node->key, key);
    strcpy(node->value, value);
    node->next_node = NULL;

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

void insert(HashTable* table, const char* key, char* value) {
    size_t id = hash_djb2(key) % table->size;
    
    HTNode* node = table->node_array[id];
    if (node == NULL) {  // there is no collision
        table->node_array[id] = create_node(key, value);
        table->count_nodes++;
        return;
    }

    // There is collision
    HTNode* prev = NULL;
    while (node) {
        if (strcmp(node->key, key) == 0) {  // we only need to update value
            free(node->value);
            node->value = strdup(value);
            return;
        }

        prev = node;
        node = node->next_node;
    }

    prev->next_node = create_node(key, value);
    table->count_nodes++;
}

void print_search(const HashTable* table, const char* key) {
    size_t id = hash_djb2(key) % table->size;
    HTNode* node = table->node_array[id];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            printf("Found by id = %zu: key = %s, value = %s\n", id, key, node->value);
            return;
        }

        node = node->next_node;
    }

    printf("Key '%s' not found\n");
}

void print_ht(const HashTable* table) {
    for (size_t i = 0; i < table->size && i < 10; ++i) {
        printf("[%zu]: ", i);

        HTNode* node = table->node_array[i];
        if (node == NULL) {
            printf("NULL\n");
            continue;
        }

        while (node->next_node) {
            printf("%s (%s) -> ", node->key, node->value);
            node = node->next_node;
        }

        printf("%s (%s)\n", node->key, node->value);
    }
    printf("\n");
}

void free_node(HTNode* node) {
    free(node->key);
    free(node->value);
    free(node);
}

void free_table(HashTable* table) {
    for (size_t i = 0; i < table->size; ++i) {
        HTNode* node = table->node_array[i];
        while (node) {
            HTNode* next = node->next_node;
            free_node(node);
            node = next;
        }
    }

    free(table->node_array);
    free(table);
}