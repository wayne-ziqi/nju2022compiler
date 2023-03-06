#include "../dataset.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

/**
 * throw all 17 kinds of errors with error kind id
 * @param error_code error kind id
 * @param line_no error line number
 * @param note additional notes
 */
static inline void throw_semantic_error(int error_code, int line_no, const char *note1, const char *note2);

/**
 * @param extDecList
 * @param inhType inherit type from specifier
 */
void resolve_ExtDecList(TNode *extDecList, Type inhType);

/**
 * resolve definition list
 * @param defListNode
 * @param defs optional list to store resolved variables for struct field, if null, means the caller wants it to add the vars to the table
 */
void resolve_DefList(TNode *defListNode, List defs);

/**
 * resolve struct declaration, like 'struct Temp1{...};' or 'struct Temp1 temp1'
 * @param specifier could has child that is StructSpecifier or TYPE, ignore Type
 * @return if it is a declaration and hasn't been declared
 */
Type resolve_Specifier(TNode *specifier);

/**
 * resolve variables
 * @param varDec
 * @param inhType
 * @param varName caller should provide a pointer of string for the method to save the name
 * @return true type of id which could be a complex array
 */
Type resolve_VarDec(TNode *varDec, Type inhType, char **varName);

/**
 * resolve functions
 * @param funDec
 * @param inhType
 * @param comp could be SEMI which means a function declaration
 */
void resolve_FunDec(TNode *funDec, Type inhType, TNode *comp);

/**
 * resolve comp statement, new scopes are allocated here, however,
 * @param compSt
 * @param funcRetType whether follows a funDec, if so give it the return type else NULL, the function will not allocate a new scope list
 * as the new scope has been allocate in the funDec
 */
void resolve_CompSt(TNode *compSt, Type funcRetType, bool fromInvoke);

/**
 * resolve variable list of function parameters
 * @param varList
 * @param vars
 */
void resolve_VarList(TNode *varList, List vars, const char *funcName);

/**
 * entry to analyse
 * @param node
 */
void resolve_ExtDefList(TNode *node);

/**
 * resolve decList for Def node
 * @param decList
 * @param inhType
 * @param defs store the [VarDefNode] in the defs and let the caller decides whether to add the variables to the symbol list
 * if defs is null, then the caller wants to add them to the table, else it wants the result and doesn't want to add to the table
 */
void resolve_DecList(TNode *decList, Type inhType, List defs);

/**
 * resolve statement list
 * @param stmtList
 * @param callers function's return type for return statement to check return type mismatch
 */
void resolve_StmtList(TNode *stmtList, Type funcRetType);

/**
 * resolve expressions
 * @param exp
 * @return Type of the exp
 */
Type resolve_Exp(TNode *exp);

/**
 *
 * @param args
 * @param argTypeList store the arguments' type
 */
void resolve_Args(TNode *args, List argTypeList);

/**
 * do some finish job at the end of the program, e.g. undefined functions
 */
void final_check();

int do_sdt() {
//    show_tree(AST__, 0);
    initSymbolSystem();
    // start constructing symbol table and do semantic analysis
    resolve_ExtDefList(AST__);
    return 0;
}


void resolve_DefList(TNode *defListNode, List defs) {
    for (TNode *child = defListNode->first_child;
         child != NULL; child = child->next_sibling) {
        if (child->value_t == DefList_)
            resolve_DefList(child, defs);
        else if (child->value_t == Def_) {
            Array defChildren = getChildren(child);
            // Specifier DecList SEMI
            assert(sizeArray(defChildren) == 3);
            Type specType = resolve_Specifier(getArray(defChildren, 0));
            if (specType != NULL)
                resolve_DecList(getArray(defChildren, 1), specType, defs);
        } else {
            assert(false);
        }
    }
}

