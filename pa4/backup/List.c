//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Structs --------------------------------------------------------
typedef struct NodeObj
{
    int data;
    struct NodeObj *next;
    struct NodeObj *previous;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj
{
    int length;
    int currentIndex;
    Node head;
    Node tail;
    Node cursor;
}ListObj;

// Constructors-Destructors ---------------------------------------------------
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->previous = NULL;
   return(N);
}

List newList(void) // Creates and returns a new empty List.
{
    List list = malloc(sizeof(ListObj));
    list->head = NULL;
    list->tail = NULL;
    list->cursor = NULL;
    list->length = 0;
    list->currentIndex = -1;
    return list;
}

void freeList(List* pL) // Frees all heap memory associated with *pL, and sets *pL to NULL.
{
    if(pL!=NULL && *pL!=NULL)
    {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

void freeNode(Node* pN) // Frees heap memory pointed to by *pN, sets *pN to NULL.
{
   if( pN!=NULL && *pN!=NULL )
    {
      free(*pN);
      *pN = NULL;
   }
}

// Access functions -----------------------------------------------------------
int length(List L) // Returns the number of elements in L.
{
    if(L == NULL)
    {
        printf("Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->length);
}

int index(List L) // Returns GetIndex of cursor element if defined, -1 otherwise.
{
    if(L == NULL)
    {
        printf("List Error: calling index() on NULL list reference\n");
        return -1;
    }

    return (L->currentIndex);
}

// make this function of type void *
int front(List L) // Returns front element of L. Pre: length()>0
{
    if(L->head == NULL)
    {
        printf("List is empty");
        exit(EXIT_FAILURE);
    }
    return L->head->data;
}

// make this function of type void *
int back(List L) // Returns back element of L. Pre: length()>0
{
    if(L == NULL)
    {
        printf("List is empty");
        exit(EXIT_FAILURE);
    }

    return L->tail->data;
}

// Returns cursor element of L. Pre: length()>0, GetIndex()>=0
int get(List L)
{
    if(length(L) > 0 && index(L) >= 0)
    {
        return (L->cursor->data);
    }
    else
    {
        printf("List Error: get() called on empty List\n");
        exit(EXIT_FAILURE);
    }
}

// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L)
{
    if(L == NULL)
    {
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    return(L->length == 0);
}

int equals(List A, List B) // Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise.
{
   int eq = 0;

   Node N;
   Node M;
   //List temp1 = A;
   //List temp2 = B;

   if(A==NULL || B==NULL)
   {
       printf("List Error: calling equals() on NULL List reference\n");
       exit(EXIT_FAILURE);
   }
   if(A->length != B->length)
   {
       return 0;
   }

   eq = (A->length == B->length);
   N = A->head;
   M = B->head;

   while(eq && N != NULL)
   {
       eq = (N->data == M->data);
       N = N->next;
       M = M->next;
   }
   return eq;
}

// Manipulation procedures ----------------------------------------------------

void clear(List L)// Resets L to its original empty state.
{
    if(L == NULL)
    {
        printf("List Error: calling clear() on null list referece\n");
        exit(EXIT_FAILURE);
    }

    if(L!=NULL)
    {
        while(L->length != 0)
        {
            deleteFront(L);
        }

 //        L->length = 0;
 //        L->cursor = NULL;
 //        L->currentIndex = -1;
 //        L = NULL;
	// // free(L);
    }
}

void moveFront(List L)// If L is non-empty, sets cursor under the front element, otherwise does nothing.
{
    if(L == NULL)
    {
        return;
    }

    if(L->length > 0)
    {
        L->cursor = L->head;
        L->currentIndex = 0;
    }
}

// SET CURSOR TO LAST ELEMENT
void moveBack(List L) // If L is non-empty, sets cursor under the back element, otherwise does nothing.
{
    if(L->length > 0)
    {
        L->cursor = L->tail;
        L->currentIndex = L->length - 1;
    }
}

 // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L)
{
    if(L->cursor != NULL && L->cursor != L->head)
    {
        L->cursor = L->cursor->previous;
        L->currentIndex--;
    }
    else if(L->cursor == L->head)
    {
        L->cursor = NULL;
        L->currentIndex = -1;
    }
    else if(L->cursor == NULL)
    {
        // printf("List Error: calling movePrev() on NULL list reference\n");
        // exit(EXIT_FAILURE);
    }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L)
{
    if (L->currentIndex == L->length - 1)
    {
        L->cursor = NULL;
        L->currentIndex = -1;
    }
    else
    {
        L->cursor = L->cursor->next;
        L->currentIndex++;
    }
}

// aka insert()
void prepend(List L, int data)// Insert new element into L. If L is non-empty, insertion takes place before front element.
{
    if(L == NULL)
    {
        printf("Error: prepend() called on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(data);

    if(L->length == 0)
    {
        L->tail = N;
        L->head = N;
    }
    else
    {
        L->head->previous = N;
        N->next = L->head;
        L->head = N;
    }

    L->length++;
    if(L->currentIndex >= 0)
    {
        L->currentIndex++;
    }
}

void append(List L, int data)// Insert new element into L. If L is non-empty, insertion takes place after back element.
{
    if(L == NULL)
    {
        printf("Error: append called on a NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(data);

    if(length(L) == 0)
    {
        L->tail = N;
        L->head = N;
    }
    else
    {
        L->tail->next = N;
        N->previous = L->tail;
        L->tail = N;
    }

    L->length++;
}

void insertBefore(List L, int data)// Insert new element before cursor. Pre: length()>0, GetIndex()>=0
{

    if(L == NULL)
    {
        printf("List error: insertBefore() called on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor == NULL)
    {
        printf("List error: insertBefore() called on a NULL cursor reference\n");
        exit(EXIT_FAILURE);
    }

        if(L->cursor == L->head) // if the cursor is on the head of the list
        {
           prepend(L, data); // make the data passed in the new head of the list
        }
        else // if the list is not null and we are not pointing to the head of the list
        {
            //// NEW
            Node N = newNode(data);
            N->next = L->cursor;
            N->previous = L->cursor->previous;
            L->cursor->previous->next = N;
            L->cursor->previous = N;
            L->length++;
            L->currentIndex++;
        }

}

void insertAfter(List L, int data)// Insert new element before cursor. Pre: length()>0, GetIndex()>=0
{
    //Node N = newNode(data);
    if(L==NULL)
    {
        printf("List error: insertAfter() called on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == NULL)
    {
        printf("List error: insertAfter() called on an empty list\n");
        exit(EXIT_FAILURE);
    }

        if(L->tail == L->cursor) // if cursor is pointing to the tail of the list
        {
            append(L, data); // make a new node and put it on the end of the list
        }
        else // if cursor is not pointing to the tail of the list
        {

        // NEW
            Node N = NULL;
            N = newNode(data);
            L->cursor->next->previous = N;
            N->previous = L->cursor;
            N->next = L->cursor->next;
            L->cursor->next = N;

            L->length++;
        }
}

void deleteFront(List L) // Delete the front element. Pre: length()>0
{
    Node N = NULL;

    /// If L is null
    if(L == NULL)
    {
        printf("List Error: calling deleteFront() on NULL List reference");
        exit(EXIT_FAILURE);
    }

    /// if list is empty
    if(length(L) == 0)
    {
        printf("List Error: calling deleteFront() on an empty list reference\n");
        exit(EXIT_FAILURE);
    }

    /// If there is only 1 node in L
    if(length(L) == 1)
    {
        N = L->head;
        L->head = NULL;
        L->tail = NULL;
        L->cursor = NULL;
        L->currentIndex = -1;
    }

    /// If length of L is greater than 1
    if(length(L)> 1)
    {
        N = L->head;

        /// but is pointing to the head of the list
        if(L->head == L->cursor)
        {
            L->cursor = NULL;

        }
            L->currentIndex--;
            L->head = L->head->next;
            L->head->previous = NULL;
    }

    freeNode(&N);
    L->length--;
}

void deleteBack(List L) // Delete the back element. Pre: length()>0
{
    Node N = NULL;

    if(L == NULL)
    {
        printf("List Error: calling deleteBack() on NULL List reference");
        exit(EXIT_FAILURE);
    }
    if(isEmpty(L))
    {
        printf("List Error: calling deleteBack() on an empty list\n");
        exit(EXIT_FAILURE);
    }

    N = L->tail;
    if(length(L)> 1)
    {
        if(L->tail == L->cursor)
        {
            L->cursor = NULL;
            L->currentIndex = -1;
        }

        L->tail = L->tail->previous;
        L->tail->next = NULL;
    }
    else
    {
        L->head = L->tail = NULL;
        L->cursor = NULL;
        L->currentIndex = -1;
    }
    L->length--;
    freeNode(&N);
}

void delete(List L) // Delete cursor element, making cursor undefined. Pre: length()>0, GetIndex()>=0
{
    //Node N = NULL;
    if(L == NULL)
    {
        printf("List Error: calling delete() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if(length(L) == 0)
    {
        printf("List Error: calling delete() on an empty list reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor == L->head)
    {
        deleteFront(L);
    }
    else if(L->cursor == L->tail)
    {
        deleteBack(L);
    }
    else
    {
         Node N = L->cursor;
         L->cursor->next->previous = L->cursor->previous;
         L->cursor->previous->next = L->cursor->next;
         L->currentIndex = -1;
         L->cursor = NULL;
         L->length--;
         freeNode(&N);
    }
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L)
{
    if(L == NULL)
    {
        fprintf(out, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    moveFront(L);
    while(index(L) != -1)
    {
        fprintf(out, "%d ", get(L));
        moveNext(L);
    }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L)
{
    List list = newList();
    Node N = L->head;

    while(N != NULL)
    {
        append(list, N->data);
        N = N->next;
    }
    return list;
}

// This function allows the client to change the long value
// at the cursor position without having to call
// insert() and delete(). Once these small changes are made,
// thoroughly test the new version of List
// with your own ListTest client.
void set(List L, int x)
{
    if(length(L) > 0 && index(L) >= 0)
    {
        // overwrites the cursor element with x.
        // Pre: length() > 0, index() >= 0
        L->cursor->data = x;
    }
}
