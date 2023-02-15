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
   //constructor testing..
   List A = newList();
   List B = newList();
   List C = newList();
   char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
              'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
   int i, w=-3; 
   bool equal = false;

   //testing append and prepend
   //initialize Lists A and B
   for(i=0; i<26; i++){
      append(A, &alphabet[i]);
   }
   for (int i = 0; i < 26; i++) {
      prepend(B, &alphabet[i]);
   }
   // testing access fucntions, movefront,next,back,prev and index
   // print both lists of alphabet in forward direction
   printf("List A printed from the Front\n");
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");

   printf("List A printed from the Back\n");
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");

   // make copy of A
   moveFront(A);
   while( index(A)>=0 ){
      append(C, get(A));
      moveNext(A);
   }
   printf("Copied List of A\n");
   // print the copy in forward direction
   for(moveFront(C); index(C)>=0; moveNext(C)){
      printf("%c ", *(char*)get(C));
   }
   printf("\n");

   // check equality of A and C 
   equal = (length(A)==length(C));
   moveFront(A);
   moveFront(C);
   while( index(A)>=0 && equal){
      equal = ( get(A)==get(C) );
      moveNext(A);
      moveNext(C);
   }
   printf("A equals C is %s\n", (equal?"true":"false") );
   
   printf("Front of List A = %c\n", *(char*)front(A));
   printf("Back of List A = %c\n", *(char*)back(A));
   //testing delete back and front
   printf("Deleting back and front of List A\n");
   deleteBack(A);
   deleteFront(A);
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");
   //testing insertbefore and after
   moveFront(A);
   for(i=0; i<5; i++) moveNext(A);     
   printf("index(A)=%d\n", index(A));
   insertBefore(A, &alphabet[3]);                
   printf("index(A)=%d\n", index(A));
   for(i=0; i<9; i++) moveNext(A);     
   printf("index(A)=%d\n", index(A));
   insertAfter(A, &alphabet[9]);                 
   printf("index(A)=%d\n", index(A));
   for(i=0; i<5; i++) movePrev(A);     
   printf("index(A)=%d\n", index(A));
   moveBack(A);                        
   printf("index(A)=%d\n", index(A));
   for(i=0; i<10; i++) movePrev(A);    
   printf("index(A)=%d\n", index(A));

   printf("List A printed from the Front\n");
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");

   //testing set
   //set(A, &w);
   //testing delete
   printf("Deleting 10 elements in List A\n");
   for (int i = 0; i < 10; i++) {
      moveFront(A);
      delete(A);
   }
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");
   // check length of A, before and after clear()
   printf("%d\n", length(A));
   //testing clear
   clear(A);
   //testing free list
   freeList(&A);
   freeList(&C);

   return(0);
}

/*
Ouput of Program
List A printed from the Front
a b c d e f g h i j k l m n o p q r s t u v w x y z 
List A printed from the Back
z y x w v u t s r q p o n m l k j i h g f e d c b a 
Copied List of A
a b c d e f g h i j k l m n o p q r s t u v w x y z 
A equals C is true
Front of List A = a
Back of List A = z
Deleting back and front of List A
b c d e f g h i j k l m n o p q r s t u v w x y 
index(A)=5
index(A)=6
index(A)=15
index(A)=15
index(A)=10
index(A)=25
index(A)=15
List A printed from the Front
b c d e f d g h i j k l m n o p j q r s t u v w x y 
Deleting 10 elements in List A
k l m n o p j q r s t u v w x y 
16
*/