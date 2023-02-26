
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

void List::setAfter(ListElement x){
   // pre: position()<length()
    if(position()>=length()){
        throw std::range_error("List: setAfter(): cursor at back");
    }
   afterCursor->data = x;

}

void List::setBefore(ListElement x){
    // pre: position()>0
    if(position()<=0){
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;

}
//puesdo help arka,sara
void List::eraseAfter(){
    // pre: position()<length()
    if(position()>=length()){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    Node *N = afterCursor;
    afterCursor -> next -> prev = beforeCursor; 
    beforeCursor -> next = afterCursor -> next;
    afterCursor = afterCursor -> next;
    num_elements += -1;
    delete N;
}

void List::eraseBefore(){
    // pre: position()>0
    if(position()<=0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    Node *N = beforeCursor;
    beforeCursor -> prev -> next = afterCursor; 
    afterCursor -> prev = beforeCursor -> prev;
    beforeCursor = afterCursor -> prev;
    num_elements += -1;
    pos_cursor += -1;
    delete N;
}
// Other Functions ---------------------------------------------------------

//iterate through list and search
int List::findNext(ListElement x){
	Node* N = afterCursor;
	for(; afterCursor != backDummy; N = N->next){
		if(N->data == x){
			moveNext();
            // std::cout << "position" << position() << std::endl;
			return position();
		}
		moveNext();
	}
	return -1;
}

int List::findPrev(ListElement x){
	Node* N = beforeCursor;
	for(; beforeCursor != frontDummy; N = N->prev){
        // std::cout << "data" << N->data << std::endl;
		if(N->data == x){
			movePrev();
            // std::cout << "position" << position() << std::endl;
			return position();
		}
		movePrev();
	}
	return -1;
}

// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.

//puesdo idea: norton, sid
void List::cleanup(){
    Node *A = frontDummy->next;
    Node *B = nullptr;
    //two counters one for each node created
    //increment everytime node moved next ->next
    int counter = 0;
    int counter2 = 0;
    while(A != backDummy){
        B = A;
        counter = counter2;
        while(B->next != backDummy){
            if(A->data == B->next->data){
                if(B->next == afterCursor){
                    afterCursor = afterCursor->next;
                }
                if(B->next == beforeCursor){
                    beforeCursor = beforeCursor->prev;
                }
                //new node to delete duplicate
                Node *C = B->next;
                B->next->next->prev = B;
                B->next = B->next->next;
                counter++;
                delete C;
                num_elements--;
                if(counter < pos_cursor){
                    pos_cursor --;
                    counter--;
                }
            }
            else{
                B = B->next;
                counter++;
            }
            // std::cout << "position" << pos_cursor << std::endl;
            // std::cout << "counter" << counter << std::endl;
        }
        A = A -> next;
        counter2 ++;
    }
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


