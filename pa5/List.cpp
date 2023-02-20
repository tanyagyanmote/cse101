
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




