//
// Created by 王紫萁 on 2022/11/23.
//

#include "cfg.h"
#include "../lib/UInt.h"
#include "../ir/ir.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * use cfg construction algorithm, CALL
 * @param cfg empty cfg
 * @param dec function descriptor
 */
static inline void construct_cfg(CFG cfg, IRFunDec dec);

CFG new_CFG(IRFunDec dec) {
    CFG cfg = (CFG) malloc(sizeof(struct CFG_));
    cfg->base_graph = new_Graph(DIRECTED, UINT);
    cfg->fun_name = dec->fun_name;
    cfg->fun_dec = dec;
    construct_cfg(cfg, dec);
    return cfg;
}

CFGEdge new_CFGEdge(CFGEKind e_kind) {
    CFGEdge edge = (CFGEdge) malloc(sizeof(struct CFGEdge_));
    edge->e_kind = e_kind;
    return edge;
}

void addEntryInfo(CFG cfg, void *info) {
    assert(cfg && info);
    assert(cfg->entry->info == NULL);
    cfg->entry->info = info;
}

void addExitInfo(CFG cfg, void *info) {
    assert(cfg && info);
    assert(cfg->exit->info == NULL);
    cfg->exit->info = info;
}

void addBlockInfoWithBid(CFG cfg, unsigned int bid, void *info) {
    assert(cfg && info);
    Block block = getBlock(cfg, bid);
    assert(block);
    block->info = info;
}

void addBlockInfoWithBLock(CFG cfg, Block block, void *info) {
    assert(block && info);
    block->info = info;
}

Block new_Block(unsigned int id, Array code_arr, void *info) {
    Block block = (Block) malloc(sizeof(struct Block_));
    block->id = id;
    block->info = info;
    block->codes = code_arr;
    if (code_arr) {
        for (int i = 0; i < sizeArray(code_arr); ++i) {
            InterCode code = getArray(code_arr, i);
            code->bid = id;
            code->offset = i;
        }
    }
    return block;
}

Block getBlock(CFG cfg, unsigned int bid) {
    UInt key = new_UInt(bid);
    GraphNode node = getGraphNode(cfg->base_graph, key);
    free_UInt(key);
    return node ? node->detail : NULL;
}

Array getAllBlocks(CFG cfg) {
    Array array = new_ArrayOfVol((int) cfg->base_graph->num_node);
    for (int i = 0; i < numCFGBlocks(cfg); ++i) {
        appendArray(array, getBlock(cfg, i));
    }
    return array;
}

bool isEntryBlock(Block block) {
    assert(block);
    return block->id == ENTRY_BID;
}

bool isExitBlock(Block block) {
    assert(block);
    return block->id == EXIT_BID;
}

int numCFGBlocks(CFG cfg) {
    return (int) cfg->base_graph->num_node;
}

List/*<Block>*/getSuccsOf(CFG cfg, unsigned int bid) {
    assert(bid >= 0 && bid < cfg->base_graph->num_node);
    List succ_list = new_list();
    UInt key = new_UInt(bid);
    GraphNode gnode = getGraphNode(cfg->base_graph, key);
    free_UInt(key);
    for (ListNode enode = getHeadNode(gnode->edge_to); enode; enode = enode->next) {
        GraphEdge edge = enode->data;
        if (edge->to->is_visible)
            pushTail(succ_list, newListNode(edge->to->detail));
    }
    return succ_list;
}

List/*<Block>*/ getPredsOf(CFG cfg, unsigned int bid) {
    assert(bid >= 0 && bid < cfg->base_graph->num_node);
    List pre_list = new_list();
    UInt key = new_UInt(bid);
    GraphNode gnode = getGraphNode(cfg->base_graph, key);
    free_UInt(key);
    for (ListNode fnode = getHeadNode(gnode->from_list); fnode; fnode = fnode->next) {
        GraphNode from = fnode->data;
        if (from->is_visible)
            pushTail(pre_list, newListNode(from->detail));
    }
    return pre_list;
}

CFG free_CFG(CFG cfg) {
    assert(0);
}

/// cfg constructor begins

/**
 * code array begin with the first code, i.g. excludes FUNCTION
 * 1. first code is leader
 * 2. every LABEL is leader
 * 3. every CALL is leader
 * 4. code following GOTO is leader
 * @param codeArr
 * @return
 */
static bool *determine_leaders(Array codeArr) {
    unsigned int num_code = codeArr->size;
    bool *leaders = (bool *) malloc(num_code * sizeof(bool));
    memset(leaders, false, num_code);
    leaders[0] = true;
    for (int i = 1; i < num_code; ++i) {
        InterCode code = getArray(codeArr, i);
        InterCode pre = getArray(codeArr, i - 1);
        if (code->kind == CODE_LABEL ||
            (pre->kind != CODE_ARG && code->kind == CODE_CALL) ||
            (pre->kind != CODE_ARG && code->kind == CODE_ARG))
            leaders[i] = true;
        if (pre->kind == CODE_GOTO ||
            pre->kind == CODE_IF ||
            pre->kind == CODE_RETURN ||
            pre->kind == CODE_CALL)
            leaders[i] = true;
    }
    return leaders;
}

