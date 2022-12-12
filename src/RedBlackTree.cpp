#include "RedBlackTree.h"

/* PRIVATE FUNCTIONS */
RedBlackNode* RedBlackTree::makeRedBlackNode(int data, int color) {
    RedBlackNode* temp = new RedBlackNode;
    temp->data = data;
    temp->color = color;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

bool RedBlackTree::isValidHelper(RedBlackNode* root) {
    if (root == NULL) {
        return true;
    }
    if (root->color != BLACK) {
        return false;
    }

    int* arr = new int[size];
    int i = 0;
    inorder(root, arr, i);
    bool sorted = is_sorted(arr, arr + size);
    delete[] arr;
    if (!sorted) {
        return false;
    }

    bool valid = true;
    ensureRedBlackProperties(root, valid);
    return valid;
}

int RedBlackTree::getColor(RedBlackNode* curr) {
    if (curr == NULL) {
        return BLACK;
    }
    return curr->color;
}

int RedBlackTree::ensureRedBlackProperties(RedBlackNode* curr, bool &valid) {
    if (curr == NULL) {
        return 1;
    }

    if (curr->color == RED
        && (getColor(curr->left) == RED
        || getColor(curr->right) == RED)) {
        valid = false;
    }

    int numLeft = ensureRedBlackProperties(curr->left, valid);
    int numRight = ensureRedBlackProperties(curr->right, valid);
    if (numLeft != numRight) {
        valid = false;
    }
    return numLeft;
}

RedBlackNode* RedBlackTree::insertHelper(RedBlackNode* curr, int data) {
    return NULL;
}

RedBlackNode* RedBlackTree::removeHelper(RedBlackNode* curr, int data) {
    return NULL;
}

RedBlackNode* RedBlackTree::find(RedBlackNode* curr, int data) {
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

RedBlackNode* RedBlackTree::purgeHelper(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    purgeHelper(curr->left);
    purgeHelper(curr->right);
    delete curr;
    size -= 1;
    return NULL;
}

RedBlackNode* RedBlackTree::rotateRight(RedBlackNode* curr) {
    RedBlackNode* child = curr->left;
    curr->left = child->right;
    child->right = curr;

    return child;
}

RedBlackNode* RedBlackTree::rotateLeft(RedBlackNode* curr) {
    RedBlackNode* child = curr->right;
    curr->right = child->left;
    child->left = curr;

    return child;
}

RedBlackNode* RedBlackTree::getMinHelper(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->left == NULL) {
        return curr;
    }
    return getMinHelper(curr->left);
}

RedBlackNode* RedBlackTree::getMaxHelper(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->right == NULL) {
        return curr;
    }
    return getMaxHelper(curr->right);
}

int RedBlackTree::getHeightHelper(RedBlackNode* curr) {
    if (curr == NULL) {
        return 0;
    }

    return max(getHeightHelper(curr->left), getHeightHelper(curr->right)) + 1;
}

void RedBlackTree::inorder(RedBlackNode* curr, int* &arr, int &i) {
    if (curr == NULL) {
        return;
    }
    inorder(curr->left, arr, i);
    arr[i++] = curr->data;
    inorder(curr->right, arr, i);
}

RedBlackTree::~RedBlackTree() {
    purge();
}
