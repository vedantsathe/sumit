#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int height(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

void printLeafNodes(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
    }

    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

struct TreeNode* mirrorImage(struct TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    struct TreeNode* mirroredRoot = createNode(root->data);
    mirroredRoot->left = mirrorImage(root->right);
    mirroredRoot->right = mirrorImage(root->left);

    return mirroredRoot;
}

void printLevel(struct TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }

    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void printLevelOrder(struct TreeNode* root) {
    int h = height(root);
    int i; // Move the variable declaration outside the loop

    for (i = 1; i <= h; i++) {
        printf("Level %d: ", i);
        printLevel(root, i);
        printf("\n");
    }
}

void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int treeHeight = height(root);
    printf("Height of the tree: %d\n", treeHeight);

    printf("Leaf nodes of the tree: ");
    printLeafNodes(root);
    printf("\n");

    struct TreeNode* mirroredTree = mirrorImage(root);

    printf("Original Tree (Level-wise):\n");
    printLevelOrder(root);

    printf("\nMirror Image Tree (Level-wise):\n");
    printLevelOrder(mirroredTree);

    freeTree(root);
    freeTree(mirroredTree);

    return 0;
}

