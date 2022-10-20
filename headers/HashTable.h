#pragma once

#include <stdbool.h>

// fast hash function for ints
unsigned int hash_int(unsigned int);

typedef struct hash_table* HashTable;

HashTable hash_initialize(void);
void hash_insert(HashTable, int);
bool hash_remove(HashTable, int);
bool hash_search(HashTable, int);
unsigned int hash_size(HashTable);
void hash_destroy(HashTable);