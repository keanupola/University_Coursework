#ifndef BST_H
#define BST_H

typedef struct BSTNode {
    int value;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef enum BSTOrder {
    PREORDER,
    INORDER,
    POSTORDER
} BSTOrder;

BSTNode* createNode(int value);
BSTNode* insertNode(BSTNode *root, int value);
void traverseBST(BSTNode *node, BSTOrder order);
void deleteBST(BSTNode *node);

#endif
