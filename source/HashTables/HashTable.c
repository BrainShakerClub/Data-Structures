#include <stdlib.h>
#include <assert.h>
#include "HashTable.h"

#define MAX_LOAD_FACTOR 0.5

// fast hash function for ints
// source: https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
unsigned int hash_int(unsigned int x)
{
    x = ((x >> 16) ^ x) * 0x45D9F3B;
    x = ((x >> 16) ^ x) * 0x45D9F3B;
    x = (x >> 16) ^ x;
    return x;
}

// this implementation uses linear probing
static inline unsigned int linear_probing(void)
{
    return 1;
}

/* array with prime sizes proven to function
   properly as hash table sizes. Rehashing occurs based
   on these numbers. If 3221225479 isn't enough, we
   double hash table's size */
static unsigned int prime_sizes[] =
{
    53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241,
    786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611,
    402653189, 805306457, 1610612741, 3221225479
};

#define START_CAPACITY prime_sizes[0]

// hash node state
typedef enum
{
    EMPTY, OCCUPIED, DELETED
} State;

typedef struct hash_node
{
    int value;
    unsigned int index; // used like a standar array index
    State state;
}* HashNode;

struct hash_table
{
    HashNode array;
    unsigned int size;
    unsigned int capacity;
};

// initializes and returns a new array
static HashNode create_array(HashTable ht)
{
    HashNode new_array = calloc(ht->capacity, sizeof(*new_array));
    assert(new_array != NULL);

    for (unsigned int i = 0; i < ht->capacity; i++)
        new_array[i].index = i;

    return new_array;
}

// rehash hash table in case load factor has exceeded
static void rehash(HashTable ht)
{
    unsigned int old_capacity = ht->capacity;
    HashNode old_array = ht->array;

    static u_int8_t prime_no = sizeof(prime_sizes) / sizeof(prime_sizes[0]);

    // search prime_sizes array to find next size
    // monobound binary-search optimization is used
    // source: https://github.com/scandum/binary_search
    u_int8_t bot = 0, top = prime_no;
    while (top > 1)
    {
        u_int8_t mid = top / 2;
        if (old_capacity >= prime_sizes[bot+mid])
            bot += mid;
        top -= mid;
    }
    ht->capacity = (bot + 1 == prime_no ? 2 * ht->capacity : prime_sizes[bot+1]);

    ht->array = create_array(ht);
    ht->size = 0;

    // insert only valid elements (chance to remove DELETED ones)
    for (unsigned int i = 0; i < old_capacity; i++)
        if (old_array[i].state == OCCUPIED)
            hash_insert(ht, old_array[i].value);

    free(old_array);
}

// finds and returns value's index in hash table or capacity if value doesn't exist
static unsigned int find_index(HashTable ht, int value)
{
    unsigned int hash_value = hash_int(value);
    for (unsigned int index = hash_value % ht->capacity, step = linear_probing(), adj = 0, count = 0, ind = index;
         count != ht->capacity && ht->array[ind].state != EMPTY;
         count++, adj += step, ind = (index + adj) % ht->capacity)
    {
        if (ht->array[ind].state == OCCUPIED && ht->array[ind].value == value)
            return ind;
    }
    return ht->capacity;
}

// initializes an empty hash table. This implementation uses double-hashing
HashTable hash_initialize(void)
{
    HashTable ht = malloc(sizeof(struct hash_table));
    assert(ht != NULL);

    ht->capacity = START_CAPACITY;
    ht->size = 0;
    ht->array = create_array(ht);
    return ht;
}

// inserts given value in hash table
void hash_insert(HashTable ht, int value)
{
    assert(ht != NULL);

    unsigned int hash_value = hash_int(value);
    unsigned int pos = hash_value % ht->capacity;
    u_int8_t step = linear_probing();

    unsigned int deleted_index = ht->capacity + 1; // save deleted node's index if found

    for (unsigned int i = 0, pos_adjustment = 0; i < ht->capacity; i++, pos_adjustment += step)
    {
        unsigned int new_pos = (pos + pos_adjustment) % ht->capacity;

        if (ht->array[new_pos].state == EMPTY)
        {
            pos = deleted_index != ht->capacity + 1 ? deleted_index : new_pos;
            break;
        }
        else if (ht->array[new_pos].state == DELETED)
        {
            /* found a deleted position
               we could insert here, but value might appear later in ht
               save index and continue searching */
            if (deleted_index == ht->capacity + 1)
                deleted_index = new_pos;
        }
        else if (ht->array[new_pos].value == value)
        {
            // key is already in the hash table, replace it with the new one
            ht->array[new_pos].value = value;
            return;
        }
    }

    ht->array[pos].value = value;
    ht->array[pos].state = OCCUPIED;
    ht->size++;

    if ((float)ht->size / ht->capacity > MAX_LOAD_FACTOR)
        rehash(ht);
}

// removes value from ht
bool hash_remove(HashTable ht, int value)
{
    if (!hash_size(ht))
        return false;

    unsigned int index = find_index(ht, value);

    if (index == ht->capacity)
        return false;

    ht->array[index].state = DELETED;
    ht->size--;
    return true;
}

// seaches for value in hash table
bool hash_search(HashTable ht, int value)
{
    if (!hash_size(ht))
        return false;
    return find_index(ht, value) != ht->capacity;
}

// returns hash table's size
unsigned int hash_size(HashTable ht)
{
    assert(ht != NULL);
    return ht->size;
}

// destroys given hash table
void hash_destroy(HashTable ht)
{
    assert(ht != NULL);
    free(ht->array);
    free(ht);
}