#include <stdio.h>
#include "hash_table.h"
#include <math.h>

void main() {
    HashTable* ht = create_table(1);

    insert(ht, "apple", "5");
    insert(ht, "orange", "3");

    return;
}