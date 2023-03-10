#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

//using mikes puesdocode 

// Dictionary::Node::Node(keyType k, valType v){
//    set key to k, val to v, left & right & parent nodes to null pointers
// }

// Dictionary::Dictionary(){
//    set nil to a new Node("someLongAssStringHere", 999) // key shouldn't be something in the dictionary
//    set the root to nil
//    set current nil
//    set num_pairs to 0
// }

// // Copy constructor.
// Dictionary::Dictionary(const Dictionary& D){
//    // create an empty Dictionary
//    set nil to a new Node("someLongAssStringHere", 999) // key shouldn't be something in the dictionary
//    set the root to nil
//    set current nil
//    set num_pairs to 0
//    pre order copy the pairs of D (root of D, nil of D) into this Dictionary 

// }

// // Destructor
// Dictionary::~Dictionary(){
//    post order delete on the root node
//    delete nil
// }

Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

Dictionary::Dictionary(){
    nil = new Node("somereallylongstring", 999);
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary &D){
    nil = new Node("somereallylongstring", 999);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary(){
	postOrderDelete(root);
	delete nil;
}

