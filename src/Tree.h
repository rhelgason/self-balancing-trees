#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

template <typename T>
class Tree {
    protected:
        T* root;
        int size;

        virtual T* Node(int data) = 0;
        virtual bool _isValid(T* curr) = 0;

        // recursive basic functions
        virtual T* _insert(T* curr, int data) = 0;
        virtual T* _remove(T* curr, int data) = 0;
        virtual T* _find(T* curr, int data) = 0;
        virtual T* _purge(T* curr) = 0;

        // recursive helper functions
        virtual T* _getMin(T* curr) = 0;
        virtual T* _getMax(T* curr) = 0;
        virtual int _getHeight(T* curr) = 0;
        virtual void _inorder(T* curr, int* &arr, int &i) = 0;

    public:
        Tree() {
            root = NULL;
            size = 0;
        }

        bool isValid() {
            return _isValid(root);
        }

        // basic functions
        void insert(int data) {
            root = _insert(root, data);
        }

        void remove(int data) {
            root = _remove(root, data);
        }

        bool includes(int data) {
            return _find(root, data) != NULL;
        }

        void purge() {
            root = _purge(root);
        }

        // helper functions
        int getSize() {
            return size;
        }

        int* getMin() {
            T* min = _getMin(root);
            if (min == NULL) {
                return NULL;
            }
            return &(min->data);
        }

        int* getMax() {
            T* max = _getMax(root);
            if (max == NULL) {
                return NULL;
            }
            return &(max->data);
        }

        int getHeight() {
            return _getHeight(root);
        }

        int* getRoot() {
            if (root == NULL) {
                return NULL;
            }
            return &(root->data);
        }

        string toString() {
            int* arr = new int[size];
            int i = 0;
            _inorder(root, arr, i);
            string str = "";
            for (i = 0; i < size - 1; i++) {
                str += to_string(arr[i]) + ", ";
            }
            str += to_string(arr[size - 1]);
            delete[] arr;
            return str;
        }

        ~Tree() {};
};

#endif
