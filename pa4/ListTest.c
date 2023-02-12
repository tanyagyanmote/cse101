/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#4
// ListTest.c
// Test client for the List ADT
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List C = newList();
   char X[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
              'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
   int i, u=-1, v=-2, w=-3; 
   bool equal = false;

   //testing append and prepend
   //initialize Lists A and B
   for(i=0; i<=25; i++){
      append(A, &X[i]);
   }
   //testing access fucntions, movefront,next,back,prev and index
   // print both lists of integers in forward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");

   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");

   // make a shallow copy of A
   moveFront(A);
   while( index(A)>=0 ){
      append(C, get(A));
      moveNext(A);
   }
   // print the copy in forward direction
   for(moveFront(C); index(C)>=0; moveNext(C)){
      printf("%c ", *(char*)get(C));
   }
   printf("\n");

   // check shallow equality of A and C by comparing pointers
   equal = (length(A)==length(C));
   moveFront(A);
   moveFront(C);
   while( index(A)>=0 && equal){
      equal = ( get(A)==get(C) );
      moveNext(A);
      moveNext(C);
   }
   printf("A equals C is %s\n", (equal?"true":"false") );

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A);     
   printf("index(A)=%d\n", index(A));
   insertBefore(A, &u);                
   printf("index(A)=%d\n", index(A));
   for(i=0; i<9; i++) moveNext(A);     
   printf("index(A)=%d\n", index(A));
   insertAfter(A, &v);                 
   printf("index(A)=%d\n", index(A));
   for(i=0; i<5; i++) movePrev(A);     
   printf("index(A)=%d\n", index(A));
   delete(A);                          
   printf("index(A)=%d\n", index(A));
   moveBack(A);                        
   printf("index(A)=%d\n", index(A));
   for(i=0; i<10; i++) movePrev(A);    
   printf("index(A)=%d\n", index(A));
   set(A, &w);

   // print A in forward and backward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");

   // check length of A, before and after clear()
   printf("%d\n", length(A));
   clear(A);

   freeList(&A);
   freeList(&C);

   return(0);
}

/*
Ouput of Program
a b c d e f g h i j k l m n o p q r s t u v w x y z 
z y x w v u t s r q p o n m l k j i h g f e d c b a 
a b c d e f g h i j k l m n o p q r s t u v w x y z 
A equals C is true
index(A)=5
index(A)=6
index(A)=15
index(A)=15
index(A)=10
index(A)=-1
index(A)=26
index(A)=16
a b c d e ? f g h i k l m n o ? ? q r s t u v w x y z 
z y x w v u t s r q ? ? o n m l k i h g f ? e d c b a 
27
*/