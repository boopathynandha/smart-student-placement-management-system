#include <stdio.h>
#include <string.h>

#include "../include/preparation.h"
#include "../include/constants.h"
#include "../include/student.h"
#include "../include/filehandler.h"
#include "../include/utils.h"
#include "../include/validation.h"


/*
 * Check whether Preparation ID already exists
 */

int isPreparationIDExists(const char *preparationID)
{
    Preparation preparations[100];

    int count = readAllRecords(
        PREPARATION_FILE,
        preparations,
        sizeof(Preparation),
        100
    );

    for (int i = 0; i < count; i++)
    {
        if (strcmp(preparations[i].id, preparationID) == 0)
        {
            return 1;
        }
    }

    return 0;
}


/*
 * Find Student
 */

static int findStudent(const char *studentID)
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


/*
 * Add Preparation Record
 */

void addPreparation(void)
{
    Preparation preparation;

    printf("\n========== Add Preparation Record ==========\n");


    /*
     * Preparation ID
     */

    printf("Enter Preparation ID: ");

    fgets(preparation.id, ID_LEN, stdin);

    trimNewline(preparation.id);


    if (!isValidID(preparation.id))
    {
        printf("\nInvalid Preparation ID.\n");
        return;
    }


    if (isPreparationIDExists(preparation.id))
    {
        printf("\nPreparation ID already exists.\n");
        return;
    }


    /*
     * Student ID
     */

    printf("Enter Student ID: ");

    fgets(preparation.studentID, ID_LEN, stdin);

    trimNewline(preparation.studentID);


    if (!isValidID(preparation.studentID))
    {
        printf("\nInvalid Student ID.\n");
        return;
    }


    if (!findStudent(preparation.studentID))
    {
        printf("\nStudent ID not found.\n");
        return;
    }


    /*
     * Skill / Topic
     */

    printf("Enter Skill / Topic: ");

    fgets(preparation.skill, NAME_LEN, stdin);

    trimNewline(preparation.skill);


    if (!isNonEmptyString(preparation.skill))
    {
        printf("\nSkill / Topic cannot be empty.\n");
        return;
    }


    /*
     * Target
     */

    printf("Enter Target: ");

    if (scanf("%d", &preparation.target) != 1)
    {
        printf("\nInvalid target.\n");

        clearInputBuffer();

        return;
    }

    clearInputBuffer();


    if (preparation.target <= 0)
    {
        printf("\nTarget must be greater than 0.\n");
        return;
    }


    /*
     * Completed
     */

    printf("Enter Completed: ");

    if (scanf("%d", &preparation.completed) != 1)
    {
        printf("\nInvalid completed value.\n");

        clearInputBuffer();

        return;
    }

    clearInputBuffer();


    if (preparation.completed < 0 ||
        preparation.completed > preparation.target)
    {
        printf(
            "\nCompleted value must be between 0 and Target.\n"
        );

        return;
    }


    /*
     * Status
     */

    printf("Enter Status: ");

    fgets(preparation.status, STATUS_LEN, stdin);

    trimNewline(preparation.status);


    if (!isNonEmptyString(preparation.status))
    {
        printf("\nStatus cannot be empty.\n");
        return;
    }


    /*
     * Remarks
     */

    printf("Enter Remarks: ");

    fgets(preparation.remarks, SKILL_LEN, stdin);

    trimNewline(preparation.remarks);


    /*
     * Save Record
     */

    if (appendRecord(
            PREPARATION_FILE,
            &preparation,
            sizeof(Preparation)) != 0)
    {
        printf("\nFailed to save preparation record.\n");

        return;
    }


    printf("\nPreparation record added successfully!\n");
}


/*
 * View Preparation Records
 */

void viewPreparations(void)
{
    Preparation preparations[100];

    int count = readAllRecords(
        PREPARATION_FILE,
        preparations,
        sizeof(Preparation),
        100
    );


    printf(
        "\n========== Placement Preparation Records ==========\n"
    );


    if (count <= 0)
    {
        printf("\nNo preparation records found.\n");

        return;
    }


    printf(
        "\n%-10s %-12s %-20s %-10s %-10s %-18s\n",
        "ID",
        "Student ID",
        "Skill / Topic",
        "Target",
        "Completed",
        "Status"
    );


    printf(
        "-------------------------------------------------------------------------------\n"
    );


    for (int i = 0; i < count; i++)
    {
        printf(
            "%-10s %-12s %-20s %-10d %-10d %-18s\n",
            preparations[i].id,
            preparations[i].studentID,
            preparations[i].skill,
            preparations[i].target,
            preparations[i].completed,
            preparations[i].status
        );
    }


    printf(
        "\nTotal Preparation Records: %d\n",
        count
    );
}


