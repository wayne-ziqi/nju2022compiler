//
// Created by 王紫萁 on 2022/11/2.
//

#ifndef PROJ3_UINT_H
#define PROJ3_UINT_H

typedef struct UInt_ *UInt;

struct UInt_ {
    unsigned int u;
};

UInt new_UInt(unsigned int from);

unsigned int value_UInt(UInt u);

void free_UInt(UInt u);

#endif //PROJ3_UINT_H
