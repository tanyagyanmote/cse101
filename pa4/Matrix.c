/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#4
* Matrix.c 
* Matrix ADT 
*********************************************************************************/ 
#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// Structs

typedef struct EntryObj *Entry;

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef struct MatrixObj {
    List *rows;
    int size;
    int nnz;
} MatrixObj;

// Constructors-Destructors

Entry newEntry(int column, double value) {
    Entry E = malloc(sizeof(EntryObj));
    E->value = value;
    E->column = column;
    return E;
}


void freeEntry(Entry *pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->rows = (List *)calloc(n + 1, sizeof(List *));
    for (int i = 1; i < n+1; i++) {
        M->rows[i] = newList();
    }
    M->nnz = 0;
    M->size = n;
    return M;
}
//puesdocode from mahyar
void freeMatrix(Matrix *pM) {
    if (pM != NULL && *pM != NULL) {
        makeZero(*pM);
        for (int i = 1; i < (*pM)->size +1; i++) {
            freeList(&(*pM)->rows[i]);
            (*pM)->rows[i] = NULL;
        }
        free((*pM)->rows);
        free(*pM);
    }

}

int size(Matrix M){
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}

int NNZ(Matrix M){
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->nnz;
}

int equals(Matrix A, Matrix B){
    if(size(A) != size(B) || (A->nnz != B->nnz)){
        return 0;
    }
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for(int i =1;i <= A->size;i++){
        //checking if the length of the rows are the same 
        if(length(A->rows[i]) != length(B->rows[i])){
            return 0;
        }
        if(length(A->rows[i]) > 0){
            moveFront(A->rows[i]);
            moveFront(B->rows[i]);
            while(index(A->rows[i]) != -1 && index(B->rows[i]) != -1){
                Entry E = get(A->rows[i]);
                Entry E2 = get(B->rows[i]);
                if(E->column != E2->column || E->value != E2->value){
                    return 0;
                }
                moveNext(A->rows[i]);
                moveNext(B->rows[i]);
            }
        }
        if (index(A->rows[i]) >= 0 || index(B->rows[i]) >= 0) {
            return 0;
        }
    }
    return 1;

}
//using puesdocode from Saeed
void makeZero(Matrix M){
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= M->size; i++) {
        for(moveFront(M->rows[i]);index(M->rows[i]) != -1;moveNext(M->rows[i])){
            EntryObj *node = get(M->rows[i]);
            freeEntry(&node);
        }
        clear(M->rows[i]);
    }
    M->nnz = 0; 
}
//puesdocode from simon and aaron
void changeEntry(Matrix M, int i, int j, double x){
    //preconditions
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if ((i < 1) || (i > size(M))) {
        fprintf(stderr, "Matrix Error: calling changeEntry() with invalid row\n");
        exit(EXIT_FAILURE);
    }
    if ((j < 1) || (j > size(M))) {
        fprintf(stderr, "Matrix Error: calling changeEntry() with invalid columnw\n");
        exit(EXIT_FAILURE);
    }
    if(length(M->rows[i]) == 0){
        if(x==0){
            return;
        }
        Entry e = newEntry(j,x);
        append(M->rows[i],e);
        M->nnz+=1;
        return;
    }
    //if there is something in the row then, iterate through the rows
    else{
        moveFront(M->rows[i]);
        //Entry e3 = get(M->rows[i]);
        while(index(M->rows[i]) != -1){
            Entry e2 = get(M->rows[i]);
            //if we r in the same column
            if(e2->column == j){
                if(x==0){
                    //if there's a 0 there, delete it
                    freeEntry(&e2);
                    delete(M->rows[i]);
                    M->nnz-=1;
                    return;
                }
                else{
                    e2->value = x;
                    return;
                }
            }
            //if the column we are in is greater than j, add it before
            else if(e2->column > j){
                if(x==0){
                    return;
                }
                Entry e = newEntry(j,x);
                insertBefore(M->rows[i],e);
                M->nnz+=1;
                return;
            }
            moveNext(M->rows[i]);
        }
        if(x == 0){
            return;
        }
        //append what ever is left
        Entry e = newEntry(j,x);
        append(M->rows[i],e);
        M->nnz+=1;
    }
}

Matrix copy(Matrix A){
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix thing = newMatrix(A->size);
    //iterate through the og matrix, and copy its values using change entry 
    for (int i =1;i <= A->size;i++){
        for(moveFront(A->rows[i]);index(A->rows[i]) != -1;moveNext(A->rows[i])){
            Entry E = get(A->rows[i]);
            changeEntry(thing,i,E->column,E->value);
        }
    }
    return thing;
}

Matrix transpose(Matrix A){
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    //same as copy but u want to switch column and row
    Matrix thing = newMatrix(A->size);
    for (int i =1;i <= A->size;i++){
        for(moveFront(A->rows[i]);index(A->rows[i]) != -1;moveNext(A->rows[i])){
            Entry E = get(A->rows[i]);
            changeEntry(thing,E->column,i,E->value);
        }
    }
    return thing;
}

