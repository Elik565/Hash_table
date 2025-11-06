#include <stdio.h>
#include "hash_table.h"
#include <math.h>

void main() {
    HashTable* ht = create_table(5);

    insert(ht, "apple", "5");
    insert(ht, "orange", "3");

    print_ht(ht, 5);

    return;
}