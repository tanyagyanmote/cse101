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

// used puesdo from BST algorithm
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

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    // if x == NIL or k == x.key
    //     return x
    // else if k < x.key
    //     return TreeSearch(x.left, k)
    // else // k > x.key
    //     return TreeSearch(x.right, k)
    if(R == nil || k == R->key){
        return R;
    }
    else if(k < R->key){
        return search(R->left,k);
    }
    else {
        return search(R->right,k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    //pre x!=nil
    // while x.left != NIL
    //     x = x.left
    // return x
    while((R->left) != nil){
        R = (R->left);
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    //pre x!=nil
    // while x.right != NIL
    //     x = x.right
    // return x
    while((R->right) != nil){
        R = (R->right);
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 

//puesdo: mike
Dictionary::Node* Dictionary::findNext(Node* N){
//    if N is nil return nil
//    else if N->right isn't nil return the minimum of N->right
//    else:
//       set a temp Node* y to the parent node of N
// 	  iterate as long as y isn't nil and N is not y->right:
// 	      set N to y and then set y to it's parent node
//     return y;
    if(N == nil){
        return nil;
    }
    else if(nil != (N->right)){
        return findMin(N->right);
    }
    else{
        Node *y = N->parent;
        while(y != nil && N == y->right){
            N = y;
            y = y->parent;
        }
        return y;
    }
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N == nil){
        return nil;
    }
    else if(nil != (N->left)){
        return findMax(N->left);
    }
    else{
        Node *y = N->parent;
        while(y != nil && N == y->left){
            N = y;
            y = y->parent;
        }
        return y;
    }
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.

// mikes puesdo
// set a temp Node* N to search from the root if k is in the dectionary
// return N is not nil
bool Dictionary::contains(keyType k) const{
    Node *n = search(root,k);
    return (n != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)

// mikes puesdo
// set a temp Node* N to search from the root if k is in the dectionary
// if N is nil:
//     throw std::logic_error("Dictionary: getValue(): key \""+k+"\" does not exist");
// return value of N
valType& Dictionary::getValue(keyType k) const{
    Node *n = search(root,k);
    if(n == nil){
        throw std::logic_error("Dictionary: getValue(): key \""+k+"\" does not exist");
    }
    return n->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const{
    if (current != nil){
        return true;
    }
    return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const{
    if (!hasCurrent()){
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const{
    if(!hasCurrent() ){
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// mikes puesdo
// post order delete on the root node
// set the root to nil
// set current nil
// set num_pairs to 0
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// used mikes puesdo
void Dictionary::setValue(keyType k, valType v){
    Node *p = nil;
    Node *r = root;
    while(r != nil){
        p = r;
        if(k < r->key){
            r = r->left;
        }
        else if(k > r->key){
            r = r->right;
        }
        else{
            r->val = v;
            return;
        }
    }
    Node *n = new Node(k,v);
    n->parent = p;
    n->left = nil;
    n->right = nil;
    if(p == nil){
        root = n;
    }
    else if(k < p->key){
        p->left = n;
    }
    else{
        p->right = n;

    }
    num_pairs +=1; 
}

//puesdo from BST example
void Dictionary::transplant(Node* u, Node* v) {
    if (u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    if(v != nil){
        v->parent = u ->parent;
    }
}

//puesdo from mike
void Dictionary::remove(keyType k){
    Node *n = search(root,k);
    if(n == nil){
        throw std::logic_error("Dictionary: remove(): key \""+k+"\" does not exist");
    }
    if (current->key == k){
        current = nil;
    }
    if(n->left == nil){
        transplant(n,n->right);
    }
    else if(n->right == nil){
        transplant(n,n->left);
    }
    else{
        Node *y = findMin(n->right);
        if(y->parent != n){
            transplant(y,y->right);
            y->right = n->right;
            y->right->parent = y;
        }
        transplant(n,y);
        y->left = n->left;
        y->left->parent = y;
    }
    delete n;
    num_pairs -= 1;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
// set the current node to the minimum leaf node from the root
void Dictionary::begin(){
	if(num_pairs != 0){
		current = findMin(root);
	}
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
// set the current node to the maximum leaf node from the root
void Dictionary::end(){
	if(num_pairs != 0){
		current = findMax(root);
	}
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
	if(!(hasCurrent())){
		throw std::logic_error("Dictionary: next(): current iterator is not defined");
	}
	current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
	if(!(hasCurrent())){
		throw std::logic_error("Dictionary: prev(): current iterator is not defined");
	}
	current = findPrev(current);
}

