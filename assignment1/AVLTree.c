
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Record.h"
#include "AVLTree.h"

typedef struct node *Node;
struct node {
    Record rec;
    Node   left;
    Node   right;
    int    height;
};

struct tree {
    Node    root;
    int     (*compare)(Record, Record);
};

////////////////////////////////////////////////////////////////////////
// Auxiliary functions

static void doTreeFree(Node n, bool freeRecords);
static Node newNode(Record rec);
static Record doTreeSearch(Tree t, Node n, Record rec);
static Node doTreeInsert(Tree t, Node n, Record rec, bool *res);
void doRotation(Tree t, Node n, Record rec);
Node rotateRight(Node n1);
Node rotateLeft(Node n2);
int adjustHeight(Node n);
static void doTreeSearchBetween(Tree t, Node n, Record lower, Record upper, List l);
static Record doTreeNext(Tree t, Node n, Record rec);
////////////////////////////////////////////////////////////////////////

static Node newNode(Record rec) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->rec = rec;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    return n;
}

////////////////////////////////////////////////////////////////////////

Tree TreeNew(int (*compare)(Record, Record)) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    t->root = NULL;
    t->compare = compare;
    return t;
}

////////////////////////////////////////////////////////////////////////

void TreeFree(Tree t, bool freeRecords) {
    doTreeFree(t->root, freeRecords);
    free(t);
}

