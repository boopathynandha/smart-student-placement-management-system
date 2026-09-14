#include <stdio.h>

#include "../include/student.h"
#include "../include/company.h"
#include "../include/utils.h"


int main(void) {

    int choice;

    while (1) {

        printf("\n=========================================\n");
        printf(" Smart Student Placement Management System\n");
        printf("=========================================\n");


        printf("\n========== Student Management ==========\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");


        printf("\n========== Company Management ==========\n");
        printf("6. Add Company\n");
        printf("7. View Companies\n");
        printf("8. Search Company\n");
        printf("9. Update Company\n");
        printf("10. Delete Company\n");


        printf("\n0. Exit\n");

        printf("\nEnter your choice: ");


        if (scanf("%d", &choice) != 1) {

            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }


        clearInputBuffer();


        switch (choice) {

            /* Student Management */

            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;


            /* Company Management */

            case 6:
                addCompany();
                break;

            case 7:
                viewCompanies();
                break;

            case 8:
                searchCompany();
                break;

            case 9:
                updateCompany();
                break;

            case 10:
                deleteCompany();
                break;


            /* Exit */

            case 0:

                printf("\nExiting program...\n");
                return 0;


            default:

                printf(
                    "\nInvalid choice. Please try again.\n"
                );
        }
    }


    return 0;
}