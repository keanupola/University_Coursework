#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main() {
    int numNodes, value, order;
    BSTNode *root = NULL;

    printf("Enter the number of nodes for the tree: ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; i++) {
        printf("Enter a node value: ");
        scanf("%d", &value);
        root = insertNode(root, value);
    }

    printf("Enter the order for traversal and printing (0-Preorder, 1-Inorder, 2-Postorder): ");
    scanf("%d", &order);
    traverseBST(root, (BSTOrder) order);
    printf("\n");

    deleteBST(root);

    return 0;
}