static void doTreeFree(Node n, bool freeRecords) {
    if (n != NULL) {
        doTreeFree(n->left, freeRecords);
        doTreeFree(n->right, freeRecords);
        if (freeRecords) {
            RecordFree(n->rec);
        }
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////

Record TreeSearch(Tree t, Record rec) {
    return doTreeSearch(t, t->root, rec);
}

static Record doTreeSearch(Tree t, Node n, Record rec) {
    if (n == NULL) {
        return NULL;
    }

    int cmp = t->compare(rec, n->rec);
    if (cmp < 0) {
        return doTreeSearch(t, n->left, rec);
    } else if (cmp > 0) {
        return doTreeSearch(t, n->right, rec);
    } else {
        return n->rec;
    }
}


////////////////////////////////////////////////////////////////////////
/* IMPORTANT: 
   Do NOT modify the code above this line. 
   You must not modify the 'node' and 'tree' structures defined above.
   You must not modify the functions defined above.
*/
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

bool TreeInsert(Tree t, Record rec) {
    bool res = false; // if the record was inserted
    t->root = doTreeInsert(t, t->root, rec, &res);
    return res;
}

static Node doTreeInsert(Tree t, Node n, Record rec, bool *res) {
    if (n == NULL) {
        *res = true;
        return newNode(rec);
    }
    int cmp = t->compare(rec, n->rec);
    if (cmp < 0) {
        n->left = doTreeInsert(t, n->left, rec, res);
        //adjustHeight(n);
    } else if (cmp > 0) {
        n->right = doTreeInsert(t, n->right, rec, res);
        //adjustHeight(n);
    } else {
        *res = false;
    }
    //doRotation(t, n, rec);
    return n;
}

void doRotation(Tree t, Node n, Record rec) {
    if (adjustHeight(n) > 1) {
        if (t->compare(rec, n->left->rec) > 0) {
            n->left = rotateLeft(n->left);
        }
        n = rotateRight(n);
    } else if (adjustHeight(n) < -1) {
        if (t->compare(rec, n->right->rec) < 0) {
            n->right = rotateRight(n->right);
        }
        n = rotateLeft(n);
    }
}

Node rotateRight(Node n1) {
    if (n1 == NULL || n1->left == NULL) {
        return n1;
    }
    Node n2 = n1->left;
    n1->left = n2->right;
    n2->right = n1;
    adjustHeight(n1);
    adjustHeight(n2);
    return n2;
}

Node rotateLeft(Node n2) {
    if (n2 == NULL || n2->right == NULL) {
        return n2;
    }
    Node n1 = n2->right;
    n2->right = n1->left;
    n1->left = n2;
    adjustHeight(n2);
    adjustHeight(n1);
    return n1;
}
int adjustHeight(Node n) {
    if (n == NULL) {
        return 0;
    }
    //If n has no leaf node, return 0
    if (n->left == NULL && n->right == NULL) {
        n->height = 0;
        return 0;
    //If n has no left branch
    } else if (n->left == NULL) { 
        n->height = n->right->height + 1;
        return -(n->right->height + 1);
    //If n has no right branch
    } else if (n->right == NULL) { 
        n->height = n->left->height + 1;
        return n->left->height + 1;
    //If right height is bigger than left height
    } else if (n->right->height > n->left->height) {
        n->height = n->right->height + 1;
    //If left height is bigger than right height
    } else if (n->left->height > n->right->height) {
        n->height = n->left->height + 1;
    //If left height and right height is equal
    } else {
        n->height = n->left->height + 1;
    }
    return n->left->height - n->right->height;
}
////////////////////////////////////////////////////////////////////////

List TreeSearchBetween(Tree t, Record lower, Record upper) {
    List l = ListNew();
    doTreeSearchBetween(t, t->root, lower, upper, l);
    return l;
}

// n - the current node
// l - a list to accumulate results
static void doTreeSearchBetween(Tree t, Node n, Record lower,
                                Record upper, List l) {
    if (n == NULL) {
        return;
    }
    int bigger = t->compare(n->rec, lower);
    int smaller = t->compare(upper, n->rec);
    if (bigger >= 0 && smaller >= 0) {
        if (n->left != NULL) {
            doTreeSearchBetween(t, n->left, lower, upper, l);
        }
        ListAppend(l, n->rec);
        if (n->right != NULL) {
            doTreeSearchBetween(t, n->right, lower, upper, l);
        }
    } else if (bigger < 0) {
        if (n->right != NULL) {
            doTreeSearchBetween(t, n->right, lower, upper, l);
        }
    } else {
        if (n->left != NULL) {
            doTreeSearchBetween(t, n->left, lower, upper, l);
        }
    }
}

////////////////////////////////////////////////////////////////////////

Record TreeNext(Tree t, Record r) {
    return doTreeNext(t, t->root, r);
    /*Record result = TreeSearch(t, r);
    if (result == NULL) {
        return doTreeNext(t, t->root, r);
    } else {
        return result;
    }*/
}

static Record doTreeNext(Tree t, Node n, Record rec) {
    if (n == NULL) {
        return NULL;
    }
    //Compare rec to current node
    int cmp = t->compare(rec, n->rec);
    //record is smaller than current node
    if (cmp < 0) {
        //If there isn't a node smaller than current node, then current node is the smallest node that is bigger than rec
        if (n->left == NULL) {
            return n->rec;
        }
        //Compare with a smaller node
        int cmpLeft = t->compare(rec, n->left->rec);
        //If rec is bigger than a smaller node, then current node is the smallest node that is bigger than rec
        if (cmpLeft > 0) {
            if (n->left->right == NULL) {
                return n->rec;
            } 
        }
        //Else, do fining in left branch
        Record r = doTreeNext(t, n->left, rec);
        //If it returns NULL, which means all nodes in left branch is smaller than rec, then current node is the smallest node that is bigger than rec
        if (r == NULL) {
            return n->rec;
        }
        return r;
        //Record is bigger than current node
    } else if (cmp > 0) {
        //If there isn't a node bigger than current node, then no node that under current node is bigger than rec, return NULL
        if (n->right == NULL) {
            return NULL;
        }
        //Compare with a bigger node
        int cmpRight = t->compare(rec, n->right->rec);
        //If rec is smaller than the bigger node, then the node is the smallest node that is bigger than rec
        if (cmpRight < 0) {
            if (n->right->left == NULL) {
                return n->right->rec;
            }
        }
        //Else, do finding in right branch
        return doTreeNext(t, n->right, rec);
    } else {
        return NULL;
    }
}
