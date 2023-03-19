/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#8
* Dictionary.cpp
* Dictionary ADT file
*********************************************************************************/ 

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
    color = 0;
}

Dictionary::Dictionary(){
    nil = new Node("somereallylongstring", 999);
    root = nil;
    current = nil;
    num_pairs = 0;
    nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	nil->color = 1;
}

Dictionary::Dictionary(const Dictionary &D){
    nil = new Node("somereallylongstring", 999);
    root = nil;
    current = nil;
    num_pairs = 0;
    nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	nil->color = 1;
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


// RBT Helper Functions (Optional) -----------------------------------------


//   // set y
//    y = x.right 
   
//    // turn y's left subtree into x's right subtree
//    x.right = y.left 
//    if y.left != T.nil     // not necessary if using sentinal nil node
//       y.left.parent = x
   
//    // link y's parent to x
//    y.parent = x.parent 
//    if x.parent == T.nil
//       T.root = y
//    else if x == x.parent.left
//       x.parent.left = y
//    else 
//       x.parent.right = y
   
//    // put x on y's left
//    y.left = x 
//    x.parent = y

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    Node *y = N->right;
    N->right = y->left;
    if(y->left != nil){
        y->left->parent = N;
    }
    y->parent = N->parent;
    if(N->parent == nil){
        root = y;
    }
    else if(N == N->parent->left){
        N->parent->left = y;
    }
    else{
        N->parent->right = y;
    }
    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    Node *y = N->left;
    N->left = y->right;
    if(y->right != nil){
        y->right->parent = N;
    }
    y->parent = N->parent;
    if(N->parent == nil){
        root = y;
    }
    else if(N == N->parent->right){
        N->parent->right =y;
    }
    else{
        N->parent->left = y;
    }
    y->right = N;
    N->parent = y;
}


