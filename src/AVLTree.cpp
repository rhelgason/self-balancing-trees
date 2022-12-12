#include "AVLTree.h"

/* PRIVATE FUNCTIONS */
AVLNode* AVLTree::Node(int data) {
    AVLNode* temp = new AVLNode;
    temp->data = data;
    temp->height = 1;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

bool AVLTree::_isValid(AVLNode* root) {
    int* arr = new int[size];
    int i = 0;
    _inorder(root, arr, i);
    bool sorted = is_sorted(arr, arr + size);
    delete[] arr;
    if (!sorted) {
        return false;
    }
    return isBalanced(root);
}

bool AVLTree::isBalanced(AVLNode* curr) {
    if (curr == NULL) {
        return true;
    }
    int balance = getBalance(curr);
    return balance >= -1 && balance <= 1 && isBalanced(curr->left) && isBalanced(curr->right);
}

AVLNode* AVLTree::_insert(AVLNode* curr, int data) {
    if (curr == NULL) {
        size += 1;
        return Node(data);
    }

    if (data < curr->data) {
        curr->left = _insert(curr->left, data);
    } else if (data > curr->data) {
        curr->right = _insert(curr->right, data);
    } else {
        return curr;
    }

    updateHeight(curr);
    int balance = getBalance(curr);

    // left-left case
    if (balance > 1 && data < curr->left->data) {
        return rotateRight(curr);
    }

    // left-right case
    if (balance > 1 && data > curr->left->data) {
        curr->left = rotateLeft(curr->left);
        return rotateRight(curr);
    }

    // right-right case
    if (balance < -1 && data > curr->right->data) {
        return rotateLeft(curr);
    }

    // right-left case
    if (balance < -1 && data < curr->right->data) {
        curr->right = rotateRight(curr->right);
        return rotateLeft(curr);
    }
    return curr;
}

AVLNode* AVLTree::_remove(AVLNode* curr, int data) {
    if (curr == NULL) {
        return NULL;
    }

    if (data < curr->data) {
        curr->left = _remove(curr->left, data);
        updateHeight(curr);
    } else if (data > curr->data) {
        curr->right = _remove(curr->right, data);
        updateHeight(curr);
    } else {
        if (curr->left == NULL || curr->right == NULL) {
            // one child or no children
            AVLNode* temp = curr->left == NULL ? curr->right : curr->left;
            delete curr;
            size -= 1;
            return temp;
        } else {
            // two children, get _inorder successor
            AVLNode* temp = _getMin(curr->right);
            curr->data = temp->data;
            curr->right = _remove(curr->right, temp->data);
        }
    }

    // tree is now empty
    if (curr == NULL) {
        return NULL;
    }

    updateHeight(curr);
    int balance = getBalance(curr);

    // left-left case
    if (balance > 1 && getBalance(curr->left) >= 0) {
        return rotateRight(curr);
    }

    // left-right case
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = rotateLeft(curr->left);
        return rotateRight(curr);
    }

    // right-right case
    if (balance < -1 && getBalance(curr->right) <= 0) {
        return rotateLeft(curr);
    }

    // right-left case
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rotateRight(curr->right);
        return rotateLeft(curr);
    }
    return curr;
}

AVLNode* AVLTree::_find(AVLNode* curr, int data) {
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

AVLNode* AVLTree::_purge(AVLNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    _purge(curr->left);
    _purge(curr->right);
    delete curr;
    size -= 1;
    return NULL;
}

int AVLTree::getBalance(AVLNode* curr) {
    if (curr == NULL) {
        return 0;
    }
    return _getHeight(curr->left) - _getHeight(curr->right);
}

void AVLTree::updateHeight(AVLNode* curr) {
    curr->height = max(_getHeight(curr->left), _getHeight(curr->right)) + 1;
}

AVLNode* AVLTree::rotateRight(AVLNode* curr) {
    AVLNode* child = curr->left;
    curr->left = child->right;
    child->right = curr;

    updateHeight(curr);
    updateHeight(child);

    return child;
}

AVLNode* AVLTree::rotateLeft(AVLNode* curr) {
    AVLNode* child = curr->right;
    curr->right = child->left;
    child->left = curr;

    updateHeight(curr);
    updateHeight(child);

    return child;
}

AVLNode* AVLTree::_getMin(AVLNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->left == NULL) {
        return curr;
    }
    return _getMin(curr->left);
}

AVLNode* AVLTree::_getMax(AVLNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->right == NULL) {
        return curr;
    }
    return _getMax(curr->right);
}

int AVLTree::_getHeight(AVLNode* curr) {
    return curr == NULL ? 0 : curr->height;
}

void AVLTree::_inorder(AVLNode* curr, int* &arr, int &i) {
    if (curr == NULL) {
        return;
    }
    _inorder(curr->left, arr, i);
    arr[i++] = curr->data;
    _inorder(curr->right, arr, i);
}

/* PUBLIC FUNCTIONS */
AVLTree::~AVLTree() {
    purge();
}
