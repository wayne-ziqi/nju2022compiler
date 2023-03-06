//
// Created by ziqi on 2022/11/23.
//

#ifndef PROJ4_CFG_H
#define PROJ4_CFG_H

// in our implementation of cfg, each node contains only one statement
#include "../lib/graph.h"
#include "../ir/ir_fundec.h"

#define ENTRY_BID 0
#define EXIT_BID 1

typedef enum CFGEKind_ {
    CFGE_FALL,
    CFGE_GOTO,
    CFGE_TRUE,
    CFGE_FALSE
} CFGEKind;

typedef struct CFG_ *CFG;
typedef struct Block_ *Block;
typedef struct CFGEdge_ *CFGEdge;

struct Block_ {
    unsigned int id;
    Array/*<InterCode>*/ codes;
    void *info; // can be used to store facts
};

struct CFGEdge_ {
    CFGEKind e_kind;
};

// use unsigned to identify every basic block
struct CFG_ {
    char *fun_name;
    int id;
    Graph base_graph;
    Block entry;    // entry has id 0 while exist has 1
    Block exit;
    IRFunDec fun_dec;
};

/**
 * should ensure end > begin and end point to the node following the last code
 * @param id
 * @param code_arr should make sure the array is a fresh new one
 * @param info
 * @return
 */
Block new_Block(unsigned int id, Array code_arr, void *info);

CFG new_CFG(IRFunDec dec);

CFGEdge new_CFGEdge(CFGEKind e_kind);

void addEntryInfo(CFG cfg, void *info);

void addExitInfo(CFG cfg, void *info);

void addBlockInfoWithBid(CFG cfg, unsigned int bid, void *info);

void addBlockInfoWithBLock(CFG cfg, Block block, void *info);

Block getBlock(CFG cfg, unsigned int bid);

Array getAllBlocks(CFG cfg);

bool isEntryBlock(Block block);

bool isExitBlock(Block block);

int numCFGBlocks(CFG cfg);

// remember to free the return list
List/*<Block>*/ getSuccsOf(CFG cfg, unsigned int bid);

// remember to free return list
List/*<Block>*/ getPredsOf(CFG cfg, unsigned int bid);

CFG free_CFG(CFG cfg);

#endif //PROJ4_CFG_H
