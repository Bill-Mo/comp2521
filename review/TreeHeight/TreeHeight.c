
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    if (t == NULL) {
        return -1;
    }
    
    if (t->left != NULL && t->right == NULL) {
        return 1 + TreeHeight(t->left);
    }
    if (t->right != NULL && t->left == NULL) {
        return 1 + TreeHeight(t->right);
    }
    int left = 1 + TreeHeight(t->left);
    int right = 1 + TreeHeight(t->right);
    if (left > right) {
        return left;
    } else {
        return right;
    }
}

