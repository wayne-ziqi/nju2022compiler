//
// Created by 王紫萁 on 2022/11/26.
//

#include "cfg_drawer.h"
#include "../ir/ir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fd_dot;

static inline void draw_node(Block block) {
    fprintf(fd_dot, "\t\"B%d\" [label=\"B%d\n", block->id, block->id);
    if (block->id == ENTRY_BID)
        fprintf(fd_dot, "ENTRY\"]\n");
    else if (block->id == EXIT_BID)
        fprintf(fd_dot, "Exit\"]\n");
    else {
        for (int i = 0; i < sizeArray(block->codes); ++i) {
            char *code = code_to_string(getArray(block->codes, i));
            if (i != sizeArray(block->codes) - 1) {
                fprintf(fd_dot, "%s \n", code);
            } else {
                fprintf(fd_dot, "%s\"]\n", code);
            }
        }
    }
}

static inline void draw_edge(Block src, Block dst, CFGEKind kind) {
    char *kind_str;
    switch (kind) {
        case CFGE_FALL:
            kind_str = "FALL";
            break;
        case CFGE_GOTO:
            kind_str = "GOTO";
            break;
        case CFGE_TRUE:
            kind_str = "IF_TRUE";
            break;
        case CFGE_FALSE:
            kind_str = "IF_FALSE";
            break;
        default:
            kind_str = "";
    }
    fprintf(fd_dot, "\tB%d -> B%d [label=\"%s\"]\n", src->id, dst->id, kind_str);
}

void draw_cfg(CFG cfg, char *filename) {
    // "filename-FunctionName.dot"
    char *dotname = (char *) malloc(strlen(filename) + strlen(cfg->fun_name) + 12);
    sprintf(dotname, "./CFG/%s-%s.dot", filename, cfg->fun_name);
    fd_dot = fopen(dotname, "w");
    fprintf(fd_dot, "digraph G {\n"
                    "\tnode [shape=box,color=\".3 .2 1.0\",style=filled];\n");
    List gnodeList = getHashAll(cfg->base_graph->vertexMap);
    for (ListNode lnode = getHeadNode(gnodeList); lnode; lnode = lnode->next) {
        GraphNode gnode = lnode->data;
        Block block = gnode->detail;
        draw_node(block);
    }
    for (ListNode lnode = getHeadNode(gnodeList); lnode; lnode = lnode->next) {
        GraphNode gnode = lnode->data;
        Block src = gnode->detail;
        for (ListNode enode = getHeadNode(gnode->edge_to); enode; enode = enode->next) {
            GraphEdge edge = enode->data;
            CFGEdge cfgEdge = edge->detail;
            Block dst = edge->to->detail;
            draw_edge(src, dst, cfgEdge->e_kind);
        }
    }
    free(dotname);
    free(gnodeList);
    fprintf(fd_dot, "}\n");
    fclose(fd_dot);
}