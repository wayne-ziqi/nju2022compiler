//
// Created by 王紫萁 on 2022/11/27.
//

#include "SolverResult.h"
#include "../../../ir/ir_varTable.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

SolverResult new_SolverResult(int block_num, int var_num) {
    SolverResult result = (SolverResult) malloc(sizeof(struct SolverResult_));
    result->var_num = var_num;
    result->block_num = block_num;
    result->box_array = new_ArrayOfVol(block_num);
    for (int i = 0; i < block_num; ++i) {
        FactBox box = new_FactBox(i, var_num);
        appendArray(result->box_array, box);
    }
    return result;
}

Fact getOutFact(SolverResult result, unsigned int bid) {
    assert(bid >= 0 && bid < result->block_num);
    FactBox box = getArray(result->box_array, (int) bid);
    return getOutFactOfBox(box);
}

Fact getInFact(SolverResult result, unsigned int bid) {
    assert(bid >= 0 && bid < result->block_num);
    FactBox box = getArray(result->box_array, (int) bid);
    return getInFactOfBox(box);
}

List getBlockResult(SolverResult result, IRFunDec fun_dec, unsigned int bid) {
    Fact outFact = getOutFact(result, bid);
    List ret = new_list();
    for (int i = 0; i < result->var_num; ++i) {
        if (getFactIn(outFact, i)) {
            char *var_name = getVarnameInFrame(fun_dec->frame, i);
            VarInfo info = getVarInfo(var_name, fun_dec->fun_name);
            assert(info->var_id == i);
            pushTail(ret, newListNode(info));
        }
    }
    return ret;
}


void setOutFact(SolverResult result, unsigned int bid, Fact fact) {
    assert(result && fact && fact->size == result->var_num);
    Fact outFact = getOutFact(result, bid);
    for (int i = 0; i < result->var_num; ++i) {
        outFact->fact_arr[i] = fact->fact_arr[i];
    }
}

void setInFact(SolverResult result, unsigned int bid, Fact fact) {
    assert(result && fact && fact->size == result->var_num);
    Fact inFact = getInFact(result, bid);
    for (int i = 0; i < result->var_num; ++i) {
        inFact->fact_arr[i] = fact->fact_arr[i];
    }
}

void print_result(SolverResult result, IRFunDec funDec) {
    printf("==========Dataflow analysis result=========\n");
    printf("Function: %s\n", funDec->fun_name);
    for (int i = 0; i < result->block_num; ++i) {
        List info_list = getBlockResult(result, funDec, i);
        printf("B%d: { ", i);
        for (ListNode node = getHeadNode(info_list); node; node = node->next) {
            VarInfo cur_info = node->data;
            printf("%s ", cur_info->var_name);
        }
        printf("}\n");
        free_list(info_list);
    }
    printf("===========================================\n");
    fflush(stdout);
}

void free_SolverResult(SolverResult result) {
    for (int i = 0; i < result->block_num; ++i) {
        FactBox box = getArray(result->box_array, i);
        free_FactBox(box);
    }
    free(result);
}