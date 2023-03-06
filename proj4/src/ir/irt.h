//
// Created by ziqi on 2022/10/28.
//

#ifndef PROJ3_IRT_H
#define PROJ3_IRT_H
// at this stage, we just generalize unoptimized ir
// later we'll traverse this ir list to find a better solution
#include "../lib/list.h"

extern List IRList;

int do_irt(char*filename);

void print_ir();

void store_ir(char *file_path);


#endif //PROJ3_IRT_H
