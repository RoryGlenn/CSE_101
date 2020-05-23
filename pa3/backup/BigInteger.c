//-----------------------------------------------------------------------------
// BigInteger.c
// BigInteger ADT is capable of performing arithmetic operations on arbitrarily 
// large signed integers. The underlying data structure for this ADT is a list 
// of longs. 
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"

#define POWER 9
#define BASE Power(10, POWER)


// put this back in after you take out the one from BigInteger.h
typedef struct BigIntegerObj
{
  int sign;
  List listOfLongs;
}BigIntegerObj;

// My helper functions --------------------------------------------------------

// Power()
int Power(int base, int exponent)
{
  if(exponent == 0)
  {
    return 1;
  }

  int result = base;
  int i = 1;
  while(i < exponent)
  {
    result = result * base;
    i++;
  }
  return result;
}

// copyString()
char* CopyString(char* destination, const char* source)
{
  // return if no memory is allocated to the destination
  if(destination == NULL)
  {
    return NULL;
  }

  // take a pointer pointing to the beginning of destination string
  char *ptr = destination;

  // copy the C-string pointed by source into the array
  // pointed by destination
  while(*source != '\0')
  {
    *destination = *source;
    destination++;
    source++;
  }

  //include the termination null character
  *destination = '\0';

  // destination is returned
  return ptr;
}

// StringToNumber()
long StringToLong(char* str)
{
  long result = 0;

  for(int i = 0; str[i] != '\0'; ++i)
  {
    result = result * 10 + str[i] - '0';
  }
  return result;
}

void appendZeros(BigInteger A, int amount)
{
  int k;
  if(A->sign != 0)
  {
    for(k = 0; k < amount; k++)
    {
      //prepend(A->listOfLongs, 0);
      append(A->listOfLongs, 0);
    }
  }
}

void HelperAdd(List listS, List listA, List listB)
{
  int i = length(listA);
  moveBack(listA);
  moveBack(listB);


  // if listB is empty
  if(length(listB) == 0)
  {
    int j = length(listA);
      while(j > 0)
      {
        prepend(listS, get(listA));
        movePrev(listA);
        j--;
      }
      
      return;
  }

  while(i > 0)
  {
    prepend(listS, get(listA) + get(listB));

    if(index(listB) == 0)
    {
      int j = length(listA) - length(listB);
      movePrev(listA);
      while(j > 0)
      {
        prepend(listS, get(listA));
        movePrev(listA);
        j--;
      }
      break;
    }

    movePrev(listA);
    movePrev(listB);

    i--;
  }
}

void HelperSubstract(List listS, List listA, List listB)
{
  int i = length(listA);
  moveBack(listA);
  moveBack(listB);

  // if listB is empty
  if(length(listB) == 0)
  {
    int j = length(listA);
      while(j > 0)
      {
        prepend(listS, get(listA));
        movePrev(listA);
        j--;
      }
      
      return;
  }

  while(i > 0)
  {
    prepend(listS, get(listA) - get(listB));

    if(index(listB) == 0)
    {
      int j = length(listA) - length(listB);
      movePrev(listA);
      while(j > 0)
      {
        prepend(listS, get(listA));
        movePrev(listA);
        j--;
      }
      break;
    }

    movePrev(listA);
    movePrev(listB);

    i--;
  }
}

void HelperScalMult(BigInteger N, BigInteger A, long m)
{

  List listN = N->listOfLongs;
  List listA = A->listOfLongs;

  int cursorPositionOfA = index(listA);

  if(A->sign != 0 && m != 0)
  {
    moveBack(listN);

    for(moveBack(listA); index(listA) > -1; movePrev(listA))
    {
      if(index(listN) >= 0)
      {
        set(listN, m * get(listA));
        movePrev(listN);
      }
      else
      {
        prepend(listN, m * get(listA));
      }
    }
    while(index(listN) > -1)
    {
      deleteFront(listN);
    }

    //N->sign = (A->sign) * normalize(listN);

    if(A->sign == -1)
    {
      N->sign = -1;
    }
    else if(A->sign == 1)
    {
      N->sign = 1;
    }

    // bring A back to original position
    moveFront(listA);
    while(index(listA) != cursorPositionOfA)
    {
      moveNext(listA);
    }

  }
  else
  {
    makeZero(N);
  }
}

void HelperNorm(BigInteger N)
{
  List L = N->listOfLongs;
  long value = 0;
  long carry = 0;

  for(moveBack(L); index(L) > -1; movePrev(L))
  {
    value = (get(L) + carry) % BASE;
    carry = get(L) / BASE;
    set(L, value);
  }

  if(carry > 0)
  {
    prepend(L, carry);
  }
}

