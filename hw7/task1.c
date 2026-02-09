#include <stdio.h>
#include <string.h>

typedef struct tree {
    int key;
    struct tree *left, *right;
} tree;

void left_traversal(tree* node)
{
    if (node == NULL)
    {
        return;
    }
    left_traversal(node->left);
    printf("%d ", node->key);
}

void right_traversal(tree* node)
{
    if (node == NULL)
    {
        return;
    }
    printf(" %d", node->key);
    right_traversal(node->right);
    
}

void btUpView(tree *root)
{
    if (root == NULL)
    {
        return;
    }
    
    left_traversal(root->left);
    printf("%d", root->key);
    right_traversal(root->right);
}

