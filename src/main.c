#include <stdio.h>

#include "../include/student.h"
#include "../include/company.h"
#include "../include/drive.h"
#include "../include/eligibility.h"


void displayMenu(void)
{
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

    printf("\n====== Placement Drive Management ======\n");
    printf("11. Add Placement Drive\n");
    printf("12. View Placement Drives\n");
    printf("13. Search Placement Drive\n");
    printf("14. Update Placement Drive\n");
    printf("15. Delete Placement Drive\n");

    printf("\n====== Eligibility Management ======\n");
    printf("16. Automatic Eligibility Checker\n");

    printf("\n0. Exit\n");
}


int main(void)
{
    int choice;

    do
    {
        displayMenu();

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");

            while (getchar() != '\n')
            {
                /* Clear invalid input */
            }

            continue;
        }

        while (getchar() != '\n')
        {
            /* Clear input buffer */
        }

        switch (choice)
        {
            /* ================= STUDENT ================= */

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


            /* ================= COMPANY ================= */

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


            /* ================= PLACEMENT DRIVE ================= */

            case 11:
                addDrive();
                break;

            case 12:
                viewDrives();
                break;

            case 13:
                searchDrive();
                break;

            case 14:
                updateDrive();
                break;

            case 15:
                deleteDrive();
                break;


            /* ================= ELIGIBILITY ================= */

            case 16:
                eligibilityChecker();
                break;


            /* ================= EXIT ================= */

            case 0:
                printf("\nThank you for using Smart Student Placement Management System!\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}