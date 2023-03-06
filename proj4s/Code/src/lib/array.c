#include "array.h"
#include <stdlib.h>
#include <assert.h>

#define DEFAULT_ARRAY_VOLUME 32

Array new_Array() {
    return new_ArrayOfVol(DEFAULT_ARRAY_VOLUME);
}

inline Array new_ArrayOfVol(int volume) {
    Array array = (Array) malloc(sizeof(struct Array_));
    array->size = 0;
    array->volume = volume;
    array->array = (void **) malloc(array->volume * sizeof(void *));
    return array;
}

Array copy_Array(Array src, int head, int tail) {
    assert(head <= tail && head >= 0 && tail < src->size);
    Array dst = new_Array();
    for (int i = head; i <= tail; ++i) {
        appendArray(dst, src->array[i]);
    }
    return dst;
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

inline void appendArray(Array array, void *data) {
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

inline void *getArray(Array array, int i) {
    assert(array);
    assert(i >= 0 && i < array->size);
    return array->array[i];
}

void *getArrayTail(Array array) {
    assert(array);
    return getArray(array, array->size - 1);
}

void *getArrayHead(Array array) {
    return getArray(array, 0);
}

int sizeArray(Array array) {
    assert(array);
    return array->size;
}

void free_Array(Array array) {
    assert(array);
    if (array->array != NULL)
        free(array->array);
    free(array);
}
