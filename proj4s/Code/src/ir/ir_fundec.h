//
// Created by 王紫萁 on 2022/11/25.
//

#ifndef PROJ4_IR_FUNDEC_H
#define PROJ4_IR_FUNDEC_H

// split the whole ir code into functions and extract variables

#include "../lib/list.h"
#include "stack_frame.h"

Array /*<IRFunDec>*/ IRFun_Array;

typedef struct IRFunDec_ *IRFunDec;
struct IRFunDec_ {
    char *fun_name;
    int id;
    ListNode begin; /* begin with code: FUNCTION func_name*/
    ListNode end;   /* end with next FUNCTION or NULL*/
    StackFrame frame;
};

IRFunDec new_IRFunDec(int id, char *fun_name, ListNode begin, ListNode end);

void free_IRFunDec(IRFunDec dec);

void init_IRFunDecs();

#endif //PROJ4_IR_FUNDEC_H
