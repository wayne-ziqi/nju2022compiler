#ifndef __QUEUE__
#define __QUEUE__

#include "list.h"

typedef struct Queue_ *Queue;

struct Queue_ {
    List list;
};

Queue new_Queue();

bool isEmptyQueue(Queue queue);

void pushQue(Queue queue, void *data);

void *pollQue(Queue queue);

void free_Queue(Queue queue);

#endif//__QUEUE__