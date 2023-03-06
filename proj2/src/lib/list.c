#include "list.h"
#include <stdlib.h>
#include <assert.h>

// implementation of list api
List new_list() {
    List list = (List) malloc(sizeof(struct List_));
    list->leader = newListNode(NULL);
    list->tail = list->leader;
    list->size = 0;
    return list;
}

bool isEmptyList(List list) {
    return list->leader->next == NULL;
}

List copy_list(List src, void *(*copy_data)(void *src)) {
    List dst = new_list();
    for (ListNode srcNode = getHeadNode(src); srcNode != NULL; srcNode = getNextNode(srcNode)) {
        pushTail(dst, newListNode(copy_data(srcNode->data)));
    }
    return dst;
}

void free_list(List list) {
    if (list == NULL) return;
    ListNode curr = list->leader;
    while (curr != NULL) {
        ListNode next = curr->next;
        freeNode(curr);
        curr = next;
    }
    free(list);
}

// implementation of list node api

ListNode newListNode(void *data) {
    ListNode node = (ListNode) malloc(sizeof(struct ListNode_));
    node->data = data;
    node->next = node->prev = NULL;
    return node;
}

void pushHead(List list, ListNode node) {
    // list and node should not be NULL
    assert(list != NULL && node != NULL);
    ListNode first = list->leader->next;
    node->next = first;
    node->prev = list->leader;
    list->leader->next = node;
    list->size++;
}

void pushTail(List list, ListNode node) {
    assert(list != NULL && node != NULL);
    assert(list->tail);
    node->next = NULL;
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
    list->size++;
}

void *pollHeadData(List list) {
    assert(list != NULL);
    if (isEmptyList(list))return NULL;
    ListNode node = list->leader->next;
    list->leader->next = node->next;
    if (list->tail == node) list->tail = list->leader;
    void *data = node->data;
    free(node);
    list->size--;
    assert(data != NULL);
    return data;
}

ListNode getHeadNode(List list) {
    assert(list != NULL);
    if (isEmptyList(list))return NULL;
    return list->leader->next;
}

ListNode getTailNode(List list) {
    assert(list);
    if (isEmptyList(list)) return NULL;
    return list->tail;
}

ListNode getNode(List list, void *searchKey, bool (*compare)(void *, void *)) {
    assert(list != NULL);
    if (isEmptyList(list))return NULL;
    for (ListNode node = list->leader->next; node != NULL; node = node->next) {
        assert(node->data != NULL);
        if (compare(searchKey, node->data)) return node;
    }
    return NULL;
}

ListNode getNextNode(ListNode curr) {
    assert(curr);
    return curr->next;
}

bool equalList(List list1, List list2, bool (*equalData)(void *, void *)) {
    assert(list1 && list2);
    if (isEmptyList(list1) && isEmptyList(list2))return true;
    ListNode p1 = list1->leader->next, p2 = list2->leader->next;
    for (; p1 && p2; p1 = p1->next, p2 = p2->next) {
        if (!equalData(p1->data, p2->data))return false;
    }
    if (!p1 && !p2) return true;
    return false;
}

void freeNode(ListNode node) {
    if (node == NULL) return;
//    if (node->data != NULL) free(node->data);
    free(node);
}


