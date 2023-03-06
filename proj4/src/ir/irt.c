//
// Created by ziqi on 2022/10/28.
//
#include "ir.h"
#include "irt.h"
#include "ir_fundec.h"
#include "../cfg/cfg_generator.h"
#include "../lib/tree.h"
#include "../semantic/symbol_table.h"
#include "../stmt/exp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

TNode *AST__;
List IRList;

/**
 * entry of translation
 * @param extDefList
 * @return
 */
List irt_ExtDefList(TNode *extDefList);

/**
 * we only focus on Specifier FunDec CompSt
 * @param extDef
 * @return
 */
List irt_ExtDef(TNode *extDef);

/**
 * resolve function definition: FUNCTION f + PARAM a...
 * @param funDec
 * @return
 */
List irt_FunDec(TNode *funDec);

/**
 * translate compst
 * @param compSt
 * @return
 */
List irt_CompSt(TNode *compSt);

/**
 * only focus on VarDec Assign Exp
 * @param defList
 * @return
 */
List irt_DefList(TNode *defList);

/**
 * only focus on VarDec Assign Exp
 * @param decList
 * @return
 */
List irt_DecList(TNode *decList);

/**
 * try to simplify amount of labels using fall code technique, fall == NULL
 * @param condExp
 * @param label_true
 * @param label_false
 * @return
 */
List irt_CondExp(TNode *condExp, Operand label_true, Operand label_false);

/**
 * translate stmt list
 * @param stmtList
 * @return
 */
List irt_StmtList(TNode *stmtList);

/**
 * translate stmt
 * @param stmt
 * @return
 */
List irt_Stmt(TNode *stmt);

/**
 * expression translator
 * @param exp
 * @param place null if the expression is a statement, i,g. x op y / op x
 */
List irt_Exp(TNode *exp, Operand place);

/**
 * when exp can induct to id/ int, there's no need to gen a new temp
 * @param exp
 * @return
 */
Operand exp_simplifier(TNode *exp, List *code, Operand place);

/**
 * get the var descriptor's id
 * @param varDec
 * @return
 */
char *get_VarDecId(TNode *varDec);

/**
 * solve exp -> exp bop exp
 * @param exp1
 * @param exp2
 * @param bop
 * @return
 */
inline List irt_binary_solver(TNode *exp1, TNode *exp2, CodeKind bop, Operand place);

/**
 * resolve calls
 * @param exp
 * @param place
 * @return
 */
List irt_funCall_solver(TNode *exp, Operand place);

/**
 *
 * @param exp
 * @param addr store the resolved address of the field from the exp
 * @return a list of code calculating the x.f address
 */
List irt_struct_solver(TNode *exp, Operand *addr, Type *field_t);

/**
 *
 * @param exp
 * @param addr
 * @return a list of code calculating the base[index] address
 */
List irt_array_solver(TNode *exp, Operand *addr, Type *elem_t);

List irt_Args(TNode *args, List arg_list);

int do_irt(char *filename) {
    if (AST__->first_child == NULL)return 0;
    IRList = irt_ExtDefList(AST__->first_child);
    init_IRFunDecs();
    char *whoami;
    (whoami = strrchr(filename, '/')) ? ++whoami : (whoami = filename);
    genCFGs(whoami);
    return 0;
}

void print_ir() {
    for (ListNode node = getHeadNode(IRList); node; node = node->next) {
        InterCode code = node->data;
        printf("%s\n", code_to_string(code));
        fflush(stdout);
    }
}

void store_ir(char *file_path) {

//    printf("%s", whoami);
    FILE *fp = fopen(file_path, "w");
    if (!fp) {
        printf("open file %s error", file_path);
        return;
    }
    for (ListNode node = getHeadNode(IRList); node; node = node->next) {
        InterCode code = node->data;
        fprintf(fp, "%s\n", code_to_string(code));
    }
    fclose(fp);
}


