#include<stdio.h>
#include<stdlib.h>
#include "tree.h"

Node* createNode(int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);

    return root;
}

void printInOrder(Node* node) {
    if (node == NULL) return;
    printInOrder(node->left);
    printf("%d ", node->value);
    printInOrder(node->right);
}

void printPreOrder(Node* node) {
    if (node == NULL) return;
    printf("%d ", node->value);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

void printPostOrder(Node* node) {
    if (node == NULL) return;
    printPostOrder(node->left);
    printPostOrder(node->right);
    printf("%d ", node->value);
}
