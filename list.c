#include "list.h"
/********************************************************************/
/* This function is allows for more concise code when creating list */
/* links. It allocates memory, checks for success then initialises  */
/* themembers of the new link structure.                            */
/********************************************************************/
static Link *CreateLink(void *data){
    Link *link = (Link*)malloc(sizeof(Link));
    if(link == NULL){
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    link->data = data;
    link->next = NULL;
    return link;
}

LinkedList *CreateLinkedList(){
    LinkedList *return_list = (LinkedList*)malloc(sizeof(LinkedList));
    if(return_list == NULL){
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    return_list->head = NULL;
    return_list->tail = NULL;
    return return_list;
}

void DestroyLinkedList(LinkedList *list){
    Link *link = list->head;
    while(link != NULL){
        Link *next = link->next;
        free(link);
        link = next;
    }
    free(list);
}

void PushData(LinkedList *list, void *data){
    if(list->head == NULL){
        list->head = CreateLink(data);
        list->tail = list->head;
    }
    else{
        list->tail->next = CreateLink(data);
        list->tail = list->tail->next;
    }
}

void PopData(LinkedList *list, void *data){
    Link *prev = NULL;
    Link *link = list->head;
    while(link->data != data){
        prev = link;
        link = link->next;
    }
    if(link == list->head){
        list->head = link->next;
    }else{
        prev->next = link->next;
    }
    if(link == list->tail){
        list->tail = prev;
    }
    free(link);
}
