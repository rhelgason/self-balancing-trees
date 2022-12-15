#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include "Tree.h"
using namespace std;

typedef struct SplayNode {
    int data;
    SplayNode* left;
    SplayNode* right;
} SplayNode;

class SplayTree : public Tree<SplayNode> {
    private:
        SplayNode* Node(int data);

        bool _isValid(SplayNode* root);

        // recursive basic functions
        SplayNode* _insert(SplayNode* curr, int data);
        SplayNode* _remove(SplayNode* curr, int data);
        SplayNode* _find(SplayNode* curr, int data);
        SplayNode* splay(SplayNode* curr, int data);
        SplayNode* _purge(SplayNode* curr);

        // rotation functions
        SplayNode* rotateRight(SplayNode* curr);
        SplayNode* rotateLeft(SplayNode* curr);

        // recursive helper functions
        SplayNode* _getMin(SplayNode* curr);
        SplayNode* _getMax(SplayNode* curr);
        int _getHeight(SplayNode* curr);
        void _inorder(SplayNode* curr, int* &arr, int &i);

    public:
        // basic functions
        void insert(int data);
        void remove(int data);

        ~SplayTree();
};

#endif
