#include "array.h"
#include <stdlib.h>
#include <assert.h>

#define DEFAULT_ARRAY_VOLUME 32

Array new_Array() {
    Array array = (Array) malloc(sizeof(struct Array_));
    array->size = 0;
    array->volume = DEFAULT_ARRAY_VOLUME;
    array->array = (void **) malloc(array->volume * sizeof(void *));
    return array;
}

bool isEmptyArray(Array array) {
    assert(array);
    return array->size == 0;
}

bool equal_array(Array array1, Array array2, bool (*compare)(void *, void *)) {
    assert(array1 && array2);
    if (array1->size != array2->size) return false;
    for (int i = 0; i < array1->size; ++i) {
        if (!compare(array1->array[i], array2->array[i]))return false;
    }
    return true;
}

void appendArray(Array array, void *data) {
    assert(array && data);
    if (array->size == array->volume) {
        array->volume *= 2;
        void **larger = (void **) malloc(array->volume * sizeof(void *));
        for (int i = 0; i < array->size; ++i) {
            larger[i] = array->array[i];
        }
        free(array->array);
        array->array = larger;
    }
    array->array[array->size++] = data;
}

void *getArray(Array array, int i) {
    assert(array);
    assert(i >= 0 && i < array->size);
    return array->array[i];
}

unsigned int sizeArray(Array array) {
    assert(array);
    return array->size;
}

void free_Array(Array array) {
    assert(array);
    if (array->array != NULL)
        free(array->array);
    free(array);
}
