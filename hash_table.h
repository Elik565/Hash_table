#include <stdlib.h>

typedef struct HTNode {
    char* key;
    char* value;
    struct HTNode* next_node;
} HTNode;

typedef struct HashTable {
    HTNode** node_array;
    int size;
    int count_nodes;
} HashTable;

HTNode* create_node(const char* key, const char* value);

HashTable* create_table(const size_t size);

size_t hash_djb2(const char* key);

void insert(HashTable* table, const char* key, char* value);

void print_ht(const HashTable* table);

void free_node(HTNode* node);

void free_table(HashTable* table);