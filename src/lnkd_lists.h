#ifndef LNKD_LISTS_H
#define LNKD_LISTS_H

struct listNode {
  void *data;
  struct listNode *nextPtr;
};

typedef struct {
  struct listNode *headPtr;
} LinkedList;

void lnkd_insert(LinkedList *llPtr, void *value, int (*comp)(const void *, const void *));
void *lnkd_delete (LinkedList *llPtr, const void *value, int (*comp)(const void *, const void *));
void *lnkd_pop (LinkedList *llPtr);
int lnkd_isEmpty(LinkedList const *llPtr);

#define lnkd_ForEach(element, list) for(struct listNode *_lnkd_node = (list)->headPtr; _lnkd_node; _lnkd_node = _lnkd_node->nextPtr) if ((el = _lnkd_node->data))

#endif