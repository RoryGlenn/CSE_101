#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

typedef struct MatrixObj
{
    int size;
    List* row;
}MatrixObj;

typedef MatrixObj* Matrix;

typedef struct EntryObj
{
    int col;
    double val;
}EntryObj;

typedef EntryObj* Entry;

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n)
{
    // 1. create matrix
    // 2. create matrix->row
    // 3. set size to n
    // 4. set matrix->row[n] equal to a new list
    // 5. fill each list in matrix->row[n] with another list
    // 6. return the matrix

    Matrix matrix;
    matrix = malloc(sizeof(MatrixObj));
    matrix->row = malloc(n * sizeof(List));


    matrix->size = n;
    //matrix->row[n] = newList();

    for(int i = 0; i < n; i++)
    {
        matrix->row[i] = newList();
    }

    return (matrix);
}

Entry NewEntry(int col, double val)
{
    Entry entry = malloc(sizeof(EntryObj));
    entry->col = col;
    entry->val = val;
    return entry;
}

// not sure if this should take a pointer or not
void freeEntry(Entry* pE)
{
    if(pE!=NULL && *pE!=NULL)
    {
        free(*pE);
        *pE = NULL;
    }
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM)
{
    // NEW freeMatrix() pseudocode
    // 1. free each entry in matrix->row[n]
    // 2. free each list matrix->row[n] (get rid of the nodes)
    // 3. free the array matrix->row
    // 4 free matrix

    if(pM!= NULL & *pM!=NULL)
    {
        // iterate over matrix
        for (int i = 0; i < size(*pM); i++)
        {
            moveFront((*pM)->row[i]);

            // iterate over array
            for (int j = 0; j < length((*pM)->row[i]); j++)
            {
                Entry entry = (Entry)get((*pM)->row[i]);

                // 1. free the entry
                freeEntry(&entry);

                // deletes a node
                delete((*pM)->row[i]);
                moveFront((*pM)->row[i]);
            }
            // 2. free the list
            freeList(&((*pM)->row[i]));
        }
        // 3. free the array
        free((*pM)->row);

        // 4. free the matrix
        free(*pM);
        *pM = NULL;
    }
}

// Access functions
//-------------------------------------------------

// Return the size of square Matrix M.
int size(Matrix M)
{
    return (M->size);
}

// Return the number of non-zero elements in M.
int NNZ(Matrix matrix)
{
    // FIX THIS
    int i = 0;
    int count = 0;

    while(i < size(matrix))
    {
        List NNZ = matrix->row[i];
        count = count + length(NNZ);
        i++;
    }
    return count;
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B)
{
    if (size(A) != size(B)) return 0;

    for (int i = 0; i < size(A); i++)
    {
        Entry entryA = (Entry) A->row[i];
        Entry entryB = (Entry) B->row[i];

        if (entryA->val - entryB->val != 0) return 0;
    }

    return 1;
}

// Manipulation procedures
//-------------------------------------------------

// Re-sets M to the zero Matrix.
void makeZero(Matrix matrix)
{
    matrix->size = 0;
    matrix->row = (List *) newList();
    for (int i = 0; i < matrix->size; ++i)
    {
        matrix->row[i] = newList();
    }
}

// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix matrix, int i, int j, double x)
{
    // i is row
    // j is column

    // checks to make sure the column we asked for is in bounds
    if(j < 1 || j > matrix->size || i < 1 || i > matrix->size)  // does not pass this check
    {
        printf("Matrix Error: calling changeEntry() on column exceeding boundaries\n");
        exit(EXIT_FAILURE);
    }

    i--;
    j--;

    // create a new jth column
    Entry entry = NewEntry(j, x);
    //List list = matrix->row[i];

    append(matrix->row[i], entry);

    // moves to the front of the matrix
    moveFront(matrix->row[i]);

    // create a new cursorEntry and set it equal
    // to the very top row of the matrix
    Entry cursorEntry = (Entry)get(matrix->row[i]);

        // move through the row
        while(getIndex(matrix->row[i]) > 0)
        {
            if(cursorEntry->col == j)
            {
                if(x == 0)
                {
                    delete(matrix->row[i]);
                }
                else if(x != 0)
                {
                    insertAfter(matrix->row[i], entry);
                    delete(matrix->row[i]);
                }
            }
            else if(j != cursorEntry->col)
            {
                prepend(matrix->row[i], entry);
            }

            // do something with x, then
            moveNext((List)matrix->row[i]);
            cursorEntry = (Entry)get(matrix->row[i]);
        }
}


// Matrix Arithmetic operations
//------------------------------------------------------------------------

// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix matrix)
{
    Matrix copiedMatrix = newMatrix(size(matrix));

    for (int i = 0; i < size(matrix); i++)
    {
        // move to the front of both matrices
        moveFront(matrix->row[i]);
        moveFront(copiedMatrix->row[i]);

        // while we have a valid index for our row
        while(getIndex(matrix->row[i]) >= 0)
        {
            // get the entry
            Entry entry = get(matrix->row[i]);

            // add the entry to the copied matrix
            changeEntry(copiedMatrix, i, entry->col, entry->val);

            // move to the next entry in matrix
            moveNext(matrix->row[i]);
        }
    }

    return copiedMatrix;
}

// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix matrix)
{
    // create a temp matrix and set the size equal to the passed in matrix size
    Matrix tempMatrix = newMatrix(matrix->size);

    // start looping through the matrix
    for (int i = 1; i <= size(matrix); i++)
    {
        // move to the front of the row
        moveFront(matrix->row[i]);

        // set entry to the row of the matrix
        // does this need to be matrix->row[i]???
        Entry entry = (Entry) get(matrix->row[i]);

        // while we didn't walk past the last item in the row
        while(getIndex(matrix->row[i]) >= 0)
        {
            changeEntry(tempMatrix, i, entry->col, entry->val);
            moveNext(matrix->row[i]);
        }
    }

    return tempMatrix;
}

// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix matrix)
{
    //List list;
    Entry entry;
    Matrix new_Matrix = copy(matrix);

    for (int i = 0; i <=  size(new_Matrix); ++i)
    {
        //list = matrix->row[i-1];
        moveFront(new_Matrix->row[i]);

            while(getIndex(new_Matrix->row[i]) != -1)
            {
                //entry = (Entry)get(list);
                entry = get((List) new_Matrix->row[i]);
                changeEntry(new_Matrix, i+1, entry->col+1, entry->val*x);
                moveNext(new_Matrix->row[i]);
            }
    }

    return matrix;
}


// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)
{
    for (int i = 0; i < size(A); i++)
    {
        // look at the front of the matrix before we start adding them together
        moveFront(A->row[i]);
    }

    for (int i = 0; i < size(B); i++)
    {
        // look at the front of the matrix before we start adding them together
        moveFront(B->row[i]);
    }


    Matrix sumMatrix;

    // if our matrices are different sizes, jump out of the function
    if(size(A) != size(B))
    {
        printf("Matrix Error: calling sum() on invalid matrix size\n");
        exit(EXIT_FAILURE);
    }
    // if they are the same size, create a new matrix
    // and initialize it to the size of either matrix
    else
    {
        sumMatrix = newMatrix(A->size);
    }

    for(int i = 0; i < size(A); i++)
    {
        // as long as there is something in the matrix
        while (getIndex(A->row[i]) || getIndex(B->row[i]) >= 0) {
            // create a new entry and set it equal to the value
            // in the matrix index that we are trying to add
            Entry entryA = (Entry) get(A->row[i]);
            Entry entryB = (Entry) get(B->row[i]);

            // is entryP's column number greater than entryQ's column number?
            if (entryA->col > entryB->col)
            {
                // move the lesser column up one column
                moveNext(B->row[i]);
            }
                // is entryP's column number less than entryQ's column number?
            else if (entryA->col < entryB->col)
            {
                // move the lesser column up on column
                moveNext(A->row[i]);
            }
                // is entryP's column the same as entryQ's?
                // if so, then you can add them!
            else
            {    // add A+B
                changeEntry(sumMatrix, i, entryB->col, entryA->val + entryB->val);
            }

        }
    }

}

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)
{
    if(size(A) != size(B))
    {
        printf("Matrix Error: calling diff() with different matrix sizes\n");
        exit(EXIT_FAILURE);
    }

    Matrix diffMatrix;
    B = scalarMult(-1, B);
    diffMatrix = sum(A, B);

    return diffMatrix;
}

// Computes the vector dot product of two matrix rows represented by Lists P and Q.
// Use this function together with function transpose() to help implement product().
// Similar helper functions for the operations sum() and diff() will also be useful, and are highly recommended.
double vectorDot(List P, List Q)
{
    // dot product
    // a*b = a1*b1 + a2*b2 + a3*b3 + ... + an*bn
    double product = 0.0;

    // look at the front of the matrix before we start adding them together
    moveFront(P);
    moveFront(Q);

    // as long as there is something in the matrix
    while (getIndex(P) || getIndex(Q) >= 0)
    {
        // create a new entry and set it equal to the value
        // in the matrix index that we are trying to add
        Entry entryP = (Entry) get(P);
        Entry entryQ = (Entry) get(Q);

        // is entryP's column number greater than entryQ's column number?
        if (entryP->col > entryQ->col)
        {
            // move the lesser column up one column
            moveNext(Q);
        }
            // is entryP's column number less than entryQ's column number?
        else if (entryP->col < entryQ->col)
        {
            // move the lesser column up on column
            moveNext(P);
        }
            // is entryP's column the same as entryQ's?
            // if so, then you can add them!
        else
        {
            // get the dot product of the vectors
            product = product + (entryP->val * entryQ->val);
            moveNext(P);
            moveNext(Q);
        }

    }

    return product;
}

// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix matrix_A, Matrix matrix_B)
{
    // call transpose
    // put it in a new matrix
    // loop through the matrix with three for loops

    // if the size of A and B are not the same
    if (size(matrix_A) != size(matrix_B)) {
        printf("Matrix error: calling product() on invalid matrices\n");
        exit(EXIT_FAILURE);
    }

    Matrix newMatrix_01 = newMatrix(size(matrix_A));
    Matrix newMatrix_02 = transpose(matrix_A);

    for(int i = 1; i <= matrix_A->size; i++)
    {
        if(length((matrix_A->row[i])) == 0)
        {
            continue;
        }
        for(int j = 1; j <= size(matrix_A); j++)
        {
            if(length(newMatrix_02->row[j]) == 0)
            {
                continue;
            }
            changeEntry(newMatrix_01, i, j, vectorDot(matrix_A->row[i], newMatrix_02->row[j]));
        }
    }
}


// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix matrix)
{
    if(matrix == NULL)
    {
        printf("Matrix Error: calling printMatrix() on a null matrix reference\n");
        exit(EXIT_FAILURE);
    }

    // moves through each one of the rows ^
    for(int i = 0; i < size(matrix); i++)
    {
        if(length(matrix->row[i]) > 0)
        {
            moveFront(matrix->row[i]);
            fprintf(out, "%d: ", i + 1);

            // moves through the columns <--->
            for (int j = 0; j < length(matrix->row[i]); j++) {
                Entry entry = get(matrix->row[i]);
                fprintf(out, "(%d, %.1f)", entry->col + 1, entry->val);
                moveNext(matrix->row[i]);
            }
            fprintf(out, "\n");
        }
    }
}