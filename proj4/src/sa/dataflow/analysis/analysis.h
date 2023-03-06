//
// Created by 王紫萁 on 2022/11/27.
//

#ifndef PROJ4_ANALYSIS_H
#define PROJ4_ANALYSIS_H

#include "../../../cfg/cfg.h"
#include "../fact/fact.h"

typedef enum AnalysisKind_ {
    LIVE_VARIABLE,
} AnalysisKind;

typedef enum AnalysisFlow_ {
    FLOW_FORWARD,
    FLOW_BACKWARD
} AnalysisFlow;

typedef struct Analysis_ *Analysis;

struct Analysis_ {
    AnalysisKind kind;

    AnalysisFlow flow;

    Fact (*newInitialFact)(CFG cfg);

    Fact (*newBoundaryFact)(CFG cfg);

    // meet function
    void (*meetInto)(Fact src, Fact dst);

    // transfer node function
    bool (*transferBlock)(CFG cfg, Block block, Fact in, Fact out);

    //transfer edge function (TBD)

};

Analysis new_Analysis(
        AnalysisKind kind,
        AnalysisFlow flow,
        Fact (*newInitialFact)(CFG cfg),
        Fact (*newBoundaryFact)(CFG cfg),
        void (*meetInto)(Fact src, Fact dst),
        bool (*transferBlock)(CFG cfg, Block block, Fact in, Fact out)
);


#endif //PROJ4_ANALYSIS_H
