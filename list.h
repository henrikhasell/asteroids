/******************************************************/
/* This sub-system provides the resources needed to   */
/* abstract a linked list data type. It can be easily */
/* extended to represent queues and stacks.           */
/******************************************************/
#ifndef LIST_H
#define LIST_H

/**********************************/
/* Standard C library headers are */
/* included here. Include guards  */
/* ensure that appropriate        */
/* headers are included for both  */
/* C and C++ compilers.           */
/**********************************/
#ifdef __cplusplus
#   include <cstdlib>
#   include <cstdio>
#else
#   include <stdlib.h>
#   include <stdio.h>
#endif

/***************************************************/
/* This structure represents a link within a list. */
/* It is singly linked with the next link in the   */
/* list. A NULL link represents the end of a list. */
/***************************************************/
typedef struct Link{
    /**************************************************/
    /* This pointer represents the data pointed to    */
    /* by the link. It can be interpreted by being    */
    /* cast to the appropriate type.                  */
    /**************************************************/
    void *data;
    /*****************************************************/
    /* This pointer points to the next link in the list. */
    /* If the pointer is NULL, the list has ended.       */
    /*****************************************************/
    struct Link *next;
}Link;

/********************************************/
/* This structure represents a linked list. */
/* It contians a head and tail pointer to   */
/* it's members to allow for fast search    */
/* and insert operations.                   */
/********************************************/
typedef struct LinkedList{
    /* This pointer represents the head of the list. */
    Link *head;
    /* This pointer represents the tail of the list. */
    Link *tail;
}LinkedList;

/*********************************************/
/* Returns a pointer to an empty LinkedList. */
/* This method should allways be used to     */
/* create a linked list; it should never be  */
/* created manually.                         */
/*********************************************/
LinkedList *CreateLinkedList();

/****************************************************/
/* Frees memory associated with CreateLinkedList(). */
/* It is important to note this function does not   */
/* free the individual members of a linked list,    */
/* this should be done manually.                    */
/****************************************************/
void DestroyLinkedList(LinkedList *list);

/**********************************************************/
/* Adds a link to the list which points to the parameter. */
/**********************************************************/
void PushData(LinkedList *list, void *data);

/***************************************************************/
/* Removes a link from the list which points to the parameter. */
/***************************************************************/
void PopData(LinkedList *list, void *data);

#endif /* LIST_H */
