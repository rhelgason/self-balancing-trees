#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include "Tree.h"
using namespace std;

typedef struct AVLNode {
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;
} AVLNode;

class AVLTree : public Tree<AVLNode> {
    private:
        AVLNode* _deepCopy(AVLNode* curr);
        AVLNode* Node(int data);

        bool _isValid(AVLNode* root);
        bool isBalanced(AVLNode* curr);

        // recursive basic functions
        AVLNode* _insert(AVLNode* curr, int data);
        AVLNode* _remove(AVLNode* curr, int data);
        AVLNode* _find(AVLNode* curr, int data);
        AVLNode* _purge(AVLNode* curr);

        // rotation functions
        int getBalance(AVLNode* curr);
        void updateHeight(AVLNode* curr);
        AVLNode* rotateRight(AVLNode* curr);
        AVLNode* rotateLeft(AVLNode* curr);

        // recursive helper functions
        AVLNode* _getMin(AVLNode* curr);
        AVLNode* _getMax(AVLNode* curr);
        int _getHeight(AVLNode* curr);
        void _inorder(AVLNode* curr, int* &arr, int &i);

    public:
        AVLTree() {};
        AVLTree(AVLTree& tree);
        ~AVLTree();
};

#endif
