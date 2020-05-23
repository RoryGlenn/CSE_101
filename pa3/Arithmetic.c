//-----------------------------------------------------------------------------
// Arithmetic.c
// Uses the exported functions of BigInteger.c and makes arbitrarily 
// large sized calculations
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[])
{
	FILE *in;
	FILE *out;

	if(argc != 3)
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	in = fopen(argv[1], "r");
	if(in == NULL)
	{
		printf("Unable to read from input file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	out = fopen(argv[2], "w");
	if(out == NULL)
	{
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	int i1;
	fscanf(in, "%d", &i1);
	char *s1 = malloc(sizeof(char) * (i1+1));
	fscanf(in, "%s", s1);

	int i2;
	fscanf(in, "%d", &i2);
	char *s2 = malloc(sizeof(char) * (i2+1));
	fscanf(in, "%s", s2);

	BigInteger A = stringToBigInteger(s1);
	BigInteger B = stringToBigInteger(s2);

	printBigInteger(out, A);
	fprintf(out, "\n\n");
	printBigInteger(out, B);
	fprintf(out, "\n\n");

	// A + B
	BigInteger sum1 = newBigInteger();
	add(sum1, A, B);
	printBigInteger(out, sum1);
	fprintf(out, "\n\n");

	freeBigInteger(&sum1);

	// A - B
	BigInteger diff1 = newBigInteger();
	subtract(diff1, A, B);
	printBigInteger(out, diff1);
	fprintf(out, "\n\n");
	freeBigInteger(&diff1);

	// A - A
	BigInteger diff2 = newBigInteger();
	subtract(diff2, A, A);
	printBigInteger(out, diff2);
	fprintf(out, "\n\n");
	freeBigInteger(&diff2);

	// 3A - 2B 
	BigInteger diff3 = newBigInteger();
	BigInteger threeTimesA = newBigInteger();
	BigInteger twoTimesB = newBigInteger();
	add(threeTimesA, A, A);
	add(threeTimesA, threeTimesA, A);
	add(twoTimesB, B, B);
	subtract(diff3, threeTimesA, twoTimesB);
	printBigInteger(out, diff3);
	fprintf(out, "\n\n");
	freeBigInteger(&threeTimesA);
	freeBigInteger(&twoTimesB);
	freeBigInteger(&diff3);

	// A * B 
	BigInteger prod1 = newBigInteger();
	prod1 = prod(A, B);
	printBigInteger(out, prod1);
	fprintf(out, "\n\n");
	freeBigInteger(&prod1);

	// A * A
	BigInteger prod2 = newBigInteger();
	prod2 = prod(A, A);
	printBigInteger(out, prod2);
	fprintf(out, "\n\n");
	freeBigInteger(&prod2);

	// B * B
	BigInteger prod3 = newBigInteger();
	prod3 = prod(B, B);
	printBigInteger(out, prod3);
	fprintf(out, "\n\n");
	freeBigInteger(&prod3);


	// 9A^4 + 16B^5
	BigInteger sum2 = newBigInteger();
	BigInteger APower4 = newBigInteger();
	BigInteger nineTimesAPower4 = newBigInteger();
	BigInteger BPower5 = newBigInteger();
	BigInteger sixteenTimesB = newBigInteger();
	// A^4
	multiply(APower4, A, A);
	multiply(APower4, APower4, APower4);
	// B^5
	multiply(BPower5, B, B);
	multiply(BPower5, BPower5, BPower5);
	multiply(BPower5, BPower5, B);

	// A^4 + A^4 = 2(A^4)
	add(nineTimesAPower4, APower4, APower4);

	// 2A^4 + 7A^4 = 9(A^4)
	for (int i = 0; i < 7; i++)
	{
		add(nineTimesAPower4, nineTimesAPower4, APower4);
	}

	// B^5 + B^5 = 2(B^5)
	add(sixteenTimesB, BPower5, BPower5);

	// 2B^5 + 14B^5 = 16(B^5)
	for (int i = 0; i < 14; i++)
	{
		add(sixteenTimesB, sixteenTimesB, BPower5);
	}
	// 9A^4 + 16B^5
	add(sum2, sixteenTimesB, nineTimesAPower4);
	printBigInteger(out, sum2);
	fprintf(out, "\n");

	freeBigInteger(&sixteenTimesB);
	freeBigInteger(&nineTimesAPower4);
	freeBigInteger(&BPower5);
	freeBigInteger(&APower4);
	freeBigInteger(&sum2);

	fclose(out);
	fclose(in);
	
	return 0;
}