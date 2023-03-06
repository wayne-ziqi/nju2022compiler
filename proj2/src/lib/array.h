#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct Array_ *Array;

struct Array_ {
    unsigned int volume;
    unsigned int size;
    void **array;
};

Array new_Array();

bool isEmptyArray(Array array);

bool equal_array(Array array1, Array array2, bool (*compare)(void *, void *));

void appendArray(Array array, void *data);

void *getArray(Array array, int i);

unsigned int sizeArray(Array array);

void free_Array(Array array);

#endif //ARRAY_H
