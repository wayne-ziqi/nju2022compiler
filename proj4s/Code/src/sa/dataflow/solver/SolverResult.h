//
// Created by 王紫萁 on 2022/11/27.
//

#ifndef PROJ4_SOLVERRESULT_H
#define PROJ4_SOLVERRESULT_H

#include "../../../lib/array.h"
#include "../fact/fact.h"
#include "../../../lib/list.h"
#include "../../../ir/ir_fundec.h"

typedef struct SolverResult_ *SolverResult;

struct SolverResult_ {
    int block_num;
    int var_num;
    Array/*<FactBox>*/ box_array;
};

SolverResult new_SolverResult(int block_num, int var_num);

Fact getOutFact(SolverResult result, unsigned int bid);

Fact getInFact(SolverResult result,unsigned int bid);

List/*<VarInfo>*/ getBlockResult(SolverResult result, IRFunDec fun_dec, unsigned int bid);

void print_result(SolverResult result, IRFunDec funDec);

/**
 *  make sure fact has the exactly same length as result's
 * @param result
 * @param bid block id
 * @param fact
 */
void setOutFact(SolverResult result, unsigned int bid, Fact fact);

/**
 *  make sure fact has the exactly same length as result's
 * @param result
 * @param bid block id
 * @param fact
 */
void setInFact(SolverResult result, unsigned int bid, Fact fact);

void free_SolverResult(SolverResult result);

#endif //PROJ4_SOLVERRESULT_H
