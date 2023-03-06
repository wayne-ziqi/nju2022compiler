#include "ir.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

unsigned int tmp_counter = 0;
unsigned int label_counter = 0;

char *opStr(RelOpKind op);

static inline int len_digit(unsigned int i) {
    if (i >= 1000000000) return 10;
    if (i >= 100000000) return 9;
    if (i >= 10000000) return 8;
    if (i >= 1000000) return 7;
    if (i >= 100000) return 6;
    if (i >= 10000) return 5;
    if (i >= 1000) return 4;
    if (i >= 100) return 3;
    if (i >= 10) return 2;
    return 1;
}

static inline char *operand_to_string(Operand o) {
    switch (o->kind) {
        case OPD_LABEL: {
            unsigned int id = o->i_label;
            int len_id = len_digit(id);
            char *retstr = (char *) malloc((6 + len_id) * sizeof(char));
            sprintf(retstr, "label%u", id);
            return retstr;
        }
        case OPD_FUN: {
            const char *name = o->fun_name;
            char *retstr = (char *) malloc((strlen(name) + 1) * sizeof(char));
            strcpy(retstr, name);
            return retstr;
        }
        case OPD_VAR: {
            const char *name = o->var_name;
            char *retstr = (char *) malloc((strlen(name) + 2 + 1) * sizeof(char));
            sprintf(retstr, "v_%s", name);
            return retstr;
        }
        case OPD_TMP: {
            unsigned int id = o->i_tmp;
            int len_id = len_digit(id);
            char *retstr = (char *) malloc((2 + len_id) * sizeof(char));
            sprintf(retstr, "t%u", id);
            return retstr;
        }
        case OPD_CONST: {
            unsigned int c = o->v_const;
            int len_c = len_digit(c);
            char *retstr = (char *) malloc((2 + len_c) * sizeof(char));
            sprintf(retstr, "#%u", c);
            return retstr;
        }
        case OPD_ADDR: {
            char *name = operand_to_string(o->o_addr);
            char *retstr = (char *) malloc((2 + strlen(name)) * sizeof(char));
            sprintf(retstr, "&%s", name);
            free(name);
            return retstr;
        }
    }
}

static inline char *single_to_string(Operand o, const char *format, unsigned int form_len) {
    char *ostr = operand_to_string(o);
    char *retstr = (char *) malloc((strlen(ostr) + form_len + 1) * sizeof(char));
    sprintf(retstr, format, ostr);
    free(ostr);
    return retstr;
}

static inline char *twin_to_string(Operand o1, Operand o2, const char *format, unsigned int form_len) {
    char *o1str = operand_to_string(o1);
    char *o2str = operand_to_string(o2);
    char *retstr = (char *) malloc((strlen(o1str) + strlen(o2str) + form_len + 1) * sizeof(char));
    sprintf(retstr, format, o1str, o2str);
    free(o1str);
    free(o2str);
    return retstr;
}

static inline char *triple_to_string(Operand o1, Operand o2, Operand o3, const char *format, unsigned int form_len) {
    char *o1str = operand_to_string(o1);
    char *o2str = operand_to_string(o2);
    char *o3str = operand_to_string(o3);
    char *retstr = (char *) malloc((strlen(o1str) + strlen(o2str) + strlen(o3str) + form_len + 1) * sizeof(char));
    sprintf(retstr, format, o1str, o2str, o3str);
    free(o1str);
    free(o2str);
    free(o3str);
    return retstr;
}

