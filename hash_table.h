#include <stdlib.h>

typedef struct HTNode {
    char* key;
    char* value;
} HTNode;

typedef struct HashTable {
    HTNode** node_array;
    int size;
    int count;
} HashTable;

HTNode* create_node(const char* key, const char* value);

HashTable* create_table(const size_t size);

void free_node(HTNode* node);

void free_table(HashTable* table);