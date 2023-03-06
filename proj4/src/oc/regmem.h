//
// Created by 王紫萁 on 2022/11/23.
//

#ifndef PROJ4_REGMEM_H
#define PROJ4_REGMEM_H

#include "../ir/ir_varInfo.h"
#include "../ir/ir.h"
#include "../ir/ir_fundec.h"
#include "../cfg/cfg.h"

#define DEF 0
#define USE 1
#define NUM_REGS 32

#define NOT_NEEDED 0
#define GLOBAL_NEEDED 1
#define IS_NEEDED 2

// t0-t7-s0-s7-t8-t9 is free to use
typedef enum RegKind {
    REG_ZERO,
    REG_AT,
    REG_V0, REG_V1,
    REG_A0, REG_A1, REG_A2, REG_A3,
    REG_T0, REG_T1, REG_T2, REG_T3, REG_T4, REG_T5, REG_T6, REG_T7,
    REG_S0, REG_S1, REG_S2, REG_S3, REG_S4, REG_S5, REG_S6, REG_S7,
    REG_T8, REG_T9,
    REG_K0, REG_K1,
    REG_GP,
    REG_SP,
    REG_FP,
    REG_RA
} RegKind;


RegKind getReg(VarInfo var, InterCode code, Block block, IRFunDec funDec, int useordef);

// get v1 for temporary use
RegKind getTmpReg();

/**
 * dangerous, currently can only set a0-a3
 * @param reg
 * @param var
 */
void setReg(RegKind reg, VarInfo var);

/**
 * get a determined reg for variable
 * @param var
 * @param useordef
 * @return
 */
const char *getRegStr(VarInfo var, InterCode code, Block block, IRFunDec funDec, int useordef);

int isNeeded(VarInfo var, InterCode code, IRFunDec funDec, Block block);

void free_reg(RegKind reg);

const char *regtostr(RegKind reg);

/**
 * spill reg back to var's offset, will check whether var exists in
 * @param reg
 * @param var
 */

void spill_reg(RegKind reg);

void save_reg(RegKind reg);

VarInfo getVarInReg(RegKind reg);

#endif //PROJ4_REGMEM_H
