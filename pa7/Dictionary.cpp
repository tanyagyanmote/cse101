#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

//using mikes puesdocode 

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
