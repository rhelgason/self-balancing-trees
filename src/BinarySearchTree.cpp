#include "BinarySearchTree.h"

/* PRIVATE FUNCTIONS */
BinarySearchNode* BinarySearchTree::Node(int data) {
    BinarySearchNode* temp = new BinarySearchNode;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

bool BinarySearchTree::_isValid(BinarySearchNode* root) {
    int* arr = new int[size];
    int i = 0;
    _inorder(root, arr, i);
    bool sorted = is_sorted(arr, arr + size);
    delete[] arr;
    return sorted;
}

BinarySearchNode* BinarySearchTree::_insert(BinarySearchNode* curr, int data) {
    if (curr == NULL) {
        size += 1;
        return Node(data);
    }

    if (data < curr->data) {
        curr->left = _insert(curr->left, data);
    } else if (data > curr->data) {
        curr->right = _insert(curr->right, data);
    }

    return curr;
}

BinarySearchNode* BinarySearchTree::_remove(BinarySearchNode* curr, int data) {
    if (curr == NULL) {
        return NULL;
    }

    if (data < curr->data) {
        curr->left = _remove(curr->left, data);
        return curr;
    } else if (data > curr->data) {
        curr->right = _remove(curr->right, data);
        return curr;
    }

    // one child or no children
    if (curr->left == NULL || curr->right == NULL) {
        BinarySearchNode* temp = curr->left == NULL ? curr->right : curr->left;
        delete curr;
        size -= 1;
        return temp;
    }

    // two children, get _inorder successor
    BinarySearchNode* temp = _getMin(curr->right);
    curr->data = temp->data;
    curr->right = _remove(curr->right, temp->data);
    return curr;
}

BinarySearchNode* BinarySearchTree::_find(BinarySearchNode* curr, int data) {
    if (curr == NULL) {
        return NULL;
    }

    if (data < curr->data) {
        return _find(curr->left, data);
    } else if (data > curr->data) {
        return _find(curr->right, data);
    }

    return curr;
}

BinarySearchNode* BinarySearchTree::_purge(BinarySearchNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    _purge(curr->left);
    _purge(curr->right);
    delete curr;
    size -= 1;
    return NULL;
}

BinarySearchNode* BinarySearchTree::_getMin(BinarySearchNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->left == NULL) {
        return curr;
    }
    return _getMin(curr->left);
}

BinarySearchNode* BinarySearchTree::_getMax(BinarySearchNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->right == NULL) {
        return curr;
    }
    return _getMax(curr->right);
}

int BinarySearchTree::_getHeight(BinarySearchNode* curr) {
    if (curr == NULL) {
        return 0;
    }

    return max(_getHeight(curr->left), _getHeight(curr->right)) + 1;
}

void BinarySearchTree::_inorder(BinarySearchNode* curr, int* &arr, int &i) {
    if (curr == NULL) {
        return;
    }
    _inorder(curr->left, arr, i);
    arr[i++] = curr->data;
    _inorder(curr->right, arr, i);
}

/* PUBLIC FUNCTIONS */
BinarySearchTree::~BinarySearchTree() {
    purge();
}
