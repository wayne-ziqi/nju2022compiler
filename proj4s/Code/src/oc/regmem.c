//
// Created by 王紫萁 on 2022/11/23.
//

#include "regmem.h"
#include "../ir/ir_varTable.h"
#include <assert.h>
#include <stdio.h>
#include "../optimizer/optimizer.h"
#include "string.h"

FILE *fd_asm;


const char RegStrMap[NUM_REGS][3] = {
        "0",
        "at",   /* assembler temporary */
        "v0", "v1", /* expression result and return value*/
        "a0", "a1", "a2", "a3", /* arguments */
        "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", /* caller save */
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", /* callee save */
        "t8", "t9", /* caller save */
        "k0", "k1", /* interrupt*/
        "gp",   /* global register*/
        "sp",   /* stack pointer */
        "fp"    /* aka s8*/,
        "ra",   /* return address */
};

VarInfo regInUse[NUM_REGS] = {NULL};

VarInfo regSaved[NUM_CALLEE_REG + NUM_CALLER_REG] = {NULL};

static inline RegKind ensure_reg(VarInfo var, InterCode code, Block block);

static inline RegKind allocate_reg(VarInfo var, InterCode code, Block block);

const char *regtostr(RegKind reg) {
    assert(reg >= 0 && reg < NUM_REGS);
    return RegStrMap[reg];
}

RegKind getReg(VarInfo var, InterCode code, Block block, IRFunDec funDec, int useordef) {
    if (useordef == DEF) {
        int exist_reg = getVarPosID(var, POS_REG);
        if (exist_reg != EMPTY_POS && regInUse[exist_reg] == var) {
            return exist_reg;
        }
        return allocate_reg(var, code, block);
    } else if (useordef == USE) {
        RegKind use = ensure_reg(var, code, block);
        return use;
    } else
        assert(0);
}

RegKind getTmpReg() {
    return REG_V1;
}


const char *getRegStr(VarInfo var, InterCode code, Block block, IRFunDec fundec, int useordef) {
    return RegStrMap[getReg(var, code, block, fundec, useordef)];
}

static RegKind searchForVarInReg(VarInfo var);

static inline RegKind ensure_reg(VarInfo var, InterCode code, Block block) {
    int reg_id = getVarPosID(var, POS_REG);
    RegKind exist = searchForVarInReg(var);
    if (exist != -1) {
        assert(regInUse[reg_id] == var || regInUse[reg_id] == NULL);
        regInUse[exist] = var;
        return exist;
    } else {
        RegKind new_reg = allocate_reg(var, code, block);
        int off = getOffsetRelFP(var);
        fprintf(fd_asm, "\tlw $%s, %d($fp)\n", RegStrMap[new_reg], off);
        return new_reg;
    }
}

static inline RegKind allocate_reg(VarInfo var, InterCode code, Block block) {
    for (int i = REG_S0; i <= REG_S7; ++i) {
        if (regInUse[i] == NULL) {
            setReg(i, var);
            return i;
        }
    }

    RegKind best = REG_S0;
    int distance = (int) 0x80000000;
    for (int i = REG_S0; i <= REG_S7; ++i) {
        VarInfo reg_var = regInUse[i];
        for (int j = sizeArray(block->codes) - 1; j >= code->offset; --j) {
            InterCode curcode = getArray(block->codes, j);
            Array uses = getUseOf(curcode);
            int cnt_uses = sizeArray(uses);
            int k = 0;
            for (; k < cnt_uses; ++k) {
                Operand use = getArray(uses, k);
                VarInfo use_info = opd_to_varinfo(use, reg_var->fun_name);
                if (use_info == reg_var)break;
            }
            free_Array(uses);
            if (k != cnt_uses && distance < j) {
                distance = j;
                best = i;
                break;
            }
        }
    }
    free_reg(best);
    setReg(best, var);
    return best;
}

static RegKind searchForVarInReg(VarInfo var) {
    for (int i = REG_S0; i <= REG_S7; ++i) {
        if (regInUse[i] == var)
            return i;
    }
    return -1;
}

void free_reg(RegKind reg) {
    assert(reg >= REG_T0 && reg <= REG_T9);
    VarInfo info = regInUse[reg];
    if (info) {
        updateVarPositionIn(info, POS_REG, EMPTY_POS);
        spill_reg(reg);
        regInUse[reg] = NULL;
    }
}

bool isNeeded(VarInfo var, InterCode code, IRFunDec funDec, Block block) {

    // use live variable to determine whether it will be used in the future
    // if var exist in live vars, return true, else return false
//    SolverResult live_solver = getSolverResultOf(funDec->id, LiveVariableAnalysis);
//    List live_vars = getBlockResult(live_solver, funDec, block->id);
//    if (existsInList(live_vars, var)) {
//        free_list(live_vars);
//        return true;
//    }
//    free_list(live_vars);
    // if it's not live find whether it'll be used in the block
    for (int i = code->offset + 1; i < sizeArray(block->codes); ++i) {
        InterCode curcode = getArray(block->codes, i);
        Array uses = getUseOf(curcode);
        for (int j = 0; j < sizeArray(uses); ++j) {
            Operand use_opd = getArray(uses, j);
            VarInfo use_info = opd_to_varinfo(use_opd, var->fun_name);
            if (use_info == var) {
                free_Array(uses);
                return true;
            }
        }
        free_Array(uses);
    }

    return false;
}

void spill_reg(RegKind reg) {
    if (regInUse[reg] == NULL)return;
    VarInfo info = regInUse[reg];
//    assert(info->offset >= 0);    arg reg can also be spilled
    int off = getOffsetRelFP(info);
    fprintf(fd_asm, "\tsw $%s, %d($fp)\n", RegStrMap[reg], off);
    updateVarPositionIn(info, POS_MEM, MEM_ID);
}

void setReg(RegKind reg, VarInfo var) {
//    assert(reg >= REG_A0 && reg <= REG_A3);
//    assert(var->varKind == IRVAR_PARA);
    regInUse[reg] = var;

    if (var) {
//        RegKind old = getVarPosID(var, POS_REG);
//        if (old != EMPTY_POS)regInUse[old] = NULL;
        updateVarPositionIn(var, POS_REG, reg);
    }
}

void save_reg(RegKind reg) {
    // save reg for stack transferring
    assert(reg >= REG_T0 && reg <= REG_T9);
    regSaved[reg - REG_T0] = regInUse[reg];
}

void recover_reg(RegKind reg) {
    // recover reg for stack transferring
    assert(reg >= REG_T0 && reg <= REG_T9);
    regInUse[reg] = regSaved[reg - REG_T0];
}

VarInfo getVarInReg(RegKind reg) {
    assert(reg >= REG_T0 && reg <= REG_T9 || reg >= REG_A0 && reg <= REG_A3);
    return regInUse[reg];
}