#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

template <typename T>
class Tree {
    protected:
        T* root;
        int size;

        virtual bool isValidHelper(T* curr) = 0;

        // recursive basic functions
        virtual T* insertHelper(T* curr, int data) = 0;
        virtual T* removeHelper(T* curr, int data) = 0;
        virtual T* find(T* curr, int data) = 0;
        virtual T* purgeHelper(T* curr) = 0;

        // recursive helper functions
        virtual T* getMinHelper(T* curr) = 0;
        virtual T* getMaxHelper(T* curr) = 0;
        virtual int getHeightHelper(T* curr) = 0;
        virtual void inorder(T* curr, int* &arr, int &i) = 0;

    public:
        Tree() {
            root = NULL;
            size = 0;
        }

        bool isValid() {
            return isValidHelper(root);
        }

        // basic functions
        void insert(int data) {
            root = insertHelper(root, data);
        }

        void remove(int data) {
            root = removeHelper(root, data);
        }

        bool includes(int data) {
            return find(root, data) != NULL;
        }

        void purge() {
            root = purgeHelper(root);
        }

        // helper functions
        int getSize() {
            return size;
        }

        int* getMin() {
            T* min = getMinHelper(root);
            if (min == NULL) {
                return NULL;
            }
            return &(min->data);
        }

        int* getMax() {
            T* max = getMaxHelper(root);
            if (max == NULL) {
                return NULL;
            }
            return &(max->data);
        }

        int getHeight() {
            return getHeightHelper(root);
        }

        string toString() {
            int* arr = new int[size];
            int i = 0;
            inorder(root, arr, i);
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
