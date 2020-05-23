#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

int main(int argc, char** argv)
{

	// read from an input file containing exactly 4 lines
	// 1. a positive integer a
	// 2. an optional sign character (+ or -) followed by a decimal digits
	// 3. a positive integer b
	// 4. an optional sign character (+ or -) followed by b decimal digits


	            BigInteger pA1 = stringToBigInteger("+111122223333");
            printf("pA1->sign: %d\n", sign(pA1));
            puts("pA1: \n"); printBigInteger(stdout, pA1);
            puts("\n");


            BigInteger pB1 = stringToBigInteger("+222211110000");
            printf("pB1->sign: %d\n", sign(pB1));
            puts("pB1: \n"); printBigInteger(stdout, pB1);
            puts("\n");


            BigInteger pC1 = newBigInteger();
            printf("pC1->sign: %d\n", sign(pC1));
            puts("pC1: \n"); printBigInteger(stdout, pC1);
            puts("\n");

            //pos + pos = pos
            BigInteger pD1 = stringToBigInteger("+333333333333");
            printf("pD1->sign: %d\n", sign(pD1));
            puts("pD1: \n"); printBigInteger(stdout, pD1);
            puts("\n");


            add(pC1, pA1, pB1);
            puts("Calling add on pA1, pB1\n");
            puts("After add pC1: "); printBigInteger(stdout, pC1);
            printf("Sign of pC1: %d\n", sign(pC1));
            printf("Sign of pD1: %d\n", sign(pD1));
            if(!equals(pC1, pD1))
            {

              puts("Returns 1\n");
              return 1;
            }
            freeBigInteger(&pB1);
            freeBigInteger(&pD1);

            puts("Success\n");

	// FILE *in, *out;

	// if(argc != 4)
	// {
	// 	printf("Usage: %s <input file> <output file>\n", argv[0]);
	// 	exit(EXIT_FAILURE);
	// }

	// in = fopen(argv[1], "r");
	// if(in == NULL)
	// {
	// 	printf("Unable to read from input file %s\n", argv[1]);
	// 	exit(EXIT_FAILURE);
	// }
	// int i1;
	// fscanf(in, "%d", &i1);
	// char *s1 = malloc(sizeof(char) * (i1+1));
	// fscanf(in, "%s", &s1);

	// int i2;
	// fscanf(in, "%d", &i2);
	// char *s2 = malloc(sizeof(char) * (i2+1));
	// fscanf(in, "%s", &s2);

	// BigInteger A = stringToBigInteger(s1);
	// BigInteger B = stringToBigInteger(s2);

	// printBigInteger(out, A);
	// printBigInteger(out, B);
	// //read the number
	// // allocate a character string with the number you read above
	// // read the string and store into the character string you made
	// // reapeat this one more time

	// // need to grab values of in file and add them to the big int

	// BigInteger sum1 = newBigInteger();
	// fprintf(out, "A + B = ");
	// sum1 = sum(A, B);
	// printBigInteger(out, sum1);
	// fprintf(out, "\n");
	// freeBigInteger(&sum1);

	// BigInteger diff1 = newBigInteger();
	// fprintf(out, "A - B = ");
	// diff1 = diff(A, B);
	// printBigInteger(out, diff1);
	// fprintf(out, "\n");
	// freeBigInteger(&diff1);

	// BigInteger diff2 = newBigInteger();
	// fprintf(out, "A - A = ");
	// diff2 = diff(A, A);
	// printBigInteger(out, diff2);
	// fprintf(out, "\n");
	// freeBigInteger(&diff2);

	// BigInteger diff3 = newBigInteger();
	// BigInteger threeTimesA = newBigInteger();
	// BigInteger twoTimesB = newBigInteger();
	// fprintf(out, "3A - 2B = ");
	// threeTimesA = sum(A, A);
	// threeTimesA = sum(threeTimesA, A);
	// twoTimesB = sum(B, B);
	// diff3 = diff(threeTimesA, twoTimesB);
	// printBigInteger(out, diff3);
	// fprintf(out, "\n");
	// freeBigInteger(&threeTimesA);
	// freeBigInteger(&twoTimesB);
	// freeBigInteger(&diff3);

	// BigInteger prod1 = newBigInteger();
	// fprintf(out, "A * B = ");
	// prod1 = prod(A, B);
	// printBigInteger(out, prod1);
	// fprintf(out, "\n");
	// freeBigInteger(&prod1);

	// BigInteger prod2 = newBigInteger();
	// fprintf(out, "A * A = ");
	// prod2 = prod(A, A);
	// printBigInteger(out, prod2);
	// fprintf(out, "\n");
	// freeBigInteger(&prod2);

	// BigInteger prod3 = newBigInteger();
	// fprintf(out, "B * B = ");
	// prod3 = prod(B, B);
	// printBigInteger(out, prod3);
	// fprintf(out, "\n");
	// freeBigInteger(&prod3);


	// BigInteger sum2 = newBigInteger();
	// BigInteger APower4 = newBigInteger();
	// BigInteger nineTimesAPower4 = newBigInteger();
	// BigInteger BPower5 = newBigInteger();
	// BigInteger sixteenTimesB = newBigInteger();
	// APower4 = prod(A, A);
	// APower4 = prod(APower4, APower4);
	// //APower4 = prod(APower4, A);
	// BPower5 = prod(B, B);
	// BPower5 = prod(BPower5, B);
	// BPower5 = prod(BPower5, B);
	// BPower5 = prod(BPower5, B);
	// nineTimesAPower4 = sum(APower4, APower4);
	// nineTimesAPower4 = sum(nineTimesAPower4, APower4);
	// nineTimesAPower4 = sum(nineTimesAPower4, APower4);
	// nineTimesAPower4 = sum(nineTimesAPower4, APower4);
	// nineTimesAPower4 = sum(nineTimesAPower4, APower4);
	// nineTimesAPower4 = sum(nineTimesAPower4, APower4);
	// nineTimesAPower4 = sum(nineTimesAPower4, APower4);
	// nineTimesAPower4 = sum(nineTimesAPower4, APower4);
	// sixteenTimesB = sum(BPower5, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);
	// sixteenTimesB = sum(sixteenTimesB, BPower5);

	// fprintf(out, "9A^4 + 16B^5 = ");
	// sum2 = sum(sixteenTimesB, nineTimesAPower4);
	// printBigInteger(out, sum2);
	// fprintf(out, "\n");

	// fclose(out);

	// freeBigInteger(&sixteenTimesB);
	// freeBigInteger(&nineTimesAPower4);
	// freeBigInteger(&BPower5);
	// freeBigInteger(&APower4);
	// freeBigInteger(&sum2);

	return 0;
}