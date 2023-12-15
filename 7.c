#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of a binary search tree node
struct TreeNode {
    char name[50];
    char phoneNumber[15];
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* createNode(char name[], char phoneNumber[]) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    strcpy(newNode->name, name);
    strcpy(newNode->phoneNumber, phoneNumber);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
struct TreeNode* insertNode(struct TreeNode* root, char name[], char phoneNumber[]) {
    if (root == NULL) {
        return createNode(name, phoneNumber);
    }

    // Compare the names to decide whether to go left or right
    int compareResult = strcmp(name, root->name);

    if (compareResult < 0) {
        root->left = insertNode(root->left, name, phoneNumber);
    } else if (compareResult > 0) {
        root->right = insertNode(root->right, name, phoneNumber);
    } else {
        // Name already exists, update the phone number if needed
        strcpy(root->phoneNumber, phoneNumber);
    }

    return root;
}

// Function to search for a name in the BST
struct TreeNode* searchNode(struct TreeNode* root, char name[]) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        return searchNode(root->left, name);
    } else {
        return searchNode(root->right, name);
    }
}

// Function to find the node with the minimum value in a BST
struct TreeNode* findMinNode(struct TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
struct TreeNode* deleteNode(struct TreeNode* root, char name[]) {
    if (root == NULL) {
        return root;
    }

    int compareResult = strcmp(name, root->name);

    if (compareResult < 0) {
        root->left = deleteNode(root->left, name);
    } else if (compareResult > 0) {
        root->right = deleteNode(root->right, name);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children, get the inorder successor (smallest in the right subtree)
        struct TreeNode* temp = findMinNode(root->right);

        // Copy the inorder successor's content to this node
        strcpy(root->name, temp->name);
        strcpy(root->phoneNumber, temp->phoneNumber);

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->name);
    }

    return root;
}

// Function to print the entire phone list (inorder traversal)
void printPhoneList(struct TreeNode* root) {
    if (root != NULL) {
        printPhoneList(root->left);
        printf("Name: %s, Phone Number: %s\n", root->name, root->phoneNumber);
        printPhoneList(root->right);
    }
}

// Function to free the memory allocated for the BST
void freeTree(struct TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct TreeNode* phoneBook = NULL;
    int choice;
    char name[50], phoneNumber[15];

    do {
        printf("\nMenu:\n");
        printf("1. Search for a name\n");
        printf("2. Insert a new name\n");
        printf("3. Delete an existing name\n");
        printf("4. Print the entire phone list\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name to search: ");
                scanf("%s", name);
                struct TreeNode* searchResult = searchNode(phoneBook, name);
                if (searchResult != NULL) {
                    printf("Phone Number: %s\n", searchResult->phoneNumber);
                } else {
                    printf("Name not found in the phone list.\n");
                }
                break;
            case 2:
                printf("Enter name to insert: ");
                scanf("%s", name);
                printf("Enter phone number: ");
                scanf("%s", phoneNumber);
                phoneBook = insertNode(phoneBook, name, phoneNumber);
                printf("Name inserted into the phone list.\n");
                break;
            case 3:
                printf("Enter name to delete: ");
                scanf("%s", name);
                phoneBook = deleteNode(phoneBook, name);
                printf("Name deleted from the phone list.\n");
                break;
            case 4:
                printf("Phone List:\n");
                printPhoneList(phoneBook);
                break;
            case 5:
                freeTree(phoneBook);
                printf("Program terminated successfully.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (1);

    return 0;
}

