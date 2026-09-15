#include <stdio.h>
#include <string.h>

#include "../include/application.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/validation.h"
#include "../include/utils.h"
#include "../include/student.h"
#include "../include/drive.h"
#include "../include/eligibility.h"

#define MAX_RECORDS 100


/* =========================================================
   Find Student by ID
   ========================================================= */

static int findStudentByID(const char *studentID, Student *student)
{
    FILE *file;

    file = fopen(STUDENT_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(student, sizeof(Student), 1, file) == 1)
    {
        if (strcmp(student->id, studentID) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}


/* =========================================================
   Find Placement Drive by ID
   ========================================================= */

static int findDriveByID(const char *driveID,
                         PlacementDrive *drive)
{
    FILE *file;

    file = fopen(DRIVE_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(drive, sizeof(PlacementDrive), 1, file) == 1)
    {
        if (strcmp(drive->id, driveID) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}


/* =========================================================
   Check Application ID
   ========================================================= */

int isApplicationIDExists(const char *applicationID)
{
    Application applications[MAX_RECORDS];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        MAX_RECORDS
    );

    for (int i = 0; i < count; i++)
    {
        if (strcmp(applications[i].id, applicationID) == 0)
        {
            return 1;
        }
    }

    return 0;
}


/* =========================================================
   Check Duplicate Student + Drive Application
   ========================================================= */

int isStudentAlreadyApplied(const char *studentID,
                            const char *driveID)
{
    Application applications[MAX_RECORDS];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        MAX_RECORDS
    );

    for (int i = 0; i < count; i++)
    {
        if (strcmp(applications[i].studentID, studentID) == 0 &&
            strcmp(applications[i].driveID, driveID) == 0)
        {
            return 1;
        }
    }

    return 0;
}


/* =========================================================
   Add Application
   ========================================================= */

void addApplication(void)
{
    Application application;
    Student student;
    PlacementDrive drive;

    printf("\n");
    printf("====================================================\n");
    printf("             ADD STUDENT APPLICATION\n");
    printf("====================================================\n");


    /* Application ID */

    while (1)
    {
        printf("\nEnter Application ID: ");

        fgets(application.id, ID_LEN, stdin);
        trimNewline(application.id);

        if (!isValidID(application.id))
        {
            printf(
                "Invalid Application ID. "
                "Please try again.\n"
            );

            continue;
        }

        if (isApplicationIDExists(application.id))
        {
            printf(
                "Application ID '%s' already exists. "
                "Please enter a different ID.\n",
                application.id
            );

            continue;
        }

        break;
    }


    /* Student ID */

    while (1)
    {
        printf("Enter Student ID: ");

        fgets(application.studentID, ID_LEN, stdin);
        trimNewline(application.studentID);

        if (!isValidID(application.studentID))
        {
            printf(
                "Invalid Student ID. "
                "Please try again.\n"
            );

            continue;
        }

        if (!findStudentByID(
                application.studentID,
                &student))
        {
            printf(
                "Student ID '%s' not found. "
                "Please enter an existing Student ID.\n",
                application.studentID
            );

            continue;
        }

        break;
    }


    /* Drive ID */

    while (1)
    {
        printf("Enter Drive ID: ");

        fgets(application.driveID, ID_LEN, stdin);
        trimNewline(application.driveID);

        if (!isValidID(application.driveID))
        {
            printf(
                "Invalid Drive ID. "
                "Please try again.\n"
            );

            continue;
        }

        if (!findDriveByID(
                application.driveID,
                &drive))
        {
            printf(
                "Placement Drive '%s' not found. "
                "Please enter an existing Drive ID.\n",
                application.driveID
            );

            continue;
        }


        /* Duplicate Application Check */

        if (isStudentAlreadyApplied(
                application.studentID,
                application.driveID))
        {
            printf(
                "\nThis student has already applied "
                "for this placement drive.\n"
            );

            return;
        }


        /* Eligibility Check */

        if (!checkStudentEligibility(
                &student,
                &drive))
        {
            printf("\n");
            printf("-----------------------------------------------\n");

            printf(
                "Student is NOT eligible "
                "for this placement drive.\n"
            );

            printf(
                "Application cannot be created.\n"
            );

            printf("-----------------------------------------------\n");

            return;
        }

        printf(
            "\nStudent is eligible "
            "for this placement drive.\n"
        );

        break;
    }


    /* Application Date */

    while (1)
    {
        printf("Enter Application Date: ");

        fgets(
            application.applicationDate,
            DATE_LEN,
            stdin
        );

        trimNewline(application.applicationDate);

        if (!isNonEmptyString(
                application.applicationDate))
        {
            printf(
                "Application date "
                "cannot be empty.\n"
            );

            continue;
        }

        break;
    }


    /* Application Status */

    while (1)
    {
        printf("Enter Application Status: ");

        fgets(
            application.status,
            STATUS_LEN,
            stdin
        );

        trimNewline(application.status);

        if (!isNonEmptyString(application.status))
        {
            printf(
                "Status cannot be empty.\n"
            );

            continue;
        }

        break;
    }


    /* Save Application */

    if (appendRecord(
            APPLICATION_FILE,
            &application,
            sizeof(Application)))
    {
        printf("\n");
        printf("===============================================\n");
        printf("     Application added successfully!\n");
        printf("===============================================\n");
    }
    else
    {
        printf(
            "\nFailed to add application.\n"
        );
    }
}


/* =========================================================
   View Applications
   ========================================================= */

void viewApplications(void)
{
    Application applications[MAX_RECORDS];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        MAX_RECORDS
    );

    printf(
        "\n========== Student Applications ==========\n\n"
    );

    if (count <= 0)
    {
        printf(
            "No applications found.\n"
        );

        return;
    }

    printf(
        "%-12s %-15s %-12s %-15s %-15s\n",
        "Application",
        "Student ID",
        "Drive ID",
        "Date",
        "Status"
    );

    printf(
        "-----------------------------------------------------------------------\n"
    );

    for (int i = 0; i < count; i++)
    {
        printf(
            "%-12s %-15s %-12s %-15s %-15s\n",
            applications[i].id,
            applications[i].studentID,
            applications[i].driveID,
            applications[i].applicationDate,
            applications[i].status
        );
    }

    printf(
        "\nTotal Applications: %d\n",
        count
    );
}


/* =========================================================
   Display Single Application Details
   ========================================================= */

static void displayApplication(
    const Application *application)
{
    printf(
        "\n----------------------------------------\n"
    );

    printf(
        "Application ID   : %s\n",
        application->id
    );

    printf(
        "Student ID       : %s\n",
        application->studentID
    );

    printf(
        "Drive ID         : %s\n",
        application->driveID
    );

    printf(
        "Application Date : %s\n",
        application->applicationDate
    );

    printf(
        "Status           : %s\n",
        application->status
    );

    printf(
        "----------------------------------------\n"
    );
}


/* =========================================================
   Search by Application ID
   ========================================================= */

static void searchByApplicationID(
    Application applications[],
    int count)
{
    char applicationID[ID_LEN];

    printf(
        "\nEnter Application ID: "
    );

    fgets(
        applicationID,
        ID_LEN,
        stdin
    );

    trimNewline(applicationID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(
                applications[i].id,
                applicationID) == 0)
        {
            printf(
                "\nApplication Found!\n"
            );

            displayApplication(
                &applications[i]
            );

            return;
        }
    }

    printf(
        "\nApplication ID '%s' not found.\n",
        applicationID
    );
}


