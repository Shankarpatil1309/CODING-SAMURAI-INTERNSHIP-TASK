#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    int rollNumber;
    char name[50];
    float marks;
} Student;

void addStudent(Student students[], int *count);
void updateStudent(Student students[], int count);
void deleteStudent(Student students[], int *count);
void displayStudents(const Student students[], int count);
void saveToFile(const Student students[], int count);
void loadFromFile(Student students[], int *count);

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    loadFromFile(students, &count);

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. Display All Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                updateStudent(students, count);
                break;
            case 3:
                deleteStudent(students, &count);
                break;
            case 4:
                displayStudents(students, count);
                break;
            case 5:
                saveToFile(students, count);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }
    printf("Enter Roll Number: ");
    scanf("%d", &students[*count].rollNumber);
    printf("Enter Name: ");
    scanf(" %[^\n]", students[*count].name);
    printf("Enter Marks: ");
    scanf("%f", &students[*count].marks);
    (*count)++;
    printf("Student added successfully.\n");
}

void updateStudent(Student students[], int count) {
    int rollNumber, i;
    printf("Enter Roll Number of the student to update: ");
    scanf("%d", &rollNumber);
    for (i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter new Marks: ");
            scanf("%f", &students[i].marks);
            printf("Student record updated successfully.\n");
            return;
        }
    }
    printf("Student with Roll Number %d not found.\n", rollNumber);
}

void deleteStudent(Student students[], int *count) {
    int rollNumber, i, j;
    printf("Enter Roll Number of the student to delete: ");
    scanf("%d", &rollNumber);
    for (i = 0; i < *count; i++) {
        if (students[i].rollNumber == rollNumber) {
            for (j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Student record deleted successfully.\n");
            return;
        }
    }
    printf("Student with Roll Number %d not found.\n", rollNumber);
}

void displayStudents(const Student students[], int count) {
    int i;
    if (count == 0) {
        printf("No student records available.\n");
        return;
    }
    printf("\n%-10s %-30s %-10s\n", "Roll No", "Name", "Marks");
    for (i = 0; i < count; i++) {
        printf("%-10d %-30s %-10.2f\n", students[i].rollNumber, students[i].name, students[i].marks);
    }
}

void saveToFile(const Student students[], int count) {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
    printf("Student records saved to file successfully.\n");
}

void loadFromFile(Student students[], int *count) {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No existing student records found. Starting fresh.\n");
        return;
    }
    fread(count, sizeof(int), 1, file);
    fread(students, sizeof(Student), *count, file);
    fclose(file);
    printf("Student records loaded from file successfully.\n");
}
