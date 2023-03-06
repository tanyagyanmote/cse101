/*********************************************************************************
* Tanya Gyanmote, tgyanmot
* 2023 Winter CSE101 PA6
* BigInteger.cpp
* BigInteger ADT
*********************************************************************************/
#include<iostream>
#include<stdexcept>
#include <sstream>
#include<string>
#include"List.h"
#include"BigInteger.h"
#include <algorithm> 
#include <cstring>
#include <iomanip>

#include<cctype>

// #define BASE 1000000000
// #define POWER 9
const ListElement BASE = 1000000000;
const int POWER = 9;

//using namespace std;

BigInteger::BigInteger() {
	signum = 0;
	List digits;
}

BigInteger::BigInteger(std::string s){
    int i = 0;
    int counter = 0;
    signum = 1;
    std::string num = std::string();
    if (s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    if(s[0] == '0'){
        signum = 0;
    }
    if(s[0] == '+'){
        if(s.length() == 1){
            throw std::invalid_argument("BigInteger: Constructor: empty string");
        }
        s.erase(0,1);
        signum = 1;
    }
    if(s[0] == '-'){
        if(s.length() == 1){
            throw std::invalid_argument("BigInteger: Constructor: empty string");
        }
        s.erase(0,1);
        signum = -1;
    }
    //puesdo idea: norton
    if(s.find_first_not_of("0123456789") != std::string::npos){
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");

    }
    //add to string
    for(i = s.length()-1; i >= 0;i--){
        counter ++;
        num += s[i];
        if(counter == POWER){
            //reverse it
            reverse(num.begin(),num.end());
            digits.insertAfter(std::stol(num));
            num = "";
            counter = 0;
        }
    }
    for(int i =0;i<POWER-counter;i++){
        num+='0';
    }
    reverse(num.begin(),num.end());
    digits.insertAfter(std::stol(num));
    //std::cout << "digits:" << digits << std::endl;
}

BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum;
    digits = N.digits;
}


// Helper Fucntion  --------------------------------------------------------

void negateList(List& L) {
	L.moveFront();
	while(L.position() != L.length()) {
		long el = L.moveNext();
		L.setBefore(-1 * el);
	}
}

int normalizeList(List& L){
    int sign = 1;
    int carry = 0;
    L.moveBack();
    while(L.position() > 0){
        if(carry != 0){
            L.setBefore(L.peekPrev() + carry);
            carry = 0;
        }
        //long ele = L.peekPrev();
        //puesdo idea from simon
        if(L.peekPrev() >= BASE){
            carry = (L.peekPrev()/BASE);
            L.setBefore(L.peekPrev() - (carry*BASE));
            L.movePrev();
        }
        else if(L.peekPrev() < 0 && L.position() > 1){
            carry = (L.peekPrev()-BASE+1)/BASE;
            L.setBefore(L.peekPrev() - (carry*BASE));
            L.movePrev();
        }
        else{
            L.movePrev();
        }
    }
    if(carry > 0){
        L.insertBefore(carry);
    }
    if(L.front() < 0){
        negateList(L);
        normalizeList(L);
        return -1;
    }
    while(L.position() < L.length()-1){
        if(L.peekNext() == 0){
            L.eraseAfter();
        }
        else{
            break;
        }
    }
    return (sign>0) ? 1:-1;
}

void sumList(List& S, List A, List B, int sgn){
    S.clear();
    A.moveBack();
    B.moveBack();
    while((A.position() != 0 && B.position() != 0)){
        long element_one = A.movePrev();
		long element_two = (sgn)*B.movePrev();
		S.insertAfter(element_one + element_two);
    }
    while(A.position() != 0){
        long element_one = (A.movePrev());
        S.insertAfter(element_one);

    }
    while(B.position() != 0){
        long element_two = (sgn)*B.movePrev();
        S.insertAfter(element_two);
    }

    //std::cout << S << std::endl; 
}

