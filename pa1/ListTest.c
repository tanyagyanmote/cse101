/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#1 
* ListTest.c 
* Tests for List ADT 
*********************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main(int argc, char* argv[]){
   // Constructor testing --------------------------------------------------------
   List A = newList();
   List B = newList();
   //testing printlist
   append(A,1);
   append(A,2);
   append(A,3);
   B = copyList(A);
   printList(stdout, A);
   printf("\n");

   // Access/Manipulation functions testing --------------------------------------

   //testing manipulation fcn moveBack, and access fcn index
   moveBack(A);
   if(index(A) == -1){
      fprintf(stderr, "List A cursor not set -> moveBack fail");
      exit(EXIT_FAILURE);
   }
   //testing manipulation fcn moveFront, and access fcn index
   moveFront(A);
   if(index(A) != 0){
      fprintf(stderr, "List A cursor not set to Front -> moveFront fail");
      exit(EXIT_FAILURE);
   }
   //testing if append worked, and access fucntion of length
   if(length(A) != 3){
      fprintf(stderr, "List A doesn't have length of 3 -> append fail");
      exit(EXIT_FAILURE);
   }
   //testing if front and back elements were set properly
   if(front(A) != 1){
      fprintf(stderr, "List A's front element not set correctly -> front fail");
      exit(EXIT_FAILURE);
   }
   if(back(A) != 3){
      fprintf(stderr, "List A's back element not set correctly -> back fail");
      exit(EXIT_FAILURE);
   }
   //testing get
   if(get(A) != 1){
      fprintf(stderr, "List A's cursor not set correctly -> get fail");
      exit(EXIT_FAILURE);
   }
   //testing copy and equals
   if(!equals(B,A)){
      fprintf(stderr, "List B was not copied correctly from List A -> copy fail");
      exit(EXIT_FAILURE);
   }
   //testing moveNext/movePrev
   moveNext(A);
   if(get(A) != 2){
      fprintf(stderr, "List A's cursor not set correctly -> moveNext fail");
      exit(EXIT_FAILURE);
   }
   movePrev(A);
   if(get(A) != 1){
      fprintf(stderr, "List A's cursor not set correctly -> moveBack fail");
      exit(EXIT_FAILURE);
   }
   //testing delete and clear
   printList(stdout, A);
   printf("\n");
   delete(A);
   if (index(A) != -1) {
     printf("index is not -1!\n");
     return 1;
   }
   clear(A);
   //testing prepend
   prepend(B,4);
   prepend(B,5);
   prepend(B,6);
   printList(stdout, B);
   printf("\n");
   moveFront(B);
   set(B, 7);
   //testing set
   if (front(B) != 7) {
      fprintf(stderr, "List B's front was not set to 7 -> set fail");
      exit(EXIT_FAILURE);
   }
   insertAfter(B,8);
   moveNext(B);
   //testing insertAfter and movenext
   if (get(B) != 8) {
      fprintf(stderr, "List B's 8 was not inserted -> insertAfter/moveNext fail");
      exit(EXIT_FAILURE);
   }
   //testing insertAfter and movenext
   insertBefore(B, 9);
   movePrev(B);
   if (get(B) != 9) {
      fprintf(stderr, "List B's 9 was not inserted -> insertBefore/movePrev fail");
      exit(EXIT_FAILURE);
   }
   deleteFront(B);
   moveFront(B);
   if (get(B) != 9) {
      fprintf(stderr, "List B's front was not deleted properly -> deleteFront fail");
      exit(EXIT_FAILURE);
   }
   deleteBack(B);
   moveBack(B);
   if (get(B) != 2) {
      fprintf(stderr, "List B's back was not deleted properly -> deleteback fail");
      exit(EXIT_FAILURE);
   }
   printList(stdout, B);
   printf("\n");
   delete(B);
   clear(B);
   List C = newList();
   append(C, 2);
   printf("List C append 2 success\n");
   append(C, 4);
   printf("List C append 4 success\n");
   append(C, 6);
   printf("List C append 6 success\n");
   append(C, 8);
   printf("List C append 8 success\n");
   int len = length(C);
   printf("len: %d\n", len);
   if (length(C) != 4) {
      fprintf(stderr,"Length is not equal to 4!");
      exit(EXIT_FAILURE);
   }
   moveBack(C);
   if (index(C) != 3) {
      fprintf(stderr,"Index is not 4!\n");
      exit(EXIT_FAILURE);
   }
   delete(C);
   clear(C);
   printf("sucessfully completed all tests\n");
   freeList(&A);
   printf("freed A\n");
   freeList(&B);
   printf("freed B\n");
   freeList(&C);
   printf("freed C\n");
   return 0;

}
/*
Output of this program:
1 2 3 
1 2 3 
6 5 4 1 2 3 
9 8 5 4 1 2 
List C append 2 success
List C append 4 success
List C append 6 success
List C append 8 success
len: 4
sucessfully completed all tests
freed A
freed B
freed C
*/

