#include "SplayTree.h"

/* PRIVATE FUNCTIONS */
SplayNode* SplayTree::_deepCopy(SplayNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    SplayNode* temp = new SplayNode;
    temp->data = curr->data;
    temp->left = _deepCopy(curr->left);
    temp->right = _deepCopy(curr->right);
    return temp;
}

SplayNode* SplayTree::Node(int data) {
    SplayNode* temp = new SplayNode;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

bool SplayTree::_isValid(SplayNode* root) {
    int* arr = new int[size];
    int i = 0;
    _inorder(root, arr, i);
    bool sorted = is_sorted(arr, arr + size);
    delete[] arr;
    return sorted;
}

SplayNode* SplayTree::_insert(SplayNode* curr, int data) {
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

SplayNode* SplayTree::_remove(SplayNode* curr, int data) {
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
        SplayNode* temp = curr->left == NULL ? curr->right : curr->left;
        delete curr;
        size -= 1;
        return temp;
    }

    // two children, get _inorder successor
    SplayNode* temp = _getMin(curr->right);
    curr->data = temp->data;
    curr->right = _remove(curr->right, temp->data);
    return curr;
}

SplayNode* SplayTree::_find(SplayNode* curr, int data) {
    root = splay(curr, data);
    if (root == NULL || root->data != data) {
        return NULL;
    }
    return root;
}

SplayNode* SplayTree::splay(SplayNode* curr, int data) {
    if (curr == NULL || curr->data == data) {
        return curr;
    }

    if (data < curr->data) {
        if (curr->left == NULL) {
            return curr;
        }

        if (data < curr->left->data) {
            // left left case
            curr->left->left = splay(curr->left->left, data);
            curr = rotateRight(curr);
        } else if (data > curr->left->data) {
            // left right case
            curr->left->right = splay(curr->left->right, data);
            curr->left = rotateLeft(curr->left);
        }
        return rotateRight(curr);
    } else {
        if (curr->right == NULL) {
            return curr;
        }

        if (data < curr->right->data) {
            // right left case
            curr->right->left = splay(curr->right->left, data);
            curr->right = rotateRight(curr->right);
        } else if (data > curr->right->data) {
            // right right case
            curr->right->right = splay(curr->right->right, data);
            curr = rotateLeft(curr);
        }
        return rotateLeft(curr);
    }
}

SplayNode* SplayTree::_purge(SplayNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    _purge(curr->left);
    _purge(curr->right);
    delete curr;
    size -= 1;
    return NULL;
}

SplayNode* SplayTree::rotateRight(SplayNode* curr) {
    if (curr->left == NULL) {
        return curr;
    }
    SplayNode* child = curr->left;
    curr->left = child->right;
    child->right = curr;
    return child;
}

SplayNode* SplayTree::rotateLeft(SplayNode* curr) {
    if (curr->right == NULL) {
        return curr;
    }
    SplayNode* child = curr->right;
    curr->right = child->left;
    child->left = curr;
    return child;
}

SplayNode* SplayTree::_getMin(SplayNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->left == NULL) {
        return curr;
    }
    return _getMin(curr->left);
}

SplayNode* SplayTree::_getMax(SplayNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->right == NULL) {
        return curr;
    }
    return _getMax(curr->right);
}

int SplayTree::_getHeight(SplayNode* curr) {
    if (curr == NULL) {
        return 0;
    }

    return max(_getHeight(curr->left), _getHeight(curr->right)) + 1;
}

void SplayTree::_inorder(SplayNode* curr, int* &arr, int &i) {
    if (curr == NULL) {
        return;
    }
    _inorder(curr->left, arr, i);
    arr[i++] = curr->data;
    _inorder(curr->right, arr, i);
}

/* PUBLIC FUNCTIONS */
void SplayTree::insert(int data) {
    root = _insert(root, data);
    root = splay(root, data);
}

void SplayTree::remove(int data) {
    root = splay(root, data);
    root = _remove(root, data);
}

SplayTree::SplayTree(SplayTree& tree) {
    root = _deepCopy(tree.getRoot());
    size = tree.getSize();
}

SplayTree::~SplayTree() {
    purge();
}
