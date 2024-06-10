#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    int element;
} node;

typedef struct {
    node *root;
    int n; // number of nodes
} binary_tree;

node* create_node(node *parent, int element) {
    node *n;

    n = (node*) malloc(sizeof(node));
    if (n == NULL) {
        return NULL;
    }
    n->parent = parent;
    n->left = n->right = NULL;
    n->element = element;

    return n;
}

binary_tree* create_binary_tree() {
    binary_tree *bt;

    bt = (binary_tree*) malloc(sizeof(binary_tree));
    if (bt == NULL) {
        return NULL;
    }
    bt->root = NULL;
    bt->n = 0;

    return bt;
}

void traversal_in_order(node *np) {
    traversal_in_order(np->left);
    printf("%d, ", np->element);
    traversal_in_order(np->right);
}

// which node come first in traversal order (in order)
node* subtree_first(node *np) {
    if (np == NULL) {
        return NULL;
    }

    if (np->left == NULL) {
        return np;
    }

    return subtree_first(np->left);
}

// which node come last in traversal order (in order)
node* subtree_last(node *np) {
    if (np == NULL) {
        return NULL;
    }

    if (np->right == NULL) {
        return np;
    }

    return subtree_last(np->right);
}

// next after node in tree's traversal order (in order)
node* successor(node *np) {
    if (np == NULL) {
        return NULL;
    }

    if (np->right) {
        return subtree_first(np->right);
    }
    else {
        node* n;

        n = np;
        while(n->parent != NULL && n == n->parent->right) {
            n = n->parent;
        }

        return n->parent;
    }
}

node* predecessor(node *np) {
    if (np == NULL) {
        return NULL;
    }

    if (np->left) {
        return subtree_last(np->left);
    }
    else {
        node *n;

        n = np;
        while(np != NULL && np == np->parent->left) {
            n = n->parent;
        }

        return n->parent;
    }
}

// insert a new node after of a specific node
int subtree_insert_after(node *np, int element) {
    if (np == NULL) {
        return -1;
    }
    if (np->right == NULL) {
        np->right = create_node(np, element);
    }
    else {
        node *n;

        n = successor(np);
        n->left = create_node(n, element);
    }

    return 0;
}

// insert a new node before of a specific node
int subtree_insert_before(node *np, int element) {
    if (np == NULL) {
        return -1;
    }
    if (np->left == NULL) {
        np->left = create_node(np, element);
    }
    else {
        node *n;

        n = predecessor(np);
        n->right = create_node(n, element);
    }

    return 0;
}
