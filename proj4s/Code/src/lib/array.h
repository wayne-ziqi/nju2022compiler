#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct Array_ *Array;

struct Array_ {
    int volume;
    int size;
    void **array;
};

Array new_Array();

Array new_ArrayOfVol(int volume);

// shallow copy
Array copy_Array(Array src, int head, int tail);

bool isEmptyArray(Array array);

bool equal_array(Array array1, Array array2, bool (*compare)(void *, void *));

void appendArray(Array array, void *data);

void *getArray(Array array, int i);

void *getArrayTail(Array array);

void *getArrayHead(Array array);

int sizeArray(Array array);

void free_Array(Array array);

#endif //ARRAY_H
