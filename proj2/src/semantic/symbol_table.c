#include "symbol_table.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>


SymbolTable SymbolTable__;
ScopeTable ScopeTable__;
ScopeStack ScopeStack__;

void initSymbolSystem() {
    SymbolTable__ = new_hashmap(STRING, DEFAULT_SLOT_SIZE);
    ScopeTable__ = new_Array();
    ScopeStack__ = new_stack();
    // prepare for the root program.
    new_ScopeList();
}

ScopeList new_ScopeList() {
    ScopeList sm_list = (ScopeList) malloc(sizeof(struct ScopeList_));
    sm_list->id_scope = ScopeTable__->size;
    sm_list->depth = ScopeStack__->size;
    sm_list->list = new_list();
    // add it to the ScopeTable and push to the stack
    appendArray(ScopeTable__, sm_list);
    push(ScopeStack__, sm_list);
    return sm_list;
}

bool isRootScope() {
    return ((ScopeList) getTop(ScopeStack__))->id_scope == 0;
}

VarDetail new_VarDetail(bool isParam, const char *func_name) {
    VarDetail detail = (VarDetail) malloc(sizeof(struct VarDetail_));
    detail->isParam = isParam;
    if (isParam) {
        assert(func_name);
        detail->func_name = (char *) malloc((strlen(func_name) + 1) * sizeof(char));
        strcpy(detail->func_name, func_name);
    } else {
        detail->isParam = -1;
    }
    return detail;
}

void free_VarDetail(VarDetail detail) {
    assert(detail);
    if (detail->isParam)
        free(detail->func_name);
    free(detail);
}

FunDetail new_FuncDetail(bool defined, int dec_line) {
    FunDetail detail = (FunDetail) malloc(sizeof(struct FunDetail_));
    detail->defined = defined;
    detail->dec_line = dec_line;
    detail->paramsType = new_list();
    detail->paramsName = new_Array();
    detail->body = NULL;
    return detail;
}


void free_FuncDetail(FunDetail detail) {
    assert(detail);
    for (ListNode node = detail->paramsType->leader->next;
         node != NULL; node = node->next) {
        assert(node->data);
        free_Type(node->data);
    }
    free_list(detail->paramsType);
    for (int i = 0; i < detail->paramsName->size; ++i) {
        free(getArray(detail->paramsName, i));
    }
    free_Array(detail->paramsName);
    free(detail);
}


bool equal_functions(SymbolInfo targetFunc, const char *srcFuncName, Type srcRetType, List srcParaList) {
    assert(targetFunc->kind == SYM_FUNC);
    if (strcmp(targetFunc->name, srcFuncName) != 0)return false;
    if (!equalType(targetFunc->type, srcRetType)) return false;
    List srcParaTypeList = new_list();
    for (ListNode node = getHeadNode(srcParaList); node != NULL; node = getNextNode(node)) {
        ListNode typeNode = newListNode(((VarDefNode) node->data)->type);
        pushTail(srcParaTypeList, typeNode);
    }
    if (!equalList(targetFunc->funDetail->paramsType, srcParaTypeList,
                   (bool (*)(void *, void *)) equalType)) {
        free_list(srcParaTypeList);
        return false;
    }
    free_list(srcParaTypeList);
    return true;
}

void addParamType(FunDetail funcDet, Type paramType) {
    assert(funcDet);
    assert(paramType);
    pushTail(funcDet->paramsType, newListNode(paramType));
}

void addParamName(FunDetail funcDet, const char *name) {
    assert(funcDet);
    assert(name);
    char *pname = (char *) malloc((strlen(name) + 1) * sizeof(char));
    strcpy(pname, name);
    appendArray(funcDet->paramsName, pname);
}

void add_FuncBody(FunDetail funcDet, ScopeList body) {
    assert(funcDet && body);
    assert(funcDet->body == NULL);
    funcDet->body = body;
}

SymbolInfo new_SymbolInfo(char *name, Type type, SymbolKind kind, void *detail) {
    SymbolInfo info = (SymbolInfo) malloc(sizeof(struct SymbolInfo_));
    info->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
    strcpy(info->name, name);
    info->type = type;
    info->id_scope = 0;
    info->kind = kind;
    if (info->kind != SYM_STRUCT)
        addDetail(info, detail);
    return info;
}

void free_SymbolInfo(SymbolInfo info) {
    assert(info);
    assert(info->name);
    free(info->name);
    free_Type(info->type);
    if (info->kind == SYM_VAR)
        free_VarDetail(info->varDetail);
    else if (info->kind == SYM_FUNC)
        free_FuncDetail(info->funDetail);
    free(info);
}

void addDetail(SymbolInfo info, void *detail) {
    assert(info && (info->kind == SYM_VAR || info->kind == SYM_FUNC));
    if (detail != NULL) {
        if (info->kind == SYM_VAR)
            info->varDetail = (VarDetail) detail;
        else if (info->kind == SYM_FUNC)
            info->funDetail = (FunDetail) detail;
        else
            assert(false);
    } else
        info->varDetail = NULL;
}

// search key for SymbolInfo
typedef struct SKEY_ {
    const char *name;
    unsigned int scope;
} SKEY;

bool searchInfoRule(SKEY *key, SymbolInfo info) {
    return key->scope == info->id_scope &&
           strcmp(key->name, info->name) == 0;
}

SymbolInfo getInfoInScope(const char *name, unsigned int scope) {
    SKEY skey = {name, scope};
    return getFirstOf(SymbolTable__, (void *) name,
                      &skey, (bool (*)(void *, void *)) searchInfoRule);

}

SymbolInfo getInfo(const char *name) {
    assert(name);
    ScopeList curScope = getTop(ScopeStack__);
    while (curScope != NULL) {
        SymbolInfo info = getInfoInScope(name, curScope->id_scope);
        if (info != NULL) return info;
        curScope = getNext(ScopeStack__, curScope);

    }
    return NULL;
}

SymbolInfo getInfoCurScope(const char *name) {
    ScopeList currScope = getTop(ScopeStack__);
    assert(currScope && currScope->list);
    return getInfoInScope(name, currScope->id_scope);
}


void addInfo(SymbolInfo info) {
    // if addInfo is called, the symbol's scope is on the scope stack's top
    assert(info && info->name);
    ScopeList currScope = getTop(ScopeStack__);
    assert(currScope && currScope->list);
    info->id_scope = currScope->id_scope;
    pushTail(currScope->list, newListNode(info));
    addHead(SymbolTable__, info->name, info);
}
