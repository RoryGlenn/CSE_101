// Created by Rory Glenn on 10/30/2019.

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

void addPreZeros(BigInteger A, int amount)
{
  int k;
  if(A->sign != 0)
  {
    for(k = 0; k < amount; k++)
    {
      prepend(A->listOfLongs, 0);
    }
  }
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

  return (N->sign);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{

  List listA = A->listOfLongs;
  List listB = B->listOfLongs;

  // check sign of A and B
  if(A->sign < B->sign)
  {
    puts("first");
    return -1;
  }
  else if(A->sign > B->sign)
  {
    return 1;
  }
  else if(A->sign == B->sign)
  {
    // positive sign check
    if(A->sign == 1 && B->sign == 1)
    {

      if(length(listA) > length(listB))
      {
        return 1;
      }
      else if(length(listA) < length(listB))
      {
        puts("second");
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
            return 1;
          }
          else if(get(listA) < get(listB))
          {
            puts("third");
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
        return -1;
      }
      else if(length(listA) < length(listB))
      {
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
            return 1;
          }
          else if(get(listA) < get(listB))
          {
            return -1;
          }

          moveNext(listA);
          moveNext(listB);
        }
      }
    }
  }
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
  BigInteger temp;
  List listS = S->listOfLongs;
  List listA = A->listOfLongs;
  List listB = B->listOfLongs;
  moveFront(listS);
  moveFront(listA);
  moveFront(listB);

  // If the signs are not the same
  if(A->sign != B->sign)
  {
    puts("Signs are not the same\n");
    if(sign(A) < sign(B))
    {
      negate(A);

      // A > B
      if(compare(A, B) == 1)
      {
        temp = diff(A, B);
        negate(temp);
        append(listS, get(temp->listOfLongs));
        S->sign = sign(temp);
      }
      // A < B
      else if(compare(A, B) == -1)
      {
        temp = diff(B, A);
        append(listS, get(temp->listOfLongs));
        S->sign = sign(temp);
      }
      // A = B
      else if(compare(A, B) == 0)
      {
        return S;
      }
    }
    else if(sign(A) > sign(B))
    {
      negate(B);
      // A > B
      if(compare(A, B) == 1)
      {
        // maybe this should be append(listS, get(diff(A, B)));

        temp = diff(A, B);
        append(listS, get(temp->listOfLongs));
        S->sign = sign(temp);
      }
      // A < B
      else if(compare(A, B) == -1)
      {
        temp = diff(B, A);
        negate(temp);
        append(listS, get(temp->listOfLongs));
        S->sign = sign(temp);
      }
      else if(compare(A, B) == 0)
      {
        //result = diff(A, B);
        // change sign to 0
        return S;
      }
    }

  }

  if(A->sign == B->sign)
  {


  // if the lists have the same length
  if(length(listA) == length(listB))
  {
    moveBack(listA);
    moveBack(listB);

    puts("list have the same length\n");
    int i = 0;
    while(i < length(listA))
    {

      prepend(listS, get(listA) + get(listB));
      movePrev(listA);
      movePrev(listB);
      i++;
    }

    if(A->sign == 1)
    {
      S->sign = 1;
    }
    else if(A->sign == -1)
    {
      S->sign = -1;
    }
    // if result is positive, change sign to pos
    // else if result is negative, change sign to negative
  }

  // if the lists we are trying to 
  // add have different lengths
  else if(length(listA) != length(listB))
  {
    if(length(listA) > length(listB))
    {
      int i = length(listA);
      moveBack(listA);
      moveBack(listB);

      // loop through the length of listA backwards putting
      // the values of listA + listB into listS from
      // smallest significance to largest significance
      while(i > 0)
      {
        prepend(listS, get(listA) + get(listB));
        movePrev(listA);
        movePrev(listB);

        // if we try to move to the prev node 
        // and we are equal to the first node
        // in the list then we can't move previous anymore
        if(index(listB) == 0)
        {
          // remember that we are on the last value in the smaller list
          // now we just need to add the get(listA) + get(listB) one
          // more time and then take the remaining values in ListA and 
          // put them directly into listS because there is nothing left to add
          prepend(listS, get(listA) + get(listB));

          int j = length(listA) - length(listB);
          while(j > 0)
          {
            // put the remaining values of listA into S
            prepend(listS, get(listA));
            movePrev(listA);
            j--;
          }

        }

        i--;

      }

    }

    else if(length(listA) < length(listB))
    {
      int i = length(listB);
      moveBack(listA);
      moveBack(listB);

      // loop through listA backwards
      while(i > 0)
      {
        prepend(listS, get(listA) + get(listB));

        // if we try to move to the prev node 
        // and we are equal to the first node
        // in the list then we can't move back anymore
        if(index(listA) == 0)
        {

          // remember that we are on the last value in the smaller list
          // now we just need to add the get(listA) + get(listB) one
          // more time and then take the remaining values in ListB and 
          // put them directly into listS because there is nothing left to add
          prepend(listS, get(listA) + get(listB));

          int j = length(listA) - length(listB);
          while(j > 0)
          {
            // put the remaining values of listA into S
            prepend(listS, get(listB));
            movePrev(listB);
            j--;
          }

          i--;

          } 
        }

     }

    }

  // moveFront(listA);
  // moveFront(listB);

  // while(index(S->listOfLongs))

  }
}



// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{

  BigInteger S = newBigInteger();
  BigInteger temp;
  List listS = S->listOfLongs;
  List listA = A->listOfLongs;
  List listB = B->listOfLongs;
  moveFront(listS);
  moveFront(listA);
  moveFront(listB);

  // If the signs are not the same
  if(A->sign != B->sign)
  {
    if(sign(A) < sign(B))
    {
      negate(A);

      // A > B
      if(compare(A, B) == 1)
      {
        temp = diff(A, B);
        negate(temp);
        append(listS, get(temp->listOfLongs));
      }
      // A < B
      else if(compare(A, B) == -1)
      {
        temp = diff(B, A);
        append(listS, get(temp->listOfLongs));
      }
      // A = B
      else if(compare(A, B) == 0)
      {
        return S;
      }
    }
    else if(sign(A) > sign(B))
    {
      negate(B);
      // A > B
      if(compare(A, B) == 1)
      {
        // maybe this should be append(listS, get(diff(A, B)));
        temp = diff(A, B);
        append(listS, get(temp->listOfLongs));
      }
      // A < B
      else if(compare(A, B) == -1)
      {
        temp = diff(B, A);
        negate(temp);
        append(listS, get(temp->listOfLongs));
      }
      else if(compare(A, B) == 0)
      {
        //result = diff(A, B);
        // change sign to 0
        return S;
      }
    }

  }

  if(length(listA) == length(listB))
  {
    int i = 0;
    while(i < length(listA))
    {
      append(listS, get(listA) + get(listB));
      moveNext(listA);
      moveNext(listB);
      i++;
    }
  }

  // if the lists we are trying to 
  // add have different lengths
  else if(length(listA) != length(listB))
  {
    if(length(listA) > length(listB))
    {
      int i = length(listA);
      moveBack(listA);
      moveBack(listB);

      // loop through the length of listA backwards putting
      // the values of listA + listB into listS from
      // smallest significance to largest significance
      while(i > 0)
      {
        prepend(listS, get(listA) + get(listB));
        movePrev(listA);
        movePrev(listB);

        // if we try to move to the prev node 
        // and we are equal to the first node
        // in the list then we can't move back anymore
        if(index(listB) == 0)
        {
          // remember that we are on the last value in the smaller list
          // now we just need to add the get(listA) + get(listB) one
          // more time and then take the remaining values in ListA and 
          // put them directly into listS because there is nothing left to add
          prepend(listS, get(listA) + get(listB));

          int j = length(listA) - length(listB);
          while(j > 0)
          {
            // put the remaining values of listA into S
            prepend(listS, get(listA));
            movePrev(listA);
            j--;
          }

        }

        i--;
      }

    }

    else if(length(listA) < length(listB))
    {
      int i = length(listB);
      moveBack(listA);
      moveBack(listB);

      // loop through listA backwards
      while(i > 0)
      {
        prepend(listS, get(listA) + get(listB));

        // if we try to move to the prev node 
        // and we are equal to the first node
        // in the list then we can't move back anymore
        if(index(listA) == 0)
        {

          // remember that we are on the last value in the smaller list
          // now we just need to add the get(listA) + get(listB) one
          // more time and then take the remaining values in ListB and 
          // put them directly into listS because there is nothing left to add
          prepend(listS, get(listA) + get(listB));

          int j = length(listB) - length(listA);
          while(j > 0)
          {
            // put the remaining values of listA into S
            prepend(listS, get(listB));
            movePrev(listB);
            j--;
          }

          i--;
        } 
      }

    }

  }
  return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
  List listD = D->listOfLongs;
  List listA = A->listOfLongs;
  List listB = B->listOfLongs;

  moveBack(listA);
  moveBack(listB);

  if(length(listA) == length(listB))
  {
    int i = length(listA);
    while(i > 0)
    {
      prepend(listD, get(listA) - get(listB));
      movePrev(listA);
      movePrev(listB);
      i--;
    }

  }
  // lists are not equals in length
  else if(length(listA) != length(listB))
  {
    // find out which list is bigger
    if(length(listA) > length(listB))
    {
      int i = length(listA);
      while(i > 0)
      {
        prepend(listD, get(listA) - get(listB));

        if(index(listB) == 0)
        {
          prepend(listD, get(listA) - get(listB));

          int j = length(listA) - length(listB);
          while(j > 0)
          {
            // put the remaining values of listA into D
            prepend(listD, get(listA));
            movePrev(listA);
            j--;
          }
        }

        i--;
      }
    }

    // find out which list is bigger
    if(length(listA) < length(listB))
    {
      int i = length(listB);

      while(i > 0)
      {
        prepend(listD, get(listA) - get(listB));

        if(index(listA) == 0)
        {
          prepend(listD, get(listA) - get(listB));

          int j = length(listB) - length(listA);
          while(j > 0)
          {
            prepend(listD, get(listB));
            movePrev(listB);
            j--;
          }
        }

        i--;
      }
    }

  }

}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
  BigInteger D = newBigInteger();

  List listD = D->listOfLongs;
  List listA = A->listOfLongs;
  List listB = B->listOfLongs;

  moveBack(listA);
  moveBack(listB);

  if(length(listA) == length(listB))
  {
    int i = length(listA);
    while(i > 0)
    {
      prepend(listD, get(listA) - get(listB));
      movePrev(listA);
      movePrev(listB);
      i--;
    }

  }
  // lists are not equals in length
  else if(length(listA) != length(listB))
  {
    // find out which list is bigger
    if(length(listA) > length(listB))
    {
      int i = length(listA);
      while(i > 0)
      {
        prepend(listD, get(listA) - get(listB));

        if(index(listB) == 0)
        {
          prepend(listD, get(listA) - get(listB));

          int j = length(listA) - length(listB);
          while(j > 0)
          {
            // put the remaining values of listA into D
            prepend(listD, get(listA));
            movePrev(listA);
            j--;
          }
        }

        i--;
      }
    }

    // find out which list is bigger
    if(length(listA) < length(listB))
    {
      int i = length(listB);

      while(i > 0)
      {
        prepend(listD, get(listA) - get(listB));

        if(index(listA) == 0)
        {
          prepend(listD, get(listA) - get(listB));

          int j = length(listB) - length(listA);
          while(j > 0)
          {
            prepend(listD, get(listB));
            movePrev(listB);
            j--;
          }
        }

        i--;
      }
    }

  }

  return D;

}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B);

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

  BigInteger C = newBigInteger();
  BigInteger temp = newBigInteger();
  List listA = A->listOfLongs;
  List listB = B->listOfLongs;
  List listC = C->listOfLongs;
  moveBack(listA);
  moveBack(listB);
  int size = length(listA) * length(listB);
  int countA = 0;
  int countB = 0;
  int carry = 0;
  int count = 0;
  long result = 0;

