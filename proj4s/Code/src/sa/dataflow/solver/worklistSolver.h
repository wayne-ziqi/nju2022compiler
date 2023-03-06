//
// Created by 王紫萁 on 2022/11/27.
//

#ifndef PROJ4_WORKLISTSOLVER_H
#define PROJ4_WORKLISTSOLVER_H

#include "../analysis/analysis.h"
#include "SolverResult.h"

typedef struct WLSolver_ *WLSolver;
struct WLSolver_ {
    Analysis analysis;
    SolverResult result;
};

WLSolver new_WLSolver(Analysis analysis);

void solve(WLSolver solver, CFG cfg);

#endif //PROJ4_WORKLISTSOLVER_H
