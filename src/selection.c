#include <stdio.h>
#include <string.h>

#include "../include/selection.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/validation.h"
#include "../include/utils.h"
#include "../include/student.h"
#include "../include/drive.h"
#include "../include/application.h"


/* =========================================================
   Helper Functions
   ========================================================= */

/* Check whether Application ID exists */
static int applicationExists(const char *applicationID)
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


/* Check whether Student ID exists */
static int studentExists(const char *studentID)
{
    Student students[100];

    int count = readAllRecords(
        STUDENT_FILE,
        students,
        sizeof(Student),
        100
    );

    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            return 1;
        }
    }

    return 0;
}


/* Check whether Drive ID exists */
static int driveExists(const char *driveID)
{
    PlacementDrive drives[100];

    int count = readAllRecords(
        DRIVE_FILE,
        drives,
        sizeof(PlacementDrive),
        100
    );

    for (int i = 0; i < count; i++)
    {
        if (strcmp(drives[i].id, driveID) == 0)
        {
            return 1;
        }
    }

    return 0;
}


/*
   Check whether an application belongs to
   the given Student + Drive combination
*/
static int applicationMatchesStudentDrive(
    const char *applicationID,
    const char *studentID,
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
        if (strcmp(applications[i].id, applicationID) == 0)
        {
            if (strcmp(applications[i].studentID, studentID) == 0 &&
                strcmp(applications[i].driveID, driveID) == 0)
            {
                return 1;
            }

            return 0;
        }
    }

    return 0;
}


/*
   Check whether same Application + Round Number
   already exists.
*/
static int isDuplicateRound(
    const char *applicationID,
    int roundNumber,
    const char *ignoreSelectionID)
{
    Selection selections[100];

    int count = readAllRecords(
        SELECTION_FILE,
        selections,
        sizeof(Selection),
        100
    );

    for (int i = 0; i < count; i++)
    {
        if (ignoreSelectionID != NULL &&
            strcmp(selections[i].id, ignoreSelectionID) == 0)
        {
            continue;
        }

        if (strcmp(selections[i].applicationID, applicationID) == 0 &&
            selections[i].roundNumber == roundNumber)
        {
            return 1;
        }
    }

    return 0;
}


/* Display complete selection round details */
static void displaySelection(const Selection *selection)
{
    printf("\n----------------------------------------\n");
    printf("Selection ID   : %s\n", selection->id);
    printf("Application ID : %s\n", selection->applicationID);
    printf("Student ID     : %s\n", selection->studentID);
    printf("Drive ID       : %s\n", selection->driveID);
    printf("Round Number   : %d\n", selection->roundNumber);
    printf("Round Name     : %s\n", selection->roundName);
    printf("Status         : %s\n", selection->status);
    printf("Remarks        : %s\n", selection->remarks);
    printf("----------------------------------------\n");
}


/* =========================================================
   Selection ID Check
   ========================================================= */

int isSelectionIDExists(const char *selectionID)
{
    Selection selections[100];

    int count = readAllRecords(
        SELECTION_FILE,
        selections,
        sizeof(Selection),
        100
    );

    for (int i = 0; i < count; i++)
    {
        if (strcmp(selections[i].id, selectionID) == 0)
        {
            return 1;
        }
    }

    return 0;
}


/* =========================================================
   Add Selection Round
   ========================================================= */

