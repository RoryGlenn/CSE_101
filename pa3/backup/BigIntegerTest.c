//-----------------------------------------------------------------------------
// BigIntegerTest.c
// Used for testing the exported functions of BigInteger.c
//-----------------------------------------------------------------------------


#include "BigInteger.h"

int main()
{
	BigInteger A = newBigInteger();
	BigInteger B = newBigInteger();
	BigInteger C = newBigInteger();
	BigInteger D = newBigInteger();


	A = stringToBigInteger("+12345");

	// check sign()
	if(sign(A) != 1)
	{
		return 1;
	}

	//check compare()
	B = stringToBigInteger("-111");
	if(compare(A, B) != 1)
	{
		return 1;
	}


	// check negate()
	negate(B);
	if(sign(B) != 1)
	{
		return 1;
	}


	// check makeZero()
	makeZero(B);
	if(sign(B) != 0)
	{
		return 1;
	}


	// check copy()
	C = stringToBigInteger("999");
	D = copy(C);

	if(compare(C, D) != 0)
	{
		return 1;
	}



	// check equals()
	if(equals(C, D) != 1)
	{
		return 1;
	}


	// check freeBigInteger()
	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&C);
	freeBigInteger(&D);


	return 0;

}