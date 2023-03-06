//
// Created by 王紫萁 on 2022/11/24.
//

#ifndef PROJ4_STACK_FRAME_H
#define PROJ4_STACK_FRAME_H

/// a static descriptor of stack frame. only records parameters, variables and temporary variables

#define SYS_BIT 32
#define BYTE_BIT 8
#define MEM_WIDTH (SYS_BIT / BYTE_BIT)
#define NUM_CALLER_REG 10
#define NUM_CALLEE_REG 8
#define NUM_ARG_REG 4
#define FRAME_HEAD_SIZE (MEM_WIDTH * (2 + NUM_CALLEE_REG + NUM_CALLER_REG + NUM_ARG_REG))
// to map position to regs, first 32 indexes are used for regs, the last stands for the memory
// note: only few regs can be used to store variables


#include "../lib/array.h"
#include "ir_varInfo.h"

typedef struct StackFrame_ *StackFrame;

/**
 *      +-------------------+ <- fp
 *      |   return addr     |
 *      +-------------------+ -4
 *      |   caller fp       |
 *      +-------------------+ -8
 *      |       s0          |
 *      +-------------------+ -12
 *      |       s1          |
 *      +-------...---------+ -16
 *      |       s7          |
 *      +-------------------+ -40
 *      |       t0          |
 *      +-------------------+ -44
 *      |       t1          |
 *      +-------...---------+
 *      |       t9          |
 *      +-------------------+ -80
 *      |       a3          |
 *      +-------------------+ -84
 *      |       a2          |
 *      +-------------------+ -88
 *      |       a1          |
 *      +-------------------+ -92
 *      |       a0          |
 *      +-------------------+ -96
 *      |     vars tmps     |   // excludes parameters
 *      +-------------------+ <- sp
 */

struct StackFrame_ {

    //frame_size == 4 * (para_cnt + var_cnt) + FRAME_HEAD_SIZE
    char *fun_name;
    int frame_size;
    int para_cnt;
    int var_cnt;   // we count variables and temporary variables
    int varstack_size;
    Array varname_arr;
//    Array /*<VarInfo>*/ var_array;

};

StackFrame new_StackFrame(char *fun_name);

void free_StackFrame(StackFrame frame);

void push_param(StackFrame frame, char *param_name);

void push_var(StackFrame frame, char *var_name, int width);

char *getVarnameInFrame(StackFrame frame, int var_id);

int getOffsetRelFP(VarInfo info);


#endif //PROJ4_STACK_FRAME_H