/*
 * Search Preparation Record
 */

void searchPreparation(void)
{
    Preparation preparations[100];

    char preparationID[ID_LEN];

    int count = readAllRecords(
        PREPARATION_FILE,
        preparations,
        sizeof(Preparation),
        100
    );


    printf(
        "\n========== Search Preparation Record ==========\n"
    );


    printf("Enter Preparation ID: ");

    fgets(preparationID, ID_LEN, stdin);

    trimNewline(preparationID);


    for (int i = 0; i < count; i++)
    {
        if (strcmp(
                preparations[i].id,
                preparationID) == 0)
        {
            printf("\nPreparation Record Found:\n");

            printf("-----------------------------\n");


            printf(
                "Preparation ID : %s\n",
                preparations[i].id
            );


            printf(
                "Student ID     : %s\n",
                preparations[i].studentID
            );


            printf(
                "Skill / Topic  : %s\n",
                preparations[i].skill
            );


            printf(
                "Target         : %d\n",
                preparations[i].target
            );


            printf(
                "Completed      : %d\n",
                preparations[i].completed
            );


            printf(
                "Status         : %s\n",
                preparations[i].status
            );


            printf(
                "Remarks        : %s\n",
                preparations[i].remarks
            );


            printf("-----------------------------\n");

            return;
        }
    }


    printf("\nPreparation record not found.\n");
}


/*
 * Update Preparation Record
 */

void updatePreparation(void)
{
    Preparation preparations[100];

    char preparationID[ID_LEN];

    int count = readAllRecords(
        PREPARATION_FILE,
        preparations,
        sizeof(Preparation),
        100
    );


    printf(
        "\n========== Update Preparation Record ==========\n"
    );


    printf("Enter Preparation ID: ");

    fgets(preparationID, ID_LEN, stdin);

    trimNewline(preparationID);


    for (int i = 0; i < count; i++)
    {
        if (strcmp(
                preparations[i].id,
                preparationID) == 0)
        {
            char input[SKILL_LEN];

            int oldTarget = preparations[i].target;

            int oldCompleted = preparations[i].completed;


            /*
             * Display Current Record
             */

            printf("\nCurrent Record:\n");

            printf("-----------------------------\n");


            printf(
                "Student ID     : %s\n",
                preparations[i].studentID
            );


            printf(
                "Skill / Topic  : %s\n",
                preparations[i].skill
            );


            printf(
                "Target         : %d\n",
                preparations[i].target
            );


            printf(
                "Completed      : %d\n",
                preparations[i].completed
            );


            printf(
                "Status         : %s\n",
                preparations[i].status
            );


            printf(
                "Remarks        : %s\n",
                preparations[i].remarks
            );


            printf("-----------------------------\n");


            /*
             * Update Student ID
             */

            printf(
                "Enter New Student ID "
                "(Press Enter to keep current): "
            );


            fgets(input, ID_LEN, stdin);

            trimNewline(input);


            if (strlen(input) > 0)
            {
                if (!isValidID(input))
                {
                    printf("\nInvalid Student ID.\n");

                    return;
                }


                if (!findStudent(input))
                {
                    printf("\nStudent ID not found.\n");

                    return;
                }


                strcpy(
                    preparations[i].studentID,
                    input
                );
            }


            /*
             * Update Skill
             */

            printf(
                "Enter New Skill / Topic "
                "(Press Enter to keep current): "
            );


            fgets(input, NAME_LEN, stdin);

            trimNewline(input);


            if (strlen(input) > 0)
            {
                strcpy(
                    preparations[i].skill,
                    input
                );
            }


            /*
             * Update Target
             */

            printf(
                "Enter New Target "
                "(Enter 0 to keep current): "
            );


            int newTarget;


            if (scanf("%d", &newTarget) != 1)
            {
                printf("\nInvalid target.\n");

                clearInputBuffer();

                return;
            }


            clearInputBuffer();


            if (newTarget == 0)
            {
                preparations[i].target = oldTarget;
            }
            else if (newTarget < 0)
            {
                printf("\nTarget cannot be negative.\n");

                return;
            }
            else
            {
                preparations[i].target = newTarget;
            }


            /*
             * Update Completed
             */

            printf(
                "Enter New Completed "
                "(Enter -1 to keep current): "
            );


            int newCompleted;


            if (scanf("%d", &newCompleted) != 1)
            {
                printf("\nInvalid completed value.\n");

                clearInputBuffer();

                return;
            }


            clearInputBuffer();


            if (newCompleted == -1)
            {
                preparations[i].completed = oldCompleted;
            }
            else if (newCompleted < 0)
            {
                printf(
                    "\nCompleted value cannot be negative.\n"
                );

                return;
            }
            else
            {
                preparations[i].completed = newCompleted;
            }


            /*
             * Validate Target and Completed
             */

            if (preparations[i].target <= 0)
            {
                printf(
                    "\nTarget must be greater than 0.\n"
                );

                return;
            }


            if (preparations[i].completed >
                preparations[i].target)
            {
                printf(
                    "\nCompleted value cannot exceed Target.\n"
                );

                return;
            }


            /*
             * Update Status
             */

            printf(
                "Enter New Status "
                "(Press Enter to keep current): "
            );


            fgets(input, STATUS_LEN, stdin);

            trimNewline(input);


            if (strlen(input) > 0)
            {
                strcpy(
                    preparations[i].status,
                    input
                );
            }


            /*
             * Update Remarks
             */

            printf(
                "Enter New Remarks "
                "(Press Enter to keep current): "
            );


            fgets(input, SKILL_LEN, stdin);

            trimNewline(input);


            if (strlen(input) > 0)
            {
                strcpy(
                    preparations[i].remarks,
                    input
                );
            }


            /*
             * Save Updated Record
             */

            if (overwriteRecordAt(
                    PREPARATION_FILE,
                    &preparations[i],
                    sizeof(Preparation),
                    i) != 0)
            {
                printf(
                    "\nFailed to update preparation record.\n"
                );

                return;
            }


            printf(
                "\nPreparation record updated successfully!\n"
            );


            return;
        }
    }


    printf("\nPreparation record not found.\n");
}


