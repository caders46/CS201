#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cmath>

using namespace std;

template <class keytype>

class BHeap {
private:
    struct Node {
        Node* sibling;
        Node* child;
        int degree;
        keytype key;

        Node() {
            sibling = NULL;
            child = NULL;
            degree = 0;
        }

        Node(keytype k) {
            sibling = NULL;
            child = NULL;
            degree = 0;
            key = k;
        }
    };

    void print(Node* node, bool isRoot) {
        if (isRoot) {
            cout << "B" << node->degree << endl;
        }
        cout << node->key << " ";
        if (node->child != NULL) {
            print(node->child, false);
        }
        if (node->sibling != NULL) {
            if (isRoot) {
                cout << endl;
                cout << endl;
                print(node->sibling, true);
            }
            else {
                print(node->sibling, false);
            }
        }
    }

    void destructorHelper(Node* node) {
        if (node == NULL) {
            return;
        }
        destructorHelper(node->child);
        destructorHelper(node->sibling);
        delete node;
    }

    Node* copyConHelper(Node* node, keytype min) {
        Node* newnode = new Node(node->key);
        if (node->child != NULL) {
            newnode->child = copyConHelper(node->child, min);
        }
        if (node->sibling != NULL) {
            newnode->sibling = copyConHelper(node->sibling, min);
        }
        if (newnode->key == min) {
            minimum = newnode;
        }
        return newnode;
    }

    Node* combineNodes(Node* n1, Node* n2) {
        Node* trav;
        Node** travPos = &trav;
        
        while(n1 && n2){
            if(n1->degree < n2->degree){
                *travPos = n1;
                n1 = n1->sibling;
            }
            else{
                *travPos = n2;
                n2 = n2->sibling;
            }
            travPos = &(*travPos)->sibling;
        }
        if(n1){
            *travPos = n1;
        }
        else{
            *travPos = n2;
        }
        return trav;
    }

    Node* mergeTrees(Node* head1, Node* head2) {
        Node* newHead;
        newHead = combineNodes(head1, head2);
        if (newHead == NULL){
            return NULL;
        }
        Node* prev = NULL;
        Node* x = newHead;
        Node* next = x->sibling;

        while (next != NULL){
            if ((x->degree != next->degree) || ((next->sibling != NULL) && (next->degree == next->sibling->degree))) {
                prev = x;
                x = next;
            }
            else if (x->key <= next->key) {
                x->sibling = next->sibling;
                link(next, x);
            }
            else{
                if (prev == NULL){
                    newHead = next;
                }
                else{
                    prev->sibling = next;
                }
                link(x, next);
                x = next;
            }
            next = x->sibling;
        }
        return newHead;
    }

    void link(Node* y, Node* z) {
        y->sibling = z->child;
        z->child = y;
        z->degree++;
    }

    void reverse(Node* y) {
        if (y->sibling != NULL) {
            reverse(y->sibling);
            (y->sibling)->sibling = y;
        }
        else {
            reversedHead = y;
        }
    }

public:
    Node* head;
    Node* reversedHead;
    Node* minimum;
    int size;

    BHeap() {
        head = NULL;
        reversedHead = NULL;
        minimum = NULL;
        size = 0;
    }

    BHeap(keytype k[], int s) {
        head = NULL;
        reversedHead = NULL;
        minimum = NULL;
        size = 0;
        for (int i = 0; i < s; i++) {
            insert(k[i]);
        }
    }

    BHeap(const BHeap& obj) {
        if (obj.head == NULL) {
            head = NULL;
            minimum = NULL;
        }
        else {
            head = copyConHelper(obj.head, obj.minimum->key);
            //the minimum node is set within the copyconstructor helper. **make sure this WORKS! otherwise i will have to traverse twice
        }
    }

    BHeap& operator =(BHeap obj) {
        if (head != NULL) {
            destructorHelper(head);
        }
        if (obj.head == NULL) {
            head = NULL;
            minimum = NULL;
        }
        else {
            head = copyConHelper(obj.head, obj.minimum->key);
        }
        return *this;
    }

    ~BHeap() {
        destructorHelper(head);
    }

    void insert(keytype k) {
        if(head == NULL){
            Node* node = new Node(k);
            head = node;
            minimum = node;
            return;
        }
        Node* node = new Node(k);
        if(k < minimum->key){
            minimum = node;
        }
        if(node == NULL){
            return;
        }
        head = mergeTrees(head, node);
    }

    void merge(BHeap<keytype>& H2) {
        if(H2.minimum != NULL && minimum != NULL){
            if(H2.minimum < minimum){
                minimum = H2.minimum;
            }
        }
        else if(H2.minimum != NULL && minimum == NULL){
            minimum = H2.minimum;
        }
        head = mergeTrees(head, H2.head);
        H2.head = NULL;
        H2.minimum = NULL;

    }

    keytype extractMin() {
        Node* oldMin = minimum;
        keytype oldKey = oldMin->key;
        reversedHead = NULL;
        Node* trav = NULL;
        Node* h = head;
        Node* x = h;
        keytype minKey = x->key;
        Node* prev = x;
        while (prev->sibling != NULL) {
            if ((prev->sibling)->key < minKey) {
                minKey = (prev->sibling)->key;
                trav = prev;
                x = prev->sibling;
            }
            prev = prev->sibling;
        }
        if (trav == NULL && x->sibling == NULL) {
            h = NULL;
        }
        else if (trav == NULL) {
            h = x->sibling;
        }
        else if (trav->sibling == NULL) {
            trav = NULL;
        }
        else {
            trav->sibling = x->sibling;
        }
        if (x->child != NULL) {
            reverse(x->child);
            (x->child)->sibling = NULL;
        }
        head = mergeTrees(h, reversedHead);
        Node* trav2 = head;
        if (head != NULL) {
            minimum = head;
        }
        else {
            minimum = NULL;
        }
        while (trav2 != NULL) {
            if (trav2->key < minimum->key) {
                minimum = trav2;
            }
            trav2 = trav2->sibling;
        }
        delete oldMin;
        return oldKey;
    }

    keytype peekKey() { //The current method for keeping track of the minimum key does not account for duplicates. Better method would be included in merge method if needed
        return minimum->key;
    }

    void printKey() {
        if (head == NULL) {
            cout << "tree is empty" << endl;
        }
        print(head, true);
        cout << endl << endl;
    }

};