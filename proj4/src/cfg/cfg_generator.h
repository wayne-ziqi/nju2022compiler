//
// Created by 王紫萁 on 2022/11/26.
//

#ifndef PROJ4_CFG_GENERATOR_H
#define PROJ4_CFG_GENERATOR_H

/// generate cfg's from IRFun_Array and store in CFG_Array;
#include "../lib/array.h"

Array /*<CFG>*/ CFG_Array;

void genCFGs(char* filename);

#endif //PROJ4_CFG_GENERATOR_H
