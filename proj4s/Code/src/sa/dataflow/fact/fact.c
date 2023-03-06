//
// Created by 王紫萁 on 2022/11/27.
//

#include "fact.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

Fact new_Fact(int size) {
    assert(size > 0);
    Fact fact = (Fact) malloc(sizeof(struct Fact_));
    fact->size = size;
    fact->fact_arr = (bool *) malloc(size * sizeof(bool));
    memset(fact->fact_arr, false, size * sizeof(bool));
    return fact;
}

Fact copy_Fact(Fact fact) {
    assert(fact);
    Fact newfact = new_Fact(fact->size);
    memcpy(newfact->fact_arr, fact->fact_arr, fact->size * sizeof(bool));
    return newfact;
}

void free_Fact(Fact fact) {
    assert(fact);
    free(fact->fact_arr);
    free(fact);
}

bool getFactIn(Fact fact, int i) {
    assert(i >= 0 && i < fact->size);
    return fact->fact_arr[i];
}

void unionFact(Fact src, Fact dst) {
    assert(src->size == dst->size);
    for (int i = 0; i < src->size; ++i) {
        dst->fact_arr[i] = dst->fact_arr[i] || src->fact_arr[i];
    }
}

void setFact(Fact fact, Fact from) {
    assert(fact && from && fact->size == from->size);
    for (int i = 0; i < fact->size; ++i) {
        fact->fact_arr[i] = from->fact_arr[i];
    }
}

void setFactIn(Fact fact, int i, bool exist) {
    assert(fact && i >= 0 && i < fact->size);
    fact->fact_arr[i] = exist;
}

bool equalsFact(Fact fact, Fact with) {
    assert(fact && with);
    if (fact->size != with->size) return false;
    for (int i = 0; i < fact->size; ++i) {
        if (fact->fact_arr[i] != with->fact_arr[i])return false;
    }
    return true;
}

FactBox new_FactBox(unsigned int bid, int var_num) {
    FactBox box = (FactBox) malloc(sizeof(struct FactBox_));
    box->bid = bid;
    box->var_num = var_num;
    box->inFact = new_Fact(var_num);
    box->outFact = new_Fact(var_num);
    return box;
}

void free_FactBox(FactBox box) {
    assert(box);
    free_Fact(box->inFact);
    free_Fact(box->outFact);
}


Fact getInFactOfBox(FactBox box) {
    assert(box);
    return box->inFact;
}

Fact getOutFactOfBox(FactBox box) {
    assert(box);
    return box->outFact;
}

void setInFactOfBox(FactBox box, int i, bool exist) {
    assert(box);
    assert(i >= 0 && i < box->var_num);
    box->inFact->fact_arr[i] = exist;
}

void setOutFactOfBox(FactBox box, int i, bool exist) {
    assert(box);
    assert(i >= 0 && i < box->var_num);
    box->outFact->fact_arr[i] = exist;
}