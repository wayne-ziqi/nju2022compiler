//
// Created by 王紫萁 on 2022/11/23.
//

#ifndef PROJ4_GRAPH_H
#define PROJ4_GRAPH_H

// graph has type of <key, data>
#include "list.h"
#include "hashMap.h"

typedef struct Graph_ *Graph;
typedef struct GraphNode_ *GraphNode;
typedef struct GraphEdge_ *GraphEdge;

typedef enum GraphKind_ {
    DIRECTED,
    UNDIRECTED
} GraphKind;

struct GraphNode_ {
    void *key;
    void *detail;
    bool is_visible;
    List from_list;
    List edge_to;
};

struct GraphEdge_ {
    GraphNode from;
    GraphNode to;
    unsigned int edgeCnt;
    void *detail;
};

struct Graph_ {
    unsigned int num_node;
    unsigned int num_edge;
    GraphKind graph_k;
    HashMap vertexMap;
};

/**
 * create a new graph
 * @param kind directed or undirected graph
 * @return new graph
 */
Graph new_Graph(GraphKind kind, KeyType key_t);

void free_Graph(Graph graph);

/**
 * create a new graph node with key
 * @param key
 * @return
 */
GraphNode new_GraphNode(void *key, void *detail);

void free_GraphNode(GraphNode node);

/**
 * create a new edge with from-to information
 */
GraphEdge new_GraphEdge(GraphNode from, GraphNode to, void *detail);

void free_GraphEdge(GraphEdge edge);

/**
 * add the edge to the graph
 */
void addGraphEdge(Graph graph, void *from, void *to, void *detail);

/**
 * add a new graph node with data
 */
void addGraphNode(Graph graph, void *key, void *detail);

/**
 * get the graph node with key
 * @param graph
 * @param key
 * @return
 */
GraphNode getGraphNode(Graph graph, void *key);

#endif //PROJ4_GRAPH_H
