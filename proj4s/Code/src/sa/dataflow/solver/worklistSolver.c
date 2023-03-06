//
// Created by 王紫萁 on 2022/11/27.
//

#include "worklistSolver.h"
#include "../../../ir/ir_varTable.h"
#include "../../../lib/queue.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

static void initialize(WLSolver solver, CFG cfg);

static void initializeBackward(CFG cfg, SolverResult result, Analysis analysis);

static void doSolveBackward(CFG cfg, SolverResult result, Analysis analysis);

static void initializeForward(CFG cfg, SolverResult result, Analysis analysis);

static void doSolveForward(CFG cfg, SolverResult result, Analysis analysis);

static void doSolve(AnalysisFlow flow, CFG cfg, SolverResult result, Analysis analysis);

WLSolver new_WLSolver(Analysis analysis) {
    WLSolver solver = (WLSolver) malloc(sizeof(struct WLSolver_));
    solver->analysis = analysis;
    solver->result = NULL;
    return solver;
}

void solve(WLSolver solver, CFG cfg) {
    initialize(solver, cfg);
    doSolve(solver->analysis->flow, cfg, solver->result, solver->analysis);
}

static void initialize(WLSolver solver, CFG cfg) {
    int block_num = (int) cfg->base_graph->num_node;
    StackFrame frame = cfg->fun_dec->frame;
    int var_num = frame->var_cnt + frame->para_cnt + NUM_ARG_REG;

    solver->result = new_SolverResult(block_num, var_num);
    if (solver->analysis->flow == FLOW_FORWARD) {
        initializeForward(cfg, solver->result, solver->analysis);
    } else {
        initializeBackward(cfg, solver->result, solver->analysis);
    }
}


static void initializeBackward(CFG cfg, SolverResult result, Analysis analysis) {
    setInFact(result, EXIT_BID, analysis->newBoundaryFact(cfg));
    setOutFact(result, EXIT_BID, analysis->newBoundaryFact(cfg));
    for (int i = 0; i < numCFGBlocks(cfg); ++i) {
        Block block = getBlock(cfg, i);
        if (!isExitBlock(block)) {
            setOutFact(result, block->id, analysis->newInitialFact(cfg));
            setInFact(result, block->id, analysis->newInitialFact(cfg));
        }
    }
}

static void doSolveBackward(CFG cfg, SolverResult result, Analysis analysis) {
    Queue/*<Block>*/ workList = new_Queue();
    for (int i = 0; i < numCFGBlocks(cfg); ++i) {
        pushQue(workList, getBlock(cfg, i));
    }
    while (!isEmptyQue(workList)) {
        Block pickedNode = pollQue(workList);
        Fact inFact = getInFact(result, pickedNode->id);
        Fact outFact = isExitBlock(pickedNode) ?
                       copy_Fact(getOutFact(result, pickedNode->id)) :
                       analysis->newInitialFact(cfg);
        List successors = getSuccsOf(cfg, pickedNode->id);
        for (ListNode snode = getHeadNode(successors); snode; snode = snode->next) {
            Block succ = snode->data;
            analysis->meetInto(getInFact(result, succ->id), outFact);
        }
        free_list(successors);
        setOutFact(result, pickedNode->id, outFact);
        bool changed = analysis->transferBlock(cfg, pickedNode, inFact, outFact);
        if (changed) {
            setInFact(result, pickedNode->id, inFact);
            addAllQue(workList, getPredsOf(cfg, pickedNode->id));
        }
        free_Fact(outFact);
    }
    free_Queue(workList);
}

static void initializeForward(CFG cfg, SolverResult result, Analysis analysis) {
    setInFact(result, ENTRY_BID, analysis->newBoundaryFact(cfg));
    setOutFact(result, ENTRY_BID, analysis->newBoundaryFact(cfg));
    for (int i = 0; i < numCFGBlocks(cfg); ++i) {
        Block block = getBlock(cfg, i);
        if (!isEntryBlock(block)) {
            setOutFact(result, block->id, analysis->newInitialFact(cfg));
            setInFact(result, block->id, analysis->newInitialFact(cfg
            ));
        }
    }
}

static void doSolveForward(CFG cfg, SolverResult result, Analysis analysis) {
    Queue/*<Block>*/ workList = new_Queue();
    for (int i = 0; i < numCFGBlocks(cfg); ++i) {
        pushQue(workList, getBlock(cfg, i));
    }
    while (!isEmptyQue(workList)) {
        Block pickedNode = pollQue(workList);
        Fact outFact = getOutFact(result, pickedNode->id);
        Fact inFact = isEntryBlock(pickedNode) ?
                      copy_Fact(getInFact(result, pickedNode->id)) :
                      analysis->newInitialFact(cfg);
        List predecessors = getPredsOf(cfg, pickedNode->id);
        for (ListNode pnode = getHeadNode(predecessors); pnode; pnode = pnode->next) {
            Block pred = pnode->data;
            analysis->meetInto(getOutFact(result, pred->id), inFact);
        }
        free_list(predecessors);
        setInFact(result, pickedNode->id, inFact);
        bool changed = analysis->transferBlock(cfg, pickedNode, inFact, outFact);
        if (changed) {
            setOutFact(result, pickedNode->id, outFact);
            addAllQue(workList, getSuccsOf(cfg, pickedNode->id));
        }
        free_Fact(inFact);
    }
    free_Queue(workList);
}

static void doSolve(AnalysisFlow flow, CFG cfg, SolverResult result, Analysis analysis) {
    if (flow == FLOW_FORWARD) {
        doSolveForward(cfg, result, analysis);
    } else {
        doSolveBackward(cfg, result, analysis);
    }
}





