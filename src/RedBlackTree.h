#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include "Tree.h"
using namespace std;

#define RED 0
#define BLACK 1
#define left 0
#define right 1

typedef struct RedBlackNode {
    int data;
    int color;
    RedBlackNode* child[2];
} RedBlackNode;

class RedBlackTree : public Tree<RedBlackNode> {
    private:
        RedBlackNode* makeRedBlackNode(int data);

        bool isValidHelper(RedBlackNode* root);
        bool isRed(RedBlackNode* curr);
        int ensureRedBlackProperties(RedBlackNode* curr, bool &valid);

        // recursive basic functions
        RedBlackNode* insertHelper(RedBlackNode* curr, int data);
        RedBlackNode* insertFix(RedBlackNode* curr, bool i);
        RedBlackNode* removeHelper(RedBlackNode* curr, int data);
        RedBlackNode* find(RedBlackNode* curr, int data);
        RedBlackNode* purgeHelper(RedBlackNode* curr);

        // rotation functions
        RedBlackNode* rotate(RedBlackNode* curr, bool i);
        RedBlackNode* doubleRotate(RedBlackNode* curr, bool i);
        void flipColors(RedBlackNode* curr);

        // recursive helper functions
        RedBlackNode* getMinHelper(RedBlackNode* curr);
        RedBlackNode* getMaxHelper(RedBlackNode* curr);
        int getHeightHelper(RedBlackNode* curr);
        void inorder(RedBlackNode* curr, int* &arr, int &i);

    public:
        // basic functions
        void insert(int data);

        ~RedBlackTree();
};

#endif
