#include "RedBlackTree.h"

/* PRIVATE FUNCTIONS */
RedBlackNode* RedBlackTree::_deepCopy(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    RedBlackNode* temp = new RedBlackNode;
    temp->data = curr->data;
    temp->color = curr->color;
    temp->child[LEFT] = _deepCopy(curr->child[LEFT]);
    temp->child[RIGHT] = _deepCopy(curr->child[RIGHT]);
    return temp;
}

RedBlackNode* RedBlackTree::Node(int data) {
    RedBlackNode* temp = new RedBlackNode;
    temp->data = data;
    temp->color = RED;
    temp->child[LEFT] = NULL;
    temp->child[RIGHT] = NULL;
    return temp;
}

bool RedBlackTree::_isValid(RedBlackNode* root) {
    if (root == NULL) {
        return true;
    }
    if (root->color != BLACK) {
        return false;
    }

    int* arr = new int[size];
    int i = 0;
    _inorder(root, arr, i);
    bool sorted = is_sorted(arr, arr + size);
    delete[] arr;
    if (!sorted) {
        return false;
    }

    bool valid = true;
    ensureRedBlackProperties(root, valid);
    return valid;
}

bool RedBlackTree::isRed(RedBlackNode* curr) {
    if (curr == NULL) {
        return false;
    }
    return curr->color == RED;
}

int RedBlackTree::ensureRedBlackProperties(RedBlackNode* curr, bool &valid) {
    if (curr == NULL) {
        return 1;
    }

    if (curr->color == RED && (isRed(curr->child[LEFT]) || isRed(curr->child[RIGHT]))) {
        valid = false;
        return -1;
    }

    int numLeft = ensureRedBlackProperties(curr->child[LEFT], valid);
    int numRight = ensureRedBlackProperties(curr->child[RIGHT], valid);
    if (numLeft != numRight) {
        valid = false;
    }
    return numLeft;
}

RedBlackNode* RedBlackTree::_insert(RedBlackNode* curr, int data) {
    if (curr == NULL) {
        size += 1;
        return Node(data);
    } else if (curr->data == data) {
        return curr;
    }

    bool i = data > curr->data;
    curr->child[i] = _insert(curr->child[i], data);
    return insertFix(curr, i);
}

RedBlackNode* RedBlackTree::insertFix(RedBlackNode* curr, bool i) {
    if (isRed(curr->child[i])) {
        if (isRed(curr->child[!i])) {
            // both children are red
            if (isRed(curr->child[i]->child[i]) || isRed(curr->child[i]->child[!i])) {
                flipColors(curr);
            }
        } else {
            // only one child is red
            if (isRed(curr->child[i]->child[i])) {
                curr = rotate(curr, !i);
            } else if (isRed(curr->child[i]->child[!i])) {
                curr = doubleRotate(curr, !i);
            }
        }
    }
    return curr;
}

RedBlackNode* RedBlackTree::_remove(RedBlackNode* curr, int data) {
    // ignore unused param for method override
    (void)curr;

    bool valid = false;
    root = _remove(root, data, valid);
    if (root != NULL) {
        root->color = BLACK;
    }
    return root;
}

RedBlackNode* RedBlackTree::_remove(RedBlackNode* curr, int data, bool &valid) {
    if (curr == NULL) {
        valid = true;
        return NULL;
    }

    if (curr->data == data) {
        if (curr->child[LEFT] == NULL || curr->child[RIGHT] == NULL) {
            // one child or no children
            RedBlackNode* temp = curr->child[LEFT] == NULL ? curr->child[RIGHT] : curr->child[LEFT];
            delete curr;
            size -= 1;
            return temp;
        } else {
            // two children, get _inorder successor
            RedBlackNode* temp = _getMin(curr->child[RIGHT]);
            curr->data = temp->data;
            curr->child[RIGHT] = _remove(curr->child[RIGHT], temp->data, valid);
        }
    }

    bool i = data > curr->data;
    curr->child[i] = _remove(curr->child[i], data, valid);
    return valid ? curr : removeFix(curr, i, valid);
}

