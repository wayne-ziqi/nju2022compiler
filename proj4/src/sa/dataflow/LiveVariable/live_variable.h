//
// Created by 王紫萁 on 2022/11/27.
//

#ifndef PROJ4_LIVE_VARIABLE_H
#define PROJ4_LIVE_VARIABLE_H

#include "../fact/fact.h"
#include "../../../cfg/cfg.h"

Fact newBoundaryFactLV(CFG cfg);

Fact newInitialFactLV(CFG cfg);

void meetIntoLV(Fact src, Fact dst);

bool transferBlockLV(CFG cfg, Block block, Fact in, Fact out);


#endif //PROJ4_LIVE_VARIABLE_H
