/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#4
* Sparse.c 
* Does matrix operations on matrices
*********************************************************************************/ 

#include <stdio.h>
#include "Matrix.h"

int main (int argc, char* argv[]) {
    //using puesdo give by mahyar
    int n, nnza, nnzb, row, col;
    double val;
    FILE* in; 
    FILE* out; 
    Matrix C, D, E, F, G, H, I, J;

    // check command line for correct number of arguments
    if( argc != 3 ) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open input file for reading
    in = fopen(argv[1], "r");
    if(!in) {
        printf("Unable to read from file %s\n", argv[1]);
        exit(1);
    }

    // open output file for writing
    out = fopen(argv[2], "w");
    if(!out) {
        printf("Unable to write to file %s\n", argv[2]);
        exit(1);
    }

    // scan and initialize Matrix 
    fscanf(in, "%d", &n);
    fscanf(in, "%d", &nnza);
    fscanf(in, "%d", &nnzb);

    // create two matrices A and B of size n
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // from 0 to nnza: 
    //      scan in the rows, columns and values
    //      assign them to matrix A

    for (int i = 0; i < nnza; i++) {
        fscanf(in, "%d", &row);
        fscanf(in, "%d", &col);
        fscanf(in, "%lf", &val);
        changeEntry(A, row, col, val);
    }
    // from 0 to nnzb: 
    //      scan in the rows, columns and values
    //      assign them to matrix B
    for (int i = 0; i < nnzb; i++) {
        fscanf(in, "%d", &row);
        fscanf(in, "%d", &col);
        fscanf(in, "%lf", &val);
        changeEntry(B, row, col, val);
    }

    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    // print out the matrix
    printMatrix(out, A);
    fprintf(out, "\nB has %d non-zero entries:\n", NNZ(B));
    // print out the matrix
    printMatrix(out, B);

    // C = multiply everything in A by 1.5
    // print out the matrix
    fprintf(out, "\n(1.5)*A =\n");
    C = scalarMult(1.5,A);
    printMatrix(out, C);

    // D = sum of a and b
    // print out the matrix
    D = sum(A, B);
    fprintf(out, "\nA+B =\n");
    printMatrix(out, D);

    // E = addition of A twice
    // print out the matrix
    E = sum(A, A);
    fprintf(out, "\nA+A =\n");
    printMatrix(out, E);

    // F = subtraction of A from B;
    // print out the matrix
    F = diff(B, A);
    fprintf(out, "\nB-A =\n");
    printMatrix(out, F);

    // G = subtraction of A from A (should be 0)
    // print out the matrix
    G = diff(A, A);
    fprintf(out, "\nA-A =\n");
    printMatrix(out, G);

    // H = transpose of A
    // print out the matrix
    H = transpose(A);
    fprintf(out, "\nTranspose(A) =\n");
    printMatrix(out, H);

    // I = product of the two matrices
    // print out the matrix
    I = product(A, B);
    fprintf(out, "\nA*B =\n");
    printMatrix(out, I);

    // J = product of B twice
    // print out the matrix
    J = product(B, B);
    fprintf(out, "\nB*B =\n");
    printMatrix(out, J);


    // free all metrices
    // close files
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
    fclose(in);
    fclose(out);

    return 0;
}