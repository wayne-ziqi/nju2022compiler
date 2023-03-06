//
// Created by 王紫萁 on 2022/11/27.
//

#include "ir_varInfo.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


static inline char *new_str(char *src) {
    char *dst = (char *) malloc((strlen(src) + 1) * sizeof(char));
    strcpy(dst, src);
    return dst;
}


VarInfo new_VarInfo(char *varname, char *fun_name, int var_id, IRVarKind varKind, int offset, unsigned int width) {
    VarInfo info = (VarInfo) malloc(sizeof(struct VarInfo_));
    info->varKind = varKind;
    info->var_name = new_str(varname);
    info->fun_name = fun_name;
    info->var_id = var_id;
    info->var_pos[POS_REG] = EMPTY_POS;
    info->var_pos[POS_MEM] = MEM_ID;  // it's in the memory originally
    info->offset = offset;
    info->width = width;
    return info;
}

void free_VarInfo(VarInfo info) {
    free(info->var_name);
    free(info->var_pos);
    free(info);
}

int getVarOffset(VarInfo info) {
    assert(info);
    return info->offset;
}


int getVarPosID(VarInfo info, int POS) {
    assert(POS == POS_REG || POS == POS_REG);  //refer to regmem.h
    assert(info);
    return info->var_pos[POS];
}

void updateVarPositionIn(VarInfo info, int POS, int pos_id) {
    assert(POS == POS_REG || POS == POS_MEM);
    assert(info);
    info->var_pos[POS] = pos_id;
}
