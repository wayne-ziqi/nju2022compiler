typedef enum valueType {
    /* TERMINAL*/
    _TYPE,
    _STRUCT,
    _RETURN,
    _IF,
    _ELSE,
    _WHILE,
    _ID,
    _SEMI,
    _COMMA,
    _RELOP,
    _ASSIGNOP,
    _PLUS,
    _MINUS,
    _STAR,
    _DIV,
    _AND,
    _OR,
    _DOT,
    _NOT,
    _LP,
    _RP,
    _LB,
    _RB,
    _LC,
    _RC,
    _INT,
    _FLOAT,
    /* NON-TERMINAL*/
    _Program,
    _ExtDefList,
    _ExtDef,
    _ExtDecList,
    _Specifier,
    _StructSpecifier,
    _OptTag,
    _Tag,
    _VarDec,
    _FunDec,
    _VarList,
    _ParamDec,
    _CompSt,
    _StmtList,
    _Stmt,
    _DefList,
    _Def,
    _DecList,
    _Dec,
    _Exp,
    _Args
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
 * @brief free memory of current node and his children
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
 * @brief print the tree led by root  in the format declared in the guide
 *
 * @param root
 * @param level level of the node for recursion, the caller should pass in 0
 */
void show_tree(TNode *root, int level);
