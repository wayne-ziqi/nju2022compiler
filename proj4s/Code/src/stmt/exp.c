//
// Created by 王紫萁 on 2022/11/2.
//

#include "exp.h"

int evaluate_int(TNode *exp, bool *valid) {
    if (!*valid)return -1;
    TNode *child1 = exp->first_child;
    if (child1->value_t == INT_)
        return child1->value.v_int;
    else if (child1->value_t == FLOAT_ || child1->value_t == ID_) {
        *valid = false;
        return -1;
    }
    if (child1->value_t == LP_)
        return evaluate_int(child1->next_sibling, valid);
    else if (child1->value_t == MINUS_)
        return -evaluate_int(child1->next_sibling, valid);
    else if (child1->value_t == Exp_) {
        TNode *exp1 = child1;
        TNode *op = exp1->next_sibling;
        TNode *exp2 = op->next_sibling;
        if (op->value_t != PLUS_ && op->value_t != MINUS_ &&
            op->value_t != STAR_ && op->value_t != DIV_) {
            *valid = false;
            return -1;
        }
        bool valid1 = true, valid2 = true;
        int value1 = evaluate_int(exp1, &valid1);
        if (!valid1) {
            *valid = false;
            return -1;
        }
        int value2 = evaluate_int(exp2, &valid2);
        if (!valid2) {
            *valid = false;
            return -1;
        }

        if (op->value_t == PLUS_)return value1 + value2;
        if (op->value_t == MINUS_)return value1 - value2;
        if (op->value_t == STAR_)return value1 * value2;
        if (op->value_t == DIV_) {
            if (value2 == 0) {
                *valid = false;
                return -1;
            } else return value1 / value2;
        }
    } else {
        *valid = false;
        return -1;
    }
    return -1;
}