// iterative process
// multiply A * B
  while(index(listB) > -1)
  {
    moveBack(listA);
    countA = 0;
    carry = 0;

    while(index(listA) > -1)
    {
      result = get(listA) * get(listB) + carry % BASE;
      carry = get(listA) * get(listB) / BASE;
      result = result * Power(BASE, countA + countB);

      append(temp->listOfLongs, result);

      // appendZeroes function here
      addPreZeros(temp, count);

      add(C, C, temp);
      size--;
      countA++;
      count++;
      movePrev(listA);
    }

    movePrev(listB);
    countB++;

  }

  puts("\n");

  size = length(listA) * length(listB);
  int theSumOfEverything = 0;
  while(size > 0)
  {
    size--;
    theSumOfEverything += temp;
  }

  puts("\n");
  //append(listC, theSumOfEverything);

  // now we need to add all the values in the array together
  // but how do we add everything together without overflow?

  return C;

}


//// normalize()
// BigInteger normalize(BigInteger A)
// {
//     int sign = 0;
//     long q, r, u;
//     long carryIn, thisCol, carryOut= 0;

//     moveFront(L);
//     while(index(L))
//     {
//         carryIn = carryout;
//         thisCol = get(L);
//         thiscol+= carryIn;
//         q = thiscol/base;
//         r = thisCol%base;
//         u = (r < 0) ? 1 : 0;

//         thisCol = r + u*base;
//         carryout = q-u;
//         set(L, thisCOl);

//         if(index(L) == length(L)-1)
//         {
//             if(carryOut > 0)
//             {
//                 append(L, 0);
//             }
//             else if(carryout< 0)
//             {
//                 append(L, carryOut);
//                 break;
//             }
//         }
//         moveNext(L);
//     }

//     while(length(L) != 0 && back(L) == 0)
//     {
//         deleteBack(L);
//     }

//     if(length(L) != 0)
//     {
//         if(back(L) > 0)
//         {
//             sign = 1;
//         }
//         else if(back(L)<0)
//         {
//             sign = -1;
//             negateList(L);
//             normalize(L);
//         }
//     }
//     return sign;  
// }

// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
  List listN = N->listOfLongs;

  moveFront(listN);
  while(index(listN) != -1)
  {
    fprintf(out, "%ld", get(listN));

    moveNext(listN);
  }

}

