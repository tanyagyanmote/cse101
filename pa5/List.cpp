
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
    // load elements of L into this
	Node* N = L.frontDummy;
	while(N != L.backDummy){
		this->insertAfter(N->data);
		N = N->next;
	}
}

List::~List() {
    Node *N = backDummy->prev;
    while (N != nullptr) {
        delete N->next;
        N = N->prev;
    }
    delete frontDummy;
}

int List::length() const{
    return num_elements;
}

ListElement List::front() const{
    // pre: length()>0
    return frontDummy->next->data;
}

ListElement List::back() const{
    // pre: length()>0
    return backDummy->prev->data;
}

int List::position() const{
    //pre: 0 <= position() <= length().
    return pos_cursor;
}

ListElement List::peekNext() const{
   // pre: position()<length()
    return afterCursor->data;
}

ListElement List::peekPrev() const{
   // pre: position()<length()
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

void List::clear(){
    moveFront();
    while(frontDummy->next != backDummy){
        eraseAfter();
    }
    return;
}

void List::moveFront(){
    if (num_elements == 0) {
        return;
    }
    else {
        pos_cursor = 0;
        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
    }
}

void List::moveBack(){
    if (num_elements == 0) {
        return;
    }
    else{
        pos_cursor = num_elements;
        beforeCursor = backDummy->prev;
        afterCursor = backDummy;
    }
}

ListElement List::moveNext(){
    // pre: position()<length() 
    beforeCursor = afterCursor;
    afterCursor = afterCursor -> next;
    pos_cursor += 1;
    return  beforeCursor->data;
}

ListElement List::movePrev(){
    // pre: position()>0
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor -> prev;
    pos_cursor -= 1;
    return  afterCursor->data;
}

void List::insertAfter(ListElement x){
    Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements += 1;
}

void List::insertBefore(ListElement x){
    Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    pos_cursor += 1;
    num_elements += 1;
}

void List::setAfter(ListElement x){
   // pre: position()<length()
   afterCursor->data = x;

}

void List::setBefore(ListElement x){
    // pre: position()>0
    beforeCursor->data = x;

}

void List::eraseAfter(){
    // pre: position()<length()
    Node *N = afterCursor;
    afterCursor -> next -> prev = beforeCursor; 
    beforeCursor -> next = afterCursor -> next;
    afterCursor = afterCursor -> next;
    num_elements += -1;
    delete N;
}

void List::eraseBefore(){
    // pre: position()>0
    Node *N = beforeCursor;
    beforeCursor -> prev -> next = afterCursor; 
    afterCursor -> prev = beforeCursor -> prev;
    beforeCursor = afterCursor -> prev;
    num_elements += -1;
    pos_cursor += -1;
    delete N;
}

// Other Functions ---------------------------------------------------------

int List::findNext(ListElement x){
    //moveFront();
    while(position() < length()){
        if((moveNext()) == x){
            return pos_cursor;
        }
    }
    return -1;
}

int List::findPrev(ListElement x){
    //moveBack();
    while(position() > 0){
        if((movePrev()) == x){
            return pos_cursor;
        }
    }
    return -1;
}

// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    int counter = 0;
    //iterate for each element in the list
    List Copy;
    Node *copy_node = this->frontDummy->next;
    while (copy_node != this->backDummy) {
        Copy.insertBefore(copy_node->data);
        copy_node = copy_node->next;
    }
    
    while(position() < length()){
        Copy.moveFront();
        Node *check = Copy.afterCursor;
        //iterate the number of elements in the list to check
        while(position() < length()){
            //if 
            moveFront();
            if(afterCursor->data != check->data){
                moveNext();
            }
            //if it's found
            else {
                counter += 1;
                if (counter > 1){
                    this->eraseAfter();
                }
            }
            Copy.moveNext();

        }
        check = check -> next;
    }
}

// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List NL;
    Node *T = this->frontDummy->next;
    Node *N = L.frontDummy->next;
    while (T != this->backDummy) {
        NL.insertBefore(T->data);
        T = T->next;
    }
    while (N != L.backDummy) {
        NL.insertBefore(N->data);
        N = N->next;
    }
    NL.moveFront();
    return NL;
}

std::string List::to_string() const{
    Node *N = nullptr;
    std::string s = "";
    for(N = frontDummy->next;N!=backDummy;N=N->next){
        s+=std::to_string(N->data) + " ";
    }
    return s;
}

// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eq;
    Node *N = nullptr;
    Node *M = nullptr;
    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy;
    M = R.frontDummy;
    while( eq && N!=NULL){
        eq = ( N->data==M->data );
        N = N -> next;
        M = M -> next;
    }
    return eq;
}

// Overriden Operators -----------------------------------------------------
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
    //not sure  
    return *this;
}