void resolve_ExtDefList(TNode *node) {
    assert(node);
    Array children = getChildren(node);
    if (children == NULL) return;
    unsigned int num_child = sizeArray(children);
//    printf("picked node type: ");
//    print_tnode_type(node);
//    printf("children number: %d\n", num_child);
    fflush(stdout);
    //for variables that don't have children, aka terminals are not supposed to be in the worklist

    switch (node->value_t) {
        case Program_:
        case ExtDefList_: {
            for (TNode *child = node->first_child; child != NULL; child = child->next_sibling) {
                resolve_ExtDefList(child);
            }
            break;
        }
        case ExtDef_: {
            TNode *specifier = getArray(children, 0);
//            print_tnode_type(specifier);
            assert(specifier->value_t == Specifier_);
            if (num_child == 2) {   //for structures like struct name{...};, but 'int;' is also valid, should ignore
                resolve_Specifier(specifier);

            } else if (num_child == 3) {
                TNode *node1 = getArray(children, 0);
                TNode *node2 = getArray(children, 1);
                Type decType = resolve_Specifier(node1);

                if (node2->value_t == ExtDecList_) {
                    if (decType != NULL)
                        resolve_ExtDecList(node2, decType);
                } else if (node2->value_t == FunDec_) {
                    if (decType != NULL)
                        resolve_FunDec(node2, decType, getArray(children, 2));
                }
            }
            break;
        }
        default:
            break;
    }

    if (node->value_t == Program_)
        final_check();
    free_Array(children);
}

void final_check() {
    for (int i = 0; i < sizeArray(ScopeTable__); i++) {
        ScopeList curList = getArray(ScopeTable__, i);
        for (ListNode node = getHeadNode(curList->list); node != NULL; node = getNextNode(node)) {
            SymbolInfo info = node->data;
            if (info->kind == SYM_FUNC && !info->funDetail->defined) {
                throw_semantic_error(18, info->funDetail->dec_line, info->name, NULL);
            }
        }
    }
}

Type resolve_Specifier(TNode *specifier) {
    assert(specifier->value_t == Specifier_);
    TNode *specKind = specifier->first_child;
    assert(specKind);
    if (specKind->value_t == TYPE_) {
        Type basicType = new_type(TYPE_BASIC);
        BasicKind bkind;
        if (strcmp(specKind->value.v_string, "int") == 0)
            bkind = BASIC_INT;
        else if (strcmp(specKind->value.v_string, "float") == 0)
            bkind = BASIC_FLOAT;
        else
            assert(false);
        initBasic(basicType, bkind);
        return basicType;
    } else {
        assert(specKind->value_t == StructSpecifier_);
        Array specArray = getChildren(specKind);
        unsigned int decSize = sizeArray(specArray);
        if (decSize == 2) { //StructSpecifier: STRUCT struct_name
            TNode *structTag = getArray(specArray, 1);
            free_Array(specArray);
            assert(structTag && structTag->value_t == Tag_);
            TNode *structName = structTag->first_child;
            assert(structName && structName->value_t == ID_);
            SymbolInfo structInfo = getInfo(structName->value.v_string);
            if (structInfo != NULL && structInfo->kind == SYM_STRUCT) {
                // return the defined struct type recorded in info
                return structInfo->type;
            } else {
                // the struct hasn't been declared
                throw_semantic_error(17, structTag->no_line, structName->value.v_string, NULL);
                return NULL;
            }
        } else if (decSize >= 3 && decSize <= 5) {
            // if the structure doesn't have a name, like 'struct{...} temp1', we should not add it into the symbol table
            // else if the symbol exists, we should throw redeclaration error, else just add it to the symbol table.
            free_Array(specArray);
            TNode *structID = NULL;
            List defs = new_list();
            Type structType = new_type(TYPE_STRUCTURE);
            for (TNode *child = specKind->first_child; child != NULL; child = child->next_sibling) {
                if (child->value_t == OptTag_) {
                    structID = child->first_child;
                    if (structID != NULL) {   // the struct has a repeated name
                        assert(structID->value_t == ID_);
                        const char *name_str = structID->value.v_string;
                        SymbolInfo definedInfo = getInfo(name_str); //the name should not appear in and above the scope
                        if (definedInfo != NULL) { // the struct name has already been registered in the current scope
                            throw_semantic_error(16, child->no_line, name_str, NULL);
                            free_list(defs);
                            free_Type(structType);
                            return NULL;
                        }
                    }
                } else if (child->value_t == DefList_) {
                    new_ScopeList();
                    resolve_DefList(child, defs);
                    assert(defs);
                    bool fieldError = false;
                    for (ListNode listNode = getHeadNode(defs);
                         listNode != NULL; listNode = getNextNode(listNode)) {
                        VarDefNode curDef = (VarDefNode) listNode->data;
                        if (curDef->initiated || !addStructField(structType, curDef)) {
                            // field is initiated or has repeated structure field name
                            throw_semantic_error(15, curDef->dec_line, curDef->name, NULL);
                            free_VarDefNode(curDef);
                            fieldError = true;
                        }
                    }
                    if (fieldError) {
                        free_list(defs);
                        free_Type(structType);
                        poll(ScopeStack__);
                        return NULL;
                    }
                    poll(ScopeStack__);
                }
            }
            free_list(defs);
            if (structID != NULL) {
                assert(structID->value_t == ID_);
                addStructName(structType, structID->value.v_string);
                // the validness has been checked in optTag
                SymbolInfo structInfo = new_SymbolInfo(
                        structID->value.v_string,
                        structType,
                        SYM_STRUCT,
                        NULL
                );
                addInfo(structInfo);
            }
            // struct type is filled
            return structType;

        } else {
            // error grammar
            assert(false);
        }
    }
}

