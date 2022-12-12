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
        BinarySearchNode* makeBinarySearchNode(int data);

        bool isValidHelper(BinarySearchNode* root);

        // recursive basic functions
        BinarySearchNode* insertHelper(BinarySearchNode* curr, int data);
        BinarySearchNode* removeHelper(BinarySearchNode* curr, int data);
        BinarySearchNode* find(BinarySearchNode* curr, int data);
        BinarySearchNode* purgeHelper(BinarySearchNode* curr);

        // recursive helper functions
        BinarySearchNode* getMinHelper(BinarySearchNode* curr);
        BinarySearchNode* getMaxHelper(BinarySearchNode* curr);
        int getHeightHelper(BinarySearchNode* curr);
        void inorder(BinarySearchNode* curr, int* &arr, int &i);

    public:
        ~BinarySearchTree();
};

#endif
