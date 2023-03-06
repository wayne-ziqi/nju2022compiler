#include "queue.h"
#include <stdlib.h>
#include <assert.h>

Queue new_Queue() {
    Queue queue = (Queue) malloc(sizeof(struct Queue_));
    queue->list = new_list();
    return queue;
}

bool isEmptyQue(Queue queue) {
    return isEmptyList(queue->list);
}

void pushQue(Queue queue, void *data) {
    assert(queue && data);
    pushTail(queue->list, newListNode(data));
}

void *pollQue(Queue queue) {
    assert(queue);
    return pollHeadData(queue->list);
}

void free_Queue(Queue queue) {
    free_list(queue->list);
    free(queue);
}

void addAllQue(Queue queue, List list) {
    concatList(queue->list, list);
}