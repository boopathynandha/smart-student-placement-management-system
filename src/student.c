#include <stdio.h>
#include <string.h>

#include "../include/student.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/validation.h"
#include "../include/utils.h"


/* =========================================
   CHECK DUPLICATE STUDENT ID
   ========================================= */

int isStudentIDExists(const char *studentID) {

    Student students[100];

    int count = readAllRecords(
        STUDENT_FILE,
        students,
        sizeof(Student),
        100
    );

    for (int i = 0; i < count; i++) {

        if (strcmp(students[i].id, studentID) == 0) {
            return 1;
        }
    }

    return 0;
}


/* =========================================
   ADD STUDENT
   ========================================= */

void addStudent(void) {

    Student student;

    printf("\n========== Add Student ==========\n");

    /* Student ID */
    while (1) {

        printf("Enter Student ID: ");
        fgets(student.id, sizeof(student.id), stdin);
        trimNewline(student.id);

        if (!isValidID(student.id)) {
            printf("Invalid ID. Use letters, numbers, '-' or '_'.\n");
            continue;
        }

        /* Check duplicate ID */
        if (isStudentIDExists(student.id)) {
            printf("Student ID '%s' already exists. Please enter a different ID.\n",
                   student.id);
            continue;
        }

        break;
    }


    /* Student Name */
    while (1) {

        printf("Enter Student Name: ");
        fgets(student.name, sizeof(student.name), stdin);
        trimNewline(student.name);

        if (!isValidName(student.name)) {
            printf("Invalid name. Use alphabets and spaces only.\n");
            continue;
        }

        break;
    }


    /* Department */
    while (1) {

        printf("Enter Department: ");
        fgets(student.department, sizeof(student.department), stdin);
        trimNewline(student.department);

        if (!isNonEmptyString(student.department)) {
            printf("Department cannot be empty.\n");
            continue;
        }

        break;
    }


    /* CGPA */
    while (1) {

        printf("Enter CGPA: ");

        if (scanf("%f", &student.cgpa) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (!isValidCGPA(student.cgpa)) {
            printf("Invalid CGPA. Enter a value between 0 and 10.\n");
            continue;
        }

        break;
    }


    /* Backlogs */
    while (1) {

        printf("Enter Number of Backlogs: ");

        if (scanf("%d", &student.backlogs) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (!isValidBacklogs(student.backlogs)) {
            printf("Invalid backlogs. Enter a value between 0 and 50.\n");
            continue;
        }

        break;
    }


    /* Skills */
    while (1) {

        printf("Enter Skills: ");
        fgets(student.skills, sizeof(student.skills), stdin);
        trimNewline(student.skills);

        if (!isNonEmptyString(student.skills)) {
            printf("Skills cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Save student */
    if (appendRecord(STUDENT_FILE, &student, sizeof(Student))) {

        printf("\nStudent added successfully!\n");

    } else {

        printf("\nError: Could not save student.\n");
    }
}


/* =========================================
   VIEW STUDENTS
   ========================================= */

void viewStudents(void) {

    Student students[100];

    int count = readAllRecords(
        STUDENT_FILE,
        students,
        sizeof(Student),
        100
    );

    printf("\n========== Student List ==========\n");

    if (count <= 0) {

        printf("No students found.\n");
        return;
    }

    printf("\n%-12s %-20s %-15s %-8s %-10s %-30s\n",
           "ID",
           "Name",
           "Department",
           "CGPA",
           "Backlogs",
           "Skills");

    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {

        printf("%-12s %-20s %-15s %-8.2f %-10d %-30s\n",
               students[i].id,
               students[i].name,
               students[i].department,
               students[i].cgpa,
               students[i].backlogs,
               students[i].skills);
    }

    printf("\nTotal Students: %d\n", count);
}


/* =========================================
   SEARCH STUDENT
   ========================================= */

void searchStudent(void) {

    Student students[100];
    char searchID[ID_LEN];

    printf("\n========== Search Student ==========\n");

    printf("Enter Student ID: ");
    fgets(searchID, sizeof(searchID), stdin);
    trimNewline(searchID);

    int count = readAllRecords(
        STUDENT_FILE,
        students,
        sizeof(Student),
        100
    );

    if (count <= 0) {

        printf("\nNo students found.\n");
        return;
    }

    for (int i = 0; i < count; i++) {

        if (strcmp(students[i].id, searchID) == 0) {

            printf("\nStudent Found!\n");
            printf("-----------------------------\n");
            printf("Student ID : %s\n", students[i].id);
            printf("Name       : %s\n", students[i].name);
            printf("Department : %s\n", students[i].department);
            printf("CGPA       : %.2f\n", students[i].cgpa);
            printf("Backlogs   : %d\n", students[i].backlogs);
            printf("Skills     : %s\n", students[i].skills);
            printf("-----------------------------\n");

            return;
        }
    }

    printf("\nStudent with ID '%s' not found.\n", searchID);
}


/* =========================================
   UPDATE STUDENT
   ========================================= */

void updateStudent(void) {

    Student students[100];
    char searchID[ID_LEN];

    printf("\n========== Update Student ==========\n");

    printf("Enter Student ID: ");
    fgets(searchID, sizeof(searchID), stdin);
    trimNewline(searchID);

    int count = readAllRecords(
        STUDENT_FILE,
        students,
        sizeof(Student),
        100
    );

    if (count <= 0) {

        printf("\nNo students found.\n");
        return;
    }

    int foundIndex = -1;

    for (int i = 0; i < count; i++) {

        if (strcmp(students[i].id, searchID) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {

        printf("\nStudent with ID '%s' not found.\n", searchID);
        return;
    }

    printf("\nStudent found: %s\n", students[foundIndex].name);


    /* Update Name */
    while (1) {

        printf("Enter New Name: ");
        fgets(students[foundIndex].name,
              sizeof(students[foundIndex].name), stdin);

        trimNewline(students[foundIndex].name);

        if (!isValidName(students[foundIndex].name)) {
            printf("Invalid name. Use alphabets and spaces only.\n");
            continue;
        }

        break;
    }


    /* Update Department */
    while (1) {

        printf("Enter New Department: ");
        fgets(students[foundIndex].department,
              sizeof(students[foundIndex].department), stdin);

        trimNewline(students[foundIndex].department);

        if (!isNonEmptyString(students[foundIndex].department)) {
            printf("Department cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Update CGPA */
    while (1) {

        printf("Enter New CGPA: ");

        if (scanf("%f", &students[foundIndex].cgpa) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (!isValidCGPA(students[foundIndex].cgpa)) {
            printf("Invalid CGPA. Enter a value between 0 and 10.\n");
            continue;
        }

        break;
    }


    /* Update Backlogs */
    while (1) {

        printf("Enter New Number of Backlogs: ");

        if (scanf("%d", &students[foundIndex].backlogs) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (!isValidBacklogs(students[foundIndex].backlogs)) {
            printf("Invalid backlogs. Enter a value between 0 and 50.\n");
            continue;
        }

        break;
    }


    /* Update Skills */
    while (1) {

        printf("Enter New Skills: ");
        fgets(students[foundIndex].skills,
              sizeof(students[foundIndex].skills), stdin);

        trimNewline(students[foundIndex].skills);

        if (!isNonEmptyString(students[foundIndex].skills)) {
            printf("Skills cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Save updated record */
    if (overwriteRecordAt(
            STUDENT_FILE,
            &students[foundIndex],
            sizeof(Student),
            foundIndex)) {

        printf("\nStudent updated successfully!\n");

    } else {

        printf("\nError: Could not update student.\n");
    }
}


/* =========================================
   DELETE STUDENT
   ========================================= */

void deleteStudent(void) {

    Student students[100];
    char deleteID[ID_LEN];
    char confirmation;

    printf("\n========== Delete Student ==========\n");

    printf("Enter Student ID: ");
    fgets(deleteID, sizeof(deleteID), stdin);
    trimNewline(deleteID);

    int count = readAllRecords(
        STUDENT_FILE,
        students,
        sizeof(Student),
        100
    );

    if (count <= 0) {

        printf("\nNo students found.\n");
        return;
    }

    int foundIndex = -1;

    /* Find student */
    for (int i = 0; i < count; i++) {

        if (strcmp(students[i].id, deleteID) == 0) {
            foundIndex = i;
            break;
        }
    }

    /* Student not found */
    if (foundIndex == -1) {

        printf("\nStudent with ID '%s' not found.\n", deleteID);
        return;
    }

    /* Display student before deletion */
    printf("\nStudent Found:\n");
    printf("-----------------------------\n");
    printf("Student ID : %s\n", students[foundIndex].id);
    printf("Name       : %s\n", students[foundIndex].name);
    printf("Department : %s\n", students[foundIndex].department);
    printf("CGPA       : %.2f\n", students[foundIndex].cgpa);
    printf("Backlogs   : %d\n", students[foundIndex].backlogs);
    printf("Skills     : %s\n", students[foundIndex].skills);
    printf("-----------------------------\n");


    /* Confirmation */
    printf("\nAre you sure you want to delete this student? (Y/N): ");
    scanf(" %c", &confirmation);
    clearInputBuffer();

    if (confirmation != 'Y' && confirmation != 'y') {

        printf("\nDeletion cancelled.\n");
        return;
    }


    /* Shift records left */
    for (int i = foundIndex; i < count - 1; i++) {
        students[i] = students[i + 1];
    }


    /* Rewrite binary file */
    if (rewriteAllRecords(
            STUDENT_FILE,
            students,
            sizeof(Student),
            count - 1)) {

        printf("\nStudent deleted successfully!\n");

    } else {

        printf("\nError: Could not delete student.\n");
    }
}