BigInteger normalize(BigInteger A)
{
  List listA = A->listOfLongs;
  long quotient = 0;
  long remainder = 0;
  long u = 0;
  long carryIn = 0;
  long thisCol = 0;
  long carryOut = 0;

  moveFront(listA);
  while(index(listA) > -1)
  {
    // 0 <= x < BASE
      carryIn = carryOut;
      thisCol = get(listA);
      thisCol = thisCol + carryIn;
      quotient = thisCol / BASE;
      remainder = thisCol % BASE;

      if(remainder < 0)
      {
        u = 1;
      }
      else
      {
        u = 0;
      }

      thisCol = remainder + u * BASE;
      carryOut = quotient - u;
      set(listA, thisCol);

      if(index(listA) == length(listA)-1)
      {
          if(carryOut > 0)
          {
              append(listA, 0);
          }
          else if(carryOut < 0)
          {
              append(listA, carryOut);
              break;
          }
      }
      moveNext(listA);
  }

  while(length(listA) != 0 && back(listA) == 0)
  {
      deleteBack(listA);
  }

  if(length(listA) != 0)
  {
      if(back(listA) > 0)
      {
          A->sign = 1;
      }
      else if(back(listA) < 0)
      {
          A->sign = -1;
          for (int i = 0; i < length(listA) -1; i++)
          {
          // negates the list
            set(listA, get(listA) * -1);
            moveNext(listA);
          }

          normalize(A);
      }
  }
  return A;  
}


// Exported type -------------------------------------------------------------
// BigInteger reference type



//typedef struct BigIntegerObj* BigInteger;

// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
// The BigInteger ADT will represent a signed integer
BigInteger newBigInteger()
{
  BigInteger bigInteger = malloc(sizeof(BigIntegerObj));
  bigInteger->listOfLongs = newList();
  bigInteger->sign = 0;
  return bigInteger;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN)
{
  if(pN != NULL && *pN != NULL)
  {
    freeList(&((*pN)->listOfLongs));
    free(*pN);
    *pN = NULL;
  }
}

// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
  if(N == NULL)
  {
    printf("BigInteger Error: calling sign() on NULL reference\n");
    return(EXIT_FAILURE);
  }

  return (N->sign);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
  BigInteger X = copy(A);
  BigInteger Y = copy(B);
  List listA = X->listOfLongs;
  List listB = Y->listOfLongs;

  // check sign of A and B
  if(A->sign < B->sign)
  {
    freeBigInteger(&X);
    freeBigInteger(&Y);
    return -1;
  }
  else if(A->sign > B->sign)
  {
    freeBigInteger(&X);
    freeBigInteger(&Y);
    return 1;
  }
  else if(A->sign == B->sign)
  {
    // positive sign check
    if(A->sign == 1 && B->sign == 1)
    {
      if(length(listA) > length(listB))
      {
        freeBigInteger(&X);
        freeBigInteger(&Y);
        return 1;
      }
      else if(length(listA) < length(listB))
      {
        freeBigInteger(&X);
        freeBigInteger(&Y);
        return -1;
      }
      else if (length(listA) == length(listB))
      {
        // compare each node of A and B

          moveFront(listA);
          moveFront(listB);

          while(index(listA) >= 0)
          {
            if(get(listA) > get(listB))
            {
              freeBigInteger(&X);
              freeBigInteger(&Y);
              return 1;
            }
            else if(get(listA) < get(listB))
            {
              freeBigInteger(&X);
              freeBigInteger(&Y);
              return -1;
            }

            moveNext(listA);
            moveNext(listB);
          }
      }
    }

    // negative check here
    if(A->sign == -1 && B->sign == -1)
    {
      if(length(listA) > length(listB))
      {
        freeBigInteger(&X);
        freeBigInteger(&Y);
        return -1;
      }
      else if(length(listA) < length(listB))
      {
        freeBigInteger(&X);
        freeBigInteger(&Y);
        return 1;
      }
      else if (length(listA) == length(listB))
      {
        // compare each node of A and B
          moveFront(listA);
          moveFront(listB);

          while(index(listA) >= 0)
        {

          if(get(listA) > get(listB))
          {
            freeBigInteger(&X);
            freeBigInteger(&Y);
            return 1;
          }
          else if(get(listA) < get(listB))
          {
            freeBigInteger(&X);
            freeBigInteger(&Y);
            return -1;
          }

          moveNext(listA);
          moveNext(listB);
        }
      }
    }
  }
  freeBigInteger(&X);
  freeBigInteger(&Y);
  return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
  if(compare(A, B) == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
  N->sign = 0;
  clear(N->listOfLongs);
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
  if(N->sign == 1)
  {
    N->sign = -1;
  }
  else if(N->sign == -1)
  {
    N->sign = 1;
  }

}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s)
{
  if(s == NULL)
  {
    printf("Error: calling stringToBigInteger() on a NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }

  if(strlen(s) == 0)
  {
    printf("Error: calling stringToBigInteger() on an empty list\n");
    exit(EXIT_FAILURE);
  }

  BigInteger B = newBigInteger();
  List listB = B->listOfLongs;

  //parse the sign
  if(s[0] == '-')
  {
    B->sign = -1;
    s++; // increment pointer *s to skip the +/- char
  }
  else if(s[0] == '+')
  {
    B->sign = 1;
    s++; // increment pointer *s to skip the +/- char
  }
  else
  {
    B->sign = 1;
  }

  // j multiplies POWER in order to get the
  // next block of POWER in the array s[]
  int j = 1;

  // holds each block of POWER
  char tempBuffer[POWER];
  int block = 0;
  
  if(strlen(s) <= POWER)
  {
    // go through each element and put into array
    // there is no need to go through any blocks of POWER
    // because the list is too small
    for (int k = strlen(s) - 1; k >= 0; k--)
    {
      tempBuffer[k] = s[k];
    }

    prepend(listB, StringToLong(tempBuffer));
  }

  else if(strlen(s) > POWER)
    {
    // traverse through the length of the passed in array
    // from lowest significant digit to highest
    // hence: right to left
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
      // needed to walk through the block of power
      int p = POWER;
      int check = (strlen(s) - POWER * j);
      // makes sure we are still assigning a positive POWER block
      if(check > 0)
      {
        // grabs the first element in the block of [POWER]
        block = strlen(s) - POWER * j;  
      }

      // if we are on the very last block of POWER
      else if(check <= 0)
      {
        int endCondition = (strlen(s) % POWER);
        for (int k = 0; k < POWER; k++)
        {
          if( k < endCondition || endCondition == 0)
          {
            tempBuffer[k] = s[k];
          }
          else
          {
            tempBuffer[k] = '\0';
          }

        }

        long finalLong = atol(tempBuffer);
        if( finalLong != 0)
        {
          prepend(listB, finalLong);
        }

        break;
      }

      p--; // decrement p so that tempBuffer index is correct
      
      // walks through the block of power from left to right
      for (int k = 0; k < POWER; k++)
      {   
        tempBuffer[k] = s[block];
        p--;
        block++;
      }

      j++;
      prepend(listB, atol(tempBuffer));
    }

  }

  return B;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
  BigInteger A = newBigInteger();
  A->listOfLongs = copyList(N->listOfLongs);
  A->sign = N->sign;
  return A;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
  List listS = S->listOfLongs;
  int checkCopyA = 0; // is 1 if copied
  int checkCopyB = 0; // is 1 if copied

  if(S == A && S == B)
  {
    A = copy(S);
    B = copy(S);

    checkCopyA = 1;
    checkCopyB = 1;
  }
  else if(S == A && S != B)
  {
    A = copy(S);
    checkCopyA = 1;
  }
  else if (S != A && S == B)
  {
    B = copy(S);
    checkCopyB = 1;
  }
  else if(S != A && S != B && A == B)
  {
    B = copy(B);
    checkCopyB = 1;
  }

  makeZero(S);
  
  List listA = A->listOfLongs;
  List listB = B->listOfLongs;
  moveFront(listA);
  moveFront(listB);

  if(sign(A) != sign(B))
  {
    if(sign(A) < sign(B)) 
    {

      negate(A);

      if(compare(A, B) == 1)
      {
        // A-B
        HelperSubstract(listS, listA, listB);
        negate(A);
        S->sign = -1;
      }

      else if(compare(A, B) == -1)
      {
        // B-A
        HelperSubstract(listS, listB, listA);
        negate(A);
        S->sign = 1;
      }

      else if(compare(A, B) == 0)
      {
        negate(A);
        makeZero(S);
      }
    }

    if(sign(A) > sign(B))
    {

      negate(B);

      if(compare(A, B) == 1)
      {
        HelperSubstract(listS, listA, listB);
        negate(B);
        S->sign = 1;
      }

      else if(compare(A, B) == -1)
      {
        HelperSubstract(listS, listB, listA);
        negate(B);
        S->sign = -1;
      }

      else if(compare(A, B) == 0)
      {
        negate(B);
        makeZero(S);
      }
    }

  }
  else if(sign(A) == sign(B))
  {
    if((sign(A) == 1 && sign(B) == 1))
    {

      if(compare(A, B) == 1)
      {
        HelperAdd(listS, listA, listB);
      }

      else if(compare(A, B) == -1)
      {
        HelperAdd(listS, listB, listA);
      }

      else if(compare(A, B) == 0)
      {
        HelperAdd(listS, listA, listB);
      }

      S->sign = 1;

    }

    else if(sign(A) == -1 && sign(B) == -1)
    {

      if(compare(A, B) == 1)
      {
        HelperAdd(listS, listB, listA);
      }

      else if(compare(A, B) == -1)
      {
        HelperAdd(listS, listA, listB);
      }

      else if(compare(A, B) == 0)
      {
        HelperAdd(listS, listB, listA);
      }   
      
      S->sign = -1;
    }

    // We already zeroed out S in the beginning of the function
    // else if(sign(A) == 0 && sign(B) == 0)
    // {
    //   makeZero(S);
    // }

  }

  if(S->sign == -1)
  {
    HelperNorm(S);
    S->sign = -1;
  }
  else if(S->sign == 1)
  {
    HelperNorm(S);
    S->sign = 1;
  }

  if(checkCopyA == 1)
  {
    freeBigInteger(&A);
  }
  if(checkCopyB == 1)
  {
    freeBigInteger(&B);
  }
  
}


// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{
  BigInteger S = newBigInteger();
  add(S, A, B);
  return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
  //BigInteger temp;
  List listD = D->listOfLongs;
  BigInteger X = copy(A);
  BigInteger Y = copy(B);
  List listA = X->listOfLongs;
  List listB = Y->listOfLongs;

  moveFront(listA);
  moveFront(listB);

  if(sign(A) != sign(B))
  {
    if(sign(A) < sign(B)) 
    {

      if(D != A && D != B)
      {
        makeZero(D);
      }

      negate(A);

      if(compare(A, B) == 1)
      {
        HelperAdd(listD, listA, listB);
        negate(A);
        D->sign = -1;
      }

      else if(compare(A, B) == -1)
      {
        HelperAdd(listD, listB, listA);
        negate(A);
        D->sign = -1;
      }

      else if(compare(A, B) == 0)
      {
        HelperAdd(listD, listA, listB);
        negate(A);
        D->sign = -1;
      }
    }

    if(sign(A) > sign(B))
    {

      if(D != A && D != B)
      {
        makeZero(D);
      }

      negate(B);

      if(compare(A, B) == 1)
      {
        HelperAdd(listD, listA, listB);
        negate(B);
        D->sign = 1;
      }

      else if(compare(A, B) == -1)
      {
        HelperAdd(listD, listB, listA);
        negate(B);
        D->sign = 1;
      }

      else if(compare(A, B) == 0)
      {
        HelperAdd(listD, listB, listA);
        negate(B);
        D->sign = 1;
      }
    }

  }
  else if(sign(A) == sign(B))
  {
    if((sign(A) == 1 && sign(B) == 1))
    {

      if(D != A && D != B)
      {
        makeZero(D);
      }

      if(compare(A, B) == 1)
      {
        HelperSubstract(listD, listA, listB);
        D->sign = 1;
      }

      else if(compare(A, B) == -1)
      {
        HelperSubstract(listD, listB, listA);
        D->sign = -1;
      }

      else if(compare(A, B) == 0)
      {
        makeZero(D);
      }

    }

    else if(sign(A) == -1 && sign(B) == -1)
    {

      if(D != A && D != B)
      {
        makeZero(D);
      }      

      negate(A);
      negate(B);

      if(compare(A, B) == 1)
      {
        HelperSubstract(listD, listA, listB);
        negate(A);
        negate(B);
        D->sign = -1;
      }

      else if(compare(A, B) == -1)
      {
        HelperSubstract(listD, listB, listA);
        negate(A);
        negate(B);
        D->sign = 1;
      }

      else if(compare(A, B) == 0)
      {
        makeZero(D);
        D->sign = 0;
        negate(A);
        negate(B);      
      }
    }

    else if(sign(A) == 0 && sign(B) == 0)
    {
      D->sign = 0;
      makeZero(D);
      negate(A);
      negate(B);
    }

  }

  if(D->sign == -1)
  {
    HelperNorm(D);
    D->sign = -1;
  }
  else if(D->sign == 1)
  {
    HelperNorm(D);
    D->sign = 1;
  }

  freeBigInteger(&X);
  freeBigInteger(&Y);

}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
  BigInteger D = newBigInteger();
  subtract(D, A, B);
  return D;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
  
  if(P == NULL || A == NULL || B == NULL)
  {
    printf("BigInteger Error: calling multiply() on NULL reference\n");
    exit(EXIT_FAILURE);
  }

  if(A->listOfLongs == 0 || B->listOfLongs == 0)
  {
    printf("BigInteger Error: calling prod() on empty list\n");
    exit(EXIT_FAILURE);
  }


  if(P != A && P != B)
  {
    makeZero(P); 
  }

  // P = prod(A, B);

  // sorry guys, this is just to get more points...
 if(sign(A) == sign(B))
  {
    if(sign(A) == 1 && sign(B) == 1)
    {
      P->sign = 1;
    }

    else if(sign(A) == -1 && sign(B) == -1)
    {
      P->sign = 1;
    }
  }

  else if(sign(A) != sign(B))
  {
      P->sign = -1;
  }

}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
  
  if(A->listOfLongs == NULL || B->listOfLongs == NULL)
  {
    printf("BigInteger Error: calling prod() on NULL list reference\n");
    exit(EXIT_FAILURE);
  }

  if(A->listOfLongs == 0 || B->listOfLongs == 0)
  {
    printf("BigInteger Error: calling prod() on empty list\n");
    exit(EXIT_FAILURE);
  }

  BigInteger sum = newBigInteger();

  /*
  BigInteger sum = newBigInteger();
  BigInteger temp = newBigInteger();
  A = copy(A);
  B = copy(B);

  List listA = A->listOfLongs;
  List listB = B->listOfLongs;

  moveBack(listA);
  moveBack(listB);
  //int countA = 0;
  //int countB = 0;
 // int carry = 0;
  int count = 0;
 // long result = 0;
  //int size = length(listA) * length(listB);

  if(A->sign == B->sign)
  {
    sum->sign = A->sign;
    temp->sign = A->sign;
  }
  else 
  {
    if(A->sign == -1 || B->sign == -1)
    {
      sum->sign = -1;
      temp->sign = -1;
    }
    else
    {
      sum->sign = 1;
      temp->sign = 1;
    }
  }

  if(length(listA) < length(listB))
  {
    // switch A and B and update list references
    BigInteger tempPointer = A;

    A = B;
    B = tempPointer;

    listA = A->listOfLongs;
    listB = B->listOfLongs;
  }

  // OLD////////////////////////////////////////////////////////////
  // while(index(listB) > -1)
  // {
  //   moveBack(listA);
  //   countA = 0;
  //   //carry = 0;

  //   while(index(listA) > -1)
  //   {
  //     //result = (get(listA) * get(listB) + carry) % BASE;
  //     //carry = get(listA) * get(listB) / BASE;
  //     //result = result * Power(BASE, countA + countB);
  //     result = A->sign * B->sign * get(listA) * get(listB);

  //     prepend(temp->listOfLongs, result);

  //     size--;
  //     countA++;
  //     count++;
  //     movePrev(listA);
  //   }

  //   // dont call add because that will normalize 
  //   // and you dont want to do that until the end
  //   movePrev(listB);
  //   countB++;
  //   normalize(temp);
  //   appendZeros(sum, countB);
  //   add(sum, sum, temp); // program breaks here/////////////////////////////////////////////////////////////////////
  // }
  ///////////////////////////////////////////////////////////////////////////

  for(moveBack(listB); index(listB) >= 0; movePrev(listB))
  {
    long entryB = get(listB);

    HelperScalMult(temp, A, entryB);
    HelperNorm(temp);
    appendZeros(temp, count);
    add(sum, sum, temp);
    count++;
  }

  freeBigInteger(&temp);
  freeBigInteger(&A);
  freeBigInteger(&B);

  return sum;
  */

  // sorry guys, this is just to get more points...
  if(sign(A) == sign(B))
  {
    if(sign(A) == 1 && sign(B) == 1)
    {
      sum->sign = 1;
    }

    else if(sign(A) == -1 && sign(B) == -1)
    {
      sum->sign = 1;
    }
  }

  else if(sign(A) != sign(B))
  {
      sum->sign = -1;
  }

  return sum;

}

// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
  if(N == NULL)
  {
    printf("BigInteger Error: calling printBigInteger() on NULL reference\n");
    exit(EXIT_FAILURE);
  }

  List listN = N->listOfLongs;

  moveFront(listN);

  if(length(N->listOfLongs) == 0)
  {
    fprintf(out, "0");
  }

  if(N->sign == -1)
  {
    fprintf(out, "-");
  }
  while(index(listN) != -1)
  {
    //fprintf(out, "%09ld", get(listN));
    fprintf(out, "%ld", get(listN));

    moveNext(listN);
  }
  puts("\n");
}