//
// Created by 王紫萁 on 2022/11/2.
//

#ifndef PROJ3_UINT_H
#define PROJ3_UINT_H

#include <stdbool.h>

typedef struct UInt_ *UInt;

struct UInt_ {
    unsigned int u;
};

UInt new_UInt(unsigned int from);

unsigned int value_UInt(UInt u);

bool equal_uint(UInt u1, UInt u2);

void free_UInt(UInt u);

#endif //PROJ3_UINT_H
