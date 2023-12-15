#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a student
struct Student {
    int rollNumber;
    char name[50];
    float percentage;
};

// Function to compare two students based on roll number
int compareStudents(const void* a, const void* b) {
    return ((struct Student*)a)->rollNumber - ((struct Student*)b)->rollNumber;
}

// Function to search for a student using binary search
int searchStudent(struct Student database[], int n, int targetRollNumber) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (database[mid].rollNumber == targetRollNumber) {
            return mid; // Student found at index mid
        } else if (database[mid].rollNumber < targetRollNumber) {
            low = mid + 1; // Search in the right half
        } else {
            high = mid - 1; // Search in the left half
        }
    }

    return -1; // Student not found
}

int main() {
    int n; // Number of students in the database
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student* database = (struct Student*)malloc(n * sizeof(struct Student));

    // Input student details
    int i;  // move the variable declaration outside the loop
    for (i = 0; i < n; ++i) {
        int roll;
        char studentName[50];
        float percentage;

        printf("Enter details for student %d:\n", i + 1);
        printf("Roll Number: ");
        scanf("%d", &roll);
        database[i].rollNumber = roll;

        printf("Name: ");
        scanf("%s", studentName);
        strcpy(database[i].name, studentName);

        printf("Percentage: ");
        scanf("%f", &percentage);
        database[i].percentage = percentage;
    }

    // Sort the database based on roll number using qsort
    qsort(database, n, sizeof(struct Student), compareStudents);

    // Input roll number to search
    int targetRollNumber;
    printf("\nEnter the roll number to search: ");
    scanf("%d", &targetRollNumber);

    // Perform binary search to find the student
    int resultIndex = searchStudent(database, n, targetRollNumber);

    // Display the search result
    if (resultIndex != -1) {
        printf("\nStudent found!\n");
        printf("Roll Number: %d\n", database[resultIndex].rollNumber);
        printf("Name: %s\n", database[resultIndex].name);
        printf("Percentage: %.2f\n", database[resultIndex].percentage);
    } else {
        printf("\nStudent not found in the database.\n");
    }

    // Free allocated memory
    free(database);

    return 0;
}

