#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
using namespace std;

typedef struct Node {
    int data;
    Node* left;
    Node* right;
} Node;

class BinarySearchTree {
    Node* makeNode(int data, Node* left, Node* right);

    struct Node* root;
    int size;

    // recursive basic functions
    Node* insert(Node* curr, int data);
    Node* remove(Node* curr, int data);
    Node* find(Node* curr, int data);
    Node* purge(Node* curr);

    // recursive helper functions
    Node* getMin(Node* curr);
    Node* getMax(Node* curr);
    int getHeight(Node* curr);
    void inorder(Node* curr);

    public:
        BinarySearchTree();

        // basic functions
        void insert(int data);
        void remove(int data);
        bool includes(int data);
        void purge();

        // helper functions
        int getSize();
        int getMin();
        int getMax();
        int getHeight();
        void inorder();

        ~BinarySearchTree();
};

#endif