Matrix scalarMult(double x, Matrix A){
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling scalarMulti() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix thing = newMatrix(A->size);
    //iterate through the og matrix and get each entry value, and multipy by x
    for (int i =1;i<=A->size;i++){
        moveFront(A->rows[i]);
        while(index(A->rows[i]) != -1){
            Entry E = get(A->rows[i]);
            changeEntry(thing,i,E->column,E->value*x);
            moveNext(A->rows[i]);
        }
    }
    return thing;
}
//got puesdo help from aaron and sahil
Matrix sum(Matrix A, Matrix B){
    //if both are 0 do nothing
    //one is zero, other isn't zero
    //neither are zero
    //if adding both = 0 then you delete
    //preconditions
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)){
        fprintf(stderr, "Matrix Error: calling sum() when Matrix A and Matrix B are different sizes\n");
        exit(EXIT_FAILURE);
    }
    //if they are the same matrix you can just multipy the matrix times 2
    if(A == B){
        return scalarMult(2,A);
    }
    Matrix added = newMatrix(A->size);
    //iterate through both matrices
    for (int i =1;i<=A->size;i++){
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        while(index(A->rows[i]) != -1 && index(B->rows[i]) != -1){
            Entry E = (get(A->rows[i]));
            Entry E2 = (get(B->rows[i]));
            //if  the columns are the same add them together 
            if(E->column == E2->column){
                changeEntry(added,i,E->column,E -> value + E2 ->value);
                moveNext(A->rows[i]);
                moveNext(B->rows[i]);
            }
            //if the A's column is greater than B's column then add B's value to the matrix
            else if(E->column > E2 ->column){
                changeEntry(added,i,E2->column,E2 -> value);
                moveNext(B->rows[i]);
            }
            //if the B's column is greater than A's column then add A's value to the matrix
            else{
                changeEntry(added,i,E->column,E -> value);
                moveNext(A->rows[i]);
            }
        }
        //if theres still values left then add them in
        if(index(A->rows[i]) == -1){
            while(index(B->rows[i]) > -1){
                Entry E = (get(B->rows[i]));
                changeEntry(added,i,E->column,E -> value);
                moveNext(B->rows[i]);
            }
        }
        else if(index(B->rows[i]) == -1){
            while(index(A->rows[i]) > -1){
                Entry E = (get(A->rows[i]));
                changeEntry(added,i,E->column,E -> value);
                moveNext(A->rows[i]);
            }
        }
    }
    return added;
}


Matrix diff(Matrix A, Matrix B){
    //preconditions
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)){
        fprintf(stderr, "Matrix Error: calling sum() when Matrix A and Matrix B are different sizes\n");
        exit(EXIT_FAILURE);
    }
    Matrix subtracted = newMatrix(A->size);
    //if the matrices are the same then return an empty matrix 
    if(A == B){
        return subtracted;
    }
    for (int i =1;i<=A->size;i++){
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        while(index(A->rows[i]) != -1 && index(B->rows[i]) != -1){
            Entry E = (get(A->rows[i]));
            Entry E2 = (get(B->rows[i]));
            //if  the columns are the same add them together 
            if(E->column == E2->column){
                changeEntry(subtracted,i,E->column,E -> value - E2 ->value);
                moveNext(A->rows[i]);
                moveNext(B->rows[i]);
            }
            //if Matrix B's column is greater than Matrix A columns then add Matrix A's value
            else if(E->column < E2 ->column){
                changeEntry(subtracted,i,E->column,E -> value);
                moveNext(A->rows[i]);
            }
            //else you are trying to subtract a value less so mul by -1, 0-1
            else{
                changeEntry(subtracted,i,E2->column,(E2 -> value * -1));
                moveNext(B->rows[i]);
            }
        }
        if(index(A->rows[i]) == -1){
            while(index(B->rows[i]) > -1){
                //trying to subtract a value less so mul by -1, 0-1
                Entry E = get(B->rows[i]);
                //fprintf(stdout, "E value: %lf\n", E -> value*-1);
                changeEntry(subtracted,i,E->column,E -> value*-1);
                moveNext(B->rows[i]);
            }
        }
        else if(index(B->rows[i]) == -1){
            while(index(A->rows[i]) > -1){
                Entry E = get(A->rows[i]);
                changeEntry(subtracted,i,E->column,E -> value);
                moveNext(A->rows[i]);
            }
        }
    }
    return subtracted;
}
//using idea from lecture
double VectorDot(List P,List Q){
    //itertate though both lists
    Entry a;
    Entry b;
    double added = 0;
    moveFront(P);
    moveFront(Q);
    while(index(P) != -1 && index(Q) != -1 ){
        //get the value at the cursor
        a = get(P);
        b = get(Q);
        //if we r in the same column then multiply the values
        if(a->column == b->column){
            added += a->value * b->value;
            moveNext(Q);
            moveNext(P);
        }
        //else if the columns aren't the same move next
        else if(a->column < b->column){
            moveNext(P);
        }
        else if(b->column < a->column){
            moveNext(Q);
        }
    }
    return added;
}

Matrix product(Matrix A, Matrix B){
    // preconditions
    //create a new matrix and a transposed matrix of B
    Matrix multi = newMatrix(A->size);
    Matrix T = transpose(B);
    double value = 0;
    //iterate through both matrices
    for(int i = 1; i <= A->size;i++){
        for(int j =1; j <= T->size; j++){
            //get matrix A's list multipled with tranposed B's lists
            value = VectorDot(A->rows[i],T->rows[j]);
            if(value != 0){
                //zero check
                changeEntry(multi,i,j,value);
            }
        }
    }
    freeMatrix(&T);
    return multi;
}

void printMatrix(FILE *out, Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        if (length(M->rows[i]) > 0) {
            fprintf(out, "%d:", i);
            moveFront(M->rows[i]);
            while(index(M->rows[i]) != -1){
                fprintf(out, " (%d, %.1f)", ((Entry)get(M->rows[i]))->column,((Entry)get(M->rows[i]))->value);
                moveNext(M->rows[i]);
            }
            fprintf(out, "\n");
        }
    }
}
