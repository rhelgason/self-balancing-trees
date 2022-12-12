#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include "Tree.h"
using namespace std;

typedef struct BinarySearchNode {
    int data;
    BinarySearchNode* left;
    BinarySearchNode* right;
} BinarySearchNode;

class BinarySearchTree : public Tree<BinarySearchNode> {
    private:
        BinarySearchNode* Node(int data);

        bool _isValid(BinarySearchNode* root);

        // recursive basic functions
        BinarySearchNode* _insert(BinarySearchNode* curr, int data);
        BinarySearchNode* _remove(BinarySearchNode* curr, int data);
        BinarySearchNode* _find(BinarySearchNode* curr, int data);
        BinarySearchNode* _purge(BinarySearchNode* curr);

        // recursive helper functions
        BinarySearchNode* _getMin(BinarySearchNode* curr);
        BinarySearchNode* _getMax(BinarySearchNode* curr);
        int _getHeight(BinarySearchNode* curr);
        void _inorder(BinarySearchNode* curr, int* &arr, int &i);

    public:
        ~BinarySearchTree();
};

#endif
