#ifndef __QUEUE__
#define __QUEUE__

#include "list.h"

typedef struct Queue_ *Queue;

struct Queue_ {
    List list;
};

Queue new_Queue();

bool isEmptyQue(Queue queue);

void pushQue(Queue queue, void *data);

void *pollQue(Queue queue);

void free_Queue(Queue queue);

/**
 * add queue will use node in the list as part of itself
 * @param queue
 * @param list
 */
void addAllQue(Queue queue, List list);

#endif//__QUEUE__