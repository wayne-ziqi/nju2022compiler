//
// Created by 王紫萁 on 2022/11/2.
//

#include "UInt.h"
#include <stdlib.h>

UInt new_UInt(unsigned int from) {
    UInt u = (UInt) malloc(sizeof(struct UInt_));
    u->u = from;
    return u;
}

unsigned int value_UInt(UInt u) {
    return u->u;
}

bool equal_uint(UInt u1, UInt u2) {
    return u1->u == u2->u;
}

void free_UInt(UInt u) {
    free(u);
}
