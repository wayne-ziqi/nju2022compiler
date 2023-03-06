//
// Created by 王紫萁 on 2022/11/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "oct.h"
#include "../cfg/cfg_generator.h"
#include "../optimizer/optimizer.h"
#include "../cfg/cfg.h"
#include "../ir/ir_varTable.h"
#include "regmem.h"


FILE *fd_asm = NULL;

static void prepare_head() {
    fprintf(fd_asm, ".data\n");
    fprintf(fd_asm, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fd_asm, "_ret: .asciiz \"\\n\"\n");
    fprintf(fd_asm, ".globl main\n");
    fprintf(fd_asm, ".text\n");
    // text start
}

static void prepare_read_write() {
    fprintf(fd_asm, "read:\n");
    fprintf(fd_asm, "\tli $v0, 4\n");
    fprintf(fd_asm, "\tla $a0, _prompt\n");
    fprintf(fd_asm, "\tsyscall\n");
    fprintf(fd_asm, "\tli $v0, 5\n");
    fprintf(fd_asm, "\tsyscall\n");
    fprintf(fd_asm, "\tjr $ra\n");

    fprintf(fd_asm, "\nwrite:\n");
    fprintf(fd_asm, "\tli $v0, 1\n");
    fprintf(fd_asm, "\tsyscall\n");
    fprintf(fd_asm, "\tli $v0, 4\n");
    fprintf(fd_asm, "\tla $a0, _ret\n");
    fprintf(fd_asm, "\tsyscall\n");
    fprintf(fd_asm, "\tmove $v0, $0\n");
    fprintf(fd_asm, "\tjr $ra\n");
}

void do_oct();

void oct_entry(char *to_file) {
    fd_asm = fopen(to_file, "w");
    prepare_head();
    prepare_read_write();
    do_oct();
    fclose(fd_asm);
}

static void oct_prologue(IRFunDec func);

static void oct_epilogue(IRFunDec func);

static void oct_call(IRFunDec func, Block callBlock);

static inline void oct_code_util(InterCode code, IRFunDec funDec, Block block, List live_vars);

void saveBackRegs(List live_vars) {
    for (int j = REG_T0; j <= REG_T9; ++j) {
        free_reg(j);
    }
}

void do_oct() {
    for (int i = 0; i < sizeArray(IRFun_Array); ++i) {
        IRFunDec funDec = getArray(IRFun_Array, i);
        assert(funDec->id == i);

        SolverResult liveResult = getSolverResultOf(i, LiveVariableAnalysis);

        // prologue
        oct_prologue(funDec);
        // body
        ListNode begin = funDec->begin->next;   // funDec.begin = FUNCTION func_name
        while (begin != funDec->end) {
            InterCode code = begin->data;
            Block block = getBlock(getArray(CFG_Array, i), code->bid);
            List/*<VarInfo>*/ live_vars = getBlockResult(liveResult, funDec, block->id);
            oct_code_util(code, funDec, block, live_vars);
            if (code->offset == sizeArray(block->codes) - 1 &&
                !(code->kind == CODE_GOTO || code->kind == CODE_IF || code->kind == CODE_RETURN)) {
                saveBackRegs(live_vars);
            }
            begin = begin->next;
        }
        oct_epilogue(funDec);
    }
}

static bool readyToFree(RegKind use_reg, VarInfo var, InterCode code, IRFunDec funDec, Block block) {
    return (use_reg >= REG_S0 && use_reg <= REG_S7) && !isNeeded(var, code, funDec, block);
}