void shiftList(List& L, int p) {
	L.moveBack();
    for(int i = 0; i < p;i++){
        L.insertBefore(0);
    }
}

void scalarMultList(List& L, ListElement m) {
	L.moveBack();
	while (L.position() != 0) {
        L.setBefore(L.peekPrev() * m);
        L.movePrev();
	}
}


// Access functions --------------------------------------------------------

int BigInteger::sign() const{
    return signum;
}
//using mikes puesdocode
int BigInteger::compare(const BigInteger& N) const{
	List T = this->digits;
	List L = N.digits;
	T.moveFront();
	L.moveFront();
    if (this->signum > N.signum){
        return 1;
    }
    if (this->signum < N.signum){
        return -1;
    }
    if(T.length() > L.length()){
        return 1;
    }
    if(L.length() > T.length()){
        return -1;
    }
    while((T.position() < T.length()) && (L.position() < L.length())){
        long ele1 = T.moveNext();
        long ele2 = L.moveNext();
        if(ele1 > ele2){
            return 1;
        }
        if(ele2 > ele1){
            return -1;
        }
    }
    return 0;

}

// Manipulation procedures -------------------------------------------------

void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

void BigInteger::negate(){
    signum = -signum;
}

// BigInteger Arithmetic operations ----------------------------------------

BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger added = BigInteger();
    List ndig = N.digits;
    List tdig = this->digits;
    //int sgn = 1;
    if(N.signum < 0){
        negateList(ndig);
        //sgn = -1;
    } 
    if(this->signum < 0){
        negateList(tdig);
        //sgn = -1;
    } 
    sumList(added.digits,tdig,ndig,1);
    added.signum = normalizeList(added.digits);
    if(added.digits.length() == 1){
        added.signum = 0;
    }
    //std::cout << added.digits << std::endl; 
    return added;

}
//ou
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger subtr = BigInteger(N);
    // List one = N.digits;
    // List two = this->digits;
    // sumList(subtr.digits,two,one,-1);
    // subtr.signum = normalizeList(subtr.digits);
    // if(subtr.digits.length() == 1){
    //     subtr.signum = 0;
    // }
    // std::cout << subtr.digits << std::endl; 
    // return subtr;
    subtr.negate();
    return add(subtr);
}

BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger Prod = BigInteger();
    int col = 0; // column number
    List A = this->digits;
    List B = N.digits;
    List C;
    List& P = Prod.digits;
    Prod.signum = this->signum * N.signum;
    B.moveBack();
    while(B.position() != 0){
        C = A;
        long ele = B.movePrev();
        scalarMultList(C,ele);
        shiftList(C,col);
        sumList(P,C,P,1);
        normalizeList(P);
        //std::cout << "hi" << std::endl; 
        col ++;
    }
    //std::cout << Prod.digits << std::endl; 
    return Prod;
}

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
// Other Functions ---------------------------------------------------------

std::string BigInteger::to_string(){
	// std::string s = "";
	// if(this->signum == 0) {
	// 	s += "0";
	// 	return s;
	// }
	// if(this->signum == -1) {
	// 	s += "-";
	// }
    std::string s = "";
    if(this->signum == 0) {
        s += "0";
        return s;
    }
    List L = this->digits;
    L.moveFront();
    while(L.position() < L.length()) {
        std::string num = std::to_string(L.moveNext());
        while ((int)num.length() < POWER && L.position() != 1){
            num = '0' + num;
        }
        s += num;
    }
    while(s[0] == '0'){
        s.erase(0,1);
    }
    if(sign() == -1){
        s.insert(0,1,'-');
    }
    return s;
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0) {
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == -1) {
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) <= 0) {
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 1) {
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) >= 0) {
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.add(B);
    return C;
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.BigInteger::add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.sub(B);
    return C;
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.BigInteger::sub(B);
    return A;
    // A = A.sub(B);
    // return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.mult(B);
    return C;
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.BigInteger::mult(B);
    return A;
}