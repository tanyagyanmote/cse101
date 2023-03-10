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

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    // InOrderTreeWalk(x)
    // if x != NIL
    //     InOrderTreeWalk(x.left)
    //     print(x.key)
    //     InOrderTreeWalk(x.right)
    if(R != nil){
        inOrderString(s,R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s,R->right);
    }

}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    // if x != NIL
    // print(x.key)
    // PreOrderTreeWalk(x.left)
    // PreOrderTreeWalk(x.right)
    if(R != nil){
        s += R->key + "\n";
        preOrderString(s,R->left);
        preOrderString(s,R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R != N){
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
    // if x != NIL
    // PostOrderTreeWalk(x.left)
    // PostOrderTreeWalk(x.right)
    // print(x.key)
    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