void oct_code_util(InterCode code, IRFunDec funDec, Block block, List live_vars) {
    char *fun_name = funDec->fun_name;
    switch (code->kind) {
        case CODE_LABEL: {
            char *label = operand_to_string(code->single.o);
            fprintf(fd_asm, "%s:\n", label);
            free(label);
            break;
        }
        case CODE_ASSIGN: {
            Operand o1 = code->twin.o1;
            Operand o2 = code->twin.o2;
            RegKind def_reg;
            if (o2->kind == OPD_CONST) {
                def_reg = getReg(opd_to_varinfo(o1, fun_name), code, block, funDec, DEF);
                fprintf(fd_asm, "\tli $%s, %d\n", regtostr(def_reg), o2->v_const);
            } else if (o2->kind == OPD_VAR || o2->kind == OPD_TMP) {
                VarInfo var_o2 = opd_to_varinfo(o2, fun_name);
                RegKind use_reg = getReg(var_o2, code, block, funDec, USE);
                def_reg = getReg(opd_to_varinfo(o1, fun_name), code, block, funDec, DEF);
                fprintf(fd_asm, "\tmove $%s, $%s\n", regtostr(def_reg), regtostr(use_reg));
                if (readyToFree(use_reg, var_o2, code, funDec, block))
                    free_reg(use_reg);
            } else {
                assert(0);
            }
            break;
        }
        case CODE_ADD:
        case CODE_SUB: {
            Operand res = code->triple.o3;
            Operand o1 = code->triple.o1;
            Operand o2 = code->triple.o2;
            VarInfo var_res = opd_to_varinfo(res, fun_name);
            VarInfo var_o1 = NULL;
            VarInfo var_o2 = NULL;
            RegKind res_reg;
            RegKind o1_reg;
            if (o1->kind == OPD_CONST) {
                RegKind const_reg = getTmpReg();
                fprintf(fd_asm, "\tli, $v1, %d\n", o1->v_const);
                o1_reg = const_reg;
            } else if (o1->kind == OPD_ADDR) {
                // parameters' addresses are also reachable
                RegKind addr_reg = getTmpReg();
                char *target = operand_to_string(o1->o_addr);
                int off = getOffsetRelFP(getVarInfo(target, fun_name));
                free(target);
                fprintf(fd_asm, "\tla $%s, %d($fp)\n", regtostr(addr_reg), off);
                o1_reg = addr_reg;
            } else {
                assert(o1->kind == OPD_VAR || o1->kind == OPD_TMP);
                var_o1 = opd_to_varinfo(o1, fun_name);
                o1_reg = getReg(var_o1, code, block, funDec, USE);

            }
            if (o2->kind == OPD_CONST) {
                res_reg = getReg(var_res, code, block, funDec, DEF);
                if (code->kind == CODE_ADD)
                    fprintf(fd_asm, "\taddi $%s, $%s, %d\n", regtostr(res_reg), regtostr(o1_reg), o2->v_const);
                else
                    fprintf(fd_asm, "\taddi $%s, $%s, -%d\n", regtostr(res_reg), regtostr(o1_reg), o2->v_const);
            } else if (o2->kind == OPD_TMP || o2->kind == OPD_VAR) {
                var_o2 = opd_to_varinfo(o2, fun_name);
                RegKind o2_reg = getReg(var_o2, code, block, funDec, USE);
                res_reg = getReg(var_res, code, block, funDec, DEF);
                if (code->kind == CODE_ADD)
                    fprintf(fd_asm, "\tadd $%s, $%s, $%s\n", regtostr(res_reg), regtostr(o1_reg), regtostr(o2_reg));
                else
                    fprintf(fd_asm, "\tsub $%s, $%s, $%s\n", regtostr(res_reg), regtostr(o1_reg), regtostr(o2_reg));

                if (readyToFree(o2_reg, var_o2, code, funDec, block))
                    free_reg(o2_reg);
            } else {
                assert(0);
            }
            if (var_o1 && var_o1 != var_o2) {
                if (readyToFree(o1_reg, var_o1, code, funDec, block))
                    free_reg(o1_reg);
            }
            break;
        }
        case CODE_MUL:
        case CODE_DIV: {
            Operand res = code->triple.o3;
            Operand o1 = code->triple.o1;
            Operand o2 = code->triple.o2;
            VarInfo var_res = opd_to_varinfo(res, fun_name);
            VarInfo var_o1 = NULL;
            VarInfo var_o2 = NULL;
            RegKind res_reg;
            RegKind o1_reg;
            RegKind o2_reg;
            if (o1->kind == OPD_CONST) {
                o1_reg = REG_V1;
                fprintf(fd_asm, "\tli $v1, %d\n", o1->v_const);
            } else {
                var_o1 = opd_to_varinfo(o1, fun_name);
                o1_reg = getReg(var_o1, code, block, funDec, USE);
            }

            if (o2->kind == OPD_CONST) {
                o2_reg = getTmpReg();
                fprintf(fd_asm, "\tli $%s, %d\n", regtostr(o2_reg), o2->v_const);
            } else {
                var_o2 = opd_to_varinfo(o2, fun_name);
                o2_reg = getReg(var_o2, code, block, funDec, USE);
            }
            // translate
            res_reg = getReg(var_res, code, block, funDec, DEF);
            if (code->kind == CODE_MUL) {
                fprintf(fd_asm, "\tmul $%s, $%s, $%s\n", regtostr(res_reg), regtostr(o1_reg), regtostr(o2_reg));
            } else {
                fprintf(fd_asm, "\tdiv $%s, $%s\n", regtostr(o1_reg), regtostr(o2_reg));
                fprintf(fd_asm, "\tmflo $%s\n", regtostr(res_reg));
            }
            if (var_o1 && readyToFree(o1_reg, var_o1, code, funDec, block))
                free_reg(o1_reg);
            if (var_o2 && var_o1 != var_o2 && readyToFree(o2_reg, var_o2, code, funDec, block))
                free_reg(o2_reg);
            break;
        }
        case CODE_LOADADDR: {    // x = *y
            Operand x = code->twin.o1;
            Operand y = code->twin.o2;
            VarInfo var_x = opd_to_varinfo(x, fun_name);
            VarInfo var_y = opd_to_varinfo(y, fun_name);
            assert(y->kind == OPD_TMP);
            RegKind y_reg = getReg(var_y, code, block, funDec, USE);
            RegKind x_reg = getReg(var_x, code, block, funDec, DEF);
            fprintf(fd_asm, "\tlw $%s, 0($%s)\n", regtostr(x_reg), regtostr(y_reg));
            if (readyToFree(y_reg, var_y, code, funDec, block))
                free_reg(y_reg);
            break;
        }
        case CODE_STOREADDR: {  // *x = y
            Operand x = code->twin.o1;
            Operand y = code->twin.o2;
            VarInfo var_x = opd_to_varinfo(x, fun_name);
            VarInfo var_y = opd_to_varinfo(y, fun_name);
            RegKind x_reg = getReg(var_x, code, block, funDec, USE);
            RegKind y_reg = getReg(var_y, code, block, funDec, USE);
            fprintf(fd_asm, "\tsw $%s, 0($%s)\n", regtostr(y_reg), regtostr(x_reg));
            if (readyToFree(x_reg, var_x, code, funDec, block))
                free_reg(x_reg);
            if (readyToFree(y_reg, var_y, code, funDec, block))
                free_reg(y_reg);
            break;
        }
        case CODE_GETADDR: {    // x = &y
            Operand x = code->twin.o1;
            Operand y = code->twin.o2;
            VarInfo var_x = opd_to_varinfo(x, fun_name);
            RegKind x_reg = getReg(var_x, code, block, funDec, DEF);
            assert(y->kind == OPD_VAR);
            char *y_name = operand_to_string(y);
            int y_off = getOffsetRelFP(getVarInfo(y_name, fun_name));
            free(y_name);
            fprintf(fd_asm, "\tla $%s, %d($fp)\n", regtostr(x_reg), y_off);
            break;
        }
        case CODE_GOTO: {
            Operand target = code->single.o;
            char *label = operand_to_string(target);
            saveBackRegs(live_vars);
            fprintf(fd_asm, "\tj %s\n", label);
            free(label);
            break;
        }
        case CODE_CALL: {
            Block callBlock = getBlock(getArray(CFG_Array, funDec->id), code->bid);
            oct_call(funDec, callBlock);
            Operand recv = code->twin.o1;
            VarInfo var_recv = opd_to_varinfo(recv, fun_name);
            RegKind recv_reg = getReg(var_recv, code, block, funDec, DEF);
            fprintf(fd_asm, "\tmove $%s, $v0\n", regtostr(recv_reg));
            break;
        }
        case CODE_READ: {
            // read function will store the return value into v0
            // stack of read can be hard-coded into translation
            Operand read_to = code->single.o;
            VarInfo var_read = opd_to_varinfo(read_to, fun_name);
            RegKind read_reg = getReg(var_read, code, block, funDec, DEF);
            fprintf(fd_asm, "\taddi $sp, $sp, -4\n");
            fprintf(fd_asm, "\tsw $ra, 0($sp)\n");
            fprintf(fd_asm, "\tjal read\n");
            fprintf(fd_asm, "\tlw $ra, 0($sp)\n");
            fprintf(fd_asm, "\taddi $sp, $sp, 4\n");
            fprintf(fd_asm, "\tmove $%s, $v0\n", regtostr(read_reg));
            break;
        }
        case CODE_WRITE: {
            // write will print value stored in the first argument, aka a0
            Operand wr = code->single.o;
            VarInfo var_wr = NULL;
            RegKind wr_reg;
            if (wr->kind == OPD_CONST) {
                wr_reg = REG_V1;
                fprintf(fd_asm, "\tli $v1, %d\n", wr->v_const);
            } else {
                var_wr = opd_to_varinfo(wr, fun_name);
                wr_reg = getReg(var_wr, code, block, funDec, USE);
            }
            fprintf(fd_asm, "\tmove $a0, $%s\n", regtostr(wr_reg));
            fprintf(fd_asm, "\taddi $sp, $sp, -4\n");
            fprintf(fd_asm, "\tsw $ra, 0($sp)\n");
            fprintf(fd_asm, "\tjal write\n");
            fprintf(fd_asm, "\tlw $ra, 0($sp)\n");
            fprintf(fd_asm, "\taddi $sp, $sp, 4\n");
            if (var_wr && readyToFree(wr_reg, var_wr, code, funDec, block))
                free_reg(wr_reg);
            break;
        }
        case CODE_RETURN: {
            Operand ret = code->single.o;
            if (ret->kind == OPD_CONST) {
                fprintf(fd_asm, "\tli $v0, %d\n", ret->v_const);
            } else {
                assert(ret->kind == OPD_TMP || ret->kind == OPD_VAR);
                VarInfo var_ret = opd_to_varinfo(ret, fun_name);
                RegKind ret_reg = getReg(var_ret, code, block, funDec, USE);
                free_reg(ret_reg);
                fprintf(fd_asm, "\tmove $v0, $%s\n", regtostr(ret_reg));
            }
            saveBackRegs(live_vars);
            // jump to return sequence which helps to deal with stack issue
            fprintf(fd_asm, "\tj ret_%s\n", fun_name);
            break;
        }
        case CODE_IF: {
            RelOpKind op = code->if_code.relop;
            Operand cond1 = code->if_code.cond1;
            Operand cond2 = code->if_code.cond2;
            VarInfo var_cond1 = NULL;
            VarInfo var_cond2 = NULL;
            RegKind reg1 = cond1->kind == OPD_CONST ? REG_V0 :
                           getReg(var_cond1 = opd_to_varinfo(cond1, fun_name), code, block, funDec, USE);
            RegKind reg2 = cond2->kind == OPD_CONST ? REG_V1 :
                           getReg(var_cond2 = opd_to_varinfo(cond2, fun_name), code, block, funDec, USE);
            if (cond1->kind == OPD_CONST)fprintf(fd_asm, "\tli $v0, %d\n", cond1->v_const);
            if (cond2->kind == OPD_CONST)fprintf(fd_asm, "\tli $v1, %d\n", cond2->v_const);
            if (var_cond1 && readyToFree(reg1, var_cond1, code, funDec, block))
                free_reg(reg1);
            if (var_cond2 && var_cond1 != var_cond2 && readyToFree(reg2, var_cond2, code, funDec, block))
                free_reg(reg2);
            char *label = operand_to_string(code->if_code.to_label);
            saveBackRegs(live_vars);
            switch (op) {
                case REL_EQ:
                    fprintf(fd_asm, "\tbeq $%s, $%s, %s\n", regtostr(reg1), regtostr(reg2), label);
                    break;
                case REL_NE:
                    fprintf(fd_asm, "\tbne $%s, $%s, %s\n", regtostr(reg1), regtostr(reg2), label);
                    break;
                case REL_GT:
                    fprintf(fd_asm, "\tbgt $%s, $%s, %s\n", regtostr(reg1), regtostr(reg2), label);
                    break;
                case REL_LT:
                    fprintf(fd_asm, "\tblt $%s, $%s, %s\n", regtostr(reg1), regtostr(reg2), label);
                    break;
                case REL_GE:
                    fprintf(fd_asm, "\tbge $%s, $%s, %s\n", regtostr(reg1), regtostr(reg2), label);
                    break;
                case REL_LE:
                    fprintf(fd_asm, "\tble $%s, $%s, %s\n", regtostr(reg1), regtostr(reg2), label);
                    break;
                default:
                    assert(0);
            }
            free(label);
            break;
        }
        case CODE_PARAM: {
            Operand para = code->single.o;
            VarInfo para_info = opd_to_varinfo(para, fun_name);
            int id = para_info->offset / MEM_WIDTH;
            if (id < 0) {
                RegKind arg_reg = id + NUM_ARG_REG + REG_A0;
                setReg(arg_reg, para_info);
                spill_reg(arg_reg);
            }
        }
        default:
            break;
    }
}

