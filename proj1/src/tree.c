#include "tree.h"

#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int proc_int_value(char *);

TNode *new_tnode(int line_number, ValueType t_value, char *value) {
    TNode *node = (TNode *)malloc(sizeof(TNode));
    if (node == NULL) {
        /* code */
        fprintf(stderr, "memory allocation failed\n");
        return NULL;
    }
    node->no_line = line_number;
    node->value_t = t_value;
    if (value != NULL) {
        if (t_value == _INT) {
            node->value.v_int = proc_int_value(value);
        } else if (t_value == _FLOAT) {
            node->value.v_float = (float)atof(value);
        } else {
            // _ID and _TYPE
            node->value.v_string = (char *)malloc(strlen(value) * sizeof(char));
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
    if ((node->value_t == _TYPE || node->value_t == _ID) && node->value.v_string != NULL) {
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

void print_info(TNode *node);
void show_tree(TNode *root, int level) {
    if (root == NULL) {
        return;
    }

    int cntTab = level;
    while (cntTab > 0) {
        printf("  ");
        cntTab--;
    }

    print_info(root);
    show_tree(root->first_child, level + 1);
    show_tree(root->next_sibling, level);
}

void print_info(TNode *node) {
    switch (node->value_t) {
        case _TYPE:
            printf("TYPE: %s\n", node->value.v_string);
            break;
        case _STRUCT:
            printf("STRUCT\n");
            break;
        case _RETURN:
            printf("RETURN\n");
            break;
        case _IF:
            printf("IF\n");
            break;
        case _ELSE:
            printf("ELSE\n");
            break;
        case _WHILE:
            printf("WHILE\n");
            break;
        case _ID:
            printf("ID: %s\n", node->value.v_string);
            break;
        case _SEMI:
            printf("SEMI\n");
            break;
        case _COMMA:
            printf("COMMA\n");
            break;
        case _RELOP:
            printf("RELOP\n");
            break;
        case _ASSIGNOP:
            printf("ASSIGNOP\n");
            break;
        case _PLUS:
            printf("PLUS\n");
            break;
        case _MINUS:
            printf("MINUS\n");
            break;
        case _STAR:
            printf("STAR\n");
            break;
        case _DIV:
            printf("DIV\n");
            break;
        case _AND:
            printf("AND\n");
            break;
        case _OR:
            printf("OR\n");
            break;
        case _DOT:
            printf("DOT\n");
            break;
        case _NOT:
            printf("NOT\n");
            break;
        case _LP:
            printf("LP\n");
            break;
        case _RP:
            printf("RP\n");
            break;
        case _LB:
            printf("LB\n");
            break;
        case _RB:
            printf("RB\n");
            break;
        case _LC:
            printf("LC\n");
            break;
        case _RC:
            printf("RC\n");
            break;
        case _INT:
            printf("INT: %d\n", node->value.v_int);
            break;
        case _FLOAT:
            printf("FLOAT: %f\n", node->value.v_float);
            break;

        /*non-terminals*/
        case _Program:
            printf("Program (%d)\n", node->no_line);
            break;
        case _ExtDefList:
            printf("ExtDefList (%d)\n", node->no_line);
            break;
        case _ExtDef:
            printf("ExtDef (%d)\n", node->no_line);
            break;
        case _ExtDecList:
            printf("ExtDecList (%d)\n", node->no_line);
            break;
        case _Specifier:
            printf("Specifier (%d)\n", node->no_line);
            break;
        case _StructSpecifier:
            printf("StructSpecifier (%d)\n", node->no_line);
            break;
        case _OptTag:
            printf("OptTag (%d)\n", node->no_line);
            break;
        case _Tag:
            printf("Tag (%d)\n", node->no_line);
            break;
        case _VarDec:
            printf("VarDec (%d)\n", node->no_line);
            break;
        case _FunDec:
            printf("FunDec (%d)\n", node->no_line);
            break;
        case _VarList:
            printf("VarList (%d)\n", node->no_line);
            break;
        case _ParamDec:
            printf("ParamDec (%d)\n", node->no_line);
            break;
        case _CompSt:
            printf("CompSt (%d)\n", node->no_line);
            break;
        case _StmtList:
            printf("StmtList (%d)\n", node->no_line);
            break;
        case _Stmt:
            printf("Stmt (%d)\n", node->no_line);
            break;
        case _DefList:
            printf("DefList (%d)\n", node->no_line);
            break;
        case _Def:
            printf("Def (%d)\n", node->no_line);
            break;
        case _DecList:
            printf("DecList (%d)\n", node->no_line);
            break;
        case _Dec:
            printf("Dec (%d)\n", node->no_line);
            break;
        case _Exp:
            printf("Exp (%d)\n", node->no_line);
            break;
        case _Args:
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
    int len = strlen(str);
    if (str == NULL || len == 0) {
        return 0;
    }
    char *endptr = NULL;
    if (len >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        return (int)strtol(str, &endptr, 16);
    else if (len >= 2 && str[0] == '0')
        return (int)strtol(str, &endptr, 8);

    return (int)strtol(str, &endptr, 10);
}
