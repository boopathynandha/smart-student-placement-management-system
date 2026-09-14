#include <stdio.h>
#include <string.h>

#include "../include/application.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/validation.h"
#include "../include/utils.h"


/* Check whether Application ID already exists */

int isApplicationIDExists(const char *applicationID)
{
    Application applications[100];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        100
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


/* Check whether the same student has already applied
   for the same placement drive */

int isStudentAlreadyApplied(const char *studentID,
                            const char *driveID)
{
    Application applications[100];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        100
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


/* Add Application */

void addApplication(void)
{
    Application application;

    printf("\n========== Add Student Application ==========\n");


    /* Application ID */

    while (1)
    {
        printf("Enter Application ID: ");
        fgets(application.id, ID_LEN, stdin);
        trimNewline(application.id);

        if (!isValidID(application.id))
        {
            printf("Invalid Application ID. Please try again.\n");
            continue;
        }

        if (isApplicationIDExists(application.id))
        {
            printf("Application ID '%s' already exists. Please enter a different ID.\n",
                   application.id);
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
            printf("Invalid Student ID. Please try again.\n");
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
            printf("Invalid Drive ID. Please try again.\n");
            continue;
        }

        if (isStudentAlreadyApplied(
                application.studentID,
                application.driveID))
        {
            printf("This student has already applied for this drive.\n");
            return;
        }

        break;
    }


    /* Application Date */

    while (1)
    {
        printf("Enter Application Date: ");
        fgets(application.applicationDate,
              DATE_LEN,
              stdin);

        trimNewline(application.applicationDate);

        if (!isNonEmptyString(application.applicationDate))
        {
            printf("Application date cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Application Status */

    while (1)
    {
        printf("Enter Application Status: ");
        fgets(application.status,
              STATUS_LEN,
              stdin);

        trimNewline(application.status);

        if (!isNonEmptyString(application.status))
        {
            printf("Status cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Save application */

    if (appendRecord(
            APPLICATION_FILE,
            &application,
            sizeof(Application)))
    {
        printf("\nApplication added successfully!\n");
    }
    else
    {
        printf("\nFailed to add application.\n");
    }
}


/* View Applications */

void viewApplications(void)
{
    Application applications[100];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        100
    );

    printf("\n========== Student Applications ==========\n\n");

    if (count <= 0)
    {
        printf("No applications found.\n");
        return;
    }

    printf("%-12s %-15s %-12s %-15s %-15s\n",
           "Application",
           "Student ID",
           "Drive ID",
           "Date",
           "Status");

    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-12s %-15s %-12s %-15s %-15s\n",
               applications[i].id,
               applications[i].studentID,
               applications[i].driveID,
               applications[i].applicationDate,
               applications[i].status);
    }

    printf("\nTotal Applications: %d\n", count);
}


/* Search Application */

void searchApplication(void)
{
    Application applications[100];
    char applicationID[ID_LEN];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        100
    );

    printf("\n========== Search Application ==========\n");

    printf("Enter Application ID: ");
    fgets(applicationID, ID_LEN, stdin);
    trimNewline(applicationID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(applications[i].id, applicationID) == 0)
        {
            printf("\nApplication Found!\n");
            printf("----------------------------------------\n");
            printf("Application ID   : %s\n", applications[i].id);
            printf("Student ID       : %s\n", applications[i].studentID);
            printf("Drive ID         : %s\n", applications[i].driveID);
            printf("Application Date : %s\n",
                   applications[i].applicationDate);
            printf("Status           : %s\n",
                   applications[i].status);
            printf("----------------------------------------\n");

            return;
        }
    }

    printf("\nApplication ID '%s' not found.\n", applicationID);
}


/* Update Application */

void updateApplication(void)
{
    Application applications[100];
    char applicationID[ID_LEN];

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        100
    );

    printf("\n========== Update Application ==========\n");

    printf("Enter Application ID: ");
    fgets(applicationID, ID_LEN, stdin);
    trimNewline(applicationID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(applications[i].id, applicationID) == 0)
        {
            char input[SKILL_LEN];


            printf("\nApplication Found!\n");


            /* Student ID */

            printf("Student ID [%s]: ",
                   applications[i].studentID);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    strcpy(applications[i].studentID, input);
                }
                else
                {
                    printf("Invalid Student ID. Keeping old value.\n");
                }
            }


            /* Drive ID */

            printf("Drive ID [%s]: ",
                   applications[i].driveID);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    strcpy(applications[i].driveID, input);
                }
                else
                {
                    printf("Invalid Drive ID. Keeping old value.\n");
                }
            }


            /* Application Date */

            printf("Application Date [%s]: ",
                   applications[i].applicationDate);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(applications[i].applicationDate, input);
            }


            /* Status */

            printf("Status [%s]: ",
                   applications[i].status);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(applications[i].status, input);
            }


            /* Save updated application */

            if (overwriteRecordAt(
                    APPLICATION_FILE,
                    &applications[i],
                    sizeof(Application),
                    i))
            {
                printf("\nApplication updated successfully!\n");
            }
            else
            {
                printf("\nFailed to update application.\n");
            }

            return;
        }
    }

    printf("\nApplication ID '%s' not found.\n",
           applicationID);
}


/* Delete Application */

void deleteApplication(void)
{
    Application applications[100];
    char applicationID[ID_LEN];
    char confirmation;

    int count = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        100
    );

    printf("\n========== Delete Application ==========\n");

    printf("Enter Application ID: ");
    fgets(applicationID, ID_LEN, stdin);
    trimNewline(applicationID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(applications[i].id, applicationID) == 0)
        {
            printf("\nApplication Found!\n");
            printf("----------------------------------------\n");
            printf("Application ID   : %s\n", applications[i].id);
            printf("Student ID       : %s\n", applications[i].studentID);
            printf("Drive ID         : %s\n", applications[i].driveID);
            printf("Application Date : %s\n",
                   applications[i].applicationDate);
            printf("Status           : %s\n",
                   applications[i].status);
            printf("----------------------------------------\n");

            printf("Are you sure you want to delete this application? (Y/N): ");
            scanf(" %c", &confirmation);
            clearInputBuffer();

            if (confirmation != 'Y' &&
                confirmation != 'y')
            {
                printf("Delete operation cancelled.\n");
                return;
            }


            /* Shift records */

            for (int j = i; j < count - 1; j++)
            {
                applications[j] = applications[j + 1];
            }

            count--;


            if (rewriteAllRecords(
                    APPLICATION_FILE,
                    applications,
                    sizeof(Application),
                    count))
            {
                printf("\nApplication deleted successfully!\n");
            }
            else
            {
                printf("\nFailed to delete application.\n");
            }

            return;
        }
    }

    printf("\nApplication ID '%s' not found.\n",
           applicationID);
}