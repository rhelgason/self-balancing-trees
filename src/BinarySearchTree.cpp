#include "BinarySearchTree.h"

/* PRIVATE FUNCTIONS */
Node* BinarySearchTree::makeNode(int data, Node* left, Node* right) {
    Node* temp = new Node;
    temp->data = data;
    temp->left = left;
    temp->right = right;
    return temp;
}

bool BinarySearchTree::isValidHelper(Node* curr) {
    int* arr = new int[size];
    int i = 0;
    inorder(root, arr, i);
    bool valid = is_sorted(arr, arr + size);
    delete[] arr;
    return valid;
}

Node* BinarySearchTree::insertHelper(Node* curr, int data) {
    if (curr == NULL) {
        size += 1;
        return makeNode(data, NULL, NULL);
    }

    if (data < curr->data) {
        curr->left = insertHelper(curr->left, data);
    } else if (data > curr->data) {
        curr->right = insertHelper(curr->right, data);
    }

    return curr;
}

Node* BinarySearchTree::removeHelper(Node* curr, int data) {
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
    if (curr->left == NULL) {
        Node* temp = curr->right;
        delete curr;
        size -= 1;
        return temp;
    } else if (curr->right == NULL) {
        Node *temp = curr->left;
        delete curr;
        size -= 1;
        return temp;
    }

    // two children
    // get inorder successor
    Node* temp = getMinHelper(curr->right);
    curr->data = temp->data;
    curr->right = removeHelper(curr->right, temp->data);
    return curr;
}

Node* BinarySearchTree::find(Node* curr, int data) {
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

Node* BinarySearchTree::purgeHelper(Node* curr) {
    if (curr == NULL) {
        return NULL;
    }

    purgeHelper(curr->left);
    purgeHelper(curr->right);
    delete curr;
    size -= 1;
    return NULL;
}

Node* BinarySearchTree::getMinHelper(Node* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->left == NULL) {
        return curr;
    }
    return getMinHelper(curr->left);
}

Node* BinarySearchTree::getMaxHelper(Node* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->right == NULL) {
        return curr;
    }
    return getMaxHelper(curr->right);
}

int BinarySearchTree::getHeightHelper(Node* curr) {
    if (curr == NULL) {
        return 0;
    }

    return max(getHeightHelper(curr->left), getHeightHelper(curr->right)) + 1;
}

void BinarySearchTree::inorder(Node* curr, int* &arr, int &i) {
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
