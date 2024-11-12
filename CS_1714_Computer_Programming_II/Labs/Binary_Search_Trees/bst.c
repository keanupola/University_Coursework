#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BSTNode* createNode(int value) {
    BSTNode *newNode = (BSTNode *) malloc(sizeof(BSTNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BSTNode* insertNode(BSTNode *root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->value) {
        root->left = insertNode(root->left, value);
    } else if (value > root->value) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

void traverseBST(BSTNode *node, BSTOrder order) {
    if (node == NULL) {
        return;
    }

    if (order == PREORDER) {
        printf("%d\t", node->value);
    }

    traverseBST(node->left, order);

    if (order == INORDER) {
        printf("%d\t", node->value);
    }

    traverseBST(node->right, order);

    if (order == POSTORDER) {
        printf("%d\t", node->value);
    }
}

void deleteBST(BSTNode *node) {
    if (node == NULL) {
        return;
    }

    deleteBST(node->left);
    deleteBST(node->right);
    free(node);
}
