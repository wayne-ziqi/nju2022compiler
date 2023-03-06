#include "hashMap.h"
#include <stdlib.h>
#include <assert.h>

static inline unsigned int hash_pjw(char *name, unsigned int slotNumber) {
    unsigned int val = 0, i;
    for (; *name; ++name) {
        val = (val << 2) + *name;
        i = val & ~slotNumber;
        if (i) val = (val ^ (i >> 12)) & slotNumber;
    }
    return val;
}

static inline unsigned int getIndex(void *key, KeyType key_t, unsigned int slotNumber) {
    unsigned int index;
    if (key_t == STRING)
        index = hash_pjw((char *) key, slotNumber);
    else
        /*add more rules for different types*/
        assert(false);
    assert(index >= 0 && index < slotNumber);
    return index;
}

HashMap new_hashmap(KeyType keyType, unsigned int slotNumber) {
    HashMap hashMap = (HashMap) malloc(sizeof(struct HashMap_));
    hashMap->key_t = keyType;
    hashMap->slot_num = slotNumber > DEFAULT_SLOT_SIZE ? slotNumber : DEFAULT_SLOT_SIZE;
    hashMap->keySet = (List *) malloc(hashMap->slot_num * sizeof(List));
    for (int i = 0; i < hashMap->slot_num; ++i) {
        hashMap->keySet[i] = new_list();
    }
    return hashMap;
}

List getList(HashMap hashMap, void *key) {
    assert(hashMap != NULL && key != NULL);
    unsigned int index = getIndex(key, hashMap->key_t, hashMap->slot_num);
    return hashMap->keySet[index];
}

void *getFirstOf(HashMap hashMap, void *key, void *searchHandle, bool (*searchRule)(void *, void *)) {
    assert(hashMap && key && searchRule);
    List curList = getList(hashMap, key);
    ListNode node = getNode(curList, searchHandle, searchRule);
    return node ? node->data : NULL;
}

void addHead(HashMap hashMap, void *key, void *data) {
    assert(hashMap && key && data);
    unsigned int index = getIndex(key, hashMap->key_t, hashMap->slot_num);
    pushHead(hashMap->keySet[index], newListNode(data));
}

void free_hashmap(HashMap hashMap) {
    if (!hashMap) return;
    for (int i = 0; i < hashMap->slot_num; ++i) {
        free_list(hashMap->keySet[i]);
    }
    free(hashMap->keySet);
    free(hashMap);
}


