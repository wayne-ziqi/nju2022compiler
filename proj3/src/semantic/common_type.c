#include "common_type.h"
#include "../lib/stack.h"
#include "../lib/UInt.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Type new_type(TypeKind type_k) {
    Type type = (Type) malloc(sizeof(struct Type_));
    type->kind = type_k;
    type->width = 0;
    if (type_k == TYPE_STRUCTURE)
        type->structure = new_Structure();
    else if (type_k == TYPE_ARRAY)
        type->array = new_ArrayNode();
    else if (type_k != TYPE_BASIC)
        // unsupported type kind
        assert(false);

    return type;
}

void free_Type(Type type) {
    if (type->kind == TYPE_ARRAY)
        free_ArrayNode(type->array);
    else if (type->kind == TYPE_STRUCTURE)
        free_Structure(type->structure);
    free(type);
}

bool equalType(Type t1, Type t2) {
    if (!(t1 && t2)) return false;
    if (t1->kind != t2->kind) return false;
    if (t1->kind == TYPE_BASIC) {
        return t1->basic == t2->basic;
    } else if (t1->kind == TYPE_ARRAY) {
        return equalArray(t1->array, t2->array);
    } else if (t1->kind == TYPE_STRUCTURE) {
        return equalStruct(t1->structure, t2->structure);
    } else {
        // unsupported type kind
        assert(false);
    }
}

Type copy_Type(Type src) {
    Type dst = new_type(src->kind);
    dst->width = src->width;
    if (dst->kind == TYPE_BASIC)
        dst->basic = src->basic;
    else if (dst->kind == TYPE_ARRAY)
        dst->array = copy_Array(src->array);
    else if (dst->kind == TYPE_STRUCTURE)
        dst->structure = copy_Structure(src->structure);
    else
        assert(false);
    return dst;
}

void initBasic(Type type, BasicKind basicKind) {
    assert(type && type->kind == TYPE_BASIC);
    if (basicKind == BASIC_INT || basicKind == BASIC_FLOAT) {
        type->basic = basicKind;
        type->width = 4;
    } else {
        assert(false);
    }
}

Type genBasic(BasicKind bkind) {
    Type basic = new_type(TYPE_BASIC);
    initBasic(basic, bkind);
    return basic;
}

void initArray(Type type, Type elem_t, unsigned int size) {
    assert(type && type->kind == TYPE_ARRAY);
    assert(elem_t);
    type->array->elem_t = elem_t;
    type->array->size = size;
    type->width = size * elem_t->width;
}

ArrayNode copy_Array(ArrayNode src) {
    ArrayNode dst = new_ArrayNode();
    dst->size = src->size;
    dst->elem_t = copy_Type(src->elem_t);
    return dst;
}


void fixArrayWidth(Type array_t) {
    Type t = array_t;
    Stack st = new_stack();
    while (t->kind == TYPE_ARRAY) {
        push(st, new_UInt(t->array->size));
        t = t->array->elem_t;
    }
    t = array_t;
    while (t->kind == TYPE_ARRAY) {
        UInt u = poll(st);
        t->array->size = value_UInt(u);
        free_UInt(u);
        t = t->array->elem_t;
    }
    assert(isEmptyStack(st));
    t = array_t;
    while (t->kind == TYPE_ARRAY) {
        push(st, t);
        t = t->array->elem_t;
    }
    while (!isEmptyStack(st)) {
        Type cur = poll(st);
        cur->width = cur->array->size * cur->array->elem_t->width;
    }
    assert(isEmptyStack(st));
    free_stack(st);
}

void addStructName(Type type, const char *name) {
    assert(type && type->kind == TYPE_STRUCTURE);
    Structure structure = type->structure;
    assert(structure);
    if (name == NULL)return;
    if (structure->name != NULL) {
        // structure can't be renamed
        assert(false);
    }
    structure->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
    strcpy(structure->name, name);
}

bool equalFieldName(const char *name, VarDefNode field) {
    assert(field);
    return strcmp(name, field->name) == 0;
}

VarDefNode getFieldNamedOf(Type type, char *name) {
    assert(type->kind == TYPE_STRUCTURE && type->structure);
    ListNode node = getNode(type->structure->field_list,
                            name, (bool (*)(void *, void *)) equalFieldName);
    return node ? node->data : NULL;
}


bool addStructField(Type type, VarDefNode field) {
    assert(type && type->kind == TYPE_STRUCTURE && type->structure);
    assert(field);
    if (getFieldNamedOf(type, field->name))return false;
    type->width += field->type->width;
    pushTail(type->structure->field_list, newListNode(field));
    return true;
}

ArrayNode new_ArrayNode() {
    ArrayNode node = (ArrayNode) malloc(sizeof(struct ArrayNode_));
    node->elem_t = NULL;
    node->size = -1;
    return node;
}

void free_ArrayNode(ArrayNode node) {
    assert(node);
    free_Type(node->elem_t);
    free(node);
}

bool equalArray(ArrayNode array1, ArrayNode array2) {
    assert(array1 && array2);
    // no need to compare size
    if (equalType(array1->elem_t, array2->elem_t))
        return true;
    return false;
}

bool equalField(VarDefNode field1, VarDefNode field2) {
    assert(field1 && field2);
    return equalType(field1->type, field2->type);
}

bool equalStruct(Structure structure1, Structure structure2) {
    // in the normal completion, structure1 == structure2 as long as their names equal,
    // but in the advanced completion, fields should be arranged equally
    assert(structure1 && structure2);
    assert(structure1->field_list && structure2->field_list);
    return equalList(structure1->field_list, structure2->field_list, (bool (*)(void *, void *)) equalField);
}

Structure new_Structure() {
    Structure structure = (Structure) malloc(sizeof(struct Structure_));
    structure->name = NULL; // vital
    structure->field_list = new_list();
    return structure;
}

Structure copy_Structure(Structure src) {
    Structure dst = new_Structure();
    if (src->name) {
        dst->name = (char *) malloc((strlen(src->name) + 1) * sizeof(char));
        strcpy(dst->name, src->name);
    } else {
        dst->name = NULL;
    }
    dst->field_list = copy_list(src->field_list, (void *(*)(void *)) copy_VarDefNode);
    return dst;
}

void free_Structure(Structure structure) {
    assert(structure);
    if (structure->name != NULL)
        free(structure->name);
    // free field node along the list
    for (ListNode node = structure->field_list->leader->next;
         node != NULL; node = node->next) {
        assert(node->data);
        free_VarDefNode(node->data);
    }
    free_list(structure->field_list);
    free(structure);
}

VarDefNode new_VarDefNode(char *name, Type type, int line_no, bool initiated) {
    assert(name && type);
    VarDefNode node = (VarDefNode) malloc(sizeof(struct VarDefNode_));
    node->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
    strcpy(node->name, name);
    node->type = copy_Type(type);
    node->initiated = initiated;
    node->dec_line = line_no;
    return node;
}

VarDefNode copy_VarDefNode(VarDefNode src) {
    return new_VarDefNode(src->name, src->type, src->dec_line, src->initiated);
}

void free_VarDefNode(VarDefNode node) {
    assert(node);
    assert(node->name);
    free(node->name);
    assert(node->type);
    free_Type(node->type);
    free(node);
}