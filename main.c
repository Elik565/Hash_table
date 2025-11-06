#include <stdio.h>
#include "hash_table.h"
#include <math.h>

void main() {
    HashTable* ht = create_table(5);

    insert(ht, "apple", "5");
    insert(ht, "peer", "3");
    insert(ht, "orange", "4");
    insert(ht, "applee", "8");

    print_ht(ht, 5);

    free_table(ht);

    return;
}