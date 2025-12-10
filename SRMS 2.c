#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    int marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int ch;
    do {
        printf("\n========== STUDENT RECORD MANAGEMENT ==========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 6);

    return 0;
}

void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.txt", "a");

    if (!fp) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%d", &s.marks);

    fprintf(fp, "%d %s %d\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen("students.txt", "r");

    if (!fp) {
        printf("No data found.\n");
        return;
    }

    printf("\nROLL\tNAME\t\tMARKS\n");
    printf("---------------------------------\n");

    while (fscanf(fp, "%d %s %d", &s.roll, s.name, &s.marks) != EOF)
        printf("%d\t%-15s\t%d\n", s.roll, s.name, s.marks);

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int r, found = 0;
    FILE *fp = fopen("students.txt", "r");

    if (!fp) {
        printf("No data file found!\n");
        return;
    }

    printf("Enter Roll No to Search: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %d", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll == r) {
            printf("\nRecord Found!\n");
            printf("Roll: %d\nName: %s\nMarks: %d\n", s.roll, s.name, s.marks);
            found = 1;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void updateStudent() {
    struct Student s;
    int r, found = 0;
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    printf("Enter Roll No to Update: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %d", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll == r) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Marks: ");
            scanf("%d", &s.marks);
            found = 1;
        }
        fprintf(temp, "%d %s %d\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) printf("Record Updated Successfully!\n");
    else printf("Record Not Found!\n");
}

void deleteStudent() {
    struct Student s;
    int r, found = 0;
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    printf("Enter Roll No to Delete: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %d", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll != r)
            fprintf(temp, "%d %s %d\n", s.roll, s.name, s.marks);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) printf("Record Deleted!\n");
    else printf("Record Not Found!\n");
}