char *to_string(InterCode code) {
    switch (code->kind) {
        case CODE_LABEL: {
            Operand o = code->single.o;
            return single_to_string(o, "LABEL %s :", 8);
        }
        case CODE_GOTO: {
            Operand o = code->single.o;
            return single_to_string(o, "GOTO %s", 5);
        }
        case CODE_FUN: {
            Operand o = code->single.o;
            return single_to_string(o, "\nFUNCTION %s :", 12);
        }
        case CODE_RETURN: {
            Operand o = code->single.o;
            return single_to_string(o, "RETURN %s", 7);
        }
        case CODE_ARG: {
            Operand o = code->single.o;
            return single_to_string(o, "ARG %s", 4);
        }
        case CODE_PARAM: {
            Operand o = code->single.o;
            return single_to_string(o, "PARAM %s", 7);
        }
        case CODE_READ: {
            Operand o = code->single.o;
            return single_to_string(o, "READ %s", 5);
        }
        case CODE_WRITE: {
            Operand o = code->single.o;
            return single_to_string(o, "WRITE %s", 6);
        }
        case CODE_ASSIGN: {
            Operand o1 = code->twin.o1;
            Operand o2 = code->twin.o2;
            return twin_to_string(o1, o2, "%s := %s", 4);
        }
        case CODE_GETADDR: {
            Operand o1 = code->twin.o1;
            Operand o2 = code->twin.o2;
            assert(o2->kind != OPD_ADDR);
            return twin_to_string(o1, o2, "%s := &%s", 5);
        }
        case CODE_FETCHADDR: {
            Operand o1 = code->twin.o1;
            Operand o2 = code->twin.o2;
            assert(o2->kind != OPD_ADDR);
            return twin_to_string(o1, o2, "%s := *%s", 5);
        }
        case CODE_STOREADDR: {
            Operand o1 = code->twin.o1;
            Operand o2 = code->twin.o2;
            assert(o1->kind != OPD_ADDR);
            return twin_to_string(o1, o2, "*%s := %s", 5);
        }
        case CODE_CALL: {
            Operand o1 = code->twin.o1;
            Operand o2 = code->twin.o2;
            return twin_to_string(o1, o2, "%s := CALL %s", 9);
        }
        case CODE_DEC: {
            Operand o1 = code->twin.o1;
            Operand o2 = code->twin.o2;
            unsigned int c = o2->v_const;
            int len_c = len_digit(c);
            char *o1str = operand_to_string(o1);
            char *retstr = (char *) malloc((strlen(o1str) + len_c + 6) * sizeof(char));
            sprintf(retstr, "DEC %s %u", o1str, c);
            free(o1str);
            return retstr;
        }
        case CODE_ADD: {
            Operand o1 = code->triple.o1;
            Operand o2 = code->triple.o2;
            Operand o3 = code->triple.o3;
            return triple_to_string(o3, o1, o2, "%s := %s + %s", 7);
        }
        case CODE_SUB: {
            Operand o1 = code->triple.o1;
            Operand o2 = code->triple.o2;
            Operand o3 = code->triple.o3;
            return triple_to_string(o3, o1, o2, "%s := %s - %s", 7);
        }
        case CODE_MUL: {
            Operand o1 = code->triple.o1;
            Operand o2 = code->triple.o2;
            Operand o3 = code->triple.o3;
            return triple_to_string(o3, o1, o2, "%s := %s * %s", 7);
        }
        case CODE_DIV: {
            Operand o1 = code->triple.o1;
            Operand o2 = code->triple.o2;
            Operand o3 = code->triple.o3;
            return triple_to_string(o3, o1, o2, "%s := %s / %s", 7);
        }
        case CODE_IF: {
            Operand cond1 = code->if_code.cond1;
            Operand cond2 = code->if_code.cond2;
            Operand label = code->if_code.to_label;
            char *opstr = opStr(code->if_code.relop);
            char *cond1str = operand_to_string(cond1);
            char *cond2str = operand_to_string(cond2);
            char *labelstr = operand_to_string(label);
            char *retstr = (char *) malloc(
                    (12 + strlen(cond1str) + strlen(opstr) + strlen(cond2str) + strlen(labelstr)));
            sprintf(retstr, "IF %s %s %s GOTO %s", cond1str, opstr, cond2str, labelstr);
            return retstr;
        }
    }
}

Operand new_Operand(OperandKind kind) {
    Operand o = (Operand) malloc(sizeof(struct Operand_));
    o->kind = kind;
    return o;
}

Operand new_Tmp() {
    Operand o = new_Operand(OPD_TMP);
    o->i_tmp = tmp_counter++;
    return o;
}


Operand new_Label() {
    Operand o = new_Operand(OPD_LABEL);
    o->i_label = label_counter++;
    return o;
}

Operand new_OpConst(unsigned int value) {
    Operand o = new_Operand(OPD_CONST);
    o->v_const = value;
    return o;
}

Operand new_OpVar(const char *name) {
    Operand o = new_Operand(OPD_VAR);
    o->var_name = name;
    return o;
}

Operand new_OpFun(const char *name) {
    Operand o = new_Operand(OPD_FUN);
    o->fun_name = name;
    return o;
}

Operand new_OpAddr(Operand o) {
    Operand addr = new_Operand(OPD_ADDR);
    addr->o_addr = o;
    return addr;
}

/*
 * group of code constructors
 */
InterCode new_code(CodeKind kind) {
    InterCode code = (InterCode) malloc(sizeof(struct InterCode_));
    code->kind = kind;
    return code;
}

InterCode genIR_label(Operand label) {
    assert(label && label->kind == OPD_LABEL);
    InterCode code = new_code(CODE_LABEL);
    code->single.o = label;
    return code;
}