/* =========================================================
   Search by Student ID
   ========================================================= */

static void searchByStudentID(
    Application applications[],
    int count)
{
    char studentID[ID_LEN];
    int found = 0;

    printf(
        "\nEnter Student ID: "
    );

    fgets(
        studentID,
        ID_LEN,
        stdin
    );

    trimNewline(studentID);

    printf(
        "\n========== Applications for Student %s ==========\n",
        studentID
    );

    for (int i = 0; i < count; i++)
    {
        if (strcmp(
                applications[i].studentID,
                studentID) == 0)
        {
            displayApplication(
                &applications[i]
            );

            found = 1;
        }
    }

    if (!found)
    {
        printf(
            "\nNo applications found for Student ID '%s'.\n",
            studentID
        );
    }
}


/* =========================================================
   Search by Drive ID
   ========================================================= */

static void searchByDriveID(
    Application applications[],
    int count)
{
    char driveID[ID_LEN];
    int found = 0;

    printf(
        "\nEnter Drive ID: "
    );

    fgets(
        driveID,
        ID_LEN,
        stdin
    );

    trimNewline(driveID);

    printf(
        "\n========== Applications for Drive %s ==========\n",
        driveID
    );

    for (int i = 0; i < count; i++)
    {
        if (strcmp(
                applications[i].driveID,
                driveID) == 0)
        {
            displayApplication(
                &applications[i]
            );

            found = 1;
        }
    }

    if (!found)
    {
        printf(
            "\nNo applications found for Drive ID '%s'.\n",
            driveID
        );
    }
}


