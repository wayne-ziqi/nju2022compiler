//
// Created by 王紫萁 on 2022/11/26.
//

#include "cfg_generator.h"
#include "cfg.h"
#include "cfg_drawer.h"

void genCFGs(char *filename) {
    int num_fun = sizeArray(IRFun_Array);
    CFG_Array = new_ArrayOfVol(num_fun);
    for (int i = 0; i < num_fun; ++i) {
        IRFunDec dec = getArray(IRFun_Array, i);
        CFG cfg = new_CFG(dec);
//        draw_cfg(cfg, filename);
        appendArray(CFG_Array, cfg);
    }
}