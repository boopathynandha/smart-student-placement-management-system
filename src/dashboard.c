#include <stdio.h>
#include <string.h>

#include "../include/dashboard.h"
#include "../include/constants.h"
#include "../include/student.h"
#include "../include/application.h"
#include "../include/selection.h"
#include "../include/preparation.h"
#include "../include/filehandler.h"


#define MAX_RECORDS 100


/*
 * Find a student by Student ID.
 *
 * Returns:
 * 1 - Student found
 * 0 - Student not found
 */
static int findStudent(
    const char *studentID,
    Student *student
)
{
    FILE *file;
    Student temp;

    file = fopen(STUDENT_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&temp, sizeof(Student), 1, file) == 1)
    {
        if (strcmp(temp.id, studentID) == 0)
        {
            *student = temp;

            fclose(file);

            return 1;
        }
    }

    fclose(file);

    return 0;
}


/*
 * Display application summary.
 */
static void displayApplicationSummary(
    const char *studentID
)
{
    FILE *file;
    Application application;

    int total = 0;
    int applied = 0;
    int shortlisted = 0;
    int selected = 0;
    int rejected = 0;

    file = fopen(APPLICATION_FILE, "rb");

    if (file != NULL)
    {
        while (
            fread(
                &application,
                sizeof(Application),
                1,
                file
            ) == 1
        )
        {
            if (
                strcmp(
                    application.studentID,
                    studentID
                ) == 0
            )
            {
                total++;

                if (
                    strcmp(
                        application.status,
                        "Applied"
                    ) == 0
                )
                {
                    applied++;
                }
                else if (
                    strcmp(
                        application.status,
                        "Shortlisted"
                    ) == 0
                )
                {
                    shortlisted++;
                }
                else if (
                    strcmp(
                        application.status,
                        "Selected"
                    ) == 0
                )
                {
                    selected++;
                }
                else if (
                    strcmp(
                        application.status,
                        "Rejected"
                    ) == 0
                )
                {
                    rejected++;
                }
            }
        }

        fclose(file);
    }


    printf("\n");
    printf("--------------- APPLICATION SUMMARY ---------------\n");

    printf("\nTotal Applications : %d\n", total);
    printf("Applied            : %d\n", applied);
    printf("Shortlisted        : %d\n", shortlisted);
    printf("Selected           : %d\n", selected);
    printf("Rejected           : %d\n", rejected);
}


/*
 * Display selection round summary.
 */
static void displaySelectionSummary(
    const char *studentID
)
{
    FILE *file;
    Selection selection;

    int total = 0;
    int cleared = 0;
    int pending = 0;

    file = fopen(SELECTION_FILE, "rb");

    if (file != NULL)
    {
        while (
            fread(
                &selection,
                sizeof(Selection),
                1,
                file
            ) == 1
        )
        {
            if (
                strcmp(
                    selection.studentID,
                    studentID
                ) == 0
            )
            {
                total++;

                if (
                    strcmp(
                        selection.status,
                        "Cleared"
                    ) == 0 ||
                    strcmp(
                        selection.status,
                        "Selected"
                    ) == 0
                )
                {
                    cleared++;
                }
                else
                {
                    pending++;
                }
            }
        }

        fclose(file);
    }


    printf("\n");
    printf("--------------- SELECTION SUMMARY ----------------\n");

    printf("\nSelection Rounds : %d\n", total);
    printf("Cleared Rounds   : %d\n", cleared);
    printf("Pending Rounds   : %d\n", pending);
}


/*
 * Display preparation summary.
 */