/* =========================================================
   Search Application
   ========================================================= */

void searchApplication(void)
{
    Application applications[MAX_RECORDS];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        MAX_RECORDS
    );

    int choice;

    if (count <= 0)
    {
        printf(
            "\n========== Search Application ==========\n"
        );

        printf(
            "\nNo applications found.\n"
        );

        return;
    }


    while (1)
    {
        printf("\n");
        printf("====================================================\n");
        printf("             SEARCH APPLICATION\n");
        printf("====================================================\n");

        printf(
            "\n1. Search by Application ID\n"
        );

        printf(
            "2. Search by Student ID\n"
        );

        printf(
            "3. Search by Drive ID\n"
        );

        printf(
            "4. Back\n"
        );

        printf(
            "\nEnter your choice: "
        );

        if (scanf("%d", &choice) != 1)
        {
            printf(
                "\nInvalid choice. "
                "Please enter a number.\n"
            );

            clearInputBuffer();

            continue;
        }

        clearInputBuffer();


        switch (choice)
        {
            case 1:
                searchByApplicationID(
                    applications,
                    count
                );
                break;

            case 2:
                searchByStudentID(
                    applications,
                    count
                );
                break;

            case 3:
                searchByDriveID(
                    applications,
                    count
                );
                break;

            case 4:
                return;

            default:
                printf(
                    "\nInvalid choice. "
                    "Please try again.\n"
                );
        }
    }
}


/* =========================================================
   Update Application
   ========================================================= */

