//
// Created by 王紫萁 on 2022/11/24.
//

#include "stack_frame.h"
#include "ir_varTable.h"
#include <stdlib.h>
#include <assert.h>

static inline int len_digit(unsigned int i) {
    if (i >= 1000000000) return 10;
    if (i >= 100000000) return 9;
    if (i >= 10000000) return 8;
    if (i >= 1000000) return 7;
    if (i >= 100000) return 6;
    if (i >= 10000) return 5;
    if (i >= 1000) return 4;
    if (i >= 100) return 3;
    if (i >= 10) return 2;
    return 1;
}

StackFrame new_StackFrame(char *fun_name) {
    StackFrame frame = (StackFrame) malloc(sizeof(struct StackFrame_));
    frame->fun_name = fun_name;
    frame->frame_size = FRAME_HEAD_SIZE;
    frame->para_cnt = -NUM_ARG_REG; // initial para count is at the first para reg
    frame->var_cnt = 0;
    frame->varstack_size = 0;
    frame->varname_arr = new_Array();
    return frame;
}

void free_StackFrame(StackFrame frame) {
    free(frame);
}

char *getVarnameInFrame(StackFrame frame, int var_id) {
    assert(var_id >= 0 && var_id < sizeArray(frame->varname_arr));
    return getArray(frame->varname_arr, var_id);
}

int getOffsetRelFP(VarInfo info) {
    if (info->varKind == IRVAR_VAR || info->varKind == IRVAR_TMP) {
        return -(info->offset + FRAME_HEAD_SIZE);
    } else if (info->varKind == IRVAR_PARA) {
        return info->offset >= 0 ? info->offset : info->offset - (FRAME_HEAD_SIZE - NUM_ARG_REG * MEM_WIDTH);
    } else {
        assert(0);
    }
}


void push_param(StackFrame frame, char *param_name) {
    VarInfo info = new_VarInfo(param_name, frame->fun_name,
                               sizeArray(frame->varname_arr), IRVAR_PARA,
                               MEM_WIDTH * frame->para_cnt, MEM_WIDTH);
    // parameter's id can be calculated as id = offset / MEM_WIDTH + NUM_ARG_REG
    addInfoToVarTab(info);
    appendArray(frame->varname_arr, param_name);
    frame->para_cnt++;
    assert(frame->para_cnt + NUM_ARG_REG + frame->var_cnt == sizeArray(frame->varname_arr));
    // parameters value are stored in a0, a1, a2, a3 or caller's frame,
    // so we shall not change the frame size
//    if (frame->para_cnt > 0)frame->frame_size += MEM_WIDTH;
}

void push_var(StackFrame frame, char *var_name, int width) {
    VarInfo info = new_VarInfo(var_name, frame->fun_name,
                               sizeArray(frame->varname_arr), IRVAR_VAR,
                               frame->varstack_size + width, width);
    addInfoToVarTab(info);
    appendArray(frame->varname_arr, var_name);
    frame->var_cnt++;
    assert(frame->para_cnt + NUM_ARG_REG + frame->var_cnt == sizeArray(frame->varname_arr));
    frame->varstack_size += width;
    frame->frame_size += width;
}