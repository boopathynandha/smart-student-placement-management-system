#include <stdio.h>

#include "../include/student.h"
#include "../include/company.h"
#include "../include/drive.h"
#include "../include/eligibility.h"
#include "../include/application.h"
#include "../include/selection.h"
#include "../include/skillgap.h"
#include "../include/matching.h"


/*
 * Display Main Menu
 */

void displayMenu(void)
{
    printf("\n=========================================\n");
    printf(" Smart Student Placement Management System\n");
    printf("=========================================\n");


    /* Student Management */

    printf("\n========== Student Management ==========\n");

    printf("1. Add Student\n");
    printf("2. View Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");


    /* Company Management */

    printf("\n========== Company Management ==========\n");

    printf("6. Add Company\n");
    printf("7. View Companies\n");
    printf("8. Search Company\n");
    printf("9. Update Company\n");
    printf("10. Delete Company\n");


    /* Placement Drive Management */

    printf("\n====== Placement Drive Management ======\n");

    printf("11. Add Placement Drive\n");
    printf("12. View Placement Drives\n");
    printf("13. Search Placement Drive\n");
    printf("14. Update Placement Drive\n");
    printf("15. Delete Placement Drive\n");


    /* Eligibility Management */

    printf("\n====== Eligibility Management ======\n");

    printf("16. Automatic Eligibility Checker\n");


    /* Application Management */

    printf("\n====== Application Management ======\n");

    printf("17. Add Student Application\n");
    printf("18. View Applications\n");
    printf("19. Search Application\n");
    printf("20. Update Application\n");
    printf("21. Delete Application\n");


    /* Selection Round Management */

    printf("\n====== Selection Round Management ======\n");

    printf("22. Add Selection Round\n");
    printf("23. View Selection Rounds\n");
    printf("24. Search Selection Round\n");
    printf("25. Update Selection Round\n");
    printf("26. Delete Selection Round\n");


    /* Skill Gap Management */

    printf("\n====== Skill Gap Management ======\n");

    printf("27. Skill Gap Analyzer\n");


    /* Company Matching */

    printf("\n====== Company Matching ======\n");

    printf("28. Company Matching / Recommendation\n");


    /* Exit */

    printf("\n0. Exit\n");
}


/*
 * Main Function
 */

int main(void)
{
    int choice;


    do
    {
        /* Display Main Menu */

        displayMenu();


        /* Get User Choice */

        printf("\nEnter your choice: ");


        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");


            /* Clear invalid input */

            while (getchar() != '\n')
            {
                /* Clear input buffer */
            }


            continue;
        }


        /* Clear input buffer */

        while (getchar() != '\n')
        {
            /* Clear input buffer */
        }


        /*
         * Execute Selected Operation
         */

        switch (choice)
        {

            /* ============================= */
            /* Student Management             */
            /* ============================= */

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


            /* ============================= */
            /* Company Management             */
            /* ============================= */

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


            /* ============================= */
            /* Placement Drive Management     */
            /* ============================= */

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


            /* ============================= */
            /* Eligibility Management         */
            /* ============================= */

            case 16:
                eligibilityChecker();
                break;


            /* ============================= */
            /* Application Management         */
            /* ============================= */

            case 17:
                addApplication();
                break;

            case 18:
                viewApplications();
                break;

            case 19:
                searchApplication();
                break;

            case 20:
                updateApplication();
                break;

            case 21:
                deleteApplication();
                break;


            /* ============================= */
            /* Selection Round Management     */
            /* ============================= */

            case 22:
                addSelectionRound();
                break;

            case 23:
                viewSelectionRounds();
                break;

            case 24:
                searchSelectionRound();
                break;

            case 25:
                updateSelectionRound();
                break;

            case 26:
                deleteSelectionRound();
                break;


            /* ============================= */
            /* Skill Gap Management           */
            /* ============================= */

            case 27:
                analyzeSkillGap();
                break;


            /* ============================= */
            /* Company Matching               */
            /* ============================= */

            case 28:
                recommendCompany();
                break;


            /* ============================= */
            /* Exit                           */
            /* ============================= */

            case 0:

                printf(
                    "\nThank you for using Smart Student Placement Management System!\n"
                );

                break;


            /* ============================= */
            /* Invalid Choice                 */
            /* ============================= */

            default:

                printf(
                    "\nInvalid choice. Please try again.\n"
                );

                break;
        }


    } while (choice != 0);


    return 0;
}