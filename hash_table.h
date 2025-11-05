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

HashTable* create_table(const int size);