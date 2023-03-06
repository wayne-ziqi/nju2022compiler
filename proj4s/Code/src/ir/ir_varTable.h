//
// Created by 王紫萁 on 2022/11/27.
//

#ifndef PROJ4_IR_VARTABLE_H
#define PROJ4_IR_VARTABLE_H

#include "../lib/hashMap.h"
#include "ir_varInfo.h"
#include "ir.h"

HashMap IRVar_Tab;

void init_IRVarTab();

void addInfoToVarTab(VarInfo info);

VarInfo getVarInfo(char *var_name, char *fun_name);

VarInfo opd_to_varinfo(Operand opd, char *fun_name);
#endif //PROJ4_IR_VARTABLE_H
