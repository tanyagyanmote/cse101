/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#6
// BigIntegerTest.c
// Test client for the BigInteger ADT
*********************************************************************************/ 
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

#define BASE 1000000000
#define POWER 9


int main(){
   string s1 = "1234509876123456098763434567687898909";
   string s2 = "9909030945390487646444";
   string s3 = "42534794048362528900000938373";
   string s4 = "3939039485765778393000";
   string s5 = "123456789098765432123456789098765432123456789";
   string s6 = "09898798768765654564787790989098098909098";

   //testing constructor
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s2);
   BigInteger C = BigInteger(s1);
   BigInteger D = BigInteger(s2); 
   BigInteger E = BigInteger(s2);

   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << "E = " << E << endl;

   cout << endl;

   BigInteger F = C+B;
   BigInteger G = B+E;
   BigInteger H = A-A;
   BigInteger I = E-A;
   BigInteger J = C*B;
   BigInteger K = B*E;
   BigInteger L = D*E;

   cout << "(A==E) = " << ((A==E)?"True":"False") << endl;
   cout << "(D>E)  = " << ((D>E)? "True":"False") << endl;
   cout << "(I<=B) = " << ((I<=B)?"True":"False") << endl;
   cout << "(K>B)  = " << ((K>B)? "True":"False") << endl;
   cout << "(L>=F) = " << ((L>=K)?"True":"False") << endl << endl;

   cout << "F = " << F << endl;
   cout << "G = " << G << endl;
   cout << "H = " << H << endl;
   cout << "I = " << I << endl;
   cout << "J = " << J << endl;
   cout << "K = " << K << endl;
   cout << "L = " << L << endl;

   cout << "(F==F) = " << ((F==F)?"True":"False") << endl;
   cout << "(G==H) = " << ((G==H)?"True":"False") << endl;
   cout << "(I==K) = " << ((I==K)?"True":"False") << endl;
   cout << "(J==L) = " << ((J==L)?"True":"False") << endl;

   cout << endl;

   A += B;
   B -= C;
   C *= D;
   D += E;
   E -= C;
   F *= D;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "D = " << A << endl;
   cout << "E = " << B << endl;
   cout << "F = " << C << endl;
   cout << endl;

   cout << A*B*D*G*H << endl << endl;

   cout << endl;

   //exceptions tests
   try{
      BigInteger J = BigInteger(" ");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("-");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("376435444$$###4982379487293847");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("4385045-112");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;

   return EXIT_SUCCESS;
}

/* output

A = 1234509876123456098763434567687898909
B = 9909030945390487646444
C = 1234509876123456098763434567687898909
D = 9909030945390487646444
E = 9909030945390487646444

(A==E) = False
(D>E)  = False
(I<=B) = True
(K>B)  = True
(L>=F) = True

F = 1234509876123466007794379958175545353
G = 19818061890780975292888
H = 0
I = -1234509876123446189732489177200252465
J = 12232796564897503979035171728091378974375179260714805329596
K = 98188894276706301369660111021185374345845136
L = 98188894276706301369660111021185374345845136
(F==F) = True
(G==H) = False
(I==K) = False
(J==L) = False

A = 1234509876123466007794379958175545353
B = -1234509876123446189732489177200252465
C = 12232796564897503979035171728091378974375179260714805329596
D = 1234509876123466007794379958175545353
E = -1234509876123446189732489177200252465
F = 12232796564897503979035171728091378974375179260714805329596

0


BigInteger: Constructor: non-numeric string
   continuing without interruption
BigInteger: Constructor: empty string
   continuing without interruption
BigInteger: Constructor: non-numeric string
   continuing without interruption
BigInteger: Constructor: non-numeric string
   continuing without interruption

*/
