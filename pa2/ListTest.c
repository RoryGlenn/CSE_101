

//        thoroughly test the new version of List with your own ListTest client.

#include "List.h"

int main()
{

    long lNum = 23426345;

    // thoroughly test the new version of List with your own ListTest client
    List L = newList();
    append(L, 5);
    moveFront(L);
    set(L, lNum);
    printf("%d", get(L));


}
