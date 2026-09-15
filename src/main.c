#include <stdio.h>

#include "../include/student.h"
#include "../include/company.h"
#include "../include/drive.h"
#include "../include/eligibility.h"
#include "../include/application.h"
#include "../include/selection.h"
#include "../include/skillgap.h"
#include "../include/matching.h"
#include "../include/preparation.h"
#include "../include/statistics.h"
#include "../include/report.h"
#include "../include/backup.h"
#include "../include/admin.h"
#include "../include/dashboard.h"
#include "../include/advanced_search.h"


/*
 * Display the main menu.
 */
void displayMenu(void)
{
    printf("\n");
    printf("=================================================\n");
    printf("     SMART STUDENT PLACEMENT MANAGEMENT SYSTEM\n");
    printf("=================================================\n");


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


    printf("\n====== Application Management ======\n");
    printf("17. Add Student Application\n");
    printf("18. View Applications\n");
    printf("19. Search Application\n");
    printf("20. Update Application\n");
    printf("21. Delete Application\n");


    printf("\n====== Selection Round Management ======\n");
    printf("22. Add Selection Round\n");
    printf("23. View Selection Rounds\n");
    printf("24. Search Selection Round\n");
    printf("25. Update Selection Round\n");
    printf("26. Delete Selection Round\n");


    printf("\n====== Skill Gap Management ======\n");
    printf("27. Skill Gap Analyzer\n");


    printf("\n====== Company Matching ======\n");
    printf("28. Company Matching / Recommendation\n");


    printf("\n====== Placement Preparation ======\n");
    printf("29. Add Preparation Record\n");
    printf("30. View Preparation Records\n");
    printf("31. Search Preparation Record\n");
    printf("32. Update Preparation Record\n");
    printf("33. Delete Preparation Record\n");


    printf("\n====== Placement Statistics ======\n");
    printf("34. View Placement Statistics\n");


    printf("\n====== Reports ======\n");
    printf("35. Generate Placement Report\n");


    printf("\n====== Backup & Restore ======\n");
    printf("36. Backup Data\n");
    printf("37. Restore Data\n");


    printf("\n====== Student Dashboard ======\n");
    printf("38. Student Placement Dashboard\n");


    /*
     * Phase 16:
     * Advanced Student Search & Filtering.
     */
    printf("\n====== Advanced Student Search ======\n");
    printf("39. Search Students by Department\n");
    printf("40. Filter Students by Minimum CGPA\n");
    printf("41. Search Students by Skill\n");
    printf("42. Find Eligible Students for a Drive\n");


    printf("\n0. Exit\n");
}


/*
 * Main function.
 */
int main(void)
{
    int choice;


    /*
     * Phase 14:
     * Create the first admin account if
     * it does not already exist.
     */
    setupAdmin();


    /*
     * Phase 14:
     * Admin login is required before
     * accessing the system.
     */
    if (!adminLogin())
    {
        return 0;
    }


    /*
     * Main menu loop.
     */
    do
    {
        displayMenu();


        printf("\nEnter your choice: ");


        /*
         * Validate menu input.
         */
        if (scanf("%d", &choice) != 1)
        {
            printf(
                "\nInvalid input. "
                "Please enter a number.\n"
            );


            /*
             * Clear invalid input.
             */
            while (getchar() != '\n')
            {
            }


            continue;
        }


        /*
         * Clear remaining input.
         */
        while (getchar() != '\n')
        {
        }


        /*
         * Process menu choice.
         */
        switch (choice)
        {
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


            case 16:
                eligibilityChecker();
                break;


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


            case 27:
                analyzeSkillGap();
                break;


            case 28:
                recommendCompany();
                break;


            case 29:
                addPreparation();
                break;


            case 30:
                viewPreparations();
                break;


            case 31:
                searchPreparation();
                break;


            case 32:
                updatePreparation();
                break;


            case 33:
                deletePreparation();
                break;


            case 34:
                displayPlacementStatistics();
                break;


            case 35:
                generatePlacementReport();
                break;


            case 36:
                backupData();
                break;


            case 37:
                restoreData();
                break;


            /*
             * Phase 15:
             * Student Placement Dashboard.
             */
            case 38:
                displayStudentDashboard();
                break;


            /*
             * Phase 16:
             * Advanced Student Search & Filtering.
             */
            case 39:
                searchStudentsByDepartment();
                break;


            case 40:
                filterStudentsByCGPA();
                break;


            case 41:
                searchStudentsBySkill();
                break;


            case 42:
                findEligibleStudentsForDrive();
                break;


            case 0:
                printf(
                    "\nThank you for using "
                    "Smart Student Placement Management System!\n"
                );
                break;


            default:
                printf(
                    "\nInvalid choice. "
                    "Please try again.\n"
                );
                break;
        }


    } while (choice != 0);


    return 0;
}