
/*********************************************************************************
* Tanya Gyanmote, tgyanmot
* 2023 Winter CSE101 PA5
* List.cpp
* List ADT
*********************************************************************************/
#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

//puesdo idea from Queue.c (constructor/destructor)
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // load elements of L
	Node* N = L.frontDummy->next;
	while(N != L.backDummy){
		this->insertBefore(N->data);
		N = N->next;
	}
}

//puesdo from arka
List::~List() {
    clear();
	delete(frontDummy);
	delete(backDummy);
}

int List::length() const{
    return num_elements;
}

ListElement List::front() const{
    // pre: length()>0
    if( length()==0 ){
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;
}

ListElement List::back() const{
    // pre: length()>0
    if( length()==0 ){
        throw std::length_error("List: back(): empty List");
    }
    return backDummy->prev->data;
}

int List::position() const{
    //pre: 0 <= position() <= length().
    return pos_cursor;
}

ListElement List::peekNext() const{
   // pre: position()<length()
    if(position() >= length()){
        throw std::range_error("List: peekNext(): cursor at front");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const{
   // pre: position()<length()
    if(position()<=0){
        throw std::range_error("List: peekPrev(): cursor at back");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------
//copied clear from list.c
void List::clear(){
    moveFront();
    while(frontDummy->next != backDummy){
        eraseAfter();
    }
    return;
}

void List::moveFront(){
    if (num_elements != 0) {
        pos_cursor = 0;
        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
    }
}

void List::moveBack(){
    if (num_elements != 0) {
        pos_cursor = num_elements;
        beforeCursor = backDummy->prev;
        afterCursor = backDummy;
    }
}

ListElement List::moveNext(){
    //pre: position()<length() 
    if(position()>=length()){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor -> next;
    pos_cursor += 1;
    return beforeCursor->data;
}

ListElement List::movePrev(){
    // pre: position()>0
    if(position()<=0){
        throw std::range_error("List: movePrev(): cursor at front");
    }
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor -> prev;
    pos_cursor -= 1;
    return  afterCursor->data;
}


void List::insertAfter(ListElement x){
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements += 1;
}

void List::insertBefore(ListElement x){
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements += 1;
    pos_cursor += 1;
}


// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.

// puesdo idea from aaron
List List::concat(const List& L) const{
    List NL;
    Node *one = this->frontDummy->next;
    Node *two = L.frontDummy->next;
    while (one != this->backDummy) {
        NL.insertAfter(one->data);
        one = one->next;
    }
    while (two != L.backDummy) {
        NL.insertAfter(two->data);
        two = two->next;
    }
    NL.moveFront();
    return NL;
}

std::string List::to_string() const{
    Node *N = nullptr;
    std::string s = "(";
    for(N = frontDummy->next;N!=backDummy->prev;N=N->next){
        s+=std::to_string(N->data) + ", ";
    }
    s+=std::to_string(N->data) + ")";
    return s;
}

// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eq = false;
    Node *N = nullptr;
    Node *M = nullptr;
    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while( eq && N!=NULL){
        eq = ( N->data==M->data );
        N = N -> next;
        M = M -> next;
    }
    return eq;
}

// Overriden Operators -----------------------------------------------------

// idea from queue.cpp puesdo 

// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if( this != &L ){ // not self assignment
        // make a copy of L
        List temp = L;
        // then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
        //do i need?
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
    }
   // return this with the new data installed
   return *this;
   // the copy, if there is one, is deleted upon return
}