/**
 * called in ExtDecList and function declaration
 * @param varDec
 * @param inhType
 * @param func_name determine whether a variable is a parameter
 * @param addToTab need add to table or the caller wants the resolved result
 * @param needRet need return value or not
 * @return pair [varType, varName] if the variable is valid, else null
 */
VarDefNode varDec_solver(TNode *varDec, Type inhType, const char *func_name, bool addToTab, bool needRet) {
    char *varName = NULL;
    Type varType = resolve_VarDec(varDec, inhType, &varName);
    // decide whether to add type,i.g. look up the symbol table 'Type varName'
    SymbolInfo info = getInfoCurScope(varName);
    SymbolInfo structInfo = getInfo(varName);
    if (info != NULL || structInfo != NULL && structInfo->kind == SYM_STRUCT) {
        // redefined variable
        throw_semantic_error(3, varDec->no_line, varName, NULL);
        free(varName);
        free_Type(varType);
    } else {
        if (addToTab) {
            SymbolInfo decInfo = new_SymbolInfo(varName,
                                                varType,
                                                SYM_VAR,
                                                new_VarDetail(func_name ? true : false, func_name)
            );
            addInfo(decInfo);
            if (!needRet) {
                return NULL;
            } else
                return new_VarDefNode(varName, varType, varDec->no_line, false);
        } else {
            if (!needRet) {
                free(varName);
                free_Type(varType);
                return NULL;
            } else
                return new_VarDefNode(varName, varType, varDec->no_line, false);
        }
    }
    return NULL;
}

void resolve_ExtDecList(TNode *extDecList, Type inhType) {
    assert(extDecList->value_t == ExtDecList_);
    for (TNode *child = extDecList->first_child; child != NULL; child = child->next_sibling) {
        if (child->value_t == ExtDecList_)
            resolve_ExtDecList(child, inhType);
        else if (child->value_t == VarDec_) {
            varDec_solver(child, inhType, NULL, true, false);
        } else
            assert(false);
    }
}

Type resolve_VarDec(TNode *varDec, Type inhType, char **name) {
    assert(varDec && varDec->value_t == VarDec_);
    TNode *node1 = varDec->first_child;
    if (node1->value_t == ID_) {
        *name = (char *) malloc((strlen(node1->value.v_string) + 1) * sizeof(char));
        strcpy(*name, node1->value.v_string);
        return copy_Type(inhType); // syn = inh
    } else if (node1->value_t == VarDec_) {
        assert(node1->next_sibling);
        TNode *node3 = node1->next_sibling->next_sibling;
        assert(node3->value_t == INT_);
        int size = node3->value.v_int;
        Type arrayType = new_type(TYPE_ARRAY);
        Type elem_t = resolve_VarDec(node1, inhType, name);
        initArray(arrayType, elem_t, size);
        return arrayType;
    } else
        assert(false);
}

