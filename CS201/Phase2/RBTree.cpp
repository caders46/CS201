#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>
#include <cstring>
#include <cmath>

using namespace std;

template<typename kT, typename vT>

class RBTree {
private:
    struct Node {
        bool color;   //FOR COLOR, 0 = BLACK and 1 = RED
        kT key;
        vT value;
        Node *left;
        Node *right;
        Node *parent;
        int numLeftChildren;
    };

    void leftRotate(Node* x){
        Node* y = x->right;
        y->numLeftChildren = y->numLeftChildren + x->numLeftChildren + 1;
        x->right = y->left;
        if(y->left != nil){
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil){
            this->root = y;
        }
        else if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x){
        Node* y = x->left;
        x->numLeftChildren = x->numLeftChildren - y->numLeftChildren - 1;
        x->left = y->right;
        if(y->right != nil){
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil){
            root = y;
        }
        else if(x == x->parent->right){
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insFixup(Node* node){
        Node* y;
        while (node->parent->color == 1) {
            if (node->parent == node->parent->parent->left) {
                y = node->parent->parent->right;
                if(y->color == 1){
                    y->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else{
                    if(node == node->parent->right){
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    rightRotate(node->parent->parent);
                }
            }
            else{
                y = node->parent->parent->left;
                if(y->color == 1){
                    node->parent->color = 0;
                    y->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else{
                    if(node == node->parent->left){
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->color = 0;
    }

    void transplant(Node* u, Node* v){
        if(u->parent == nil){
            root = v;
        }
        else if(u == u->parent->left){
            u->parent->left = v;
        }
        else{
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node* minimum(Node* node) {
        while(node->left!=nil){
            node = node->left;
        }
        return node;
    }
    
    Node* maximum(Node* node) {
        while (node->right != nil) {
            node = node->right;
        }
        return node;
    }

    void delFixup(Node* x){
        Node* w;
        while(x!=root && x->color == 0){
            if(x == x->parent->left){
                w = x->parent->right;
                if(w->color == 1){
                    w->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if(w->left->color == 0 && w->right->color == 0){
                    w->color = 1;
                    x = x->parent;
                }
                else{
                    if(w->right->color == 0){
                        w->left->color = 0;
                        w->color = 1;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else{
                w = x->parent->left;
                if(w->color == 1){
                    w->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if(w->right->color == 0 && w->left->color == 0){
                    w->color = 1;
                    x = x->parent;
                }
                else{
                    if(w->left->color == 0){
                        w->right->color = 0;
                        w->color = 1;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    Node* createTreeInOrder(kT k[], vT v[], int start, int end, bool treeFull, int endLevel, int level, Node* par){
        int median = (start+end)/2;
        Node* node = new Node;
        node->color = false;
        node->parent = par;
        node->key = k[median];
        node->value = v[median];
        node->left = nil;
        node->right = nil;
        node->numLeftChildren = median - start;

        if(!treeFull && level == endLevel){
            node->color = true;
        }
        if(start == end){
            node->left = nil;
            node->right = nil;
        }
        else{
            if(start != median){
                node->left = createTreeInOrder(k, v, start, median-1, treeFull, endLevel, level+1, node);
            }
            else{
                node->left = nil;
            }
            if(end != median){
                node->right = createTreeInOrder(k, v, median+1, end, treeFull, endLevel, level+1, node);
            }
            else{
                node->right = nil;
            }
        }
        treesize++;
        return node;
    }

    Node* copyconHelper(Node* orgnode, Node* par, Node* orgNil){
        Node* node = new Node;
        node->color = orgnode->color;
        node->key = orgnode->key;
        node->value = orgnode->value;
        node->numLeftChildren = orgnode->numLeftChildren;
        node->parent = par;
        if(orgnode->left != orgNil){
            node->left = copyconHelper(orgnode->left, node, orgNil);
        }
        else{
            node->left = nil;
        }
        if(orgnode->right != orgNil){
            node->right = copyconHelper(orgnode->right, node, orgNil);
        }
        else{
            node->right = nil;
        }
        return node;
    }
    
    void destructorHelper(Node* node){
        if(node!=nil){
            destructorHelper(node->left);
            destructorHelper(node->right);
            delete node;
        }
    }

    void preorderHelper(Node* node){
        cout << node->key;
        if(node->left != nil){
            cout << " ";
            preorderHelper(node->left);
        }
        if(node->right != nil){
            cout << " ";
            preorderHelper(node->right);
        }
    }

    void inorderHelper(Node* node){
        if(node->left != nil){
            inorderHelper(node->left);
            cout << " ";
        }
        cout << node->key;
        if(node->right != nil){
            cout << " ";
            inorderHelper(node->right);
        }
    }

    void postorderHelper(Node* node){
        if(node->left != nil){
            postorderHelper(node->left);
            cout << " ";
        }
        if(node->right != nil){
            postorderHelper(node->right);
            cout << " ";
        }
        cout << node->key;
    }

public:
    
    
    Node* root;          //top of the tree
    int treesize;
    Node* nil;

    RBTree() {
        nil = new Node;
        nil->color = 0;
        nil->left = NULL;
        nil->right = NULL;
        nil->numLeftChildren = 0;
        root = nil;
        treesize = 0;
    }

    RBTree(kT k[], vT v[], int s){
        nil = new Node;
        nil->color = 0;
        nil->left = NULL;
        nil->right = NULL;
        nil->numLeftChildren = 0;
        root = nil;
        treesize = 0;
        if(s == 1){
            insert(k[0],v[0]);
        }
        else{
            bool inOrder = true;
            for(int i = 0; i < s-1; i++){
                if(k[i] > k[i+1]){
                    inOrder = false;
                }
            } 
            if(inOrder){
                int expEndLevel = 1;
                bool treeIsFull = true;
                while((pow(2,expEndLevel)-1) < s){
                    expEndLevel++;
                }
                if((pow(2, expEndLevel)-1) == s){
                    treeIsFull = true;
                }
                else{
                    treeIsFull = false;
                }
                root = createTreeInOrder(k, v, 0, s-1, treeIsFull, expEndLevel, 1, nil);
            }
            else{
                for(int i = 0; i < s; i++){
                    insert(k[i], v[i]);
                }
            }
        }
    }

    //copycon
    RBTree(const RBTree& obj){
        treesize = obj.treesize;
        nil = new Node;
        nil->color = 0;
        nil->left = NULL;
        nil->right = NULL;
        nil->numLeftChildren = 0;
        if(obj.root == obj.nil){
            root = nil;
        }
        else{
            root = copyconHelper(obj.root, nil, obj.nil);
        }
    }

    RBTree& operator=(const RBTree& obj){
        if(this != &obj){
            destructorHelper(root);
            delete nil;
            Node* nil = new Node;
            nil->color = 0;
            nil->left = NULL;
            nil->right = NULL;
            nil->numLeftChildren = 0;
            treesize = obj.treesize;
            root = copyconHelper(obj.root, nil, obj.nil);
        }
        return *this;
    }

    ~RBTree(){
        destructorHelper(this->root);
        delete nil;
    }

    void insert(kT k, vT v){
        treesize++;
        Node* node = new Node;
        node->color = 1;
        node->key = k;
        node->value = v;
        node->left = nil;
        node->right = nil;
        node->parent = nil;
        node->numLeftChildren = 0;
        
        
        Node* x = this->root;
        Node* y = nil;


        while(x != nil){
            y = x;
            if(node->key < x->key){
                x->numLeftChildren++;
                x = x->left;
            }
            else{
                x = x->right;
            }
        }


        node->parent = y;
        
        if(y == nil){
            root = node;
        }
        else if(node->key < y->key){
            y->left = node;
        }
        else{
            y->right = node;
        }

        node->left = nil;
        node->right = nil;
        node->color = 1;
        node->numLeftChildren = 0;

        insFixup(node);
    }

    int size(){
        return treesize;           //done
    }

    vT* search(kT k){                //done
        Node* current = this->root;
        bool foundOrEnd = false;
        while(!foundOrEnd){
            if(current->key == k){
                foundOrEnd = true;
                return &current->value;
            }
            else if(k < current->key){
                if(current->left != nil){
                    current = current->left;
                }
                else{
                    foundOrEnd = true;
                    return NULL;
                }
            }
            else{
                if(current->right != nil){
                    current = current->right;
                }
                else{
                    foundOrEnd = true;
                    return NULL;
                }
            }
        }
        
        return NULL;
    }

    int remove(kT k){                    //done
        Node* current = this->root;
        bool found = false;
        while(!found){
            if(current->key == k){
                found = true;
                break;
            }
            else if(k < current->key){
                if(current->left != nil){
                    current = current->left;
                }
                else{
                    break;
                }
            }
            else{
                if(current->right != nil){
                    current = current->right;
                }
                else{
                    break;
                }
            }
        }
        if(found){
            Node* y = current;
            Node* x;
            bool yOriginalColor = y->color;
            if(current->left == nil){
                x = current->right;
                transplant(current, current->right);
            }
            else if(current->right == nil){
                x = current->left;
                transplant(current,current->left);
            }
            else{
                y = maximum(current->left);
                yOriginalColor = y->color;
                x = y->left;
                if(y->parent == current){
                    x->parent = y;
                }
                else{
                    transplant(y, y->left);
                    y->left = current->left;
                    y->left->parent = y;
                }
                transplant(current, y);
                y->right = current->right;
                y->right->parent = y;
                y->color = current->color;
                y->numLeftChildren = current->numLeftChildren;
            }
            
            Node* currentcopy = x;
            while(currentcopy != this->root){
                if(currentcopy->key < currentcopy->parent->key && currentcopy->parent->numLeftChildren > 0){
                    currentcopy->parent->numLeftChildren -= 1;
                }
                currentcopy = currentcopy->parent;
            }

            if(yOriginalColor == 0){
                delFixup(x);
            }

            delete current;
            return 1;
        }
        return 0;
    }

    int rank(kT k){
        Node* current = root;
        int rank = 1;
        while(current != nil){
            if(k == current->key){
                rank+=current->numLeftChildren;
                return rank;
            }
            else if(k < current->key){
                current = current->left;
            }
            else{
                rank = rank + current->numLeftChildren + 1;
                current = current->right;
            }
            
            
            
            
            /*if(k < current->key){
                current = current->left;
            }
            else if(k > current->key){
                rank = rank + current->numLeftChildren + 1;
                current = current->right;
            }
            else{
                return rank + current->numLeftChildren;
            }*/
        }
        return 0;
    }

    kT select(int pos){
        if(root != nil){
            Node* current = root;
            int position = current->numLeftChildren + 1;
            bool foundOrEnd = false;
            while(!foundOrEnd){
                if(position == pos){
                    foundOrEnd = true;
                    return current->key;
                }
                else{
                    if(pos < position){
                        if(current->left == nil){
                            foundOrEnd = true;
                            break;
                        }
                        else{
                            position = position - current->numLeftChildren;
                            current = current->left;
                            position = position + current->numLeftChildren;
                        }
                    }
                    else{
                        if(current->right == nil){
                            foundOrEnd = true;
                            break;
                        }
                        else{
                            current = current->right;
                            position = position + current->numLeftChildren + 1;
                        }
                    }
                }
            }
        }
        return 0;
    }

    kT* successor(kT k){              //done
        Node* current = this->root;
        bool found = false;
        while(!found){
            if(current->key == k){
                found = true;
                break;
            }
            else if(k < current->key){
                if(current->left != nil){
                    current = current->left;
                }
                else{
                    break;
                }
            }
            else{
                if(current->right != nil){
                    current = current->right;
                }
                else{
                    break;
                }
            }
        }
        if(found){
            Node* succ;
            if(current->right != nil){
                succ = minimum(current->right);
                return &succ->key;
            }

            Node* currParent = current->parent;
            while(currParent != nil && current == currParent->right){
                current = currParent;
                currParent = currParent->parent;
            }
            
            if(currParent != nil){
                succ = currParent;
                return &succ->key;
            }
            else{
                return NULL;
            }

        }
        return NULL;
    }

    kT* predecessor(kT k){          //done
        Node* current = this->root;
        bool found = false;
        while(!found){
            if(current->key == k){
                found = true;
                break;
            }
            else if(k < current->key){
                if(current->left != nil){
                    current = current->left;
                }
                else{
                    break;
                }
            }
            else{
                if(current->right != nil){
                    current = current->right;
                }
                else{
                    break;
                }
            }
        }
        if(found){
            Node* pred;
            if(current->left != nil){
                pred = maximum(current->left);
                return &pred->key;
            }

            Node* currParent = current->parent;
            while(currParent != nil && current == currParent->left){
                current = currParent;
                currParent = currParent->parent;
            }
            
            if(currParent != nil){
                pred = currParent;
                return &pred->key;
            }
            else{
                return NULL;
            }

        }
        return NULL;
    }

    void preorder(){                   //done
        preorderHelper(this->root);
        cout << endl;
    }

    void inorder(){                    //done
        inorderHelper(this->root);
        cout << endl;
    }

    void postorder(){                   //done
        postorderHelper(this->root);
        cout << endl;
    }
};