#ifndef __STACK__
#define __STACK__

#include "list.h"

typedef struct Stack_ *Stack;

struct Stack_ {
    unsigned int size;
    List list;
};

/**
 * @return empty stack
 */
Stack new_stack();

/**
 *
 * @param stack
 * @return true if stack is empty
 */
bool isEmptyStack(Stack stack);

/**
 * push data into stack
 * @param stack
 * @param data
 */
void push(Stack stack, void *data);

/**
 * get the top data of stack
 * @param stack
 * @return
 */
void *getTop(Stack stack);

/**
 * get the top data of stack and then pop it
 * @param stack
 * @return data
 */
void *poll(Stack stack);

/**
 * Attention, data should be the one returned originally from the stack, i.g. two data that hold the same value but
 * point to different addresses are treated as different ones, use 'curr = getNext(stack, curr);' to iterate the stack
 * @param stack
 * @param data current data
 * @return the next data in the stack, i.g. beneath the stack entry of data. if the data is the bottom, then return null
 */
void *getNext(Stack stack, void *data);

/**
 * destructor of the stack
 * @param stack
 */
void free_stack(Stack stack);

#endif