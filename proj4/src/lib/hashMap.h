#ifndef __HASH_MAP__
#define __HASH_MAP__

#include "list.h"

#define DEFAULT_SLOT_SIZE 0x3fff

typedef enum {
    STRING,
    UINT
} KeyType;

typedef struct HashMap_ *HashMap;

struct HashMap_ {
    KeyType key_t;
    unsigned int slot_num;
    List *keySet;
};

/**
 *
 * @param keyType type of key, currently supports string
 * @param slotNumber total number of slots
 * @return an empty hashmap
 */
HashMap new_hashmap(KeyType keyType, unsigned int slotNumber);

/**
 *
 * @param key
 * @return the alias list of slot[key]
 */
List getList(HashMap hashMap, void *key);

/**
 * get the first data in map with key, using search rule and handle to locate
 * @param key
 * @param searchRule
 * @return first satisfied data
 */
void *getFirstOf(HashMap hashMap, void *key, void *searchHandle, bool (*searchRule)(void *, void *));

/**
 * add data to the head of the list slot[key]
 * @param key
 * @param data
 */
void addHead(HashMap hashMap, void *key, void *data);

/**
 * get all data stored in the map
 * @param hashMap
 */
List getHashAll(HashMap hashMap);

/**
 * free hashmap
 */
void free_hashmap(HashMap hashMap);

#endif //__HASH_MAP__