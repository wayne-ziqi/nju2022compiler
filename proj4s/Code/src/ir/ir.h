#ifndef __IR__
#define __IR__

#include "../lib/array.h"

typedef enum OperandKind {
    OPD_VAR,
    OPD_ADDR,
    OPD_TMP,
    OPD_CONST,
    OPD_FUN,
    OPD_LABEL
} OperandKind;

typedef enum CodeKind {
    CODE_LABEL,     // single
    CODE_GOTO,      // single
    CODE_FUN,       // single
    CODE_RETURN,    // single
    CODE_ARG,       // single
    CODE_PARAM,     // single
    CODE_READ,      // single
    CODE_WRITE,     // single
    CODE_ASSIGN,    // twin, includes variable assign and function call
    CODE_GETADDR,   // twin, x = &y
    CODE_LOADADDR, // twin, x = *y
    CODE_STOREADDR, // twin, *x = y
    CODE_CALL,      // twin, x = call f
    CODE_DEC,       // twin
    CODE_ADD,       // triple
    CODE_SUB,       // triple
    CODE_MUL,       // triple
    CODE_DIV,       // triple
    CODE_IF         // triple
} CodeKind;

typedef enum RelOpKind {
    REL_EQ,
    REL_NE,
    REL_LT,
    REL_LE,
    REL_GT,
    REL_GE
} RelOpKind;

typedef struct Operand_ *Operand;
typedef struct InterCode_ *InterCode;

struct Operand_ {
    OperandKind kind;
    union {
        unsigned int i_tmp;              // ith tmp in the temporary variable table, like t1, t2...
        unsigned int i_label;            // label number
        unsigned int v_const;                       // constant value
        Operand o_addr;                 // use the defined operand as the address value
        const char *fun_name;         // function name read from the symbol table
        const char *var_name;         // variable name read from the symbol table
    };
};

// three address code
struct InterCode_ {
    CodeKind kind;
    unsigned opd_num;
    /// extensions
    unsigned int bid;    // block id the code belongs to
    int offset; // offset in the block, starts from 0
    ///
    union {
        struct {
            Operand o;
        } single;
        struct {
            Operand o1;
            Operand o2;
        } twin;
        struct {
            Operand o1;
            Operand o2;
            Operand o3;/*aka result or target*/
        } triple;
        struct {
            Operand cond1;
            Operand cond2;
            RelOpKind relop;
            Operand to_label;

        } if_code;
    };
};

/// group of operand constructors

char *operand_to_string(Operand o);

char *code_to_string(InterCode code);

Operand new_Tmp();

Operand new_Label();

// constants are all integers
Operand new_OpConst(unsigned int value);

Operand new_OpVar(const char *name);

Operand new_OpFun(const char *name);

Operand new_OpAddr(Operand o);


/// group of code constructors


// LABEL label
InterCode genIR_label(Operand label);

// GOTO label
InterCode genIR_goto(Operand label);

// FUNCTION fun
InterCode genIR_fun(Operand fun);

// RETURN retVal
InterCode genIR_return(Operand retVal);

// ARG arg
InterCode genIR_arg(Operand arg);

// PARAM param
InterCode genIR_param(Operand param);

// READ to
InterCode genIR_read(Operand to);

// WRITE value
InterCode genIR_write(Operand value);

// left = right
InterCode genIR_assign(Operand left, Operand right);

// left = &addr
InterCode genIR_getAddr(Operand left, Operand right);

// left = *addr
InterCode genIR_fetchAddr(Operand left, Operand addr);

// *left = right
InterCode genIR_storeAddr(Operand addr, Operand right);

// left = CALL call
InterCode genIR_call(Operand left, Operand call);

// res = o1 k_binary o2
InterCode genIR_Binary(Operand res, Operand o1, Operand o2, CodeKind k_binary);

// DEC var memory
InterCode genIR_dec(Operand var, Operand memory);

// if cond_o1 relOp cond_o2 GOTO to_label
InterCode genIR_if(Operand cond_o1, Operand cond_o2, RelOpKind relOp, Operand to_label);

// relop funtions
RelOpKind getOp(char *opstr);

RelOpKind notOp(RelOpKind op);

/// Operand helpers

/**
 * if code has defined operand then return it,
 * else return null
 * @param code
 * @return
 */
Operand getDefOf(InterCode code);

/**
 * get all used operand of code
 * @param code
 * @return
 */
Array/*<Operand>*/ getUseOf(InterCode code);

#endif//__IR__