List irt_ExtDefList(TNode *extDefList) {
    assert(extDefList->value_t == ExtDefList_);
    List code1 = NULL;
    List code2 = NULL;
    for (TNode *child = extDefList->first_child; child; child = child->next_sibling) {
        if (child->value_t == ExtDef_)
            code1 = irt_ExtDef(child);
        else if (child->value_t == ExtDefList_)
            code2 = irt_ExtDefList(child);
    }
    concatList(code1, code2);
    return code1;
}

List irt_ExtDef(TNode *extDef) {
    assert(extDef && extDef->value_t == ExtDef_);
    TNode *child1 = extDef->first_child;    // specifier
    TNode *child2 = child1->next_sibling;
    if (child2->value_t != FunDec_)
        return new_list();
    TNode *child3 = child2->next_sibling;

    assert(child3);
    if (child3->value_t != CompSt_)  // function declaration
        return new_list();

    List code1 = irt_FunDec(child2);
    List code2 = irt_CompSt(child3);
    concatList(code1, code2);
    return code1;
}

List irt_FunDec(TNode *funDec) {
    assert(funDec->value_t == FunDec_);
    List code = new_list();
    char *fun_name = funDec->first_child->value.v_string;
    InterCode fun = genIR_fun(new_OpFun(fun_name));
    pushTail(code, newListNode(fun));
    // prepare parameters
    SymbolInfo func_info = getInfoFlat(fun_name);
    Array params = func_info->funDetail->paramsName;
    for (int i = 0; i < sizeArray(params); ++i) {
        InterCode para = genIR_param(new_OpVar(getArray(params, i)));
        pushTail(code, newListNode(para));
    }
    return code;
}

List irt_CompSt(TNode *compSt) {
    assert(compSt->value_t == CompSt_);
    List code1 = NULL;
    List code2 = NULL;
    for (TNode *child = compSt->first_child; child; child = child->next_sibling) {
        if (child->value_t == DefList_)
            code1 = irt_DefList(child);
        else if (child->value_t == StmtList_)
            code2 = irt_StmtList(child);
    }
    if (code1 == NULL)code1 = new_list();
    concatList(code1, code2);
    return code1;
}

List irt_DefList(TNode *defList) {
    assert(defList->value_t == DefList_);
    List code1 = NULL;
    List code2 = NULL;
    for (TNode *child = defList->first_child; child; child = child->next_sibling) {
        if (child->value_t == Def_) {
            TNode *decList = child->first_child->next_sibling;
            code1 = irt_DecList(decList);
        } else if (child->value_t == DefList_) {
            code2 = irt_DefList(child);
        }
    }
    concatList(code1, code2);
    return code1;
}

List irt_DecList(TNode *decList) {
    assert(decList->value_t == DecList_);
    List code1 = new_list();
    List code2 = NULL;
    for (TNode *child = decList->first_child; child; child = child->next_sibling) {
        if (child->value_t == Dec_) {
            TNode *vardec = child->first_child;
            TNode *assign = vardec->next_sibling;
            char *dec_name = get_VarDecId(vardec);
            SymbolInfo decInfo = getInfoFlat(dec_name);
            Type decType = decInfo->type;
            if (decType->kind == TYPE_STRUCTURE || decType->kind == TYPE_ARRAY) {
                pushTail(code1, newListNode(genIR_dec(new_OpVar(dec_name), new_OpConst(decType->width))));
            }
            if (assign != NULL) {   // VarDec ASSIGNOP Exp
                List codeExp = irt_Exp(assign->next_sibling, new_OpVar(dec_name));
                concatList(code1, codeExp);
            }
        } else if (child->value_t == DecList_)
            code2 = irt_DecList(child);
    }
    concatList(code1, code2);
    return code1;
}

List irt_StmtList(TNode *stmtList) {
    assert(stmtList->value_t == StmtList_);
    List code1 = NULL;
    List code2 = NULL;
    for (TNode *child = stmtList->first_child; child; child = child->next_sibling) {
        if (child->value_t == Stmt_)
            code1 = irt_Stmt(child);
        else if (child->value_t == StmtList_)
            code2 = irt_StmtList(child);
    }
    concatList(code1, code2);
    return code1;
}

