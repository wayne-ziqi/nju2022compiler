#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__

/**
 * in our implementation, a symbol table system has there parts
 * 1. Symbol table: the main symbol table
 * 2. Symbol List: list of symbols belonging to the same scope
 * 3. Scope Array: array that records symbol list, and the index is their scope id
 */

#include "../lib/stack.h"
#include "../lib/hashMap.h"
#include "../lib/array.h"
#include "common_type.h"


typedef enum {
    SYM_VAR,
    SYM_FUNC,
    SYM_STRUCT
} SymbolKind;

typedef HashMap SymbolTable;
typedef Stack ScopeStack;
typedef Array ScopeTable;
typedef struct ScopeList_ *ScopeList;
typedef struct SymbolInfo_ *SymbolInfo;
typedef struct VarDetail_ *VarDetail;
typedef struct FunDetail_ *FunDetail;

extern SymbolTable SymbolTable__;
extern ScopeTable ScopeTable__;
extern ScopeStack ScopeStack__;

/**
 *  <ul>
 *  <li> name: name of symbol to avoid alias
 *  <li> SymbolKind: variable of function
 *  <li> id_scope: id of the scope
 *  <li> type: variable's type, struct declaration, function return type
 *  <li> detail: determined by SymbolKind, struct declaration doesn't have detail
 *  </ul>
 */

/**
 * structure declarations are all saved in Type filed.
 * the structure's name is unique in this scope and its subscope, i.g.
 * any variable that has the same name as the struct is forbidden
 */
struct SymbolInfo_ {
    char *name;
    SymbolKind kind;
    unsigned int id_scope;
    Type type;
    union {
        VarDetail varDetail;
        FunDetail funDetail;
    };
};

/**
 * <ul>
 * <li> isParam: parameter or not
 * <li> type: the variable's basic type
 * </ul>
 */
struct VarDetail_ {
    bool isParam;
    char *func_name;
};

/**
 * use the details and function name to identify a function, which  called a function's sub-signature
 * <ul>
 * <li> defined: whether has been defined, could be used to check use-before-define error
 * <li> retType: return type of the function, null if void(not supported)
 * <li> paramType: list of parameter type.
 * </ul>
 */
struct FunDetail_ {
    bool defined;
    int dec_line;
    List paramsType;
    Array paramsName;
    ScopeList body;
};

struct ScopeList_ {
    // attention: id_scope is also the topological order of the scope
    unsigned int id_scope;
    unsigned int depth;
    // list of defined symbols
    List list;
};

/**
 * create new symbol table, symbol list, symbol stack, and push the program
 * scope(root scope) to the stack and scope table
 */
void initSymbolSystem();

/**
 * create a new scope list which will be added to scope table and stack automatically
 * so scope id is reachable in scope list field
 */
ScopeList new_ScopeList();

/**
 *
 * @return true if current scope is the root
 */
bool isRootScope();

/**
 * create a new variable detailed entry, type should be filled before calling.
 * if it is a parameter, should pass the order in the parameters list counting from 0
 */
VarDetail new_VarDetail(bool isParam, const char *func_name);

void free_VarDetail(VarDetail detail);

/**
 * create a new function detail entry whose parameter list is emtpy
 */
FunDetail new_FuncDetail(bool defined, int dec_line);

void free_FuncDetail(FunDetail detail);

/**
 *
 * @param targetFunc symbol info that has already existed
 * @param srcFuncName function's name
 * @param srcRetType src function's return type
 * @param srcParaList [!VarDefNode!] list of source function's parameters
 * @return true if the two functions have the same signature
 */
bool equal_functions(SymbolInfo targetFunc, const char *srcFuncName, Type srcRetType, List srcParaList);

/**
 *
 * @param funcDet
 * @param paramType
 */
void addParamType(FunDetail funcDet, Type paramType);

void addParamName(FunDetail funcDet, const char *name);

/**
 * add a body scope to the function, the function's current body should be null
 * @param funcDet
 * @param body
 */
void add_FuncBody(FunDetail funcDet, ScopeList body);

/**
 * create a new symbolInfo entry, detail entry is optional(null)
 */
SymbolInfo new_SymbolInfo(char *name, Type type, SymbolKind kind, void *detail);

void free_SymbolInfo(SymbolInfo info);

/**
 * add detail to info. note, you should assure the class of the detail
 * matches the info type
 * @param info
 * @param detail
 */
void addDetail(SymbolInfo info, void *detail);

/**
 * core method of symbol system, get the first valid data in the stack
 * @param name
 * @return the symbol's information in or above the current scope, null if doesn't exist
 */
SymbolInfo getInfo(const char *name);


/**
 * used before calling add info
 * @param name
 * @return the info with name in the current scope
 */
SymbolInfo getInfoCurScope(const char *name);

/**
 * core method of symbol system
 * NOTE: add info will not check whether the info exists in the top scope,
 * you should call getInfoCurScope to check its existence. the intention to
 * design in this way is to avoid useless allocated Symbol info.
 * @param info fulfilled information entry.
 *
 */
void addInfo(SymbolInfo info);

#endif  // __SYMBOL_TABLE__