// RB_InsertFixUp(T, z)
//    while z.parent.color == RED
//       if z.parent == z.parent.parent.left
//          y = z.parent.parent.right
//          if y.color == RED
//             z.parent.color = BLACK              // case 1
//             y.color = BLACK                     // case 1
//             z.parent.parent.color = RED         // case 1
//             z = z.parent.parent                 // case 1
//          else 
//             if z == z.parent.right
//                z = z.parent                     // case 2
//                LeftRotate(T, z)                 // case 2
//             z.parent.color = BLACK              // case 3
//             z.parent.parent.color = RED         // case 3
//             RightRotate(T, z.parent.parent)     // case 3
//       else 
//          y = z.parent.parent.left
//          if y.color == RED
//             z.parent.color = BLACK              // case 4
//             y.color = BLACK                     // case 4
//             z.parent.parent.color = RED         // case 4
//             z = z.parent.parent                 // case 4
//          else 
//             if z == z.parent.left
//                z = z.parent                     // case 5
//                RightRotate(T, z)                // case 5
//             z.parent.color = BLACK              // case 6
//             z.parent.parent.color = RED         // case 6
//             LeftRotate(T, z.parent.parent)      // case 6
//    T.root.color = BLACK

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    while (N->parent->color == 0){
        if (N->parent == N->parent->parent->left){
            Node *y = N->parent->parent->right;
            if(y->color == 0){
                N->parent->color = 1;
                y->color = 1;
                N->parent->parent->color = 0;
                N = N->parent->parent;
            }
            else{
                if(N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = 1;
                N->parent->parent->color = 0;
                RightRotate(N->parent->parent);
            }
        }
        else{
            Node *y = N->parent->parent->left;
            if(y->color == 0){
                N->parent->color = 1;
                y->color = 1;
                N->parent->parent->color = 0;
                N = N->parent->parent;
            }
            else{
                if(N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = 1;
                N->parent->parent->color= 0;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = 1;
}
//    if u.parent == T.nil
//       T.root = v
//    else if u == u.parent.left
//       u.parent.left = v
//    else 
//       u.parent.right = v
//    v.parent = u.parent

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil) {
		root = v;
	}
	else if(u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

//    while x != T.root and x.color == BLACK
//       if x == x.parent.left
//          w = x.parent.right
//          if w.color == RED
//             w.color = BLACK                        // case 1
//             x.parent.color = RED                   // case 1
//             LeftRotate(T, x.parent)                // case 1
//             w = x.parent.right                     // case 1
//          if w.left.color == BLACK and w.right.color == BLACK
//             w.color = RED                          // case 2
//             x = x.parent                           // case 2
//          else 
//             if w.right.color == BLACK
//                w.left.color = BLACK                // case 3
//                w.color = RED                       // case 3
//                RightRotate(T, w)                   // case 3
//                w = x.parent.right                  // case 3
//             w.color = x.parent.color               // case 4
//             x.parent.color = BLACK                 // case 4
//             w.right.color = BLACK                  // case 4
//             LeftRotate(T, x.parent)                // case 4
//             x = T.root                             // case 4
//       else 
//          w = x.parent.left
//          if w.color == RED
//             w.color = BLACK                        // case 5
//             x.parent.color = RED                   // case 5
//             RightRotate(T, x.parent)               // case 5
//             w = x.parent.left                      // case 5
//          if w.right.color == BLACK and w.left.color == BLACK
//             w.color = RED                          // case 6
//             x = x.parent                           // case 6
//          else 
//             if w.left.color == BLACK
//                w.right.color = BLACK               // case 7
//                w.color = RED                       // case 7
//                LeftRotate(T, w)                    // case 7
//                w = x.parent.left                   // case 7
//             w.color = x.parent.color               // case 8
//             x.parent.color = BLACK                 // case 8
//             w.left.color = BLACK                   // case 8
//             RightRotate(T, x.parent)               // case 8
//             x = T.root                             // case 8
//    x.color = BLACK

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    while(N != root && N->color == 1){
        if(N == N->parent->left){
            Node *w = N->parent->right;
            if(w->color == 0){
                w->color = 1;
                N->parent->color = 0;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if((N->left->color == 1) && (N->right->color == 1)){
                w->color = 0;
                N = N->parent;
            }
            else{
                if(w->right->color == 1){
                    w->left->color = 1;
                    w->color = 0;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
				N->parent->color = 1;
				w->right->color = 1;
				LeftRotate(N->parent);
				N = root;
            }
        }
        else{
            Node *w = N->parent->left;
            if(w->color == 0){
                w->color = 1;
				N->parent->color = 0;
				RightRotate(N->parent);
				w = N->parent->left;
            }
            if((w->right->color == 1) && (w->left->color == 1)){
                w->color = 0;
				N = N->parent;
            }
            else{
                if(w->left->color == 1){
                    w->right->color = 1;
                    w->color = 0;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = 1;
                w->left->color = 1;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = 1;
}


//    y = z
//    y_original_color = y.color
//    if z.left == T.nil
//       x = z.right
//       RB_Transplant(T, z, z.right)
//    else if z.right == T.nil
//       x = z.left
//       RB_Transplant(T, z, z.left)
//    else 
//       y = TreeMinimum(z.right)
//       y_original_color = y.color
//       x = y.right
//       if y.parent == z
//          x.parent = y
//       else 
//          RB_Transplant(T, y, y.right)
//          y.right = z.right
//          y.right.parent = y
//       RB_Transplant(T, z, y)
//       y.left = z.left
//       y.left.parent = y
//       y.color = z.color
//    if y_original_color == BLACK
//       RB_DeleteFixUp(T, x)
// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node *y = N;
    int y_original_color = y->color;
    Node *x;
    if(N->left == nil){
        x = N->right;
        RB_Transplant(N,N->right);
    }
    else if(N->right == nil){
        x = N->left;
        RB_Transplant(N,N->left);
    }
    else{
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == N){
            x->parent = y;
        }
        else{
            RB_Transplant(y,y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N,y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if(y_original_color == 1){
        RB_DeleteFixUp(x);
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
    //k.compare(r->key) < 0
    //k.compare(r->key) > 0
    //k.compare(p->key) < 0
    while(r != nil){
        p = r;
        if(k.compare(r->key) < 0){
            r = r->left;
        }
        else if(k.compare(r->key) > 0){
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
    else if(k.compare(p->key) < 0){
        p->left = n;
    }
    else{
        p->right = n;

    }
    num_pairs +=1;
    n->color = 0;
    RB_InsertFixUp(n); 
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
    // if(n->left == nil){
    //     transplant(n,n->right);
    // }
    // else if(n->right == nil){
    //     transplant(n,n->left);
    // }
    // else{
    //     Node *y = findMin(n->right);
    //     if(y->parent != n){
    //         transplant(y,y->right);
    //         y->right = n->right;
    //         y->right->parent = y;
    //     }
    //     transplant(n,y);
    //     y->left = n->left;
    //     y->left->parent = y;
    // }
    RB_Delete(n);
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

// Other Functions ---------------------------------------------------------

//used mikes puesdocode

std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    return (this->to_string() == D.to_string());
}

// Overloaded Operators -------------------------------------------------------


std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D){
    if(this != &D){
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}