List irt_Stmt(TNode *stmt) {
    assert(stmt->value_t == Stmt_);
    TNode *child1 = stmt->first_child;
    if (child1->value_t == CompSt_) {
        // stmt -> compst
        return irt_CompSt(child1);
    } else if (child1->value_t == Exp_) {
        // stmt -> exp semi
        return irt_Exp(child1, NULL);
    } else if (child1->value_t == RETURN_) {
        // stmt -> return exp semi
        List code1;
        Operand t = exp_simplifier(child1->next_sibling, &code1, NULL);
        InterCode code2 = genIR_return(t);
        pushTail(code1, newListNode(code2));
        return code1;
    } else if (child1->value_t == WHILE_) {
        // stmt -> while lp exp rp stmt
        TNode *condExp = child1->next_sibling->next_sibling;
        TNode *stmt_while = condExp->next_sibling->next_sibling;
        Operand begin = new_Label();
        Operand label_true = NULL;  // fall
        Operand label_false = new_Label();
        List code1 = irt_CondExp(condExp, label_true, label_false);
        List code2 = irt_Stmt(stmt_while);
        // label begin || code1 || code2 || goto begin || label false
        pushHead(code1, newListNode(genIR_label(begin)));
        pushTail(code2, newListNode(genIR_goto(begin)));
        pushTail(code2, newListNode(genIR_label(label_false)));
        concatList(code1, code2);
        return code1;
    } else if (child1->value_t == IF_) {
        TNode *condExp = child1->next_sibling->next_sibling;
        assert(condExp->value_t == Exp_);
        TNode *stmt1 = condExp->next_sibling->next_sibling;
        assert(stmt1->value_t == Stmt_);
        if (stmt1->next_sibling == NULL) {
            // stmt -> if lp exp rp stmt
            Operand label_true = NULL;
            Operand label_false = new_Label();
            List code1 = irt_CondExp(condExp, label_true, label_false);
            List code2 = irt_Stmt(stmt1);
            pushTail(code2, newListNode(genIR_label(label_false)));
            concatList(code1, code2);
            return code1;
        } else {
            // stmt -> if lp exp rp stmt else stmt
            TNode *stmt2 = stmt1->next_sibling->next_sibling;
            assert(stmt2->value_t == Stmt_);
            Operand label_true = false;
            Operand label_false = new_Label();
            Operand label_next = new_Label();
            List code1 = irt_CondExp(condExp, label_true, label_false);
            List code2 = irt_Stmt(stmt1);
            List code3 = irt_Stmt(stmt2);
            pushTail(code2, newListNode(genIR_goto(label_next)));
            pushHead(code3, newListNode(genIR_label(label_false)));
            pushTail(code3, newListNode(genIR_label(label_next)));
            concatList(code1, code2);
            concatList(code1, code3);
            return code1;
        }
    } else { assert(false); }
}

List irt_binary_solver(TNode *exp1, TNode *exp2, CodeKind bop, Operand place) {
    List code1;
    List code2;
    Operand t1 = exp_simplifier(exp1, &code1, NULL);
    Operand t2 = exp_simplifier(exp2, &code2, NULL);
    pushTail(code2, newListNode(genIR_Binary(place, t1, t2, bop)));
    concatList(code1, code2);
    return code1;
}

List irt_Args(TNode *args, List arg_list) {
    assert(args->value_t == Args_);
    List code = new_list();
    for (TNode *child = args->first_child; child; child = child->next_sibling) {
        if (child->value_t == Exp_) {
            List code1;
            Operand t = exp_simplifier(child, &code1, NULL);
            if (t->kind == OPD_VAR) {
                SymbolInfo varinfo = getInfoFlat(t->var_name);
                if (varinfo->type->kind != TYPE_BASIC && !varinfo->varDetail->isParam)
                    t = new_OpAddr(t);
            }
            pushHead(arg_list, newListNode(t));
            concatList(code1, code);
            code = code1;
        } else if (child->value_t == Args_) {
            List code1 = irt_Args(child, arg_list);
            concatList(code1, code);
            code = code1;
        }
    }
    return code;
}

