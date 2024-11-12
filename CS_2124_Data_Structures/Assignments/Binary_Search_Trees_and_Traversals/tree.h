#ifndef TREE_H
#define TREE_H

// node struct
typedef struct node {
    int value;
    struct node* left;
    struct node* right;
} Node;

Node* createNode(int value);
Node* insert(Node* root, int value);
void printInOrder(Node* node);
void printPreOrder(Node* node);
void printPostOrder(Node* node);

#endif
