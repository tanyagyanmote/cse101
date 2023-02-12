/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#4
// MatrixTest.c
// Test client for the Matrix ADT
*********************************************************************************/ 
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H, I, J;

   changeEntry(A, 1,1,9); 
   changeEntry(A, 1,2,8); 
   changeEntry(A, 1,3,7); 
   changeEntry(A, 2,1,6); 
   changeEntry(A, 2,2,5); 
   changeEntry(A, 2,3,4); 
   changeEntry(A, 3,1,3); 
   changeEntry(A, 3,2,2); 
   changeEntry(A, 3,3,1); 
   changeEntry(B, 1,1,1);
   changeEntry(B, 1,2,0);
   changeEntry(B, 1,3,1);
   changeEntry(B, 2,1,0);
   changeEntry(B, 2,2,1);
   changeEntry(B, 2,3,0);
   changeEntry(B, 3,1,1);
   changeEntry(B, 3,2,1);
   changeEntry(B, 3,3,1);


   printf("A has %d non-zero entries:\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\nB has %d non-zero entries:\n", NNZ(B));
   printMatrix(stdout, B);

   printf("\n%s\n", equals(A, B)?"true":"false" );

   printf("\n(1.5)*A =\n");
   C = scalarMult(1.5,A);
   printMatrix(stdout, C);

   D = sum(A, B);
   printf("\nA+B =\n");
   printMatrix(stdout, D);

   E = sum(A, A);
   printf("\nA+A =\n");
   printMatrix(stdout, E);

   F = diff(B, A);
   printf("\nB-A =\n");
   printMatrix(stdout, F);

   G = diff(A, A);
   printf("\nA-A =\n");
   printMatrix(stdout, G);

   H = transpose(A);
   printf("\nTranspose(A) =\n");
   printMatrix(stdout, H);

   I = product(A, B);
   printf("\nA*B =\n");
   printMatrix(stdout, I);

   J = product(B, B);
   printf("\nB*B =\n");
   printMatrix(stdout, J);

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

   return 0;
}


/*
Output of this program:
A has 9 non-zero entries:
1: (1, 9.0) (2, 8.0) (3, 7.0)
2: (1, 6.0) (2, 5.0) (3, 4.0)
3: (1, 3.0) (2, 2.0) (3, 1.0)

B has 6 non-zero entries:
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

false

(1.5)*A =
1: (1, 13.5) (2, 12.0) (3, 10.5)
2: (1, 9.0) (2, 7.5) (3, 6.0)
3: (1, 4.5) (2, 3.0) (3, 1.5)

A+B =
1: (1, 10.0) (2, 8.0) (3, 8.0)
2: (1, 6.0) (2, 6.0) (3, 4.0)
3: (1, 4.0) (2, 3.0) (3, 2.0)

A+A =
1: (1, 18.0) (2, 16.0) (3, 14.0)
2: (1, 12.0) (2, 10.0) (3, 8.0)
3: (1, 6.0) (2, 4.0) (3, 2.0)

B-A =
1: (1, -8.0) (2, -8.0) (3, -6.0)
2: (1, -6.0) (2, -4.0) (3, -4.0)
3: (1, -2.0) (2, -1.0)

A-A =

Transpose(A) =
1: (1, 9.0) (2, 6.0) (3, 3.0)
2: (1, 8.0) (2, 5.0) (3, 2.0)
3: (1, 7.0) (2, 4.0) (3, 1.0)

A*B =
1: (1, 16.0) (2, 15.0) (3, 16.0)
2: (1, 10.0) (2, 9.0) (3, 10.0)
3: (1, 4.0) (2, 3.0) (3, 4.0)

B*B =
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

*/