List irt_funCall_solver(TNode *exp, Operand place) {
    assert(exp->value_t == Exp_);
    TNode *id = exp->first_child;
    assert(id->value_t == ID_);
    TNode *args = id->next_sibling->next_sibling;
    if (args->value_t == RP_) {
        List code = new_list();
        char *fun_name = id->value.v_string;
        SymbolInfo funInfo = getInfoFlat(fun_name);
        assert(funInfo->kind == SYM_FUNC);
        if (strcmp(funInfo->name, "read") == 0) pushTail(code, newListNode(genIR_read(place)));
        else {
            if (place == NULL)
                place = new_Tmp();
            pushTail(code, newListNode(genIR_call(place, new_OpFun(funInfo->name))));
        }
        return code;
    } else {
        assert(args->value_t == Args_);
        char *fun_name = id->value.v_string;
        SymbolInfo funInfo = getInfoFlat(fun_name);
        assert(funInfo->kind == SYM_FUNC);
        List arg_list = new_list();
        List code = irt_Args(args, arg_list);
        if (strcmp(fun_name, "write") == 0) {
            pushTail(code, newListNode(genIR_write(getHeadNode(arg_list)->data)));
            if (place)
                pushTail(code, newListNode(genIR_assign(place, new_OpConst(0))));
            free_list(arg_list);
            return code;
        } else {
            if (place == NULL)
                place = new_Tmp();
            for (ListNode arg = getHeadNode(arg_list); arg; arg = arg->next) {
                Operand curArg = arg->data;
                pushTail(code, newListNode(genIR_arg(curArg)));
            }
            pushTail(code, newListNode(genIR_call(place, new_OpFun(funInfo->name))));
            free_list(arg_list);
            return code;
        }
    }
}

List irt_struct_solver(TNode *exp, Operand *addr, Type *field_t) {
    // exp -> exp1 dot id
    // exp1 -> id | exp11 dot id12 | exp11 [ exp12 ]
    TNode *exp1 = exp->first_child;
    TNode *id3 = exp1->next_sibling->next_sibling;
    char *field3 = id3->value.v_string;
    TNode *exp11 = exp1->first_child;
    if (exp11->value_t == ID_) {
        // * addr = &base + offset
        SymbolInfo st_info = getInfoFlat(exp11->value.v_string);
        Type struct_t = st_info->type;
        bool isparam = st_info->varDetail->isParam;
        assert(struct_t->kind == TYPE_STRUCTURE);
        unsigned int offset = 0;
        Type target_t = NULL;
        for (ListNode fnode = getHeadNode(struct_t->structure->field_list); fnode; fnode = fnode->next) {
            VarDefNode cur_field = fnode->data;
            if (strcmp(cur_field->name, field3) == 0) {
                target_t = cur_field->type;
                break;
            } else {
                offset += cur_field->type->width;
            }
        }
        assert(target_t);
        *field_t = target_t;    // give the caller the field's type
        *addr = new_Tmp();
        List code = new_list();
        Operand base = isparam ? new_OpVar(st_info->name) : new_OpAddr(new_OpVar(st_info->name));
        if (offset == 0)
            pushTail(code, newListNode(genIR_assign(*addr, base)));
        else
            pushTail(code, newListNode(genIR_Binary(
                    *addr,
                    base,
                    new_OpConst(offset), CODE_ADD))
            );


        return code;
    } else if (exp11->value_t == Exp_) {
        TNode *op = exp11->next_sibling;
        // get the
        Operand base;
        Type base_type;
        List code1;
        if (op->value_t == DOT_)code1 = irt_struct_solver(exp1, &base, &base_type);
        else code1 = irt_array_solver(exp1, &base, &base_type);
        // solve the field offset
        Type cur_type = NULL;
        unsigned int offset = 0;
        assert(base && base_type);
        assert(base_type->kind == TYPE_STRUCTURE);
        for (ListNode fnode = getHeadNode(base_type->structure->field_list); fnode; fnode = fnode->next) {
            VarDefNode cur_field = fnode->data;
            if (strcmp(cur_field->name, field3) == 0) {
                cur_type = cur_field->type;
                break;
            } else {
                offset += cur_field->type->width;
            }
        }
        // generate ir, which means we should dispatch the array
        if (cur_type->kind == TYPE_ARRAY)
            *field_t = cur_type->array->elem_t;
        else
            *field_t = cur_type;
        if (offset == 0)
            *addr = base;   // no need to generate offset calculation code
        else {
            *addr = new_Tmp();
            pushTail(code1, newListNode(genIR_Binary(*addr, base, new_OpConst(offset), CODE_ADD)));
        }
        return code1;

    } else { assert(false); }
}

