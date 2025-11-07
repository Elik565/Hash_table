#include <stdio.h>
#include "hash_table.h"
#include <math.h>
#include <string.h>

void main() {
    HashTable* ht = create_table(1);

    insert(ht, "apple", "5");
    insert(ht, "orange", "7");
    insert(ht, "apple", "9");
    insert(ht, "pear", "10");
    insert(ht, "apple", "2");
    insert(ht, "pear", "12");

    print_ht(ht);

    print_search(ht, "pear");

    free_table(ht);

    return;
}