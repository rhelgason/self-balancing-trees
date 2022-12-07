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
        AVLNode* makeAVLNode(int data, AVLNode* left, AVLNode* right);

        bool isValidHelper(AVLNode* root);
        bool isBalancedHelper(AVLNode* curr);

        // recursive basic functions
        AVLNode* insertHelper(AVLNode* curr, int data);
        AVLNode* removeHelper(AVLNode* curr, int data);
        AVLNode* find(AVLNode* curr, int data);
        AVLNode* purgeHelper(AVLNode* curr);

        // rotation functions
        int getBalanceHelper(AVLNode* curr);
        void updateHeight(AVLNode* curr);
        AVLNode* rotateRight(AVLNode* curr);
        AVLNode* rotateLeft(AVLNode* curr);

        // recursive helper functions
        AVLNode* getMinHelper(AVLNode* curr);
        AVLNode* getMaxHelper(AVLNode* curr);
        int getHeightHelper(AVLNode* curr);
        void inorder(AVLNode* curr, int* &arr, int &i);

    public:
        ~AVLTree();
};

#endif
