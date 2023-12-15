#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* head, int value) {
    struct Node* newNode = createNode(value);
    if (head == NULL) {
        return newNode;
    }

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    return head;
}

struct Node* deleteNode(struct Node* head, int value) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return head;
    }

    if (head->data == value) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        printf("Node with value %d deleted successfully.\n", value);
        return head;
    }

    struct Node* temp = head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next == NULL) {
        printf("Node with value %d not found.\n", value);
        return head;
    }

    struct Node* deletedNode = temp->next;
    temp->next = temp->next->next;
    free(deletedNode);
    printf("Node with value %d deleted successfully.\n", value);
    return head;
}

struct Node* reverseList(struct Node* head) {
    struct Node *prev, *current, *next;
    prev = NULL;
    current = head;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
    return head;
}

int searchNode(struct Node* head, int value) {
    struct Node* temp = head;
    int position = 1;

    while (temp != NULL) {
        if (temp->data == value) {
            printf("Node with value %d found at position %d.\n", value, position);
            return 1; // Node found
        }
        temp = temp->next;
        position++;
    }

    printf("Node with value %d not found.\n", value);
    return 0; // Node not found
}

int countNodes(struct Node* head) {
    struct Node* temp = head;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    printf("Number of nodes in the list: %d\n", count);
    return count;
}

void displayList(struct Node* head) {
    struct Node* temp = head;

    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(struct Node* head) {
    struct Node* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Reverse List\n");
        printf("4. Search Node\n");
        printf("5. Count Nodes\n");
        printf("6. Display List\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                head = insertNode(head, value);
                break;
            case 2:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                head = deleteNode(head, value);
                break;
            case 3:
                head = reverseList(head);
                printf("List reversed successfully.\n");
                break;
            case 4:
                printf("Enter the value to search: ");
                scanf("%d", &value);
                searchNode(head, value);
                break;
            case 5:
                countNodes(head);
                break;
            case 6:
                displayList(head);
                break;
            case 7:
                freeList(head);
                printf("Program terminated successfully.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (1);

    return 0;
}