static void displayPreparationSummary(
    const char *studentID
)
{
    FILE *file;
    Preparation preparation;

    int total = 0;
    int completed = 0;
    int inProgress = 0;

    int totalTarget = 0;
    int totalCompleted = 0;

    float progress = 0.0f;


    file = fopen(PREPARATION_FILE, "rb");

    if (file != NULL)
    {
        while (
            fread(
                &preparation,
                sizeof(Preparation),
                1,
                file
            ) == 1
        )
        {
            if (
                strcmp(
                    preparation.studentID,
                    studentID
                ) == 0
            )
            {
                total++;

                totalTarget += preparation.target;

                totalCompleted += preparation.completed;


                if (
                    strcmp(
                        preparation.status,
                        "Completed"
                    ) == 0
                )
                {
                    completed++;
                }
                else
                {
                    inProgress++;
                }
            }
        }

        fclose(file);
    }


    if (totalTarget > 0)
    {
        progress =
            ((float) totalCompleted /
             (float) totalTarget) * 100.0f;
    }


    printf("\n");
    printf("--------------- PREPARATION SUMMARY ---------------\n");

    printf("\nPreparation Records : %d\n", total);
    printf("Completed           : %d\n", completed);
    printf("In Progress         : %d\n", inProgress);

    printf(
        "Overall Progress    : %.2f%%\n",
        progress
    );
}


/*
 * Display overall placement status.
 */
static void displayPlacementStatus(
    const char *studentID
)
{
    FILE *file;
    Application application;

    int hasApplication = 0;
    int isSelected = 0;
    int isShortlisted = 0;


    file = fopen(APPLICATION_FILE, "rb");

    if (file != NULL)
    {
        while (
            fread(
                &application,
                sizeof(Application),
                1,
                file
            ) == 1
        )
        {
            if (
                strcmp(
                    application.studentID,
                    studentID
                ) == 0
            )
            {
                hasApplication = 1;


                if (
                    strcmp(
                        application.status,
                        "Selected"
                    ) == 0
                )
                {
                    isSelected = 1;
                }


                if (
                    strcmp(
                        application.status,
                        "Shortlisted"
                    ) == 0
                )
                {
                    isShortlisted = 1;
                }
            }
        }

        fclose(file);
    }


    printf("\n");
    printf("--------------- PLACEMENT STATUS -------------------\n");


    if (isSelected)
    {
        printf("\nCurrent Status : PLACED\n");
    }
    else if (isShortlisted)
    {
        printf("\nCurrent Status : SHORTLISTED\n");
    }
    else if (hasApplication)
    {
        printf("\nCurrent Status : APPLICATION IN PROGRESS\n");
    }
    else
    {
        printf("\nCurrent Status : NOT YET APPLIED\n");
    }
}


/*
 * Student Placement Dashboard
 */
void displayStudentDashboard(void)
{
    char studentID[ID_LEN];

    Student student;


    printf("\n");
    printf("====================================================\n");
    printf("          STUDENT PLACEMENT DASHBOARD\n");
    printf("====================================================\n");


    printf("\nEnter Student ID: ");

    fgets(
        studentID,
        sizeof(studentID),
        stdin
    );

    studentID[
        strcspn(studentID, "\n")
    ] = '\0';


    /*
     * Find student.
     */
    if (!findStudent(studentID, &student))
    {
        printf("\nStudent not found.\n");
        return;
    }


    /*
     * Display student details.
     */
    printf("\n");
    printf("---------------- STUDENT DETAILS ------------------\n");

    printf("\nStudent ID   : %s\n", student.id);
    printf("Name         : %s\n", student.name);
    printf("Department   : %s\n", student.department);
    printf("CGPA         : %.2f\n", student.cgpa);
    printf("Backlogs     : %d\n", student.backlogs);
    printf("Skills       : %s\n", student.skills);


    /*
     * Display application information.
     */
    displayApplicationSummary(studentID);


    /*
     * Display selection information.
     */
    displaySelectionSummary(studentID);


    /*
     * Display preparation information.
     */
    displayPreparationSummary(studentID);


    /*
     * Display placement status.
     */
    displayPlacementStatus(studentID);


    printf("\n");
    printf("====================================================\n");
}