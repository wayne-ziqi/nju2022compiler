#include "stack.h"
#include <stdlib.h>
#include <assert.h>

Stack new_stack() {
    Stack stack = (Stack) malloc(sizeof(struct Stack_));
    stack->list = new_list();
    stack->size = 0;
    return stack;
}

bool isEmptyStack(Stack stack) {
    return isEmptyList(stack->list);
}

void push(Stack stack, void *data) {
    assert(stack != NULL);
    assert(data != NULL);
    pushHead(stack->list, newListNode(data));
    stack->size++;
}

void *getTop(Stack stack) {
    assert(stack != NULL);
    ListNode node = getHeadNode(stack->list);
    return node == NULL ? NULL : node->data;
}

void *poll(Stack stack) {
    assert(stack != NULL);
    stack->size--;
    return pollHeadData(stack->list);
}

static inline bool comparePointers(void *p1, void *p2) {
    return p1 == p2;
}

void *getNext(Stack stack, void *data) {
    ListNode node = getNode(stack->list, data, comparePointers);
    if (node != NULL && node->next != NULL)
        return node->next->data;
    return NULL;
}

void free_stack(Stack stack) {
    if (stack == NULL) return;
    free_list(stack->list);
    free(stack);
}