InterCode genIR_goto(Operand label) {
    assert(label && label->kind == OPD_LABEL);
    InterCode code = new_code(CODE_GOTO);
    code->single.o = label;
    return code;
}

InterCode genIR_fun(Operand fun) {
    assert(fun && fun->kind == OPD_FUN);
    InterCode code = new_code(CODE_FUN);
    code->single.o = fun;
    return code;
}

InterCode genIR_return(Operand retVal) {
    assert(retVal);
    InterCode code = new_code(CODE_RETURN);
    code->single.o = retVal;
    return code;
}

InterCode genIR_arg(Operand arg) {
    assert(arg);
    InterCode code = new_code(CODE_ARG);
    code->single.o = arg;
    return code;
}

InterCode genIR_param(Operand param) {
    assert(param);
    InterCode code = new_code(CODE_PARAM);
    code->single.o = param;
    return code;
}

InterCode genIR_read(Operand to) {
    assert(to);
    InterCode code = new_code(CODE_READ);
    code->single.o = to;
    return code;
}

InterCode genIR_write(Operand value) {
    assert(value);
    InterCode code = new_code(CODE_WRITE);
    code->single.o = value;
    return code;
}

InterCode genIR_assign(Operand left, Operand right) {
    assert(left && right);
    InterCode code = new_code(CODE_ASSIGN);
    code->twin.o1 = left;
    code->twin.o2 = right;
    return code;
}

InterCode genIR_getAddr(Operand left, Operand right) {
    assert(left && right);
    InterCode code = new_code(CODE_GETADDR);
    code->twin.o1 = left;
    code->twin.o2 = right;
    return code;
}

InterCode genIR_fetchAddr(Operand left, Operand addr) {
    assert(left && addr);
    InterCode code = new_code(CODE_FETCHADDR);
    code->twin.o1 = left;
    code->twin.o2 = addr;
    return code;
}

InterCode genIR_storeAddr(Operand addr, Operand right) {
    assert(right && addr);
    InterCode code = new_code(CODE_STOREADDR);
    code->twin.o1 = addr;
    code->twin.o2 = right;
    return code;
}

InterCode genIR_call(Operand left, Operand call) {
    assert(left && call && call->kind == OPD_FUN);
    InterCode code = new_code(CODE_CALL);
    code->twin.o1 = left;
    code->twin.o2 = call;
    return code;
}

InterCode genIR_Binary(Operand res, Operand o1, Operand o2, CodeKind k_binary) {
    assert(o1 && o2 && res);
    assert(k_binary == CODE_ADD || k_binary == CODE_SUB ||
           k_binary == CODE_MUL || k_binary == CODE_DIV);
    InterCode code = new_code(k_binary);
    code->triple.o1 = o1;
    code->triple.o2 = o2;
    code->triple.o3 = res;
    return code;
}

InterCode genIR_dec(Operand var, Operand memory) {
    assert(var && memory);
    InterCode code = new_code(CODE_DEC);
    code->twin.o1 = var;
    code->twin.o2 = memory;
    return code;
}

InterCode genIR_if(Operand cond_o1, Operand cond_o2, RelOpKind relOp, Operand to_label) {
    assert(cond_o1 && cond_o2 && to_label && to_label->kind == OPD_LABEL);
    InterCode code = new_code(CODE_IF);
    code->if_code.cond1 = cond_o1;
    code->if_code.cond2 = cond_o2;
    code->if_code.relop = relOp;
    code->if_code.to_label = to_label;
    return code;
}

RelOpKind getOp(char *opstr) {
    if (strcmp(opstr, "==") == 0) return REL_EQ;
    else if (strcmp(opstr, "!=") == 0)return REL_NE;
    else if (strcmp(opstr, ">") == 0)return REL_GT;
    else if (strcmp(opstr, ">=") == 0)return REL_GE;
    else if (strcmp(opstr, "<") == 0)return REL_LT;
    else if (strcmp(opstr, "<=") == 0)return REL_LE;
    else
        assert(0);
}

char *opStr(RelOpKind op) {
    if (op == REL_EQ)return "==";
    else if (op == REL_NE) return "!=";
    else if (op == REL_GT) return ">";
    else if (op == REL_GE) return ">=";
    else if (op == REL_LT) return "<";
    else if (op == REL_LE) return "<=";
    else
        assert(0);
}

RelOpKind notOp(RelOpKind op) {
    if (op == REL_EQ)return REL_NE;
    else if (op == REL_NE) return REL_EQ;
    else if (op == REL_GT) return REL_LE;
    else if (op == REL_GE) return REL_LT;
    else if (op == REL_LT) return REL_GE;
    else if (op == REL_LE) return REL_GT;
    else
        assert(0);
}