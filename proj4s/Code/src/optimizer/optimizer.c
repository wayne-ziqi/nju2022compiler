//
// Created by 王紫萁 on 2022/11/27.
//

#include "optimizer.h"
#include "../cfg/cfg_generator.h"
#include "../sa/dataflow/LiveVariable/live_variable.h"
#include "../sa/dataflow/solver/worklistSolver.h"
#include <assert.h>
#include <stdio.h>

Array/*<WLSolver>*/ liveVarSolverArray;

void init_optimizer(unsigned int analysisKind) {
    if ((analysisKind & LiveVariableAnalysis) == LiveVariableAnalysis) {
        liveVarSolverArray = new_Array();
        for (int i = 0; i < sizeArray(CFG_Array); ++i) {
            Analysis analysis = new_Analysis(
                    LIVE_VARIABLE, FLOW_BACKWARD,
                    newInitialFactLV,
                    newBoundaryFactLV,
                    meetIntoLV,
                    transferBlockLV
            );
            WLSolver solver = new_WLSolver(analysis);
            appendArray(liveVarSolverArray, solver);
            solve(solver, getArray(CFG_Array, i));
            printf("Live variable:\n");
            print_result(solver->result, getArray(IRFun_Array, i));
        }
    }
}

SolverResult getSolverResultOf(int fun_id, unsigned int analysisKind) {
    if (analysisKind == LiveVariableAnalysis) {
        assert(fun_id >= 0 && fun_id < sizeArray(liveVarSolverArray));
        WLSolver solver = getArray(liveVarSolverArray, fun_id);
        return solver->result;
    } else {
        assert(0);
    }
}