/*
* Name: Angelique Emily Lau En Xian
* File name: linkedlist.c
* Last MOD: 3 October 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

LinkedList *createLinkedList() /*LinkedList here is the datatype.*/
{
    /*creating and initialising the linked list*/
    LinkedList *LL = NULL;
    LL = (LinkedList *)malloc(sizeof(LinkedList));
    LL->head = NULL;
    LL->count = 0;

    /*returning LL which has the datatype of LinkedList. Will return 
    to LL in the main function*/
    return LL; 
}

/*insert new entry at the front of the linked list*/
void insertStart(LinkedList *list, void *entry)
{
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = entry; /*newNode's data points to the new entry data*/
    newNode->next = list->head; /*newNode's next points to where list's head is pointed to*/
    list->head = newNode; /*make the list's head point to the newNode since its insertFirst*/
    list->count++;
}

/*remove new entry at the front of the linked list*/
/*this function returns void pointer*/
void* removeStart(LinkedList* list)
{
    void *data = NULL;
    /*firstNode points to where list's head is pointing which is the node at the 
    front of the linked list*/
    LinkedListNode *firstNode = list->head; 
    if(firstNode != NULL)
    {
        data = firstNode->data; /*data points to the firstNode's data*/
        /*make list's head point to the firstNode's next (which will be the new first 
        node in the linked list after the original first node is deleted)*/
        list->head = firstNode->next; 
        free(firstNode);
        list->count--;
    }
    return data;
}

/*insertLast and removeLast is not used to complete this assignment*/

/*to print out the whole linked list*/
void printLinkedList(LinkedList *list, listFunc funcPtr)
{
    LinkedListNode *curr = list->head;
    while(curr != NULL)
    {
        /*following the example above, (*funcPtr) will be pointing to printResult() in main.c, 
        which then prints out the linked list*/
        (*funcPtr)(curr->data); /*calling the print result function*/
        curr = curr->next;
    }
}

/*function to free the dynamically allocated memory*/
void freeLinkedList(LinkedList *list, listFunc funcPtr)
{
    LinkedListNode *curr = list->head;
    LinkedListNode *nextNode = NULL;
    while(curr != NULL)
    {
        nextNode = curr->next;
        /*-free data pointer
        - (*funcPtr) here will be pointing to freeNode() in the main.c*/
        (*funcPtr)(curr->data);
        free(curr);
        curr = nextNode;
    }
    free(list);
}