/**
 * locate the block using dest label
 * @param block_arr
 * @param dst_label
 * @return block id
 */
static unsigned int locate_block(Array block_arr, Operand dst_label) {
    int i = 2;
    for (; i < sizeArray(block_arr); ++i) {
        Block cur_block = getArray(block_arr, i);
        InterCode leader = getArray(cur_block->codes, 0);
        if (leader->kind == CODE_LABEL) {
            Operand label = leader->single.o;
            assert(label);
            if (label->i_label == dst_label->i_label)
                return i;
        }
    }
    return i;
}

static void addEdgeUtil(CFG cfg, unsigned int src, unsigned int dst, CFGEKind e_kind) {
    UInt src_key = new_UInt(src);
    UInt dst_key = new_UInt(dst);
    addGraphEdge(cfg->base_graph, src_key, dst_key, new_CFGEdge(e_kind));
    free_UInt(src_key);
    free_UInt(dst_key);
}

static void add_blocks(CFG cfg, Array blockArr) {
    // add blocks to graph nodes
    for (int i = 0; i < sizeArray(blockArr); ++i) {
        Block block = getArray(blockArr, i);
        addGraphNode(cfg->base_graph, new_UInt(i), block);
    }
    if (sizeArray(blockArr) == 2) {
        addEdgeUtil(cfg, ENTRY_BID, EXIT_BID, CFGE_FALL);
        return;
    }
    // add edges among blocks;
    // entry to the first valid node
    addEdgeUtil(cfg, ENTRY_BID, 2, CFGE_FALL);
    for (int i = 2; i < sizeArray(blockArr); ++i) {
        Block block = getArray(blockArr, i);
        InterCode last = getArrayTail(block->codes);
        if (last->kind == CODE_GOTO) {
            Operand label = last->single.o;
            assert(label->kind == OPD_LABEL);
            unsigned int dest_block = locate_block(blockArr, label);
            assert(dest_block < sizeArray(blockArr));
            addEdgeUtil(cfg, i, dest_block, CFGE_GOTO);
        } else if (last->kind == CODE_IF) {
            Operand true_label = last->if_code.to_label;
            unsigned int dest_block = locate_block(blockArr, true_label);
            assert(dest_block < sizeArray(blockArr));
            addEdgeUtil(cfg, i, dest_block, CFGE_TRUE);
            unsigned int fall_to = (i + 1 == sizeArray(blockArr)) ? EXIT_BID : i + 1;
            addEdgeUtil(cfg, i, fall_to, CFGE_FALSE);
        } else if (last->kind == CODE_RETURN) {
            addEdgeUtil(cfg, i, EXIT_BID, CFGE_FALL);
        } else {    //other code
            unsigned int fall_to = (i + 1 == sizeArray(blockArr)) ? EXIT_BID : i + 1;
            addEdgeUtil(cfg, i, fall_to, CFGE_FALL);
        }
    }
}

static inline void construct_cfg(CFG cfg, IRFunDec dec) {
    cfg->entry = new_Block(ENTRY_BID, NULL, NULL);
    cfg->exit = new_Block(EXIT_BID, NULL, NULL);
    Array code_arr = new_Array();
    for (ListNode begin = dec->begin->next; begin != dec->end; begin = begin->next) {
        appendArray(code_arr, begin->data);
    }
    unsigned int num_code = code_arr->size;
    bool *leaders = determine_leaders(code_arr);
    // construct blocks
    Array block_arr = new_Array();
    appendArray(block_arr, cfg->entry);
    appendArray(block_arr, cfg->exit);
    int i_leader = 0;
    int i_end = i_leader;
    while (i_end < num_code) {
        if (i_end != i_leader && leaders[i_end]) {
            Array cur_codes = copy_Array(code_arr, i_leader, i_end - 1);
            Block cur_block = new_Block(block_arr->size, cur_codes, NULL);
            appendArray(block_arr, cur_block);
            i_leader = i_end;
        } else {
            ++i_end;
        }
    }
    Array cur_codes = copy_Array(code_arr, i_leader, i_end - 1);
    Block cur_block = new_Block(block_arr->size, cur_codes, NULL);
    appendArray(block_arr, cur_block);

    // add the blocks into cfg
    add_blocks(cfg, block_arr);

    // free memory
    free_Array(code_arr);
    free_Array(block_arr);
}
