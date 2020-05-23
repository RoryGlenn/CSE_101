#include "BigInteger.h"

int main()
{
 /*
             * Adding numbers fall into one of 4 cases, denote pos = positive number, neg = negative number
             *
             * pos + pos = pos
             *
             * pos + neg = 0
             *           < 0
             *           > 0
             *
             * neg + pos = 0
             *           < 0
             *           > 0
             *
             * neg + neg = neg
             *
             * */

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


            

            // //add a positive and a negative integer
            // //-> pos + neg = 0
            // BigInteger pB = stringToBigInteger("-111122223333");
            // add(pC1, pA1, pB1);
            // if(sign(pC) != 0)
            // {
            //   puts("Second: 1");
            //  return 1;
            // }
            // freeBigInteger(&pB);

            // //-> pos + neg > 0
            // BigInteger pB = stringToBigInteger("-110122223333");
            // add(pC, pA, pB);
            // if(sign(pC) != 1)
            // {
            //  puts("Third: 1");
            //  return 1;
            // }
            // freeBigInteger(&pB);

            // //-> pos + neg < 0
            // BigInteger pB = stringToBigInteger("-112122223333");
            // add(pC, pA, pB);
            // if(sign(pC) != -1) 
            // {
            //   puts("Fourth: 1");
            //   return 1;
            // }

            // //-> neg + neg = neg
            // freeBigInteger(pA);
            // BigInteger pA = stringToBigInteger("-221211110000");
            // BigInteger pD = stringToBigInteger("-333333333333");
            // add(pC, pA, pB);
            // if(!equals(pC, pD))
            // {
            //   puts("Fifth: 1");
            //  return 1;
            // }

          
            puts("Success");
            return 0;

}