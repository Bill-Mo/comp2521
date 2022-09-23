
#include "tree.h"
static Tree doTreeCopy(Tree t, int depth);

Tree TreeCopy(Tree t, int depth) {
	return doTreeCopy(t, depth);
}

static Tree doTreeCopy(Tree t, int depth) {
    Tree new = malloc(sizeof(Tree));
    new->value = t->value;
    if (depth <= 0 || (t->left == NULL && t->right == NULL)) {
        return new;
    }
    if (t->left != NULL) {
        new->left = doTreeCopy(t->left, depth - 1);
    }
    if (t->right != NULL) {
        new->right = doTreeCopy(t->right, depth - 1);
    }
    return new;
}