#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a student
struct Student {
    int rollNumber;
    char name[50];
    float percentage;
};

// Function to compare two students based on percentage (descending order)
int compareStudents(const void* a, const void* b) {
    return ((struct Student*)b)->percentage - ((struct Student*)a)->percentage;
}

// Function to perform Bubble Sort on the student database
void bubbleSort(struct Student database[], int n) {
    int i, j;
    struct Student temp;

    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - i - 1; ++j) {
            if (database[j].percentage < database[j + 1].percentage) {
                // Swap the students if they are in the wrong order
                temp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n = 10; // Number of students in the database

    struct Student database[10];
    // Initializing the database with student data
    database[0] = (struct Student){23, "Emily Johnson", 87.5};
    database[1] = (struct Student){45, "Jason Smith", 92.3};
    database[2] = (struct Student){67, "Amanda Lee", 78.9};
    database[3] = (struct Student){89, "Brandon Davis", 85.2};
    database[4] = (struct Student){10, "Sarah Miller", 89.6};
    database[5] = (struct Student){24, "Kevin Wilson", 91.0};
    database[6] = (struct Student){1, "Jessica Brown", 76.8};
    database[7] = (struct Student){34, "Alex Taylor", 84.3};
    database[8] = (struct Student){56, "Rachel White", 88.1};
    database[9] = (struct Student){78, "Matthew Carter", 79.4};

    // Perform Bubble Sort to arrange students in descending order of percentage
    bubbleSort(database, n);

    // Display the first ten toppers
    printf("\nTop Ten Toppers:\n");
    int limit = (n < 10) ? n : 10;
    for (int k = 0; k < limit; ++k) {
        printf("Rank %d:\n", k + 1);
        printf("Roll Number: %d\n", database[k].rollNumber);
        printf("Name: %s\n", database[k].name);
        printf("Percentage: %.2f%%\n", database[k].percentage);
        printf("\n");
    }

    return 0;
}
