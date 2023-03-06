//
// Created by 王紫萁 on 2022/11/27.
//

#ifndef PROJ4_FACT_H
#define PROJ4_FACT_H

#include "../../../lib/array.h"
#include <stdbool.h>

typedef struct Fact_ *Fact;
struct Fact_ {
    int size;
    bool *fact_arr;
};

Fact new_Fact(int size);

Fact copy_Fact(Fact fact);

void free_Fact(Fact fact);

bool getFactIn(Fact fact, int i);

void unionFact(Fact src, Fact dst);

void setFact(Fact fact, Fact from);

void setFactIn(Fact fact, int i, bool exist);

bool equalsFact(Fact fact, Fact with);


typedef struct FactBox_ *FactBox;
struct FactBox_ {
    unsigned int bid;
    int var_num;
    Fact inFact;
    Fact outFact;
};

FactBox new_FactBox(unsigned int bid, int var_num);

void free_FactBox(FactBox box);

Fact getInFactOfBox(FactBox box);

Fact getOutFactOfBox(FactBox box);

void setInFactOfBox(FactBox box, int i, bool exist);

void setOutFactOfBox(FactBox box, int i, bool exist);

#endif //PROJ4_FACT_H
