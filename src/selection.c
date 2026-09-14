#include <stdio.h>
#include <string.h>

#include "../include/selection.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/validation.h"
#include "../include/utils.h"


/* Check whether Selection ID already exists */

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


/* Add Selection Round */

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

        break;
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


    /* Save Selection Round */

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


/* View Selection Rounds */

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


/* Search Selection Round */

void searchSelectionRound(void)
{
    Selection selections[100];
    char selectionID[ID_LEN];

    int count = readAllRecords(
        SELECTION_FILE,
        selections,
        sizeof(Selection),
        100
    );

    printf("\n========== Search Selection Round ==========\n");

    printf("Enter Selection ID: ");
    fgets(selectionID, ID_LEN, stdin);
    trimNewline(selectionID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(selections[i].id, selectionID) == 0)
        {
            printf("\nSelection Round Found!\n");
            printf("----------------------------------------\n");
            printf("Selection ID   : %s\n", selections[i].id);
            printf("Application ID : %s\n", selections[i].applicationID);
            printf("Student ID     : %s\n", selections[i].studentID);
            printf("Drive ID       : %s\n", selections[i].driveID);
            printf("Round Number   : %d\n", selections[i].roundNumber);
            printf("Round Name     : %s\n", selections[i].roundName);
            printf("Status         : %s\n", selections[i].status);
            printf("Remarks        : %s\n", selections[i].remarks);
            printf("----------------------------------------\n");

            return;
        }
    }

    printf("\nSelection ID '%s' not found.\n", selectionID);
}


/* Update Selection Round */

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


            /* Application ID */

            printf("Application ID [%s]: ",
                   selections[i].applicationID);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    strcpy(selections[i].applicationID, input);
                }
                else
                {
                    printf("Invalid Application ID. Keeping old value.\n");
                }
            }


            /* Student ID */

            printf("Student ID [%s]: ",
                   selections[i].studentID);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    strcpy(selections[i].studentID, input);
                }
                else
                {
                    printf("Invalid Student ID. Keeping old value.\n");
                }
            }


            /* Drive ID */

            printf("Drive ID [%s]: ",
                   selections[i].driveID);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                if (isValidID(input))
                {
                    strcpy(selections[i].driveID, input);
                }
                else
                {
                    printf("Invalid Drive ID. Keeping old value.\n");
                }
            }


            /* Round Number */

            printf("Round Number [%d]: ",
                   selections[i].roundNumber);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                int newRoundNumber;

                if (sscanf(input, "%d", &newRoundNumber) == 1 &&
                    newRoundNumber > 0)
                {
                    selections[i].roundNumber = newRoundNumber;
                }
                else
                {
                    printf("Invalid Round Number. Keeping old value.\n");
                }
            }


            /* Round Name */

            printf("Round Name [%s]: ",
                   selections[i].roundName);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(selections[i].roundName, input);
            }


            /* Status */

            printf("Status [%s]: ",
                   selections[i].status);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(selections[i].status, input);
            }


            /* Remarks */

            printf("Remarks [%s]: ",
                   selections[i].remarks);

            fgets(input, sizeof(input), stdin);
            trimNewline(input);

            if (isNonEmptyString(input))
            {
                strcpy(selections[i].remarks, input);
            }


            /* Save updated record */

            if (overwriteRecordAt(
                    SELECTION_FILE,
                    &selections[i],
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


/* Delete Selection Round */

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
            printf("----------------------------------------\n");
            printf("Selection ID   : %s\n", selections[i].id);
            printf("Application ID : %s\n", selections[i].applicationID);
            printf("Student ID     : %s\n", selections[i].studentID);
            printf("Drive ID       : %s\n", selections[i].driveID);
            printf("Round Number   : %d\n", selections[i].roundNumber);
            printf("Round Name     : %s\n", selections[i].roundName);
            printf("Status         : %s\n", selections[i].status);
            printf("Remarks        : %s\n", selections[i].remarks);
            printf("----------------------------------------\n");

            printf("Are you sure you want to delete this selection round? (Y/N): ");
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