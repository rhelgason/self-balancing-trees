#include "BinarySearchTree.h"

/* PRIVATE FUNCTIONS */
Node* BinarySearchTree::makeNode(int data, Node* left, Node* right) {
    Node* temp = new Node;
    temp->data = data;
    temp->left = left;
    temp->right = right;
    return temp;
}

Node* BinarySearchTree::insert(Node* curr, int data) {
    if (curr == NULL) {
        size += 1;
        return makeNode(data, NULL, NULL);
    }

    if (data < curr->data) {
        curr->left = insert(curr->left, data);
    } else if (data > curr->data) {
        curr->right = insert(curr->right, data);
    }

    return curr;
}

Node* BinarySearchTree::remove(Node* curr, int data) {
    if (curr == NULL) {
        return NULL;
    }

    if (data < curr->data) {
        curr->left = remove(curr->left, data);
    } else if (data > curr->data) {
        curr->right = remove(curr->right, data);
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
    Node* temp = getMin(curr->right);
    curr->data = temp->data;
    curr->right = remove(curr->right, temp->data);
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

Node* BinarySearchTree::purge(Node* curr) {
    if (curr == NULL) {
        return NULL;
    }

    purge(curr->left);
    purge(curr->right);
    delete curr;
    size -= 1;
    return NULL;
}

Node* BinarySearchTree::getMin(Node* curr) {
    if (curr->left == NULL) {
        return curr;
    }
    return getMin(curr->left);
}

Node* BinarySearchTree::getMax(Node* curr) {
    if (curr->right == NULL) {
        return curr;
    }
    return getMax(curr->right);
}

int BinarySearchTree::getHeight(Node* curr) {
    if (curr == NULL) {
        return 0;
    }

    return max(getHeight(curr->left), getHeight(curr->right)) + 1;
}

void BinarySearchTree::inorder(Node* curr) {
    if (curr == NULL) {
        return;
    }

    inorder(curr->left);
    cout << curr->data << '\n';
    inorder(curr->right);
}

/* PUBLIC FUNCTIONS */
BinarySearchTree::BinarySearchTree() {
    root = NULL;
    size = 0;
}

void BinarySearchTree::insert(int data) {
    root = insert(root, data);
}

void BinarySearchTree::remove(int data) {
    root = remove(root, data);
}

bool BinarySearchTree::includes(int data) {
    return find(root, data) != NULL;
}

void BinarySearchTree::purge() {
    root = purge(root);
}

int BinarySearchTree::getSize() {
    return size;
}

int BinarySearchTree::getMin() {
    return getMin(root)->data;
}

int BinarySearchTree::getMax() {
    return getMax(root)->data;
}

int BinarySearchTree::getHeight() {
    return getHeight(root);
}

void BinarySearchTree::inorder() {
    inorder(root);
}

BinarySearchTree::~BinarySearchTree() {
    purge();
}