void addSelectionRound(void)
{
    Selection selection;

    printf("\n========== Add Selection Round ==========\n");


    /* Selection ID */

    while (1)
    {
        printf("Enter Selection ID: ");

        fgets(selection.id, ID_LEN, stdin);
        trimNewline(selection.id);

        if (!isValidID(selection.id))
        {
            printf("Invalid Selection ID. Please try again.\n");
            continue;
        }

        if (isSelectionIDExists(selection.id))
        {
            printf("Selection ID '%s' already exists. Please enter a different ID.\n",
                   selection.id);
            continue;
        }

        break;
    }


    /* Application ID */

    while (1)
    {
        printf("Enter Application ID: ");

        fgets(selection.applicationID, ID_LEN, stdin);
        trimNewline(selection.applicationID);

        if (!isValidID(selection.applicationID))
        {
            printf("Invalid Application ID. Please try again.\n");
            continue;
        }

        if (!applicationExists(selection.applicationID))
        {
            printf("Application ID '%s' does not exist. Please try again.\n",
                   selection.applicationID);
            continue;
        }

        break;
    }


    /* Student ID */

    while (1)
    {
        printf("Enter Student ID: ");

        fgets(selection.studentID, ID_LEN, stdin);
        trimNewline(selection.studentID);

        if (!isValidID(selection.studentID))
        {
            printf("Invalid Student ID. Please try again.\n");
            continue;
        }

        if (!studentExists(selection.studentID))
        {
            printf("Student ID '%s' does not exist. Please try again.\n",
                   selection.studentID);
            continue;
        }

        break;
    }


    /* Drive ID */

    while (1)
    {
        printf("Enter Drive ID: ");

        fgets(selection.driveID, ID_LEN, stdin);
        trimNewline(selection.driveID);

        if (!isValidID(selection.driveID))
        {
            printf("Invalid Drive ID. Please try again.\n");
            continue;
        }

        if (!driveExists(selection.driveID))
        {
            printf("Drive ID '%s' does not exist. Please try again.\n",
                   selection.driveID);
            continue;
        }

        break;
    }


    /*
       Validate Application + Student + Drive relationship
    */

    if (!applicationMatchesStudentDrive(
            selection.applicationID,
            selection.studentID,
            selection.driveID))
    {
        printf("\nERROR: Application does not belong to the given Student and Drive.\n");
        printf("Please check Application ID, Student ID and Drive ID.\n");
        return;
    }


    /* Round Number */

    while (1)
    {
        printf("Enter Round Number: ");

        if (scanf("%d", &selection.roundNumber) != 1)
        {
            printf("Invalid Round Number. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (selection.roundNumber <= 0)
        {
            printf("Round Number must be greater than 0.\n");
            continue;
        }

        if (isDuplicateRound(
                selection.applicationID,
                selection.roundNumber,
                NULL))
        {
            printf("This Application already has Round %d.\n",
                   selection.roundNumber);
            continue;
        }

        break;
    }


    /* Round Name */

    while (1)
    {
        printf("Enter Round Name: ");

        fgets(selection.roundName, NAME_LEN, stdin);
        trimNewline(selection.roundName);

        if (!isNonEmptyString(selection.roundName))
        {
            printf("Round Name cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Status */

    while (1)
    {
        printf("Enter Round Status: ");

        fgets(selection.status, STATUS_LEN, stdin);
        trimNewline(selection.status);

        if (!isNonEmptyString(selection.status))
        {
            printf("Round Status cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Remarks */

    printf("Enter Remarks: ");

    fgets(selection.remarks, SKILL_LEN, stdin);
    trimNewline(selection.remarks);


    /* Save */

    if (appendRecord(
            SELECTION_FILE,
            &selection,
            sizeof(Selection)))
    {
        printf("\nSelection round added successfully!\n");
    }
    else
    {
        printf("\nFailed to add selection round.\n");
    }
}


/* =========================================================
   View Selection Rounds
   ========================================================= */

void viewSelectionRounds(void)
{
    Selection selections[100];

    int count = readAllRecords(
        SELECTION_FILE,
        selections,
        sizeof(Selection),
        100
    );

    printf("\n========== Selection Rounds ==========\n\n");

    if (count <= 0)
    {
        printf("No selection rounds found.\n");
        return;
    }

    printf("%-10s %-12s %-12s %-10s %-8s %-20s %-15s\n",
           "Select ID",
           "Application",
           "Student ID",
           "Drive ID",
           "Round",
           "Round Name",
           "Status");

    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-10s %-12s %-12s %-10s %-8d %-20s %-15s\n",
               selections[i].id,
               selections[i].applicationID,
               selections[i].studentID,
               selections[i].driveID,
               selections[i].roundNumber,
               selections[i].roundName,
               selections[i].status);
    }

    printf("\nTotal Selection Rounds: %d\n", count);
}


/* =========================================================
   Search Selection Round
   ========================================================= */

void searchSelectionRound(void)
{
    Selection selections[100];

    int count = readAllRecords(
        SELECTION_FILE,
        selections,
        sizeof(Selection),
        100
    );

    if (count <= 0)
    {
        printf("\nNo selection rounds found.\n");
        return;
    }

    int choice;

    printf("\n========== Search Selection Round ==========\n");
    printf("1. Search by Selection ID\n");
    printf("2. Search by Student ID\n");
    printf("3. Search by Drive ID\n");
    printf("4. Search by Application ID\n");
    printf("0. Back\n");

    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid choice.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (choice == 0)
    {
        return;
    }

    char searchValue[ID_LEN];

    printf("Enter search value: ");

    fgets(searchValue, ID_LEN, stdin);
    trimNewline(searchValue);

    if (!isValidID(searchValue))
    {
        printf("Invalid ID.\n");
        return;
    }

    int found = 0;

    for (int i = 0; i < count; i++)
    {
        int match = 0;

        if (choice == 1 &&
            strcmp(selections[i].id, searchValue) == 0)
        {
            match = 1;
        }
        else if (choice == 2 &&
                 strcmp(selections[i].studentID, searchValue) == 0)
        {
            match = 1;
        }
        else if (choice == 3 &&
                 strcmp(selections[i].driveID, searchValue) == 0)
        {
            match = 1;
        }
        else if (choice == 4 &&
                 strcmp(selections[i].applicationID, searchValue) == 0)
        {
            match = 1;
        }

        if (match)
        {
            displaySelection(&selections[i]);
            found = 1;

            if (choice == 1)
            {
                break;
            }
        }
    }

    if (!found)
    {
        printf("\nNo selection round found for '%s'.\n",
               searchValue);
    }
}


/* =========================================================
   Update Selection Round
   ========================================================= */

void updateSelectionRound(void)
{
    Selection selections[100];

    char selectionID[ID_LEN];
    char input[SKILL_LEN];

    int count = readAllRecords(
        SELECTION_FILE,
        selections,
        sizeof(Selection),
        100
    );

    printf("\n========== Update Selection Round ==========\n");

    printf("Enter Selection ID: ");

    fgets(selectionID, ID_LEN, stdin);
    trimNewline(selectionID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(selections[i].id, selectionID) == 0)
        {
            printf("\nSelection Round Found!\n");
            displaySelection(&selections[i]);


            /*
               Store old relationship values.
               We validate the final combination before saving.
            */

            Selection updated = selections[i];


            /* Application ID */

            printf("Application ID [%s]: ",
                   updated.applicationID);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    strcpy(updated.applicationID, input);
                }
                else
                {
                    printf("Invalid Application ID. Keeping old value.\n");
                }
            }


            /* Student ID */

            printf("Student ID [%s]: ",
                   updated.studentID);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    strcpy(updated.studentID, input);
                }
                else
                {
                    printf("Invalid Student ID. Keeping old value.\n");
                }
            }


            /* Drive ID */

            printf("Drive ID [%s]: ",
                   updated.driveID);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    strcpy(updated.driveID, input);
                }
                else
                {
                    printf("Invalid Drive ID. Keeping old value.\n");
                }
            }


            /* Validate relationship */

            if (!applicationExists(updated.applicationID))
            {
                printf("\nInvalid Application ID. Update cancelled.\n");
                return;
            }

            if (!studentExists(updated.studentID))
            {
                printf("\nInvalid Student ID. Update cancelled.\n");
                return;
            }

            if (!driveExists(updated.driveID))
            {
                printf("\nInvalid Drive ID. Update cancelled.\n");
                return;
            }

            if (!applicationMatchesStudentDrive(
                    updated.applicationID,
                    updated.studentID,
                    updated.driveID))
            {
                printf("\nERROR: Application does not belong to the given Student and Drive.\n");
                printf("Update cancelled.\n");
                return;
            }


            /* Round Number */

            printf("Round Number [%d]: ",
                   updated.roundNumber);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                int newRoundNumber;

                if (sscanf(input, "%d", &newRoundNumber) == 1 &&
                    newRoundNumber > 0)
                {
                    updated.roundNumber = newRoundNumber;
                }
                else
                {
                    printf("Invalid Round Number. Keeping old value.\n");
                }
            }


            /* Check duplicate round */

            if (isDuplicateRound(
                    updated.applicationID,
                    updated.roundNumber,
                    updated.id))
            {
                printf("\nThis Application already has Round %d.\n",
                       updated.roundNumber);
                printf("Update cancelled.\n");
                return;
            }


            /* Round Name */

            printf("Round Name [%s]: ",
                   updated.roundName);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(updated.roundName, input);
            }


            /* Status */

            printf("Status [%s]: ",
                   updated.status);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(updated.status, input);
            }


            /* Remarks */

            printf("Remarks [%s]: ",
                   updated.remarks);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(updated.remarks, input);
            }


            /* Save */

            if (overwriteRecordAt(
                    SELECTION_FILE,
                    &updated,
                    sizeof(Selection),
                    i))
            {
                printf("\nSelection round updated successfully!\n");
            }
            else
            {
                printf("\nFailed to update selection round.\n");
            }

            return;
        }
    }

    printf("\nSelection ID '%s' not found.\n",
           selectionID);
}


/* =========================================================
   Delete Selection Round
   ========================================================= */

void deleteSelectionRound(void)
{
    Selection selections[100];

    char selectionID[ID_LEN];
    char confirmation;

    int count = readAllRecords(
        SELECTION_FILE,
        selections,
        sizeof(Selection),
        100
    );

    printf("\n========== Delete Selection Round ==========\n");

    printf("Enter Selection ID: ");

    fgets(selectionID, ID_LEN, stdin);
    trimNewline(selectionID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(selections[i].id, selectionID) == 0)
        {
            printf("\nSelection Round Found!\n");

            displaySelection(&selections[i]);

            printf(
                "Are you sure you want to delete this selection round? (Y/N): "
            );

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
                selections[j] = selections[j + 1];
            }

            count--;


            /* Rewrite binary file */

            if (rewriteAllRecords(
                    SELECTION_FILE,
                    selections,
                    sizeof(Selection),
                    count))
            {
                printf("\nSelection round deleted successfully!\n");
            }
            else
            {
                printf("\nFailed to delete selection round.\n");
            }

            return;
        }
    }

    printf("\nSelection ID '%s' not found.\n",
           selectionID);
}