List irt_array_solver(TNode *exp, Operand *addr, Type *elem_t) {
    // exp -> exp1 [ exp2 ]
    // exp1 could be exp dot exp, so should first solve exp1
    TNode *exp1 = exp->first_child;
    // exp1 could be id, exp dot exp, exp [ exp ]
    TNode *exp2 = exp1->next_sibling->next_sibling;
    assert(exp2->value_t == Exp_);
    TNode *exp11 = exp1->first_child;
    Operand index = NULL;
    List code1 = NULL;
    bool valid = false;
    int i_val = -1;
    if (exp2->first_child->value_t == ID_ && exp2->first_child->next_sibling == NULL) {
        index = new_OpVar(exp2->first_child->value.v_string);
    } else {
        valid = true;
        i_val = evaluate_int(exp2, &valid);
        if (valid) {
            index = new_OpConst(i_val);
        } else {
            index = new_Tmp();
            code1 = irt_Exp(exp2, index);
        }
    }

    if (exp11->value_t == ID_) {
        // tmp_off = t_index * (array_t.elem_t)
        // *addr = t3 = &id + tmp_off
        SymbolInfo arrayInfo = getInfoFlat(exp11->value.v_string);
        bool isparam = arrayInfo->varDetail->isParam;
        Type array_t = arrayInfo->type; // int a[3][4]
        assert(array_t->array->elem_t);
        unsigned int elem_w = array_t->array->elem_t->width;
//        if (array_t->array->elem_t->kind == TYPE_ARRAY) {
//            *elem_t = array_t->array->elem_t->array->elem_t;
//        } else {
        // the next element doesn't exist, so just return the element type
        *elem_t = array_t->array->elem_t;
//        }
        if (code1 == NULL) code1 = new_list();
        if (valid && i_val == 0) {
            // needn't gen offset calculation code
            // just gen base getter
            *addr = new_Tmp();
            // if base is a parameter, the var is already an address, should not get address again
            if (!isparam)
                pushTail(code1, newListNode(genIR_getAddr(*addr, new_OpVar(arrayInfo->name))));
            else
                *addr = new_OpVar(arrayInfo->name);
            return code1;
        } else if (valid) {
            // i_val != 0, just calculate the constant offset
            Operand off = new_OpConst(i_val * elem_w);
            *addr = new_Tmp();
            Operand base = isparam ? new_OpVar(arrayInfo->name) : new_OpAddr(new_OpVar(arrayInfo->name));
            pushTail(code1, newListNode(genIR_Binary(*addr, base, off, CODE_ADD)));
            return code1;
        } else {
            Operand tmp_off = new_Tmp();
            pushTail(code1, newListNode(genIR_Binary(tmp_off, index, new_OpConst(elem_w), CODE_MUL)));
            *addr = new_Tmp();
            // if base is a parameter, the array var is already an address, should not get address again
            Operand base = isparam ? new_OpVar(arrayInfo->name) : new_OpAddr(new_OpVar(arrayInfo->name));
            pushTail(code1,
                     newListNode(genIR_Binary(*addr, base, tmp_off, CODE_ADD)));
            return code1;
        }

    } else if (exp11->value_t == Exp_) {
        TNode *exp12 = exp11->next_sibling;
        if (exp12->value_t == LB_) {    // exp1 -> exp11 [ exp12 ]
            Operand base;
            Type cur_elem;
            List code2 = irt_array_solver(exp1, &base, &cur_elem);
            assert(base && cur_elem);
            if (cur_elem->kind == TYPE_ARRAY) {
                *elem_t = cur_elem->array->elem_t;
            } else {
                *elem_t = cur_elem;
            }
            Operand tmp_off = new_Tmp();
            pushTail(code2, newListNode(genIR_Binary(tmp_off, index, new_OpConst((*elem_t)->width), CODE_MUL)));
            *addr = new_Tmp();
            pushTail(code2, newListNode(genIR_Binary(*addr, base, tmp_off, CODE_ADD)));
            if (code1 == NULL) code1 = new_list();
            concatList(code1, code2);
            return code1;
        } else if (exp12->value_t == DOT_) {   //  struct   // exp[exp].field
            // the base type is structure
            Operand base;
            Type cur_elem;
            List code2 = irt_struct_solver(exp1, &base, &cur_elem);
            assert(base && cur_elem);
            if (cur_elem->kind == TYPE_ARRAY)
                *elem_t = cur_elem->array->elem_t;
            else
                *elem_t = cur_elem; // if cur_elem == array: cur_elem.array.elem
            Operand tmp_off = new_Tmp();
            // tmp_off = tmp_index * elem_w
            pushTail(code2, newListNode(genIR_Binary(
                    tmp_off, index, new_OpConst((*elem_t)->width), CODE_MUL)));
            // *addr = base + tmp_off
            *addr = new_Tmp();
            pushTail(code2, newListNode(genIR_Binary(*addr, base, tmp_off, CODE_ADD)));
            if (code1 == NULL) code1 = new_list();
            concatList(code1, code2);
            return code1;
        } else {
            assert(false);
        }
    } else {
        assert(false);
    }
    assert(false);
}

