#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include "Tree.h"
using namespace std;

typedef struct Node {
    int data;
    Node* left;
    Node* right;
} Node;

class BinarySearchTree : public Tree<Node> {
    private:
        Node* makeNode(int data, Node* left, Node* right);

        bool isValidHelper(Node* curr);

        // recursive basic functions
        Node* insertHelper(Node* curr, int data);
        Node* removeHelper(Node* curr, int data);
        Node* find(Node* curr, int data);
        Node* purgeHelper(Node* curr);

        // recursive helper functions
        Node* getMinHelper(Node* curr);
        Node* getMaxHelper(Node* curr);
        int getHeightHelper(Node* curr);
        void inorder(Node* curr, int* &arr, int &i);

    public:
        ~BinarySearchTree();
};

#endif
