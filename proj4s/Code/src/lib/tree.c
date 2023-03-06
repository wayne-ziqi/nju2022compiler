#include "tree.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int proc_int_value(char *);

TNode *new_tnode(int line_number, ValueType t_value, char *value) {
    TNode *node = (TNode *) malloc(sizeof(TNode));
    if (node == NULL) {
        /* code */
        fprintf(stderr, "width allocation failed\n");
        return NULL;
    }
    node->no_line = line_number;
    node->value_t = t_value;
    if (value != NULL) {
        if (t_value == INT_) {
            node->value.v_int = proc_int_value(value);
        } else if (t_value == FLOAT_) {
            node->value.v_float = (float) atof(value);
        } else {
            // _ID, _TYPE, RELOP_
            node->value.v_string = (char *) malloc(strlen(value) * sizeof(char));
            strcpy(node->value.v_string, value);
        }
    } else {
        // non-terminals
        node->value.v_string = NULL;
    }
    node->father = NULL;
    node->first_child = NULL;
    node->next_sibling = NULL;
    node->prev_sibling = NULL;
    return node;
}

void free_tnode(TNode *node) {
    if (node == NULL) {
        return;
    }
    TNode *next = node->next_sibling;
    if (node->prev_sibling != NULL) {
        node->prev_sibling->next_sibling = next;
        if (next != NULL) {
            next->prev_sibling = node->prev_sibling;
        }
    } else {
        // node is the first sibling of its father
        // should link node.next to its first child
        if (node->father != NULL) {
            node->father->first_child = next;
            // next become the first child
            if (next != NULL) {
                next->prev_sibling = NULL;
            }
        }
    }

    // free the tree recursively
    TNode *child = node->first_child;
    if ((node->value_t == TYPE_ || node->value_t == ID_) && node->value.v_string != NULL) {
        free(node->value.v_string);
    }
    free(node);
    free_tnode(child);
}

void add_child(TNode *father, TNode *current) {
    if (father == NULL) {
        fprintf(stderr, "father should not be NULL in add_child()\n");
        return;
    } else if (current == NULL) {
        return;
    }
    current->father = father;
    TNode *last_child = father->first_child;
    // find last child of father and link current to it
    if (last_child == NULL) {
        // father has no child
        father->first_child = current;
        current->prev_sibling = NULL;
        current->next_sibling = NULL;
    } else {
        while (last_child->next_sibling != NULL) {
            last_child = last_child->next_sibling;
        }
        last_child->next_sibling = current;
        current->prev_sibling = last_child;
        current->next_sibling = NULL;
    }
}

Array getChildren(TNode *node) {
    if (!node || !node->first_child)return NULL;
    Array array = new_Array();
    for (TNode *child = node->first_child; child != NULL; child = child->next_sibling) {
        appendArray(array, child);
    }
    return array;
}


void show_tree(TNode *root, int level) {
    if (root == NULL) {
        return;
    }

    int cntTab = level;
    while (cntTab > 0) {
        printf("  ");
        cntTab--;
    }

    print_tnode_type(root);
    show_tree(root->first_child, level + 1);
    show_tree(root->next_sibling, level);
}

void print_tnode_type(TNode *node) {
    switch (node->value_t) {
        case TYPE_:
            printf("TYPE: %s\n", node->value.v_string);
            break;
        case STRUCT_:
            printf("STRUCT\n");
            break;
        case RETURN_:
            printf("RETURN\n");
            break;
        case IF_:
            printf("IF\n");
            break;
        case ELSE_:
            printf("ELSE\n");
            break;
        case WHILE_:
            printf("WHILE\n");
            break;
        case ID_:
            printf("ID: %s\n", node->value.v_string);
            break;
        case SEMI_:
            printf("SEMI\n");
            break;
        case COMMA_:
            printf("COMMA\n");
            break;
        case RELOP_:
            printf("RELOP\n");
            break;
        case ASSIGNOP_:
            printf("ASSIGNOP\n");
            break;
        case PLUS_:
            printf("PLUS\n");
            break;
        case MINUS_:
            printf("MINUS\n");
            break;
        case STAR_:
            printf("STAR\n");
            break;
        case DIV_:
            printf("DIV\n");
            break;
        case AND_:
            printf("AND\n");
            break;
        case OR_:
            printf("OR\n");
            break;
        case DOT_:
            printf("DOT\n");
            break;
        case NOT_:
            printf("NOT\n");
            break;
        case LP_:
            printf("LP\n");
            break;
        case RP_:
            printf("RP\n");
            break;
        case LB_:
            printf("LB\n");
            break;
        case RB_:
            printf("RB\n");
            break;
        case LC_:
            printf("LC\n");
            break;
        case RC_:
            printf("RC\n");
            break;
        case INT_:
            printf("INT: %d\n", node->value.v_int);
            break;
        case FLOAT_:
            printf("FLOAT: %f\n", node->value.v_float);
            break;

            /*non-terminals*/
        case Program_:
            printf("Program (%d)\n", node->no_line);
            break;
        case ExtDefList_:
            printf("ExtDefList (%d)\n", node->no_line);
            break;
        case ExtDef_:
            printf("ExtDef (%d)\n", node->no_line);
            break;
        case ExtDecList_:
            printf("ExtDecList (%d)\n", node->no_line);
            break;
        case Specifier_:
            printf("Specifier (%d)\n", node->no_line);
            break;
        case StructSpecifier_:
            printf("StructSpecifier (%d)\n", node->no_line);
            break;
        case OptTag_:
            printf("OptTag (%d)\n", node->no_line);
            break;
        case Tag_:
            printf("Tag (%d)\n", node->no_line);
            break;
        case VarDec_:
            printf("VarDec (%d)\n", node->no_line);
            break;
        case FunDec_:
            printf("FunDec (%d)\n", node->no_line);
            break;
        case VarList_:
            printf("VarList (%d)\n", node->no_line);
            break;
        case ParamDec_:
            printf("ParamDec (%d)\n", node->no_line);
            break;
        case CompSt_:
            printf("CompSt (%d)\n", node->no_line);
            break;
        case StmtList_:
            printf("StmtList (%d)\n", node->no_line);
            break;
        case Stmt_:
            printf("Stmt (%d)\n", node->no_line);
            break;
        case DefList_:
            printf("DefList (%d)\n", node->no_line);
            break;
        case Def_:
            printf("Def (%d)\n", node->no_line);
            break;
        case DecList_:
            printf("DecList (%d)\n", node->no_line);
            break;
        case Dec_:
            printf("Dec (%d)\n", node->no_line);
            break;
        case Exp_:
            printf("Exp (%d)\n", node->no_line);
            break;
        case Args_:
            printf("Args (%d)\n", node->no_line);
            break;
        default:
            printf(" undeclared type %s\n", node->value.v_string);
            break;
    }
}

/**
 * @brief caculate real value with literal value in dec, hex or oct
 *
 * @param str
 * @return int dec type of int
 */
int proc_int_value(char *str) {
    int len = (int) strlen(str);
    if (str == NULL || len == 0) {
        return 0;
    }
    char *endptr = NULL;
    if (len >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        return (int) strtol(str, &endptr, 16);
    else if (len >= 2 && str[0] == '0')
        return (int) strtol(str, &endptr, 8);

    return (int) strtol(str, &endptr, 10);
}