Operand exp_simplifier(TNode *exp, List *code, Operand place) {
    if (exp->first_child->value_t == ID_ && exp->first_child->next_sibling == NULL) {
        *code = new_list();
        return new_OpVar(exp->first_child->value.v_string);

    } else if (exp->first_child->value_t == INT_) {
        *code = new_list();
        return new_OpConst(exp->first_child->value.v_int);
    } else {
        Operand ret;
        if (place != NULL)ret = place;  // for i = i + 1
        else ret = new_Tmp();
        *code = irt_Exp(exp, ret);
        return ret;
    }
}

List irt_Exp(TNode *exp, Operand place) {
    assert(exp->value_t == Exp_);
    TNode *child1 = exp->first_child;
    if (child1->value_t == INT_) {
        assert(place);
        int value = child1->value.v_int;
        List code = new_list();
        pushTail(code, newListNode(genIR_assign(place, new_OpConst(value))));
        return code;
    } else if (child1->value_t == ID_) {
        TNode *child2 = child1->next_sibling;
        if (child2 == NULL) {
            assert(place);
            SymbolInfo var = getInfoFlat(child1->value.v_string);
            List code = new_list();
            if (var->type->kind == TYPE_BASIC) {
                pushTail(code, newListNode(genIR_assign(place, new_OpVar(var->name))));
            } else { //type array or structure
                pushTail(code, newListNode(genIR_getAddr(place, new_OpVar(var->name))));
            }
            return code;
        } else {
            // ID LP RP, function call
            return irt_funCall_solver(exp, place);
        }
    } else if (child1->value_t == MINUS_) {
        Operand t = new_Tmp();
        List code1 = irt_Exp(child1->next_sibling, t);
        InterCode code2 = genIR_Binary(place, new_OpConst(0), t, CODE_SUB);
        pushTail(code1, newListNode(code2));
        return code1;
    } else if (child1->value_t == LP_) {
        // (E)
        return irt_Exp(child1->next_sibling, place);
    } else if (child1->value_t == Exp_ || child1->value_t == NOT_) {
        TNode *child2 = child1->next_sibling;
        if (child2->value_t == ASSIGNOP_) {
            TNode *id = child1->first_child;
            if (id->value_t == ID_) {
                SymbolInfo var = getInfoFlat(id->value.v_string);
                List code1;
                Operand varopd = new_OpVar(var->name);
                Operand t = exp_simplifier(child2->next_sibling, &code1, varopd);
                // for assignment between array and structures
                if (varopd != t && t->kind == OPD_VAR && var->type->kind != TYPE_BASIC) {
                    SymbolInfo rightInfo = getInfoFlat(t->var_name);
                    if (equalType(var->type, rightInfo->type)) {
                        // from now on the variable will be used as a pointer
                        // i.g. others should not get its address again.
                        var->varDetail->isParam = true;
                        pushTail(code1, newListNode(genIR_getAddr(varopd, t)));
                        if (place)
                            pushTail(code1, newListNode(genIR_assign(place, varopd)));
                        return code1;
                    }
                }
                if (varopd != t)
                    pushTail(code1, newListNode(genIR_assign(varopd, t)));
                if (place)
                    pushTail(code1, newListNode(genIR_assign(place, varopd)));
                return code1;
            } else {
                // should consider struct and array
                // exp lb exp rb
                // exp dot ID
                TNode *expSub = id;
                assert(expSub->value_t == Exp_);
                Operand t = new_Tmp();
                List code1 = irt_Exp(child2->next_sibling, t);
                if (expSub->next_sibling->value_t == LB_) {
                    Operand addr;
                    Type elem_t;
                    List code2 = irt_array_solver(child1, &addr, &elem_t);
                    pushTail(code2, newListNode(genIR_storeAddr(addr, t)));
                    if (place)
                        pushTail(code2, newListNode(genIR_fetchAddr(place, addr)));
                    concatList(code1, code2);
                    return code1;
                } else if (expSub->next_sibling->value_t == DOT_) {
                    Operand addr;
                    Type field_t;
                    List code2 = irt_struct_solver(child1, &addr, &field_t);
                    pushTail(code2, newListNode(genIR_storeAddr(addr, t)));
                    if (place)
                        pushTail(code2, newListNode(genIR_fetchAddr(place, addr)));
                    concatList(code1, code2);
                    return code1;
                } else {
                    assert(false);
                }
            }

        } else if (child2->value_t == PLUS_) {
            return irt_binary_solver(child1, child2->next_sibling, CODE_ADD, place);
        } else if (child2->value_t == MINUS_) {
            return irt_binary_solver(child1, child2->next_sibling, CODE_SUB, place);
        } else if (child2->value_t == STAR_) {
            return irt_binary_solver(child1, child2->next_sibling, CODE_MUL, place);
        } else if (child2->value_t == DIV_) {
            return irt_binary_solver(child1, child2->next_sibling, CODE_DIV, place);
        } else if (child2->value_t == DOT_) { //struct
            Operand addr;
            Type field_t;
            List code1 = irt_struct_solver(exp, &addr, &field_t);
            if (field_t->kind != TYPE_BASIC) {
                if (addr->kind == OPD_VAR)
                    pushTail(code1, newListNode(genIR_getAddr(place, addr)));
                else
                    pushTail(code1, newListNode(genIR_assign(place, addr)));
            } else {
                //appear in the right, get the value in the address and assign to the place
                pushTail(code1, newListNode(genIR_fetchAddr(place, addr)));
            }

            return code1;
        } else if (child2->value_t == LB_) {    //array
            Operand addr;
            Type elem_t;
            List code1 = irt_array_solver(exp, &addr, &elem_t);
            if (elem_t->kind != TYPE_BASIC) {
                if (addr->kind == OPD_VAR)
                    pushTail(code1, newListNode(genIR_getAddr(place, addr)));
                else
                    pushTail(code1, newListNode(genIR_assign(place, addr)));
            } else {
                pushTail(code1, newListNode(genIR_fetchAddr(place, addr)));

            }
            return code1;
        } else {
            // condition exp
            Operand label_true = NULL;
            Operand label_false = new_Label();
            InterCode false_assign = genIR_assign(place, new_OpConst(0));
            List code1 = irt_CondExp(exp, label_true, label_false);
            pushHead(code1, newListNode(false_assign));
            pushTail(code1, newListNode(genIR_assign(place, new_OpConst(1))));
            pushTail(code1, newListNode(genIR_label(label_false)));
            return code1;
        }
    } else {
        // unsupported value type float
        assert(false);
    }
}


