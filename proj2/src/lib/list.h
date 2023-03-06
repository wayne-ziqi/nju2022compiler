#ifndef __LIST__
#define __LIST__

#include "stdbool.h"

typedef struct ListNode_ *ListNode;
typedef struct List_ *List;

struct ListNode_ {
    /* data */
    void *data;
    ListNode prev;
    ListNode next;
};

struct List_ {
    /* data */
    int size;
    ListNode leader;
    ListNode tail;
};

/**
 * @brief create an empty list with a leader node, an leader node's data is null
 *
 * @return List* empty list
 */
List new_list();

/**
 * @param list
 * @return true if list is empty
 * @return false list has valid data
 */
bool isEmptyList(List list);

/**
 * deep copy using copy function of the data;
 * @param src
 * @param copy_data
 * @return
 */
List copy_list(List src, void*(*copy_data)(void *src));

/**
 * destructor of list
 * @param list
 */
void free_list(List list);

/**
 * @brief return a new list node filled with data
 * , should molloc the data before calling
 * @param data
 * @return LNode*
 */
ListNode newListNode(void *data);

/**
 * @brief intsert data into head, should create a new node before calling
 *
 * @param node
 */
void pushHead(List list, ListNode node);

/**
 * push the node to the tail
 * @param list
 * @param node
 */
void pushTail(List list, ListNode node);

/**
 * @brief get the first valid data node in the list and
 * remove it from the list
 *
 * @param list
 * @return void* valid data if not empty else null
 */
void *pollHeadData(List list);

/**
 *
 * @param list
 * @return first node with valid data
 */
ListNode getHeadNode(List list);

/**
 *
 * @param list
 * @return tail node with valid data
 */
ListNode getTailNode(List list);

/**
 * locate the first node in the list with data using function compare
 *
 * @param list
 * @param searchKey the key of compare function, i.g. node.data satisfies the key
 * under condition of compare
 * @param compare
 * @return ListNode
 */
ListNode getNode(List list, void *searchKey, bool (*compare)(void *, void *));

ListNode getNextNode(ListNode curr);
/**
 * judge whether the given lists are equal using data equivalence rule
 */
bool equalList(List list1, List list2, bool (*equalData)(void *, void *));

/**
 * free node manually
 * @param node
 */
void freeNode(ListNode node);

#endif