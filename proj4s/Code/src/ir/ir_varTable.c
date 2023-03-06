//
// Created by 王紫萁 on 2022/11/27.
//

#include "ir_varTable.h"
#include "ir_varInfo.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void init_IRVarTab() {
    IRVar_Tab = new_hashmap(STRING, DEFAULT_SLOT_SIZE);
}

void addInfoToVarTab(VarInfo info) {
    addHead(IRVar_Tab, info->var_name, info);
}

typedef struct IRSearKey {
    char *var_name;
    char *fun_name;
} IRSearKey;

bool compare_IRVarDec(IRSearKey* key, VarInfo info) {
    return strcmp(key->var_name, info->var_name) == 0 &&
           strcmp(key->fun_name, info->fun_name) == 0;
}

VarInfo getVarInfo(char *var_name, char *fun_name) {
    IRSearKey key = {var_name, fun_name};
    return getFirstOf(IRVar_Tab, var_name, &key, (bool (*)(void *, void *)) compare_IRVarDec);
}

VarInfo opd_to_varinfo(Operand opd, char *fun_name) {
    char *name = operand_to_string(opd);
    VarInfo info = getVarInfo(name, fun_name);
    free(name);
    return info;
}