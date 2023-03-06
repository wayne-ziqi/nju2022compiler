//
// Created by 王紫萁 on 2022/11/25.
//
#include "ir_fundec.h"
#include "ir.h"
#include "ir_varTable.h"
#include <stdlib.h>
#include <assert.h>

List IRList;

IRFunDec new_IRFunDec(int id, char *fun_name, ListNode begin, ListNode end) {
    IRFunDec dec = (IRFunDec) malloc(sizeof(struct IRFunDec_));
    dec->id = id;
    dec->fun_name = fun_name;
    dec->frame = new_StackFrame(fun_name);
    dec->begin = begin;
    dec->end = end;
    return dec;
}

void free_IRFunDec(IRFunDec dec) {
    free_StackFrame(dec->frame);
    free(dec);
}

static inline void var_pusher(StackFrame frame, Operand o, unsigned int width) {
    char *left_name = operand_to_string(o);
    VarInfo exist = getVarInfo(left_name, frame->fun_name);
    if (exist)free(left_name);
    else {
        push_var(frame, left_name, (int) width);
    }
}

/**
 * gather all variables and temps
 * @param irstart_node FUNCTION fun_name
 * @param irend_node   NULL / FUNCTION next_func
 */
void proc_fun_frame(ListNode irstart_node, ListNode irend_node) {
    InterCode funcode = irstart_node->data;
    assert(funcode->kind == CODE_FUN);
    char *fun_name = operand_to_string(funcode->single.o);
    IRFunDec cur_dec = new_IRFunDec(sizeArray(IRFun_Array), fun_name, irstart_node, irend_node);
    StackFrame cur_frame = cur_dec->frame;
    appendArray(IRFun_Array, cur_dec);
    // push defines
    for (ListNode node = irstart_node->next; node != irend_node; node = node->next) {
        InterCode code = node->data;
        switch (code->opd_num) {
            case 1: {
                Operand o = code->single.o;
                if (code->kind == CODE_PARAM) {
                    char *para_name = operand_to_string(o);
                    VarInfo exist = getVarInfo(para_name, fun_name);
                    if (exist)free(para_name);
                    else push_param(cur_frame, para_name);
                } else if (code->kind == CODE_READ) {
                    char *read_name = operand_to_string(o);
                    VarInfo exist = getVarInfo(read_name, fun_name);
                    if (exist)free(read_name);
                    else push_var(cur_frame, read_name, MEM_WIDTH);
                }
                break;
            }
            case 2 : {
                Operand o1 = code->twin.o1;
                Operand o2 = code->twin.o2;
                if (code->kind == CODE_ASSIGN || code->kind == CODE_CALL ||
                    code->kind == CODE_GETADDR || code->kind == CODE_LOADADDR
                        ) {
                    var_pusher(cur_frame, o1, MEM_WIDTH);
                } else if (code->kind == CODE_DEC) {
                    assert(o2->kind == OPD_CONST);
                    var_pusher(cur_frame, o1, o2->v_const);
                }
                break;
            }
            case 3: {
                Operand result = code->triple.o3;
                var_pusher(cur_frame, result, MEM_WIDTH);
                break;
            }
        }
    }
}

void init_IRFunDecs() {
    init_IRVarTab();
    IRFun_Array = new_Array();
    ListNode begin = getHeadNode(IRList);
    assert(((InterCode) begin->data)->kind == CODE_FUN);
    ListNode end = begin;
    while (end) {
        InterCode code = end->data;
        if (end != begin && code->kind == CODE_FUN) {
            proc_fun_frame(begin, end);
            begin = end;
        } else {
            end = end->next;
        }
    }
    proc_fun_frame(begin, end);
}

