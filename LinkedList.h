#ifndef LL_H
#define LL_H

/*for linked list nodes*/
typedef struct LLNode
{
    void *data;
    struct LLNode *next;
} LinkedListNode;

/*for head pointers*/
typedef struct 
{
    LinkedListNode *head;
    int count; /*stores the number of nodes created*/
} LinkedList;

typedef void (*listFunc)(void *data);

LinkedList *createLinkedList();
void insertStart(LinkedList* list, void* entry);
void* removeStart(LinkedList* list);
void printLinkedList(LinkedList *list, listFunc funcPtr);
void freeLinkedList(LinkedList *list, listFunc funcPtr);

#endif