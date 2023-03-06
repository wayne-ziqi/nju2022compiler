//
// Created by 王紫萁 on 2022/11/23.
//

#include "graph.h"
#include "UInt.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Graph new_Graph(GraphKind kind, KeyType key_t) {
    Graph graph = (Graph) malloc(sizeof(struct Graph_));
    graph->num_edge = graph->num_node = 0;
    graph->vertexMap = new_hashmap(key_t, DEFAULT_SLOT_SIZE);
    graph->graph_k = kind;
    return graph;
}

void free_Graph(Graph graph) {
    assert(graph);
    List datalist = getHashAll(graph->vertexMap);
    for (ListNode node = getHeadNode(datalist); node; node = node->next) {
        GraphNode curnode = node->data;
        free_GraphNode(curnode);
    }
    free_list(datalist);
    free(graph);
}

GraphNode new_GraphNode(void *key, void *detail) {
    assert(key && detail);
    GraphNode node = (GraphNode) malloc(sizeof(struct GraphNode_));
    node->key = key;
    node->detail = detail;
    node->is_visible = true;
    node->edge_to = new_list();
    node->from_list = new_list();
    return node;
}

void free_GraphNode(GraphNode node) {
    for (ListNode lnode = getHeadNode(node->edge_to); lnode; lnode = lnode->next) {
        GraphEdge edge = lnode->data;
        free_GraphEdge(edge);
    }
    free_list(node->from_list);
    free_list(node->edge_to);
}

GraphEdge new_GraphEdge(GraphNode from, GraphNode to, void *detail) {
    assert(from && to);
    GraphEdge edge = (GraphEdge) malloc(sizeof(struct GraphEdge_));
    edge->from = from, edge->to = to;
    edge->detail = detail;
    edge->edgeCnt = 1;
    return edge;
}

void free_GraphEdge(GraphEdge edge) {
    assert(edge);
    assert(edge->from);
    assert(edge->to);
    // should remove 'from' from to's from_list
    free(edge);
}

void addGraphEdge(Graph graph, void *from, void *to, void *detail) {
    assert(graph && from && to);
    GraphNode v_from = getGraphNode(graph, from);
    GraphNode v_to = getGraphNode(graph, to);
    assert(v_from), assert(v_to);
    graph->num_edge++;
    for (ListNode node_edge = getHeadNode(v_from->edge_to); node_edge; node_edge = node_edge->next) {
        GraphEdge edge = node_edge->data;
        if (v_to == edge->to) {
            edge->edgeCnt++;
            return;
        }
    }
    pushTail(v_to->from_list, newListNode(v_from));
    GraphEdge edge = new_GraphEdge(v_from, v_to, detail);
    pushTail(v_from->edge_to, newListNode(edge));
}

static bool equal_name(char *name, GraphNode node) {
    return strcmp(name, (char *) node->key) == 0;
}

static bool equal_id(UInt id, GraphNode node) {
    return equal_uint(id, (UInt) node->key);
}

GraphNode getGraphNode(Graph graph, void *key) {
    return getFirstOf(graph->vertexMap, key, key,
                      graph->vertexMap->key_t == STRING ?
                      (bool (*)(void *, void *)) equal_name :
                      (bool (*)(void *, void *)) equal_id
    );
}

void addGraphNode(Graph graph, void *key, void *detail) {
    assert(graph && key && detail);
    GraphNode exist_node = getGraphNode(graph, key);
    if (exist_node)assert(0);
    graph->num_node++;
    addHead(graph->vertexMap, key, new_GraphNode(key, detail));
}