RedBlackNode* RedBlackTree::removeFix(RedBlackNode* curr, bool i, bool &valid) {
    RedBlackNode* parent = curr;
    RedBlackNode* sibling = curr->child[!i];

    if (isRed(sibling)) {
        curr = rotate(curr, i);
        sibling = parent->child[!i];
    }

    if (sibling != NULL) {
        if (!isRed(sibling->child[LEFT]) && !isRed(sibling->child[RIGHT])) {
            // black sibling with two black children
            if (isRed(parent)) {
                valid = true;
            }
            parent->color = BLACK;
            sibling->color = RED;
        } else {
            // black sibling with red child
            int parentColor = parent->color;
            bool isRedSibling = curr != parent;

            if (isRed(sibling->child[!i])) {
                parent = rotate(parent, i);
            } else {
                parent = doubleRotate(parent, i);
            }

            parent->color = parentColor;
            parent->child[LEFT]->color = BLACK;
            parent->child[RIGHT]->color = BLACK;

            if (isRedSibling) {
                curr->child[i] = parent;
            } else {
                curr = parent;
            }
            valid = true;
        }
    }
    return curr;
}

RedBlackNode* RedBlackTree::_find(RedBlackNode* curr, int data) {
    if (curr == NULL) {
        return NULL;
    }

    if (data < curr->data) {
        return _find(curr->child[LEFT], data);
    } else if (data > curr->data) {
        return _find(curr->child[RIGHT], data);
    }

    return curr;
}

RedBlackNode* RedBlackTree::_purge(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    _purge(curr->child[LEFT]);
    _purge(curr->child[RIGHT]);
    delete curr;
    size -= 1;
    return NULL;
}

RedBlackNode* RedBlackTree::rotate(RedBlackNode* curr, bool i) {
    RedBlackNode* child = curr->child[!i];
    curr->child[!i] = child->child[i];
    child->child[i] = curr;

    child->color = curr->color;
    curr->color = RED;

    return child;
}

RedBlackNode* RedBlackTree::doubleRotate(RedBlackNode* curr, bool i) {
    curr->child[!i] = rotate(curr->child[!i], !i);
    return rotate(curr, i);
}

void RedBlackTree::flipColors(RedBlackNode* curr) {
    curr->color = curr->color^1;
    curr->child[LEFT]->color = curr->child[LEFT]->color^1;
    curr->child[RIGHT]->color = curr->child[RIGHT]->color^1;
}

RedBlackNode* RedBlackTree::_getMin(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->child[LEFT] == NULL) {
        return curr;
    }
    return _getMin(curr->child[LEFT]);
}

RedBlackNode* RedBlackTree::_getMax(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->child[RIGHT] == NULL) {
        return curr;
    }
    return _getMax(curr->child[RIGHT]);
}

int RedBlackTree::_getHeight(RedBlackNode* curr) {
    if (curr == NULL) {
        return 0;
    }

    return max(_getHeight(curr->child[LEFT]), _getHeight(curr->child[RIGHT])) + 1;
}

void RedBlackTree::_inorder(RedBlackNode* curr, int* &arr, int &i) {
    if (curr == NULL) {
        return;
    }
    _inorder(curr->child[LEFT], arr, i);
    arr[i++] = curr->data;
    _inorder(curr->child[RIGHT], arr, i);
}

/* PUBLIC FUNCTIONS */
void RedBlackTree::insert(int data) {
    root = _insert(root, data);
    root->color = BLACK;
}

RedBlackTree::RedBlackTree(RedBlackTree& tree) {
    root = _deepCopy(tree.getRoot());
    size = tree.getSize();
}

RedBlackTree::~RedBlackTree() {
    purge();
}
