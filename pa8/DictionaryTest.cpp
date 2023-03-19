/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#8
* DictionaryTest.cpp 
* Doing arithmetic operations on big integers
*********************************************************************************/ 

//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

    string s;
    int x;
    string S[] =   {
                        "manufacture",
                        "wing",
                        "achieve",
                        "meadow",
                        "switch",
                        "appointment",
                        "net",
                        "chase",
                        "paralyzed",
                        "weakness",
                        "view",
                        "version",
                        "god",
                        "minimum",
                        "volunteer",
                        "sacred",
                        "moon",
                        "distinct",
                        "agenda"
                    };
   string T[] =   {
                    "net",
                    "chase",
                    "paralyzed",
                    "weakness",
                    "view",
                    "version",
                    "god",
                    "minimum",
                    "volunteer",
                    "sacred",
                    "moon",
                    "distinct",
                    "agenda"     
                  };

    Dictionary A;

    cout << endl;

    cout << "A.size() = " << A.size() << endl  << A << endl;

    // insert some pairs into A
    for(int i=0; i<20; i++){
        A.setValue(S[i], i+1);
    }

    Dictionary B;

    B = A;

    cout << "A==B is " << (A==B?"true":"false") << endl;

    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << "B.size() = " << B.size() << endl  << B << endl;

    B.setValue("glide", 70);
    B.setValue("amber", 91);

    A.setValue("garbage", 90);
    A.setValue("force", 63);
    A.setValue("unique", 78);

    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << "B.size() = " << B.size() << endl  << B << endl;

    // call copy constructor
    Dictionary C;
    C = B;

    cout << "B.size() = " << B.size() << endl  << B << endl;
    cout << "C.size() = " << C.size() << endl  << C << endl;

    // check operator==()
    cout << "A==B is " << (A==B?"true":"false") << endl;
    cout << "B==C is " << (B==C?"true":"false") << endl;
    cout << "C==A is " << (C==A?"true":"false") << endl << endl;

    // remove some pairs from A
    for(int i=0; i<1; i++){
        cout << "removing " << T[i] << " from Dictionary A" << endl; 
        A.remove(T[i]);
    }

    // remove some pairs from B
    for(int i=0; i<1; i++){
        cout << "removing " << T[i] << " from Dictionary B" << endl; 
        B.remove(T[i]);
        C.remove(T[i]);
    }

    // // remove some pairs from C
    // for(int i=0; i<1; i++){
    //     cout << "removing " << T[i] << " from Dictionary C" << endl; 
    //     C.remove(T[i]);
    // }

    cout << "after remove loop" << endl;

    // check state of A
    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << A.pre_string() << endl;

    // check state of B
    cout << "B.size() = " << B.size() << endl  << B << endl;
    cout << B.pre_string() << endl;

    // check state of C
    cout << "C.size() = " << C.size() << endl  << C << endl;
    cout << C.pre_string() << endl;


    // perform alterations on A
    cout << A.getValue("manufacture") << endl;
    A.getValue("manufacture") *= 7; // change the value associated with "manufacture"
    cout << A.getValue("manufacture") << endl << endl;

    // check state of A
    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << A.pre_string() << endl;


    // do forward iteration on B
    for(B.begin(); B.hasCurrent(); B.next()){
        s = B.currentKey();
        x = B.currentVal();
        cout << "("+s+", " << x << ") ";
    }
    cout << endl << endl;

    // do reverse iteration on C
    for(C.end(); C.hasCurrent(); C.prev()){
        s = C.currentKey();
        x = C.currentVal();
        cout << "("+s+", " << x << ") ";
    }

    // do forward iteration on A
    for(A.begin(); A.hasCurrent(); A.next()){
        s = A.currentKey();
        x = A.currentVal();
        cout << "("+s+", " << x << ") ";
    }
    cout << endl << endl;

    // do reverse iteration on B
    for(B.end(); B.hasCurrent(); B.prev()){
        s = B.currentKey();
        x = B.currentVal();
        cout << "("+s+", " << x << ") ";
    }

    cout << endl << endl;
   
    // check exceptions
    try{
        C.getValue("ran");
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        B.remove("dom");
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.currentKey();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.currentVal();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }  
    try{
        A.next();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.prev();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }

    cout << endl;  

    return( EXIT_SUCCESS );

}

