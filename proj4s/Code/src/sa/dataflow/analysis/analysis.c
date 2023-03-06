//
// Created by 王紫萁 on 2022/11/27.
//

#include "analysis.h"
#include <stdlib.h>
#include <assert.h>

Analysis new_Analysis(
        AnalysisKind kind,
        AnalysisFlow flow,
        Fact (*newInitialFact)(CFG cfg),
        Fact (*newBoundaryFact)(CFG cfg),
        void (*meetInto)(Fact src, Fact dst),
        bool (*transferBlock)(CFG cfg, Block block, Fact in, Fact out)
) {
    Analysis analysis = (Analysis) malloc(sizeof(struct Analysis_));
    analysis->kind = kind;
    analysis->flow = flow;
    analysis->meetInto = meetInto;
    analysis->transferBlock = transferBlock;
    analysis->newInitialFact = newInitialFact;
    analysis->newBoundaryFact = newBoundaryFact;
    return analysis;
}