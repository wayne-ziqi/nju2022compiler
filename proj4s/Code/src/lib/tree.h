#ifndef __TREE__
#define __TREE__

#include "array.h"

typedef enum valueType {
    /* TERMINAL*/
    TYPE_,
    STRUCT_,
    RETURN_,
    IF_,
    ELSE_,
    WHILE_,
    ID_,
    SEMI_,
    COMMA_,
    RELOP_,
    ASSIGNOP_,
    PLUS_,
    MINUS_,
    STAR_,
    DIV_,
    AND_,
    OR_,
    DOT_,
    NOT_,
    LP_,
    RP_,
    LB_,
    RB_,
    LC_,
    RC_,
    INT_,
    FLOAT_,
    /* NON-TERMINAL*/
    Program_,
    ExtDefList_,
    ExtDef_,
    ExtDecList_,
    Specifier_,
    StructSpecifier_,
    OptTag_,
    Tag_,
    VarDec_,
    FunDec_,
    VarList_,
    ParamDec_,
    CompSt_,
    StmtList_,
    Stmt_,
    DefList_,
    Def_,
    DecList_,
    Dec_,
    Exp_,
    Args_
} ValueType;

typedef struct tree_t {
    int no_line;        // line number of current node
    ValueType value_t;  // value type of the scanned node
    union {
        int v_int;
        float v_float;
        char *v_string;
    } value;
    struct tree_t *father;
    struct tree_t *first_child;
    struct tree_t *next_sibling;
    struct tree_t *prev_sibling;
} TNode;

/**
 * @brief create a new tree node with
 * given node value type and the literal value
 *
 * @param t_value tree node value type (enum ValueType)
 * @param value literal value of current node
 * @return TNode*
 */
TNode *new_tnode(int line_number, ValueType t_value, char *value);

/**
 * @brief free width of current node and his children
 *
 * @param node node to be freed
 */
void free_tnode(TNode *node);

/**
 * @brief add current node into father node list,
 *
 * @param father father node of current node, should not be null
 * @param current current node
 */
void add_child(TNode *father, TNode *current);

/**
 * get direct children of node, remember to free array after using the information
 * @param node
 * @return children of the node recorded in the array, null if node is null or has no child
 */
Array getChildren(TNode *node);

/**
 * print type of node
 * @param node
 */
void print_tnode_type(TNode *node);
/**
 * @brief print the tree led by root  in the format declared in the guide
 *
 * @param root
 * @param level level of the node for recursion, the caller should pass in 0
 */
void show_tree(TNode *root, int level);

#endif  // __TREE__