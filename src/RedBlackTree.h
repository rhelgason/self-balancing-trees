#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include "Tree.h"
using namespace std;

#define BLACK -1
#define RED 1

typedef struct RedBlackNode {
    int data;
    int color;
    RedBlackNode* left;
    RedBlackNode* right;
    RedBlackNode* parent;
} RedBlackNode;

class RedBlackTree : public Tree<RedBlackNode> {
    private:
        RedBlackNode* makeRedBlackNode(int data, int color, RedBlackNode* left, RedBlackNode* right, RedBlackNode* parent);

        bool isValidHelper(RedBlackNode* root);
        int getColor(RedBlackNode* curr);
        int ensureRedBlackProperties(RedBlackNode* curr, bool &valid);

        // recursive basic functions
        RedBlackNode* insertHelper(RedBlackNode* curr, int data);
        RedBlackNode* removeHelper(RedBlackNode* curr, int data);
        RedBlackNode* find(RedBlackNode* curr, int data);
        RedBlackNode* purgeHelper(RedBlackNode* curr);

        // rotation functions
        RedBlackNode* rotateRight(RedBlackNode* curr);
        RedBlackNode* rotateLeft(RedBlackNode* curr);

        // recursive helper functions
        RedBlackNode* getMinHelper(RedBlackNode* curr);
        RedBlackNode* getMaxHelper(RedBlackNode* curr);
        int getHeightHelper(RedBlackNode* curr);
        void inorder(RedBlackNode* curr, int* &arr, int &i);

    public:
        ~RedBlackTree();
};

#endif
