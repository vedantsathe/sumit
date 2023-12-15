#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rollNumber;
    char name[50];
    char division;
    char address[100];
} Student;

void addStudent(FILE *file) {
    Student student;

    printf("Enter Roll Number: ");
    scanf("%d", &student.rollNumber);
    printf("Enter Name: ");
    scanf("%s", student.name);
    printf("Enter Division: ");
    scanf(" %c", &student.division);
    printf("Enter Address: ");
    scanf("%s", student.address);

    // Append the student information to the file
    fseek(file, 0, SEEK_END);
    fwrite(&student, sizeof(Student), 1, file);

    printf("Student added successfully.\n");
}

void deleteStudent(FILE *file, int rollNumber) {
    FILE *tempFile = fopen("temp.dat", "wb");
    Student student;

    rewind(file);

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.rollNumber != rollNumber) {
            fwrite(&student, sizeof(Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    printf("Student with Roll Number %d deleted successfully.\n", rollNumber);
}

void displayStudent(FILE *file, int rollNumber) {
    Student student;
    int found = 0;

    rewind(file);

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.rollNumber == rollNumber) {
            printf("Roll Number: %d\n", student.rollNumber);
            printf("Name: %s\n", student.name);
            printf("Division: %c\n", student.division);
            printf("Address: %s\n", student.address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found.\n", rollNumber);
    }
}

int main() {
    FILE *file = fopen("students.dat", "ab+");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    int choice, rollNumber;

    do {
        printf("\n1. Add Student\n2. Delete Student\n3. Display Student\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(file);
                break;
            case 2:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(file, rollNumber);
                break;
            case 3:
                printf("Enter Roll Number to display: ");
                scanf("%d", &rollNumber);
                displayStudent(file, rollNumber);
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    fclose(file);

    return 0;
}
