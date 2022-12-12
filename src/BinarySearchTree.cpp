#include "BinarySearchTree.h"

/* PRIVATE FUNCTIONS */
BinarySearchNode* BinarySearchTree::makeBinarySearchNode(int data) {
    BinarySearchNode* temp = new BinarySearchNode;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

bool BinarySearchTree::isValidHelper(BinarySearchNode* root) {
    int* arr = new int[size];
    int i = 0;
    inorder(root, arr, i);
    bool sorted = is_sorted(arr, arr + size);
    delete[] arr;
    return sorted;
}

BinarySearchNode* BinarySearchTree::insertHelper(BinarySearchNode* curr, int data) {
    if (curr == NULL) {
        size += 1;
        return makeBinarySearchNode(data);
    }

    if (data < curr->data) {
        curr->left = insertHelper(curr->left, data);
    } else if (data > curr->data) {
        curr->right = insertHelper(curr->right, data);
    }

    return curr;
}

BinarySearchNode* BinarySearchTree::removeHelper(BinarySearchNode* curr, int data) {
    if (curr == NULL) {
        return NULL;
    }

    if (data < curr->data) {
        curr->left = removeHelper(curr->left, data);
        return curr;
    } else if (data > curr->data) {
        curr->right = removeHelper(curr->right, data);
        return curr;
    }

    // one child or no children
    if (curr->left == NULL || curr->right == NULL) {
        BinarySearchNode* temp = curr->left == NULL ? curr->right : curr->left;
        delete curr;
        size -= 1;
        return temp;
    }

    // two children, get inorder successor
    BinarySearchNode* temp = getMinHelper(curr->right);
    curr->data = temp->data;
    curr->right = removeHelper(curr->right, temp->data);
    return curr;
}

BinarySearchNode* BinarySearchTree::find(BinarySearchNode* curr, int data) {
    if (curr == NULL) {
        return NULL;
    }

    if (data < curr->data) {
        return find(curr->left, data);
    } else if (data > curr->data) {
        return find(curr->right, data);
    }

    return curr;
}

BinarySearchNode* BinarySearchTree::purgeHelper(BinarySearchNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    purgeHelper(curr->left);
    purgeHelper(curr->right);
    delete curr;
    size -= 1;
    return NULL;
}

BinarySearchNode* BinarySearchTree::getMinHelper(BinarySearchNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->left == NULL) {
        return curr;
    }
    return getMinHelper(curr->left);
}

BinarySearchNode* BinarySearchTree::getMaxHelper(BinarySearchNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->right == NULL) {
        return curr;
    }
    return getMaxHelper(curr->right);
}

int BinarySearchTree::getHeightHelper(BinarySearchNode* curr) {
    if (curr == NULL) {
        return 0;
    }

    return max(getHeightHelper(curr->left), getHeightHelper(curr->right)) + 1;
}

void BinarySearchTree::inorder(BinarySearchNode* curr, int* &arr, int &i) {
    if (curr == NULL) {
        return;
    }
    inorder(curr->left, arr, i);
    arr[i++] = curr->data;
    inorder(curr->right, arr, i);
}

BinarySearchTree::~BinarySearchTree() {
    purge();
}
