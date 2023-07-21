#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include "Tree.h"
using namespace std;

#define RED 0
#define BLACK 1
#define LEFT 0
#define RIGHT 1

typedef struct RedBlackNode {
    int data;
    int color;
    RedBlackNode* child[2];
} RedBlackNode;

class RedBlackTree : public Tree<RedBlackNode> {
    private:
        RedBlackNode* _deepCopy(RedBlackNode* curr);
        RedBlackNode* Node(int data);

        bool _isValid(RedBlackNode* root);
        bool isRed(RedBlackNode* curr);
        int ensureRedBlackProperties(RedBlackNode* curr, bool &valid);

        // recursive basic functions
        RedBlackNode* _insert(RedBlackNode* curr, int data);
        RedBlackNode* insertFix(RedBlackNode* curr, bool i);
        RedBlackNode* _remove(RedBlackNode* curr, int data);
        RedBlackNode* _remove(RedBlackNode* curr, int data, bool &valid);
        RedBlackNode* removeFix(RedBlackNode* curr, bool i, bool &valid);
        RedBlackNode* _find(RedBlackNode* curr, int data);
        RedBlackNode* _purge(RedBlackNode* curr);

        // rotation functions
        RedBlackNode* rotate(RedBlackNode* curr, bool i);
        RedBlackNode* doubleRotate(RedBlackNode* curr, bool i);
        void flipColors(RedBlackNode* curr);

        // recursive helper functions
        RedBlackNode* _getMin(RedBlackNode* curr);
        RedBlackNode* _getMax(RedBlackNode* curr);
        int _getHeight(RedBlackNode* curr);
        void _inorder(RedBlackNode* curr, int* &arr, int &i);

    public:
        // basic functions
        void insert(int data);

        RedBlackTree() {};
        RedBlackTree(RedBlackTree& tree);
        ~RedBlackTree();
};

#endif