List irt_CondExp(TNode *condExp, Operand label_true, Operand label_false) {
    assert(condExp->value_t == Exp_);
    TNode *child1 = condExp->first_child;
    TNode *child2 = child1->next_sibling;
    if (child1->value_t == NOT_)
        return irt_CondExp(child1->next_sibling, label_false, label_true);
    else if (child1->value_t == Exp_ && child2 &&
             (child2->value_t == AND_ || child2->value_t == OR_ || child2->value_t == RELOP_)) {
        TNode *child3 = child2->next_sibling;   // exp2
        assert(child3->value_t == Exp_);
        if (child2->value_t == RELOP_) {
            List code1;
            List code2;
            Operand t1 = exp_simplifier(child1, &code1, NULL);
            Operand t2 = exp_simplifier(child3, &code2, NULL);
            char *opstr = child2->value.v_string;
            RelOpKind op = getOp(opstr);
            List code3 = new_list();
            if (label_true && label_false) {
                pushTail(code3, newListNode(genIR_if(t1, t2, op, label_true)));
                pushTail(code3, newListNode(genIR_goto(label_false)));
            } else if (label_true) {
                pushTail(code3, newListNode(genIR_if(t1, t2, op, label_true)));
            } else if (label_false) {
                // ifFalse
                pushTail(code3, newListNode(genIR_if(t1, t2, notOp(op), label_false)));
            }
            concatList(code1, code2);
            concatList(code1, code3);
            return code1;
        } else if (child2->value_t == OR_) {
            // B1 or B2
            Operand b1_true = label_true ? label_true : new_Label();
            Operand b1_false = NULL;    // fall to B2
            List code1 = irt_CondExp(child1, b1_true, b1_false);
            List code2 = irt_CondExp(child3, label_true, label_false);
            concatList(code1, code2);
            if (label_true == NULL) pushTail(code1, newListNode(genIR_label(b1_true)));
            return code1;
        } else if (child2->value_t == AND_) {
            Operand b1_true = NULL;
            Operand b1_false = label_false ? label_false : new_Label();
            List code1 = irt_CondExp(child1, b1_true, b1_false);
            List code2 = irt_CondExp(child3, label_true, label_false);
            concatList(code1, code2);
            if (label_false == NULL) pushTail(code1, newListNode(genIR_label(b1_false)));
            return code1;
        }
    }
    Operand t = new_Tmp();
    List code1 = irt_Exp(condExp, t);
    List code2 = new_list();
    if (label_true && label_false) {
        pushTail(code2, newListNode(genIR_if(t, new_OpConst(0), REL_NE, label_true)));
        pushTail(code2, newListNode(genIR_goto(label_false)));
    } else if (label_true) {
        pushTail(code2, newListNode(genIR_if(t, new_OpConst(0), REL_NE, label_true)));
    } else if (label_false) {
        pushTail(code2, newListNode(genIR_if(t, new_OpConst(0), REL_EQ, label_false)));
    }
    concatList(code1, code2);
    return code1;
}

char *get_VarDecId(TNode *varDec) {
    assert(varDec->value_t == VarDec_);
    for (TNode *child = varDec->first_child; child != NULL; child = child->next_sibling) {
        if (child->value_t == ID_)
            return child->value.v_string;
        else if (child->value_t == VarDec_)
            return get_VarDecId(child);
    }
    return NULL;
}