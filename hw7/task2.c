#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree {
    int key;
    struct tree *left, *right;
    struct tree *parent;
} tree;

tree* search_tree(tree *root, int key) {
    if(root == NULL || root->key == key)
        return root;
    else if(root->key > key)
        return search_tree(root->left, key);
    else
        return search_tree(root->right, key);
}

tree* findBrother(tree *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    tree* res = search_tree(root, key);
    if (res == NULL)
    {
        return NULL;
    }
    if (res->parent == NULL)
    {
        return NULL;
    }
    if (res->key < res->parent->key)
    {
        return res->parent->right;
    }
    return res->parent->left;
}
