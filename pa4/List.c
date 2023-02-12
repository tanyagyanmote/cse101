/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#4
* List.c 
* List ADT 
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
    void* data;
    Node next;
    Node prev; 
} NodeObj;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* data){
    Node N = malloc(sizeof(NodeObj));
    assert( N!=NULL );
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
      pN = NULL;
   }
}

List newList(void) {
    List L = malloc(sizeof(ListObj));
    assert(L!=NULL);
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->index = -1;
    L->length = 0;
    return(L);
}

void freeList(List* pL) {
    // puesdo
    // while (front) :
    // temp = front;
    // front = front->next;
    // free(temp)
    if (pL != NULL && *pL != NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

int length(List L) {
    //precondition
    if (L == NULL) {
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
}

int index(List L) {
    //precondition
    if (L == NULL) {
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->index);
}

void* front(List L){
    //preconditions
    if (L == NULL) {
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling front() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
}

void* back(List L){
    //preconditions
    if (L == NULL) {
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}

void* get(List L){
    //preconditions
    if (L == NULL) {
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) {
        fprintf(stderr, "List Error: calling get() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    return(L->cursor->data);
}


// Manipulation procedures ----------------------------------------------------qw
// Resets L to its original empty state.
void clear(List L){
    //preconditions
    if (L == NULL) {
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    //if list exsits start deleting
    while(length(L) > 0){
        deleteFront(L);
    }
    //set length to 0, and cursor as undefined
    L->length = 0;
    L->index = -1;
}
// Overwrites the cursor element’s data with x.
void set(List L, void* x) {
    //preconditions
    if (L == NULL) {
        fprintf(stderr, "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling set() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) {
        fprintf(stderr, "List Error: calling set() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    //preconditions
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    //if cursor is not at front, set it to the front, and index @ 0
    if (L->length != 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    //preconditions
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    //if cursor is not at front, set it to the front, and index @ the end
    if (L->length != 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }

}
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
    //precondition
    if (L == NULL) {
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) == -1) {
        return;
    }
    if(L->index == 0) {
        L->cursor = NULL;
        L->index = -1;
        return;
    }
    L->cursor = L->cursor->prev;
    L->index -= 1;
}
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    //precondition
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) == -1) {
        return;
    }
    if(L->index == (length(L)-1)) {
        L->cursor = NULL;
        L->index = -1;
        return;
    }
    L->cursor = L->cursor->next;
    L->index += 1;
}
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, void* x) {
    //precondition
    if (L == NULL) {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if(L->length == 0){
        L->front = N;
        L->back = N;
    }
    else{
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
    }
    if (L->index != -1) {
        L->index++;
    }
    L->length += 1;
}
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* x) {
    //precondition
    if (L == NULL) {
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    //if list is empty
    Node N = newNode(x);
    if(L->length ==0){
        L->front = N;
        L->back = N;
    }
    //if not empty
    else{
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length += 1;
}
// Insert new element before cursor.
// puesdo from oh: Arka Pal
void insertBefore(List L, void* x){
    //precondition
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling insertBefore() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) {
        fprintf(stderr, "List Error: calling insertBefore() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    if(L->index == 0){
        prepend(L,x);
    }
    else{
        Node new = newNode(x);
        L->cursor->prev->next = new;
        new->prev = L->cursor->prev;
        L->cursor->prev = new;
        new->next = L->cursor;
        L->index += 1;
        L->length += 1;
    }

}
// Insert new element after cursor.
// puesdo from oh: Arka Pal
void insertAfter(List L, void* x){
    //preconditions
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling insertAfter() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) {
        fprintf(stderr, "List Error: calling insertAfter() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    //condition if inserting at back
    if(L->index == length(L)-1){
        append(L,x);
    }
    else{
        Node new = newNode(x);
        L->cursor->next->prev = new;
        new->next = L->cursor->next;
        L->cursor->next = new;
        new->prev = L->cursor;
        L->length += 1;
    }

}
// Delete the front element
void deleteFront(List L) {
    //preconditions
    Node temp = NULL;
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling deleteFront() on empty List\n");
        exit(EXIT_FAILURE);
    }
    temp = L -> front;
    if (L->front == L->cursor) {
      L->index = -1;
    } else {
      L->index -= 1;
    }
    if(length(L)>1) { 
        L->front = L->front->next; 
    }else{ 
        L->front = L->back = NULL; 
    }
    L->length-=1;
    freeNode(&temp);

}
// Delete the back element
// puesdo given in oh: Sara, Arka
void deleteBack(List L) {
    //preconditions
    Node temp = NULL;
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling deleteFront() on empty List\n");
        exit(EXIT_FAILURE);
    }
    temp = L -> back -> prev;
    if (L->back == L->cursor) {
      L->index = -1;
      L->cursor = NULL;
    }
    if(length(L)>1) { 
        temp->next = NULL; 
        freeNode(&L->back);
        L->back = temp;
    }else{
        Node temp2 = L->back;
        L->back = L->back->prev; 
        L->front = NULL;
        L->back = NULL;
        freeNode(&temp2);
    }
    L->length-=1;

}
// puesdo given in oh: raj
// Delete cursor element, making cursor undefined.
void delete(List L) {
    //preconditions
    if (L == NULL) {
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling delete() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) {
        fprintf(stderr, "List Error: calling delete() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    //if cursor is at the front delete front
    //else if it's at the back delete back
    if (L->cursor == L->front) {
        deleteFront(L);
    } else if (L->cursor == L->back) {
        deleteBack(L);
    } else {
        Node temp = NULL;
        temp = L->cursor->prev; 
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = temp;
        freeNode(&L->cursor);
        //default
        L->cursor = NULL;
        L->length -= 1;
        L->index = -1;
    }
}

// Other operations -----------------------------------------------------------

void printList(FILE* out, List L){
    if (L == NULL){
        printf("List error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node temp = NULL;
    for(temp = L->front; temp != NULL; temp = temp->next){
        fprintf(out, "%p ", temp->data);
    }
}

// List copyList(List L){
//     if (L == NULL){
//         printf("List error: calling copyList() on NULL List reference\n");
//         exit(EXIT_FAILURE);
//     }
//     //creating new list, and temp node to store value from og list
//     List copy = newList();
//     Node temp = L ->front;
//     //if not null then theres more to copy
//     while (temp != NULL) {
//         //append the data, move to next element
//         append(copy, temp->data);
//         temp = temp->next;
//     }
//     return (copy);
// }