void oct_prologue(IRFunDec func) {
    int frame_size = func->frame->frame_size;
    fprintf(fd_asm, "\n%s:\n", func->fun_name);
    // prepare stack frame: move down sp
    fprintf(fd_asm, "\tsubu $sp, $sp, %d\n", frame_size);
    // save return address to stack bottom
    fprintf(fd_asm, "\tsw $ra, %d($sp)\n", frame_size - MEM_WIDTH);
    // save the caller's fp to stack bottom + 4
    fprintf(fd_asm, "\tsw $fp, %d($sp)\n", frame_size - 2 * MEM_WIDTH);
    // let fp point to the stack bottom
    fprintf(fd_asm, "\taddi $fp, $sp, %d\n", frame_size);
    // callee-stored regs
    for (int i = 0; i < NUM_CALLEE_REG; ++i) {
        fprintf(fd_asm, "\tsw $s%d, -%d($fp)\n", i, (3 + i) * MEM_WIDTH);  // fp - 12: s0
    }
}

void oct_epilogue(IRFunDec func) {
    int frame_size = func->frame->frame_size;
    // recover s0-s7
    // return label, every return code should jump here after saving the return value to v0
    fprintf(fd_asm, "ret_%s:\n", func->fun_name);
    for (int i = 0; i < NUM_CALLEE_REG; ++i) {
        fprintf(fd_asm, "\tlw $s%d, -%d($fp)\n", i, (3 + i) * MEM_WIDTH);
    }
    //recover return address
    fprintf(fd_asm, "\tlw $ra, %d($sp)\n", frame_size - MEM_WIDTH);
    // recover fp
    fprintf(fd_asm, "\tlw $fp, %d($sp)\n", frame_size - 2 * MEM_WIDTH);
    // erase frame
    fprintf(fd_asm, "\taddi $sp, $sp, %d\n", frame_size);
    // jump back;
    fprintf(fd_asm, "\tjr $ra\n");
}


