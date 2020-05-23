//-----------------------------------------------------------------------------
// ListTest.c
// A test client for List ADT
//-----------------------------------------------------------------------------


#include "List.h"

int main()
{

	List A = newList();
	List B = newList();
	List C = newList();
	List D = newList();
	List E = newList();
	List F = newList();
	List G = newList();	
	List H = newList();	
	List I = newList();
	List J = newList();
	List K = newList();

	List empty = newList();

	// check length
	if(length(A) != 0)
	{
		return 0;
	}

	// check append
	append(A, 1);
	append(A, 2);
	append(A, 3);
	append(A, 4);

	if(length(A) != 4)
	{
		return 1;
	}

	//check prepend
	prepend(B, 6);
	prepend(B, 5);
	prepend(B, 4);
	prepend(B, 3);

	if(length(B) != 4)
	{
		return 2;
	}


	// check insert after
    append(C, 1);
    append(C, 2);
    append(C, 3);
    append(C, 5);
    moveFront(C);
    insertAfter(C, 12);

    if (length(C) != 5) 
    {
    	return 1;
    }


// check insert before
    prepend(D, 76);
    prepend(D, 4);
    prepend(D, 3);
    prepend(D 1);
    moveFront(D);
    insertBefore(D, 100);

    if (length(D) != 5) 
    {
    	return 1;
    }


    // check delete front
    prepend(E, 76);
    prepend(E, 4);
    deleteFront(E);
    prepend(E, 3);
    prepend(E, 1);
    moveFront(E);
    insertBefore(E, 100);
    deleteFront(E);

    if (length(E) != 3)
    {
    	return 1;
    }


    // check delete back
    append(F, 1);
    deleteBack(F);
    append(F, 2);
    append(F, 3);
    append(F, 5);
    moveFront(F);
    insertAfter(F, 12);
    deleteBack(F);
    if (length(F) != 3)
    {
    	return 1;
    } 


    // check delete length
    append(G, 1);
    append(G, 2);
    moveFront(G);
    delete(G);
    append(G, 3);
    append(G, 5);
    moveFront(G);
    insertAfter(G, 12);
    delete(G);

    if (length(G) != 3)
    {
     return 1;
    }

    // check empty list
    if(index(empty) != -1)
    {
    	return 1;
    }


// check move front
    append(H, 1);
    append(H, 5);
    append(H, 16);
    append(H, 176);
    append(H, 3214);
    moveFront(H);

    if (index(H) != 0) 
    {
    	return 1;
    }


//check move back
    append(I, 1);
    append(I, 5);
    append(I, 16);
    append(I, 176);
    append(I, 3214);
    moveBack(I);
    if (index(I) != 4)
    {

     return 1;
    }


    // check movenext index
    append(J, 1);
    append(J, 5);
    append(J, 16);
    append(J, 176);
    append(J, 3214);
    moveFront(J);
    moveNext(J);
    moveNext(J);
    if (index(J) != 2) 
    {
    	return 1;
    }

    moveNext(J);
    moveNext(J);
    moveNext(J);

    if (index(J) != -1) 
    {
    	return 2;
    }

	// check moveprev index      
	append(K, 1);
	append(K, 5);
	append(K, 3214);
	moveBack(K);
	movePrev(K);

	if (index(K) != 1)
	{
	 return 1;
	}

	movePrev(K);
	movePrev(K);

	if (index(K) != -1) 
	{
		return 2;
	}

	freeList(&A);
	freeList(&B);
	freeList(&C);
	freeList(&D);
	freeList(&E);
	freeList(&F);
	freeList(&G);
	freeList(&H);
	freeList(&I);
	freeList(&J);
	freeList(&K);
	freeList(&empty);


    return 0;
}
