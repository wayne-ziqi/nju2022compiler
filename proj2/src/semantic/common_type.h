#ifndef __COMMON_TYPE__
#define __COMMON_TYPE__

#include "../lib/list.h"

typedef struct Type_ *Type;
typedef struct VarDefNode_ *VarDefNode;
typedef struct ArrayNode_ *ArrayNode;
typedef struct Structure_ *Structure;

typedef enum type_kind {
    TYPE_BASIC = 1, TYPE_ARRAY, TYPE_STRUCTURE
} TypeKind;

typedef enum basic_kind {
    BASIC_INT, BASIC_FLOAT
} BasicKind;

struct Type_ {
    TypeKind kind;
    unsigned int memory;
    union {
        BasicKind basic;
        ArrayNode array;
        Structure structure;
    };
};

struct ArrayNode_ {
    Type elem_t;
    unsigned int size;
};

struct VarDefNode_ {
    Type type;
    char *name;
    int dec_line;
    bool initiated;
};

struct Structure_ {
    char *name;
    List field_list;
};

/**
 *
 * @param type_k
 * <ol>
 * <li> BASIC: should call initBasic to specify int or float with BasicKind</li>
 * <li> ARRAY: should call initArray to set element type and setSize to fill array size</li>
 * <li> STRUCT: should just call addField with correct type and name, i.g. FieldList is initialized here</li>
 * </ol>
 * @brief allocate a new Type with type kind type_k,
 * should fill more details after allocation using method below
 */
Type new_type(TypeKind type_k);

/**
 * judge whether the two type is literally equal
 */
bool equalType(Type t1, Type t2);

Type copy_Type(Type src);

void free_Type(Type type);

/**
 * fill the basic type with kind int/float
 * @param type
 * @param basicKind int/float
 */
void initBasic(Type type, BasicKind basicKind);

/**
 * @brief set array element type and size which shall be allocated ahead
 */
void initArray(Type type, Type elem_t, unsigned int size);

ArrayNode copy_Array(ArrayNode src);

/**
 * @brief name is alternative in structure's definition
 */
void addStructName(Type type, const char *name);

/**
 * @param type
 * @param name
 * @return varDefNode of the field with name
 */
VarDefNode getFieldNamedOf(Type type, char *name);

/**
 * @brief add a new fulfilled node to the structure's field list
 * @param type
 * @param field
 * @return true if successfully added, or the field that is alias has already existed
 */
bool addStructField(Type type, VarDefNode field);

/**
 * @brief allocate an empty array node
 */
ArrayNode new_ArrayNode();

void free_ArrayNode(ArrayNode node);

/**
 * arrays are equal if item type and size are equal
 */
bool equalArray(ArrayNode array1, ArrayNode array2);

/**
 *
 * @param name
 * @param type type of the field, should be filled before calling
 * @param initiated whether the defined variable is initiated by ID = Exp
 * @return a new field node with name and type
 */
VarDefNode new_VarDefNode(char *name, Type type, int line_no, bool initiated);

VarDefNode copy_VarDefNode(VarDefNode src);

void free_VarDefNode(VarDefNode node);

/**
 *  equal then the type is equal
 */
bool equalField(VarDefNode field1, VarDefNode field2);

/**
 * @return empty structure
 */
Structure new_Structure();

Structure copy_Structure(Structure src);

void free_Structure(Structure structure);

/**
 * the struct are equal if
 */
bool equalStruct(Structure structure1, Structure structure2);

#endif  //__COMMON_TYPE__