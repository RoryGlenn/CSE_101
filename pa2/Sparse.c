#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

Matrix createMatrix(int size, int entries, FILE* in);

int main(int argc, char** argv) {
	FILE *in, *out;
	char line[128];
	int size, entryA, entryB;

	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	in = fopen(argv[1], "r");
	if (in == NULL) {
		printf("Unable to read from input file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	//Get the size and no of entries of A and B Matrix
	if (fgets(line, sizeof(line), in) != NULL && line[0] != '\n') {
		sscanf(line, "%d %d %d", &size, &entryA, &entryB);
	}

	fgets(line, sizeof(line), in);
	//Create Matrix A
	Matrix A = createMatrix(size, entryA, in);
	fgets(line, sizeof(line), in);
	//Create Matrix A
	Matrix B = createMatrix(size, entryB, in);

	//Close input file
	fclose(in);

	out = fopen(argv[2], "w");

	//print Matrix A
	fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out, A);
	fprintf(out, "\n");

	//print Matrix B
	fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
	printMatrix(out, B);
	fprintf(out, "\n");


	fprintf(out, "(1.5)*A = \n");
	Matrix scalar = scalarMult(1.5, A);
	printMatrix(out, scalar);
	fprintf(out, "\n");
	freeMatrix(&scalar);

	fprintf(out, "A+B = \n");
	Matrix sum1 = sum(A, B);
	printMatrix(out, sum1);
	fprintf(out, "\n");
	freeMatrix(&sum1);

	fprintf(out, "A+A = \n");
	Matrix sum2 = sum(A, A);
	printMatrix(out, sum2);
	fprintf(out, "\n");
	freeMatrix(&sum2);

	fprintf(out, "B-A = \n");
	Matrix diff1 = diff(B, A);
	printMatrix(out, diff1);
	fprintf(out, "\n");
	freeMatrix(&diff1);

	fprintf(out, "A-A = \n");
	Matrix diff2 = diff(A, A);
	printMatrix(out, diff2);
	fprintf(out, "\n");
	freeMatrix(&diff2);

	fprintf(out, "Transpose(A) = \n");
	Matrix trans = transpose(A);
	printMatrix(out, trans);
	fprintf(out, "\n");
	freeMatrix(&trans);

	fprintf(out, "A*B = \n");
	Matrix prod1 = product(A, B);
	printMatrix(out, prod1);
	fprintf(out, "\n");
	freeMatrix(&prod1);

	fprintf(out, "B*B = \n");
	Matrix prod2 = product(B, B);
	printMatrix(out, prod2);
	fprintf(out, "\n");
	freeMatrix(&prod2);

	fclose(out);

	freeMatrix(&A);
	freeMatrix(&B);
	return 0;
}

Matrix createMatrix(int size, int entries, FILE* in) {
	char line[128];
	int row, column;
	double val;

	Matrix C = newMatrix(size);
	for (int i = 0; i < entries; i++) {
		if (fgets(line, sizeof(line), in) != NULL) {
			sscanf(line, "%d %d %lf", &row, &column, &val);
			changeEntry(C, row, column, val);
		}
	}
	return C;
}
