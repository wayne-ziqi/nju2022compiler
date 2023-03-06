//
// Created by 王紫萁 on 2022/11/27.
//

#ifndef PROJ4_OPTIMIZER_H
#define PROJ4_OPTIMIZER_H

#include "../sa/dataflow/solver/SolverResult.h"

#define LiveVariableAnalysis 0x1

void init_optimizer(unsigned int analysisKind);

SolverResult getSolverResultOf(int fun_id, unsigned int analysisKind);

#endif //PROJ4_OPTIMIZER_H
