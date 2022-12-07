#include "AVLTree.h"

/* PRIVATE FUNCTIONS */
AVLNode* AVLTree::makeAVLNode(int data, AVLNode* left, AVLNode* right) {
    AVLNode* temp = new AVLNode;
    temp->data = data;
    temp->height = 1;
    temp->left = left;
    temp->right = right;
    return temp;
}

bool AVLTree::isValidHelper(AVLNode* root) {
    int* arr = new int[size];
    int i = 0;
    inorder(root, arr, i);
    bool sorted = is_sorted(arr, arr + size);
    delete[] arr;
    if (!sorted) {
        return false;
    }
    return isBalancedHelper(root);
}

bool AVLTree::isBalancedHelper(AVLNode* curr) {
    if (curr == NULL) {
        return true;
    }
    int balance = getBalanceHelper(curr);
    return balance >= -1 && balance <= 1 && isBalancedHelper(curr->left) && isBalancedHelper(curr->right);
}

AVLNode* AVLTree::insertHelper(AVLNode* curr, int data) {
    if (curr == NULL) {
        size += 1;
        return makeAVLNode(data, NULL, NULL);
    }

    if (data < curr->data) {
        curr->left = insertHelper(curr->left, data);
    } else if (data > curr->data) {
        curr->right = insertHelper(curr->right, data);
    } else {
        return curr;
    }

    updateHeight(curr);
    int balance = getBalanceHelper(curr);

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

AVLNode* AVLTree::removeHelper(AVLNode* curr, int data) {
    if (curr == NULL) {
        return NULL;
    }

    if (data < curr->data) {
        curr->left = removeHelper(curr->left, data);
        updateHeight(curr);
    } else if (data > curr->data) {
        curr->right = removeHelper(curr->right, data);
        updateHeight(curr);
    } else {
        if (curr->left == NULL || curr->right == NULL) {
            AVLNode* temp = curr->left == NULL ? curr->right : curr->left;
            if (temp == NULL) {
                // no children
                temp = curr;
                delete temp;
                curr = NULL;
            } else {
                // one child
                curr->data = temp->data;
                delete temp;
            }
            size -= 1;
        } else {
            // two children, get inorder successor
            AVLNode* temp = getMinHelper(curr->right);
            curr->data = temp->data;
            curr->right = removeHelper(curr->right, temp->data);
        }
    }

    // tree is now empty
    if (curr == NULL) {
        return NULL;
    }

    updateHeight(curr);
    int balance = getBalanceHelper(curr);

    // left-left case
    if (balance > 1 && getBalanceHelper(curr->left) >= 0) {
        return rotateRight(curr);
    }

    // left-right case
    if (balance > 1 && getBalanceHelper(curr->left) < 0) {
        curr->left = rotateLeft(curr->left);
        return rotateRight(curr);
    }

    // right-right case
    if (balance < -1 && getBalanceHelper(curr->right) <= 0) {
        return rotateLeft(curr);
    }

    // right-left case
    if (balance < -1 && getBalanceHelper(curr->right) > 0) {
        curr->right = rotateRight(curr->right);
        return rotateLeft(curr);
    }
    return curr;
}

AVLNode* AVLTree::find(AVLNode* curr, int data) {
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

AVLNode* AVLTree::purgeHelper(AVLNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    purgeHelper(curr->left);
    purgeHelper(curr->right);
    delete curr;
    size -= 1;
    return NULL;
}

int AVLTree::getBalanceHelper(AVLNode* curr) {
    if (curr == NULL) {
        return 0;
    }
    return getHeightHelper(curr->left) - getHeightHelper(curr->right);
}

void AVLTree::updateHeight(AVLNode* curr) {
    curr->height = max(getHeightHelper(curr->left), getHeightHelper(curr->right)) + 1;
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

AVLNode* AVLTree::getMinHelper(AVLNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->left == NULL) {
        return curr;
    }
    return getMinHelper(curr->left);
}

AVLNode* AVLTree::getMaxHelper(AVLNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->right == NULL) {
        return curr;
    }
    return getMaxHelper(curr->right);
}

int AVLTree::getHeightHelper(AVLNode* curr) {
    return curr == NULL ? 0 : curr->height;
}

void AVLTree::inorder(AVLNode* curr, int* &arr, int &i) {
    if (curr == NULL) {
        return;
    }
    inorder(curr->left, arr, i);
    arr[i++] = curr->data;
    inorder(curr->right, arr, i);
}

AVLTree::~AVLTree() {
    purge();
}