void updateApplication(void)
{
    Application applications[MAX_RECORDS];

    char applicationID[ID_LEN];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        MAX_RECORDS
    );

    printf(
        "\n========== Update Application ==========\n"
    );

    printf(
        "Enter Application ID: "
    );

    fgets(
        applicationID,
        ID_LEN,
        stdin
    );

    trimNewline(applicationID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(
                applications[i].id,
                applicationID) == 0)
        {
            char input[SKILL_LEN];

            char oldStudentID[ID_LEN];
            char oldDriveID[ID_LEN];


            printf(
                "\nApplication Found!\n"
            );


            /* Store old values */

            strcpy(
                oldStudentID,
                applications[i].studentID
            );

            strcpy(
                oldDriveID,
                applications[i].driveID
            );


            /* Student ID */

            printf(
                "Student ID [%s]: ",
                applications[i].studentID
            );

            fgets(
                input,
                sizeof(input),
                stdin
            );

            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    Student student;

                    if (findStudentByID(
                            input,
                            &student))
                    {
                        strcpy(
                            applications[i].studentID,
                            input
                        );
                    }
                    else
                    {
                        printf(
                            "Student ID '%s' not found. "
                            "Keeping old value.\n",
                            input
                        );
                    }
                }
                else
                {
                    printf(
                        "Invalid Student ID. "
                        "Keeping old value.\n"
                    );
                }
            }


            /* Drive ID */

            printf(
                "Drive ID [%s]: ",
                applications[i].driveID
            );

            fgets(
                input,
                sizeof(input),
                stdin
            );

            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    PlacementDrive drive;

                    if (findDriveByID(
                            input,
                            &drive))
                    {
                        strcpy(
                            applications[i].driveID,
                            input
                        );
                    }
                    else
                    {
                        printf(
                            "Placement Drive '%s' not found. "
                            "Keeping old value.\n",
                            input
                        );
                    }
                }
                else
                {
                    printf(
                        "Invalid Drive ID. "
                        "Keeping old value.\n"
                    );
                }
            }


            /* Validate changed Student + Drive */

            if (strcmp(
                    applications[i].studentID,
                    oldStudentID) != 0 ||
                strcmp(
                    applications[i].driveID,
                    oldDriveID) != 0)
            {
                Student student;
                PlacementDrive drive;

                int duplicate = 0;


                /* Duplicate check */

                for (int j = 0; j < count; j++)
                {
                    if (j != i &&
                        strcmp(
                            applications[j].studentID,
                            applications[i].studentID) == 0 &&
                        strcmp(
                            applications[j].driveID,
                            applications[i].driveID) == 0)
                    {
                        duplicate = 1;
                        break;
                    }
                }


                if (duplicate)
                {
                    printf(
                        "This student has already "
                        "applied for this drive.\n"
                    );

                    strcpy(
                        applications[i].studentID,
                        oldStudentID
                    );

                    strcpy(
                        applications[i].driveID,
                        oldDriveID
                    );
                }
                else if (
                    findStudentByID(
                        applications[i].studentID,
                        &student) &&
                    findDriveByID(
                        applications[i].driveID,
                        &drive))
                {
                    if (!checkStudentEligibility(
                            &student,
                            &drive))
                    {
                        printf(
                            "Student is NOT eligible "
                            "for the selected drive.\n"
                        );

                        printf(
                            "Keeping previous Student ID "
                            "and Drive ID.\n"
                        );

                        strcpy(
                            applications[i].studentID,
                            oldStudentID
                        );

                        strcpy(
                            applications[i].driveID,
                            oldDriveID
                        );
                    }
                    else
                    {
                        printf(
                            "Student is eligible "
                            "for the selected drive.\n"
                        );
                    }
                }
            }


            /* Application Date */

            printf(
                "Application Date [%s]: ",
                applications[i].applicationDate
            );

            fgets(
                input,
                sizeof(input),
                stdin
            );

            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(
                    applications[i].applicationDate,
                    input
                );
            }


            /* Status */

            printf(
                "Status [%s]: ",
                applications[i].status
            );

            fgets(
                input,
                sizeof(input),
                stdin
            );

            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(
                    applications[i].status,
                    input
                );
            }


            /* Save updated application */

            if (overwriteRecordAt(
                    APPLICATION_FILE,
                    &applications[i],
                    sizeof(Application),
                    i))
            {
                printf(
                    "\nApplication updated successfully!\n"
                );
            }
            else
            {
                printf(
                    "\nFailed to update application.\n"
                );
            }

            return;
        }
    }

    printf(
        "\nApplication ID '%s' not found.\n",
        applicationID
    );
}


/* =========================================================
   Delete Application
   ========================================================= */

void deleteApplication(void)
{
    Application applications[MAX_RECORDS];

    char applicationID[ID_LEN];
    char confirmation;

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        MAX_RECORDS
    );

    printf(
        "\n========== Delete Application ==========\n"
    );

    printf(
        "Enter Application ID: "
    );

    fgets(
        applicationID,
        ID_LEN,
        stdin
    );

    trimNewline(applicationID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(
                applications[i].id,
                applicationID) == 0)
        {
            printf(
                "\nApplication Found!\n"
            );

            printf(
                "----------------------------------------\n"
            );

            printf(
                "Application ID   : %s\n",
                applications[i].id
            );

            printf(
                "Student ID       : %s\n",
                applications[i].studentID
            );

            printf(
                "Drive ID         : %s\n",
                applications[i].driveID
            );

            printf(
                "Application Date : %s\n",
                applications[i].applicationDate
            );

            printf(
                "Status           : %s\n",
                applications[i].status
            );

            printf(
                "----------------------------------------\n"
            );

            printf(
                "Are you sure you want to delete "
                "this application? (Y/N): "
            );

            scanf(
                " %c",
                &confirmation
            );

            clearInputBuffer();

            if (confirmation != 'Y' &&
                confirmation != 'y')
            {
                printf(
                    "Delete operation cancelled.\n"
                );

                return;
            }


            /* Shift records */

            for (int j = i; j < count - 1; j++)
            {
                applications[j] =
                    applications[j + 1];
            }

            count--;


            /* Rewrite file */

            if (rewriteAllRecords(
                    APPLICATION_FILE,
                    applications,
                    sizeof(Application),
                    count))
            {
                printf(
                    "\nApplication deleted successfully!\n"
                );
            }
            else
            {
                printf(
                    "\nFailed to delete application.\n"
                );
            }

            return;
        }
    }

    printf(
        "\nApplication ID '%s' not found.\n",
        applicationID
    );
}