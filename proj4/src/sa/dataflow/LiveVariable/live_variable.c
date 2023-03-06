//
// Created by 王紫萁 on 2022/11/23.
//
#include "live_variable.h"
#include "../../../ir/ir_varTable.h"
#include "../../../ir/ir.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static int getVarId(Operand def, char *fun_name) {
    char *def_name = operand_to_string(def);
    VarInfo def_info = getVarInfo(def_name, fun_name);
    assert(def_info);
    free(def_name);
    return def_info->var_id;
}

Fact newBoundaryFactLV(CFG cfg) {
    return new_Fact(sizeArray(cfg->fun_dec->frame->varname_arr));
}

Fact newInitialFactLV(CFG cfg) {
    return new_Fact(sizeArray(cfg->fun_dec->frame->varname_arr));
}

void meetIntoLV(Fact src, Fact dst) {
    unionFact(src, dst);
}

bool transferBlockLV(CFG cfg, Block block, Fact in, Fact out) {
    Fact oldIn = copy_Fact(in);
    setFact(in, out);

    // for assign statement x = y, we consider y is live when x is live
    if (block->codes)
        for (int i = sizeArray(block->codes) - 1; i >= 0; --i) {
            InterCode code = getArray(block->codes, i);
            /// kill defined
            Operand def = getDefOf(code);
            if (def) {
                int def_id = getVarId(def, cfg->fun_name);
                setFactIn(in, def_id, false);
            }
            /// gen used
            if (code->kind == CODE_ASSIGN) {
                Operand x = code->twin.o1;
                Operand y = code->twin.o2;
                if (y->kind == OPD_VAR || y->kind == OPD_TMP) {
                    int id_x = getVarId(x, cfg->fun_name);
                    int id_y = getVarId(y, cfg->fun_name);
                    if (getFactIn(out, id_x))
                        setFactIn(in, id_y, true);
                }
            } else {
                Array uses = getUseOf(code);
                for (int j = 0; j < sizeArray(uses); ++j) {
                    Operand use = getArray(uses, j);
                    int id_use = getVarId(use, cfg->fun_name);
                    setFactIn(in, id_use, true);
                }
                free_Array(uses);
            }
        }

    bool equal = equalsFact(in, oldIn);
    free_Fact(oldIn);
    return !equal;
}