void resolve_FunDec(TNode *funDec, Type inhType, TNode *comp) {
    // comp could be semi
    assert(funDec && funDec->value_t == FunDec_);
    bool isFunDefine = comp->value_t == CompSt_;
    Array children = getChildren(funDec);
    TNode *nameNode = getArray(children, 0);
    assert(nameNode->value_t == ID_);
    char *funName = nameNode->value.v_string;
    // function is unique that can only be defined in the root scope
    // but can be declared in inner scope
    if (isFunDefine) { // function definition
        if (!isRootScope()) {
            throw_semantic_error(20, funDec->no_line, NULL, NULL);
            free_Array(children);
            return;
        }

        SymbolInfo definedInfo = getInfoCurScope(funName);
        if (definedInfo) {
            //redefined function
            if (definedInfo->kind == SYM_FUNC && definedInfo->funDetail->defined || definedInfo->kind != SYM_FUNC) {
                //redefined function
                throw_semantic_error(4, funDec->no_line, funName, NULL);
                free_Array(children);
                return;
            }

            List paramList = new_list();
            if (sizeArray(children) == 4) {
                resolve_VarList(getArray(children, 2), paramList, NULL);
            }
            if (!equal_functions(definedInfo, funName, inhType, paramList)) {
                // the defined and the current in inconsistent
                throw_semantic_error(19, funDec->no_line, funName, NULL);
                free_Array(children);
                for (ListNode para = getHeadNode(paramList); para != NULL; para = getNextNode(para)) {
                    free_VarDefNode(para->data);
                }
                free_list(paramList);
                return;
            } else {
                definedInfo->funDetail->defined = true;
                ScopeList paramScope = new_ScopeList();
                add_FuncBody(definedInfo->funDetail, paramScope);
                // push arguments
                for (ListNode para = getHeadNode(paramList); para != NULL; para = para->next) {
                    VarDefNode curDef = para->data;
                    addParamName(definedInfo->funDetail, curDef->name);
                    SymbolInfo info = new_SymbolInfo(
                            curDef->name, curDef->type,
                            SYM_VAR, new_VarDetail(true, funName)
                    );
                    addInfo(info);
                }
                resolve_CompSt(comp, inhType, true);
                for (ListNode para = getHeadNode(paramList); para != NULL; para = getNextNode(para)) {
                    free_VarDefNode(para->data);
                }
                free_list(paramList);
                free_Array(children);
                return;
            }
        } else {
            SymbolInfo funInfo = new_SymbolInfo(funName, inhType, SYM_FUNC, new_FuncDetail(true, funDec->no_line));
            new_ScopeList(); // create parameter's scope list
            List params = new_list();
            if (sizeArray(children) == 4) {
                resolve_VarList(getArray(children, 2), params, funName);
            }
            for (ListNode para = getHeadNode(params); para != NULL; para = getNextNode(para)) {
                addParamType(funInfo->funDetail, ((VarDefNode) para->data)->type);
                // can't free name, as name will be used inside the scope
                addParamName(funInfo->funDetail, ((VarDefNode) para->data)->name);
                free(para->data);
            }
            ScopeList paraScope = poll(ScopeStack__);
            // current scope is the root scope
            add_FuncBody(funInfo->funDetail, paraScope);
            addInfo(funInfo);
            push(ScopeStack__, paraScope);
            free_list(params);
            free_Array(children);
            resolve_CompSt(comp, inhType, true);
            return;
        }
    } else { // function declaration
        // search and add the function to the current scope, if function exists but has different parameter and return type
        // raise inconsistent declaration
        // should find declaration from curr to root
        SymbolInfo definedDec = getInfo(funName);
        if (definedDec) {
            if (definedDec->kind != SYM_FUNC) {
                //redefined function
                throw_semantic_error(4, funDec->no_line, funName, NULL);
                free_Array(children);
                return;
            } else { //function declaration exists, just check the equivalence of the two declarations(definition).
                List params = new_list();
                if (sizeArray(children) == 4) {
                    resolve_VarList(getArray(children, 2), params, NULL);
                }
                if (!equal_functions(definedDec, funName, inhType, params)) {
                    throw_semantic_error(19, funDec->no_line, funName, NULL);
                    free_Array(children);
                    for (ListNode para = getHeadNode(params); para != NULL; para = getNextNode(para)) {
                        free_VarDefNode(para->data);
                    }
                    free_list(params);
                    return;
                }

            }
        } else {    //first declaration, simply add a new one;
            List params = new_list();
            if (sizeArray(children) == 4) {
                resolve_VarList(getArray(children, 2), params, NULL);
            }
            SymbolInfo funInfo = new_SymbolInfo(funName, inhType, SYM_FUNC, new_FuncDetail(false, funDec->no_line));
            for (ListNode para = getHeadNode(params); para != NULL; para = getNextNode(para)) {
                VarDefNode curDef = (VarDefNode) para->data;
                addParamType(funInfo->funDetail, curDef->type);
                // just need type information;
                free(curDef->name);
                free(para->data);
            }
            addInfo(funInfo);
            free_list(params);
            free_Array(children);
            return;
        }
    }
}