/*
 * Delete Preparation Record
 */

void deletePreparation(void)
{
    Preparation preparations[100];

    char preparationID[ID_LEN];

    int count = readAllRecords(
        PREPARATION_FILE,
        preparations,
        sizeof(Preparation),
        100
    );


    printf(
        "\n========== Delete Preparation Record ==========\n"
    );


    printf("Enter Preparation ID: ");

    fgets(preparationID, ID_LEN, stdin);

    trimNewline(preparationID);


    for (int i = 0; i < count; i++)
    {
        if (strcmp(
                preparations[i].id,
                preparationID) == 0)
        {
            char confirm;


            /*
             * Display Record
             */

            printf("\nPreparation Record Found:\n");

            printf("-----------------------------\n");


            printf(
                "Preparation ID : %s\n",
                preparations[i].id
            );


            printf(
                "Student ID     : %s\n",
                preparations[i].studentID
            );


            printf(
                "Skill / Topic  : %s\n",
                preparations[i].skill
            );


            printf(
                "Target         : %d\n",
                preparations[i].target
            );


            printf(
                "Completed      : %d\n",
                preparations[i].completed
            );


            printf(
                "Status         : %s\n",
                preparations[i].status
            );


            printf(
                "Remarks        : %s\n",
                preparations[i].remarks
            );


            printf("-----------------------------\n");


            /*
             * Confirmation
             */

            printf(
                "\nAre you sure you want to delete "
                "this record? (Y/N): "
            );


            scanf(" %c", &confirm);

            clearInputBuffer();


            if (confirm != 'Y' &&
                confirm != 'y')
            {
                printf("\nDeletion cancelled.\n");

                return;
            }


            /*
             * Shift Remaining Records
             */

            for (int j = i; j < count - 1; j++)
            {
                preparations[j] = preparations[j + 1];
            }


            count--;


            /*
             * Open Preparation File
             */

            FILE *fp = fopen(
                PREPARATION_FILE,
                "wb"
            );


            if (fp == NULL)
            {
                printf(
                    "\nFailed to open preparation file.\n"
                );

                return;
            }


            /*
             * Write Remaining Records
             */

            if (count > 0)
            {
                size_t written = fwrite(
                    preparations,
                    sizeof(Preparation),
                    count,
                    fp
                );


                if (written != (size_t)count)
                {
                    fclose(fp);

                    printf(
                        "\nFailed to write preparation records.\n"
                    );

                    return;
                }
            }


            /*
             * Close File
             */

            fclose(fp);


            printf(
                "\nPreparation record deleted successfully!\n"
            );


            return;
        }
    }


    printf("\nPreparation record not found.\n");
}