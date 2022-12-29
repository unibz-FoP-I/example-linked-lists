#include <stdio.h>
#include <stdlib.h>
#include "lnkd_lists.h"

void lnkd_insert(LinkedList *llPtr, void *value, int (*comp)(const void *, const void *)) {
  struct listNode *newPtr = malloc(sizeof(struct listNode)); // create node

  if (newPtr != NULL) {     // is space available?
    newPtr->data = value;   // place value in node
    newPtr->nextPtr = NULL; // node does not link to another node

    struct listNode *previousPtr = NULL;
    struct listNode *currentPtr = llPtr->headPtr;

    // loop to find the correct location in the list
    while (currentPtr != NULL && comp(value, currentPtr->data) >= 0) {
      previousPtr = currentPtr;         // walk to ...
      currentPtr = currentPtr->nextPtr; // ... next node
    }

    // insert new node at beginning of list
    if (!previousPtr) {
      newPtr->nextPtr = llPtr->headPtr;
      llPtr->headPtr = newPtr;
    } else { // insert new node between previousPtr and currentPtr
      previousPtr->nextPtr = newPtr;
      newPtr->nextPtr = currentPtr;
    }
  } else {
    fputs("Object not inserted. No memory available.", stderr);
  }
}

void *lnkd_delete (LinkedList *llPtr, const void *value, int (*comp)(const void *, const void *)) {

  struct listNode *previousPtr = NULL;
  struct listNode *currentPtr = llPtr->headPtr;
  int is_different = 1;

  // loop to find the correct location in the list
  while (currentPtr != NULL) {
    if ((is_different = comp(value, currentPtr->data)) <= 0) break;
    previousPtr = currentPtr;         // walk to ...
    currentPtr = currentPtr->nextPtr; // ... next node
  }

  if (!currentPtr || is_different) {
    return 0;
  } else {
    struct listNode *tempPtr = currentPtr;
    if (previousPtr) {
      previousPtr->nextPtr = currentPtr->nextPtr;
    } else {
      llPtr->headPtr = currentPtr->nextPtr;
    }
    void *return_valuePtr = tempPtr->data;
    free(tempPtr);
    return return_valuePtr;
  }
}

void *lnkd_pop (LinkedList *llPtr) {
  if (lnkd_isEmpty(llPtr)) return 0;

  struct listNode *headPtr = llPtr->headPtr;
  void *head_valuePtr = headPtr->data;;
  llPtr->headPtr = headPtr->nextPtr;
  free(headPtr);
  return head_valuePtr;
}


int lnkd_isEmpty(LinkedList const *llPtr) { return !(llPtr->headPtr); }