void resolve_VarList(TNode *varList, List vars, const char *funcName) {
    // if funcName == NULL, means the declaration is not a function definition, should add resolved result's type to vars
    assert(varList->value_t == VarList_);
    for (TNode *child = varList->first_child; child != NULL; child = child->next_sibling) {
        if (child->value_t == VarList_) {
            resolve_VarList(child, vars, funcName);
        } else if (child->value_t == ParamDec_) {
            TNode *specifier = child->first_child;
            Type specType = resolve_Specifier(specifier);
            if (specType != NULL) {
                TNode *varDec = specifier->next_sibling;
                assert(varDec->value_t == VarDec_);
                assert(vars);
                // function declaration(whose funcName is NULL) shouldn't be added to the symTable, or if it is a function definition, just add
                VarDefNode curDef = varDec_solver(varDec, specType, funcName, funcName != NULL, true);
                if (curDef != NULL) pushTail(vars, newListNode(curDef));

            } else return;
        }
    }
}

void resolve_CompSt(TNode *compSt, Type funcRetType, bool fromInvoke) {
    // if compSt is from a function, should not new a scopeList and also should check the return type
    assert(compSt->value_t == CompSt_);

    if (!fromInvoke)
        new_ScopeList();

    for (TNode *child = compSt->first_child; child != NULL; child = child->next_sibling) {
        if (child->value_t == DefList_) {
            // defList could be reduced to empty
            resolve_DefList(child, NULL);
        } else if (child->value_t == StmtList_)
            resolve_StmtList(child, funcRetType);
    }

    // leave the current scope
    poll(ScopeStack__);
}

void resolve_DecList(TNode *decList, Type inhType, List defs) {
    assert(decList->value_t == DecList_);
    for (TNode *child = decList->first_child; child != NULL; child = child->next_sibling) {
        if (child->value_t == Dec_) {
            Array decChild = getChildren(child);
            TNode *vardec = getArray(decChild, 0);
            assert(vardec->value_t == VarDec_);
            VarDefNode var = varDec_solver(vardec, inhType, NULL, defs ? false : true, true);
            if (sizeArray(decChild) == 1) {
                // VarDec
                if (defs && var)pushTail(defs, newListNode(var));
            } else if (sizeArray(decChild) == 3) {
                //VarDec ASSIGNOP Exp
                if (var != NULL) {
                    var->initiated = true;
                    Type expType = resolve_Exp(getArray(decChild, 2));
                    if (expType != NULL && !equalType(var->type, expType)) {
                        throw_semantic_error(5, vardec->no_line, NULL, NULL);
                        free_VarDefNode(var);
                    } else if (defs && expType)pushTail(defs, newListNode(var));
                }

            } else
                assert(false);
            free_Array(decChild);
        } else if (child->value_t == DecList_)
            resolve_DecList(child, inhType, defs);
    }
}