void oct_call(IRFunDec func, Block callBlock) {
    SolverResult res_live = getSolverResultOf(func->id, LiveVariableAnalysis);
    List live_list = getBlockResult(res_live, func, callBlock->id);
    // if t0-t1 9contains var store them to the stack
    bool live_regs[10];
    int callerReg_off = MEM_WIDTH * (2 + NUM_CALLEE_REG);
    memset(live_regs, false, 10 * sizeof(bool));
    for (ListNode lnode = getHeadNode(live_list); lnode; lnode = lnode->next) {
        VarInfo var = lnode->data;
        RegKind inreg = getVarPosID(var, POS_REG);
        if (inreg >= REG_T0 && inreg <= REG_T7) live_regs[inreg - REG_T0] = true;
        else if (inreg == REG_T8 || inreg == REG_T9) live_regs[8 + inreg - REG_T8] = true;
    }
    for (int i = 0; i < 10; ++i) {
        if (live_regs[i]) {
            fprintf(fd_asm, "\tsw $t%d, -%d($fp)\n", i, callerReg_off + (i + 1) * MEM_WIDTH);
        }
    }

    // prepare for callee's args
    int arg_cnt = sizeArray(callBlock->codes) - 1;  // call block's last code is call
    if (arg_cnt > NUM_ARG_REG)
        fprintf(fd_asm, "\tsubu $sp, $sp, %d\n", (arg_cnt - NUM_ARG_REG) * MEM_WIDTH);
    for (int i = arg_cnt - 1, j = 0; i >= 0; --i, ++j) {
        InterCode arg_code = getArray(callBlock->codes, i);
        assert(arg_code->kind == CODE_ARG);
        Operand arg = arg_code->single.o;
        if (arg->kind == OPD_CONST) {
            if (j < NUM_ARG_REG) {
                fprintf(fd_asm, "\tli $a%d, %d\n", j, arg->v_const);
            } else {
                // save const to sp using v1
                fprintf(fd_asm, "\tli $v1, %d\n", arg->v_const);
                fprintf(fd_asm, "\tsw $v1, %d($sp)\n", (j - NUM_ARG_REG) * MEM_WIDTH);
            }
        } else if (arg->kind == OPD_ADDR) {
            assert(0);
            // given that all variables are normal.
        } else if (arg->kind == OPD_TMP || arg->kind == OPD_VAR) {
            VarInfo var_arg = opd_to_varinfo(arg, func->fun_name);
            //arg is the para of the caller
            RegKind arg_reg = getReg(var_arg, arg_code, callBlock, func, USE);
            if (j < NUM_ARG_REG) {
                fprintf(fd_asm, "\tmove $a%d, $%s\n", j, regtostr(arg_reg));
            } else {
                fprintf(fd_asm, "\tsw $%s, %d($sp)\n", regtostr(arg_reg), (j - NUM_ARG_REG) * MEM_WIDTH);
            }
            if (readyToFree(arg_reg, var_arg, arg_code, func, callBlock))
                free_reg(arg_reg);
        } else {
            assert(0);
        }
    }
    // jump to callee
    InterCode callcode = getArrayTail(callBlock->codes);
    assert(callcode->kind == CODE_CALL);
    assert(callcode->twin.o2->kind == OPD_FUN);
    char *fun_name = operand_to_string(callcode->twin.o2);
    fprintf(fd_asm, "\tjal %s\n", fun_name);
    free(fun_name);

    // recover
    if (arg_cnt > NUM_ARG_REG)
        fprintf(fd_asm, "\taddi, $sp, $sp, %d\n", (arg_cnt - NUM_ARG_REG) * MEM_WIDTH);
    for (int i = 0; i < 10; ++i) {
        if (live_regs[i]) {
            fprintf(fd_asm, "\tlw $t%d, -%d($fp)\n", i, callerReg_off + (i + 1) * MEM_WIDTH);
        }
    }
}