/*output 

A.size() = 0

A==B is true
A.size() = 20
 : 20
achieve : 3
agenda : 19
appointment : 6
chase : 8
distinct : 18
god : 13
manufacture : 1
meadow : 4
minimum : 14
moon : 17
net : 7
paralyzed : 9
sacred : 16
switch : 5
version : 12
view : 11
volunteer : 15
weakness : 10
wing : 2

B.size() = 20
 : 20
achieve : 3
agenda : 19
appointment : 6
chase : 8
distinct : 18
god : 13
manufacture : 1
meadow : 4
minimum : 14
moon : 17
net : 7
paralyzed : 9
sacred : 16
switch : 5
version : 12
view : 11
volunteer : 15
weakness : 10
wing : 2

A.size() = 23
 : 20
achieve : 3
agenda : 19
appointment : 6
chase : 8
distinct : 18
force : 63
garbage : 90
god : 13
manufacture : 1
meadow : 4
minimum : 14
moon : 17
net : 7
paralyzed : 9
sacred : 16
switch : 5
unique : 78
version : 12
view : 11
volunteer : 15
weakness : 10
wing : 2

B.size() = 22
 : 20
achieve : 3
agenda : 19
amber : 91
appointment : 6
chase : 8
distinct : 18
glide : 70
god : 13
manufacture : 1
meadow : 4
minimum : 14
moon : 17
net : 7
paralyzed : 9
sacred : 16
switch : 5
version : 12
view : 11
volunteer : 15
weakness : 10
wing : 2

B.size() = 22
 : 20
achieve : 3
agenda : 19
amber : 91
appointment : 6
chase : 8
distinct : 18
glide : 70
god : 13
manufacture : 1
meadow : 4
minimum : 14
moon : 17
net : 7
paralyzed : 9
sacred : 16
switch : 5
version : 12
view : 11
volunteer : 15
weakness : 10
wing : 2

C.size() = 22
 : 20
achieve : 3
agenda : 19
amber : 91
appointment : 6
chase : 8
distinct : 18
glide : 70
god : 13
manufacture : 1
meadow : 4
minimum : 14
moon : 17
net : 7
paralyzed : 9
sacred : 16
switch : 5
version : 12
view : 11
volunteer : 15
weakness : 10
wing : 2

A==B is false
B==C is true
C==A is false

removing net from Dictionary A
removing chase from Dictionary A
removing paralyzed from Dictionary A
removing weakness from Dictionary A
removing view from Dictionary A
removing net from Dictionary A
removing chase from Dictionary A
removing net from Dictionary A
removing chase from Dictionary A
removing paralyzed from Dictionary A
removing weakness from Dictionary A
removing view from Dictionary A
removing version from Dictionary A
removing god from Dictionary A
removing minimum from Dictionary A
removing volunteer from Dictionary A
after remove loop
A.size() = 18
 : 20
achieve : 3
agenda : 19
appointment : 6
distinct : 18
force : 63
garbage : 90
god : 13
manufacture : 1
meadow : 4
minimum : 14
moon : 17
sacred : 16
switch : 5
unique : 78
version : 12
volunteer : 15
wing : 2

manufacture
achieve

appointment
agenda
god
distinct
garbage
force
wing
meadow
switch
sacred
minimum
moon
volunteer
version
unique

B.size() = 20
 : 20
achieve : 3
agenda : 19
amber : 91
appointment : 6
distinct : 18
glide : 70
god : 13
manufacture : 1
meadow : 4
minimum : 14
moon : 17
paralyzed : 9
sacred : 16
switch : 5
version : 12
view : 11
volunteer : 15
weakness : 10
wing : 2

manufacture
achieve

appointment
agenda
amber
god
distinct
glide
wing
meadow
switch
paralyzed
minimum
moon
sacred
weakness
view
version
volunteer

C.size() = 13
 : 20
achieve : 3
agenda : 19
amber : 91
appointment : 6
distinct : 18
glide : 70
manufacture : 1
meadow : 4
moon : 17
sacred : 16
switch : 5
wing : 2

manufacture
achieve

appointment
agenda
amber
distinct
glide
wing
meadow
switch
sacred
moon

1
7

A.size() = 18
 : 20
achieve : 3
agenda : 19
appointment : 6
distinct : 18
force : 63
garbage : 90
god : 13
manufacture : 7
meadow : 4
minimum : 14
moon : 17
sacred : 16
switch : 5
unique : 78
version : 12
volunteer : 15
wing : 2

manufacture
achieve

appointment
agenda
god
distinct
garbage
force
wing
meadow
switch
sacred
minimum
moon
volunteer
version
unique

(, 20) (achieve, 3) (agenda, 19) (amber, 91) (appointment, 6) (distinct, 18) (glide, 70) (god, 13) (manufacture, 1) (meadow, 4) (minimum, 14) (moon, 17) (paralyzed, 9) (sacred, 16) (switch, 5) (version, 12) (view, 11) (volunteer, 15) (weakness, 10) (wing, 2) 

(wing, 2) (switch, 5) (sacred, 16) (moon, 17) (meadow, 4) (manufacture, 1) (glide, 70) (distinct, 18) (appointment, 6) (amber, 91) (agenda, 19) (achieve, 3) (, 20) (, 20) (achieve, 3) (agenda, 19) (appointment, 6) (distinct, 18) (force, 63) (garbage, 90) (god, 13) (manufacture, 7) (meadow, 4) (minimum, 14) (moon, 17) (sacred, 16) (switch, 5) (unique, 78) (version, 12) (volunteer, 15) (wing, 2) 

(wing, 2) (weakness, 10) (volunteer, 15) (view, 11) (version, 12) (switch, 5) (sacred, 16) (paralyzed, 9) (moon, 17) (minimum, 14) (meadow, 4) (manufacture, 1) (god, 13) (glide, 70) (distinct, 18) (appointment, 6) (amber, 91) (agenda, 19) (achieve, 3) (, 20) 

Dictionary: getValue(): key "ran" does not exist
   continuing without interruption
Dictionary: remove(): key "dom" does not exist
   continuing without interruption
Dictionary: currentKey(): current undefined
   continuing without interruption
Dictionary: currentVal(): current undefined
   continuing without interruption
Dictionary: next(): current iterator is not defined
   continuing without interruption
Dictionary: prev(): current iterator is not defined
   continuing without interruption

*/