void resolve_Stmt(TNode *stmt, Type funcRetType) {
    TNode *firstChild = stmt->first_child;
    if (firstChild->value_t == RETURN_) {
        TNode *exp = firstChild->next_sibling;
        assert(exp->value_t == Exp_);
        Type expType = resolve_Exp(exp);
        if (!equalType(expType, funcRetType)) {
            throw_semantic_error(8, stmt->no_line, NULL, NULL);
        }
    } else {    //other productions
        for (TNode *node = firstChild; node != NULL; node = node->next_sibling) {
            switch (node->value_t) {
                case Exp_: {
                    resolve_Exp(node);
                    break;
                }
                case CompSt_: {
                    resolve_CompSt(node, funcRetType, false);
                    break;
                }
                case Stmt_: {
                    resolve_Stmt(node, funcRetType);
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void resolve_StmtList(TNode *stmtList, Type funcRetType) {
    assert(stmtList->value_t == StmtList_);
    for (TNode *child = stmtList->first_child; child != NULL; child = child->next_sibling) {
        if (child->value_t == Stmt_) {
            resolve_Stmt(child, funcRetType);
        } else if (child->value_t == StmtList_) {
            resolve_StmtList(child, funcRetType);
        } else
            assert(false);
    }
}

static inline char *gen_paramsTypeStr(FunDetail detail);

/**
 * called by resolve_exp to get type of function or throw errors
 * @param id
 * @param args
 * @return
 */
Type invoke_solver(TNode *id, TNode *args, int line_no) {
    //foo()
    assert(id->value_t == ID_);
    SymbolInfo func = getInfo(id->value.v_string);
    if (func == NULL) {
        // undefined function
        throw_semantic_error(2, line_no, id->value.v_string, NULL);
        return NULL;
    } else if (func->kind != SYM_FUNC) {
        // not a function
        throw_semantic_error(11, line_no, id->value.v_string, NULL);
        return NULL;
    } else if (!func->funDetail->defined) {
        // declared but not defined
        throw_semantic_error(18, line_no, id->value.v_string, NULL);
        return NULL;
    } else if (args == NULL && !isEmptyList(func->funDetail->paramsType)) {
        char *typeStr = gen_paramsTypeStr(func->funDetail);
        throw_semantic_error(9, line_no, id->value.v_string, typeStr);
        free(typeStr);
        return NULL;
    } else if (args) {
        List argTypeList = new_list();
        resolve_Args(args, argTypeList);
        if (!equalList(argTypeList, func->funDetail->paramsType, (bool (*)(void *, void *)) equalType)) {
            throw_semantic_error(9, line_no, id->value.v_string, gen_paramsTypeStr(func->funDetail));
            return NULL;
        }
    }
    return func->type;
}

Type resolve_Exp(TNode *exp) {
    assert(exp->value_t == Exp_);
    Array expChild = getChildren(exp);
    if (sizeArray(expChild) == 1) {
        TNode *child = getArray(expChild, 0);
        free_Array(expChild);
        if (child->value_t == INT_) {
            Type itype = new_type(TYPE_BASIC);
            initBasic(itype, BASIC_INT);
            return itype;
        } else if (child->value_t == FLOAT_) {
            Type ftype = new_type(TYPE_BASIC);
            initBasic(ftype, BASIC_FLOAT);
            return ftype;
        } else if (child->value_t == ID_) {
            SymbolInfo id = getInfo(child->value.v_string);
            if (id == NULL) {
                throw_semantic_error(1, exp->no_line, child->value.v_string, NULL);
                return NULL;
            } else {
                return id->type;
            }
        } else {
            assert(false);
        }
    } else if (sizeArray(expChild) == 2) {
        // minus exp, not exp
        TNode *node2 = getArray(expChild, 1);
        assert(node2->value_t == Exp_);
        free_Array(expChild);
        return resolve_Exp(node2);
    } else if (sizeArray(expChild) == 3) {
        TNode *node1 = getArray(expChild, 0);
        TNode *node2 = getArray(expChild, 1);
        TNode *node3 = getArray(expChild, 2);
        free_Array(expChild);
        if (node1->value_t == LP_) {
            //E = (E)
            return resolve_Exp(node2);
        } else if (node1->value_t == ID_) {
            return invoke_solver(node1, NULL, exp->no_line);
        } else {
            // node1 == exp

            if (node2->value_t == DOT_) {
                Type expType = resolve_Exp(node1);
                if (expType == NULL || expType->kind != TYPE_STRUCTURE) {
                    throw_semantic_error(13, node1->no_line, NULL, NULL);
                    return NULL;
                } else {
                    assert(node3->value_t == ID_);
                    VarDefNode field = getFieldNamedOf(expType, node3->value.v_string);
                    if (field) {
                        return field->type;
                    } else {
                        throw_semantic_error(14, node1->no_line, node3->value.v_string, NULL);
                        return NULL;
                    }
                }
            } else { // exp op exp
                if (node2->value_t == ASSIGNOP_) {
                    Array leftChild = getChildren(node1);
                    if (!(sizeArray(leftChild) == 1 && ((TNode *) getArray(leftChild, 0))->value_t == ID_ ||
                          sizeArray(leftChild) == 3 && ((TNode *) getArray(leftChild, 1))->value_t == DOT_ ||
                          sizeArray(leftChild) == 4 && ((TNode *) getArray(leftChild, 1))->value_t == LB_
                    )) {
                        //only ID, Exp LB Exp RB, Exp DOT ID can be left value
                        throw_semantic_error(6, node1->no_line, NULL, NULL);
                        free_Array(leftChild);
                        return NULL;
                    } else {
                        free_Array(leftChild);
                        Type exp1T = resolve_Exp(node1);
                        Type exp2T = resolve_Exp(node3);
                        if (!exp1T || !exp2T) return NULL;
                        else {
                            if (equalType(exp1T, exp2T))
                                return exp1T;
                            else {
                                throw_semantic_error(5, node1->no_line, NULL, NULL);
                                return NULL;
                            }
                        }
                    }
                } else {
                    Type exp1T = resolve_Exp(node1);
                    Type exp2T = resolve_Exp(node3);
                    if (!exp1T || !exp2T) return NULL;  //error has been raised
                    else { //binary exp
                        // incompatible types
                        if (equalType(exp1T, exp2T)) {
                            if ((node2->value_t == RELOP_ || node2->value_t == AND_ || node2->value_t == OR_)) {
                                Type basic = new_type(TYPE_BASIC);
                                initBasic(basic, BASIC_INT);
                                return basic;
                            }
                            return exp1T;
                        } else {
                            throw_semantic_error(7, node1->no_line, NULL, NULL);
                            return NULL;
                        }
                    }
                }
            }
        }
    } else if (sizeArray(expChild) == 4) {
        // ID LP Args RP, Exp LB Exp RB
        TNode *node1 = getArray(expChild, 0);
        TNode *node3 = getArray(expChild, 2);
        free_Array(expChild);
        if (node1->value_t == ID_) {
            return invoke_solver(node1, node3, exp->no_line);
        } else if (node1->value_t == Exp_) {
            Type arrayT = resolve_Exp(node1);
            Type indexT = resolve_Exp(node3);
            if (!arrayT || arrayT->kind != TYPE_ARRAY) {
                throw_semantic_error(10, exp->no_line, NULL, NULL);
                return NULL;
            } else if (indexT->kind != TYPE_BASIC || indexT->basic != BASIC_INT) {
                throw_semantic_error(12, exp->no_line, NULL, NULL);
            } else {
                return arrayT->array->elem_t;
            }
        }
    } else {
        assert(false);
    }
    return NULL;
}

void resolve_Args(TNode *args, List argTypeList) {
    assert(args->value_t == Args_);
    for (TNode *child = args->first_child; child != NULL; child = child->next_sibling) {
        if (child->value_t == Exp_) {
            Type pType = resolve_Exp(child);
            if (pType) pushTail(argTypeList, newListNode(pType));
        } else if (child->value_t == Args_) {
            resolve_Args(child, argTypeList);
        }
    }
}

char *newStrCat(char *s1, char *s2);

/**
 * @param detail
 * @return
 */
char *gen_paramsTypeStr(FunDetail detail) {
    char *s = (char *) malloc(2 * sizeof(char));
    s[0] = '(';
    for (ListNode para = getHeadNode(detail->paramsType); para != NULL; para = getNextNode(para)) {
        Type curT = (Type) para->data;
        switch (curT->kind) {
            case TYPE_BASIC: {
                if (curT->basic == BASIC_INT) {
                    char *s1 = newStrCat(s, "int,");
                    free(s);
                    s = s1;
                } else {
                    char *s1 = newStrCat(s, "float,");
                    free(s);
                    s = s1;
                }
                break;
            }
            case TYPE_ARRAY: {
                char *s1 = newStrCat(s, "array,");
                free(s);
                s = s1;
                break;
            }
            case TYPE_STRUCTURE: {
                char *s1 = newStrCat(s, "structure<");
                free(s);
                s = s1;
                s1 = newStrCat(s, curT->structure->name);
                free(s);
                s = s1;
                s1 = newStrCat(s, ">,");
                free(s);
                s = s1;
                break;
            }
        }
    }
    int lens = (int) strlen(s);
    if (lens == 1) {
        free(s);
        s = (char *) malloc(3 * sizeof(char));
        s[0] = '(', s[1] = ')';
        return s;
    }
    s[lens - 1] = ')';
    return s;
}

char *newStrCat(char *s1, char *s2) {
    char *s = (char *) malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
    strcpy(s, s1);
    strcat(s, s2);
    return s;
}

void throw_semantic_error(int error_code, int line_no, const char *note1, const char *note2) {
    switch (error_code) {
        case 1: {
            printf("Error type 1 at Line %d: Undefined variable \"%s\".\n", line_no, note1 ? note1 : "");
            break;
        }
        case 2: {
            printf("Error type 2 at Line %d: Undefined function \"%s\".\n", line_no, note1 ? note1 : "");
            break;
        }
        case 3: {
            printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", line_no, note1 ? note1 : "");
            break;
        }
        case 4: {
            printf("Error type 4 at Line %d: Redefined function \"%s\".\n", line_no, note1 ? note1 : "");
            break;
        }
        case 5: {
            printf("Error type 5 at Line %d: Type mismatched for assignment.\n", line_no);
            break;
        }
        case 6: {
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", line_no);
            break;
        }
        case 7: {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n", line_no);
            break;
        }
        case 8: {
            printf("Error type 8 at Line %d: Type mismatched for return.\n", line_no);
            break;
        }
        case 9: {
            printf("Error type 9 at Line %d: Function \"%s\" is not applicable for arguments \"%s\".\n", line_no,
                   note1 ? note1 : "", note2 ? note2 : "");
            break;
        }
        case 10: {
            printf("Error type 10 at Line %d: variable is not an array.\n", line_no);
            break;
        }
        case 11: {
            printf("Error type 11 at Line %d: \"%s\" is not a function.\n", line_no, note1 ? note1 : "");
            break;
        }
        case 12: {
            printf("Error type 12 at Line %d: index is not an integer.\n", line_no);
            break;
        }
        case 13: {
            printf("Error type 13 at Line %d: Illegal use of \".\".\n", line_no);
            break;
        }
        case 14: {
            printf("Error type 14 at Line %d: Non-existent field \"%s\".\n", line_no, note1 ? note1 : "");
            break;
        }
        case 15: {
            printf("Error type 15 at Line %d: Redefined field \"%s\".\n", line_no, note1 ? note1 : "");
            break;
        }
        case 16: {
            printf("Error type 16 at Line %d: Duplicated name \"%s\".\n", line_no, note1 ? note1 : "");
            break;
        }
        case 17: {
            printf("Error type 17 at Line %d: Undefined structure \"%s\".\n", line_no, note1 ? note1 : "");
            break;
        }
        case 18: {
            printf("Error type 18 at Line %d : Undefined function \"%s\".\n", line_no, note1 ? note1 : "");
            break;
        }
        case 19: {
            printf("Error type 19 at Line %d: Inconsistent declaration of function \"%s\".\n", line_no,
                   note1 ? note1 : "");
            break;
        }
        case 20: {
            printf("Error type 20 at Line %d: function definition is not allowed here.\n", line_no);
            break;
        }
        default: {
            printf("error code: %d\n", error_code);
            assert(false);
            break;
        }
    }
}