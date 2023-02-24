/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#5
// ListTest.c
// Test client for the List ADT
*********************************************************************************/ 
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   //testing constructor
   int i, n=10;
   List A, B, C, D;

   //testing insert Before/After

   A.insertAfter(5);
   A.insertBefore(10);
   A.insertAfter(21);
   A.insertBefore(1);   
   A.insertBefore(2);
   A.insertBefore(2);
   A.insertBefore(2);
   A.insertBefore(2);
   A.insertBefore(2);
   A.insertAfter(6);

   B.insertAfter(2);
   B.insertBefore(8);
   B.insertAfter(1);
   B.insertBefore(7);   
   B.insertAfter(3);
   B.insertBefore(0);
   B.insertAfter(3);
   B.insertBefore(4);
   B.insertAfter(5);
   B.insertBefore(8);

   for(i=1; i<=n; i++){
      C.insertBefore(i);
      D.insertAfter(i);
   }

   cout << "A = " << A << endl;
   cout << "length: " << A.length() << endl;
   cout << "front: " << A.front() << endl;
   cout << "back: " << A.back() << endl;
   cout << "position: " << A.position() << endl;


   //testing position
   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   cout << endl << "B: ";
   cout << B.movePrev() << " ";
   cout << B.moveNext() << " ";
   cout << B.movePrev() << " ";

   cout << endl << "B.position() = " << B.position() << endl;
   

   cout << endl << "D: ";
   cout << D.moveNext() << " ";
   cout << D.moveNext() << " ";
   cout << D.moveNext() << " ";
   cout << D.movePrev() << " ";
   cout << D.movePrev() << " ";

   cout << endl << "D.position() = " << D.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "D==C is " << (D==A?"true":"false") << endl;
   cout << endl;

   //testing manipulation procedures
   A.moveFront();
   A.moveNext();
   A.moveNext();
   B.moveBack();
   C.moveFront();
   D.moveBack();

   cout << A.findNext(21) << endl;
   cout << "A = " << A << endl;
   A.eraseBefore();
   A.eraseAfter();
   cout << A << endl;
   cout << A.position() << endl;
   cout << A.findPrev(2) << endl;
   
   cout << C.findNext(8) << endl;
   cout << "C = " << A << endl;
   C.eraseBefore();
   C.eraseAfter();
   cout << C.position() << endl;
   cout << C.findPrev(2) << endl;
   cout << C << endl;
   cout << endl;


   cout << "B peekNext: " << C.peekNext() << endl;

   A.cleanup();
   cout << "A = " << A << endl;
   cout << endl;

   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;

   List F = D.concat(A);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   F.moveBack();
   for( i=8; i>=0; i--){
      cout << "peekNext: " << F.peekPrev() << endl;
      cout << F.movePrev() << endl; 
   }
   cout << "F = " << F << endl;
   cout << endl;
   F.clear();

   return( EXIT_SUCCESS );
}

/* output

A = (10, 1, 2, 2, 2, 2, 2, 6, 21, 5)
length: 10
front: 10
back: 5
position: 7

A = (10, 1, 2, 2, 2, 2, 2, 6, 21, 5)
A.position() = 7
B = (8, 7, 0, 4, 8, 5, 3, 3, 1, 2)
B.position() = 5
C = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
C.position() = 10
D = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
D.position() = 0


B: 8 8 8 
B.position() = 4

D: 10 9 8 8 9 
D.position() = 1

A==B is false
D==C is false

9
A = (10, 1, 2, 2, 2, 2, 2, 6, 21, 5)
(10, 1, 2, 2, 2, 2, 2, 6)
8
6
8
C = (10, 1, 2, 2, 2, 2, 2, 6)
7
1
(1, 2, 3, 4, 5, 6, 7, 10)

B peekNext: 2
A = (10, 1, 2, 6)

E==A is true

F = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 1, 2, 6)
length: 14
front: 10
back: 6
position: 0
peekNext: 6
6
peekNext: 2
2
peekNext: 1
1
peekNext: 10
10
peekNext: 1
1
peekNext: 2
2
peekNext: 3
3
peekNext: 4
4
peekNext: 5
5
F = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 1, 2, 6)

*/