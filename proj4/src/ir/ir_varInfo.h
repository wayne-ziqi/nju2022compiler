//
// Created by 王紫萁 on 2022/11/27.
//

#ifndef PROJ4_IR_VARINFO_H
#define PROJ4_IR_VARINFO_H

#include <stdbool.h>


#define NUM_VAR_POS 2   // in reg
#define POS_REG 0
#define POS_MEM 1
#define EMPTY_POS -1
#define MEM_ID -2

typedef struct VarInfo_ *VarInfo;

typedef enum IRVarKind_ {
    IRVAR_PARA,
    IRVAR_VAR,
    IRVAR_TMP
} IRVarKind;

struct VarInfo_ {
    char *var_name;
    char *fun_name;
    int var_id;
    int offset;
    unsigned int width;
    IRVarKind varKind;
    int var_pos[NUM_VAR_POS];   // could only exist in mem or reg
};


VarInfo new_VarInfo(char *var_name, char *fun_name, int var_id,  IRVarKind varKind, int offset, unsigned int width);

void free_VarInfo(VarInfo info);

int getVarOffset(VarInfo info);

int getVarPosID(VarInfo info, int POS);

/**
 * update variable existence state in POS reg or mem
 * if in reg pos id should be reg id, else in MEM_ID
 * @param info
 * @param POS
 * @param pos_id
 */
void updateVarPositionIn(VarInfo info, int POS, int pos_id);



#endif //PROJ4_IR_VARINFO_H
