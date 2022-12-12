#include "RedBlackTree.h"

/* PRIVATE FUNCTIONS */
RedBlackNode* RedBlackTree::makeRedBlackNode(int data) {
    RedBlackNode* temp = new RedBlackNode;
    temp->data = data;
    temp->color = RED;
    temp->child[left] = NULL;
    temp->child[right] = NULL;
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

    if (curr->color == RED && (isRed(curr->child[left]) || isRed(curr->child[right]))) {
        valid = false;
        return -1;
    }

    int numLeft = ensureRedBlackProperties(curr->child[left], valid);
    int numRight = ensureRedBlackProperties(curr->child[right], valid);
    if (numLeft != numRight) {
        valid = false;
    }
    return numLeft;
}

RedBlackNode* RedBlackTree::insertHelper(RedBlackNode* curr, int data) {
    if (curr == NULL) {
        size += 1;
        return makeRedBlackNode(data);
    } else if (curr->data == data) {
        return curr;
    }

    bool i = data > curr->data;
    curr->child[i] = insertHelper(curr->child[i], data);
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

RedBlackNode* RedBlackTree::removeHelper(RedBlackNode* curr, int data) {
    bool valid = false;
    root = removeHelper(root, data, valid);
    if (root != NULL) {
        root->color = BLACK;
    }
    return root;
}

RedBlackNode* RedBlackTree::removeHelper(RedBlackNode* curr, int data, bool &valid) {
    if (curr == NULL) {
        valid = true;
        return NULL;
    }

    if (curr->data == data) {
        if (curr->child[left] == NULL || curr->child[right] == NULL) {
            // one child or no children
            RedBlackNode* temp = curr->child[right] == NULL ? curr->child[left] : curr->child[right];
            if (isRed(curr)) {
                delete curr;
                valid = true;
            } else if (isRed(temp)) {
                temp->color = BLACK;
                delete temp;
                valid = true;
            }

            size -= 1;
            return temp;
        } else {
            // two children, get inorder successor
            RedBlackNode* temp = getMinHelper(curr->child[right]);
            curr->data = temp->data;
            curr->child[right] = removeHelper(curr->child[right], temp->data, valid);
        }
    }

    bool i = data > curr->data;
    curr->child[i] = removeHelper(curr->child[i], data, valid);
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
        if (!isRed(sibling->child[left]) && !isRed(sibling->child[right])) {
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
            parent->child[left]->color = BLACK;
            parent->child[right]->color = BLACK;

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

RedBlackNode* RedBlackTree::find(RedBlackNode* curr, int data) {
    if (curr == NULL) {
        return NULL;
    }

    if (data < curr->data) {
        return find(curr->child[left], data);
    } else if (data > curr->data) {
        return find(curr->child[right], data);
    }

    return curr;
}

RedBlackNode* RedBlackTree::purgeHelper(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    purgeHelper(curr->child[left]);
    purgeHelper(curr->child[right]);
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
    curr->child[left]->color = curr->child[left]->color^1;
    curr->child[right]->color = curr->child[right]->color^1;
}

RedBlackNode* RedBlackTree::getMinHelper(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->child[left] == NULL) {
        return curr;
    }
    return getMinHelper(curr->child[left]);
}

RedBlackNode* RedBlackTree::getMaxHelper(RedBlackNode* curr) {
    if (curr == NULL) {
        return NULL;
    }

    if (curr->child[right] == NULL) {
        return curr;
    }
    return getMaxHelper(curr->child[right]);
}

int RedBlackTree::getHeightHelper(RedBlackNode* curr) {
    if (curr == NULL) {
        return 0;
    }

    return max(getHeightHelper(curr->child[left]), getHeightHelper(curr->child[right])) + 1;
}

void RedBlackTree::inorder(RedBlackNode* curr, int* &arr, int &i) {
    if (curr == NULL) {
        return;
    }
    inorder(curr->child[left], arr, i);
    arr[i++] = curr->data;
    inorder(curr->child[right], arr, i);
}

/* PUBLIC FUNCTIONS */
void RedBlackTree::insert(int data) {
    root = insertHelper(root, data);
    root->color = BLACK;
}

RedBlackTree::~RedBlackTree() {
    purge();
}
