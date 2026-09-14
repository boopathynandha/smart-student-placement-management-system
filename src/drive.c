#include <stdio.h>
#include <string.h>

#include "../include/drive.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/validation.h"
#include "../include/utils.h"


/* =========================================
   CHECK DUPLICATE DRIVE ID
   ========================================= */

int isDriveIDExists(const char *driveID) {

    PlacementDrive drives[100];

    int count = readAllRecords(
        DRIVE_FILE,
        drives,
        sizeof(PlacementDrive),
        100
    );

    for (int i = 0; i < count; i++) {

        if (strcmp(drives[i].id, driveID) == 0) {
            return 1;
        }
    }

    return 0;
}


/* =========================================
   ADD PLACEMENT DRIVE
   ========================================= */

void addDrive(void) {

    PlacementDrive drive;

    printf("\n========== Add Placement Drive ==========\n");


    /* Drive ID */

    while (1) {

        printf("Enter Drive ID: ");

        fgets(drive.id, sizeof(drive.id), stdin);
        trimNewline(drive.id);

        if (!isValidID(drive.id)) {

            printf(
                "Invalid ID. Use letters, numbers, '-' or '_'.\n"
            );

            continue;
        }

        if (isDriveIDExists(drive.id)) {

            printf(
                "Drive ID '%s' already exists. Please enter a different ID.\n",
                drive.id
            );

            continue;
        }

        break;
    }


    /* Company ID */

    while (1) {

        printf("Enter Company ID: ");

        fgets(
            drive.companyID,
            sizeof(drive.companyID),
            stdin
        );

        trimNewline(drive.companyID);

        if (!isValidID(drive.companyID)) {

            printf(
                "Invalid Company ID. Use letters, numbers, '-' or '_'.\n"
            );

            continue;
        }

        break;
    }


    /* Drive Date */

    while (1) {

        printf("Enter Drive Date (DD-MM-YYYY): ");

        fgets(
            drive.driveDate,
            sizeof(drive.driveDate),
            stdin
        );

        trimNewline(drive.driveDate);

        if (!isNonEmptyString(drive.driveDate)) {

            printf("Drive date cannot be empty.\n");

            continue;
        }

        break;
    }


    /* Minimum CGPA */

    while (1) {

        printf("Enter Minimum CGPA: ");

        if (scanf("%f", &drive.minimumCGPA) != 1) {

            printf(
                "Invalid input. Please enter a number.\n"
            );

            clearInputBuffer();

            continue;
        }

        clearInputBuffer();

        if (!isValidCGPA(drive.minimumCGPA)) {

            printf(
                "Invalid CGPA. Enter a value between 0 and 10.\n"
            );

            continue;
        }

        break;
    }


    /* Maximum Backlogs */

    while (1) {

        printf("Enter Maximum Allowed Backlogs: ");

        if (scanf("%d", &drive.maximumBacklogs) != 1) {

            printf(
                "Invalid input. Please enter a number.\n"
            );

            clearInputBuffer();

            continue;
        }

        clearInputBuffer();

        if (!isValidBacklogs(drive.maximumBacklogs)) {

            printf(
                "Invalid backlogs. Enter a value between 0 and 50.\n"
            );

            continue;
        }

        break;
    }


    /* Eligible Departments */

    while (1) {

        printf("Enter Eligible Departments: ");

        fgets(
            drive.eligibleDepartments,
            sizeof(drive.eligibleDepartments),
            stdin
        );

        trimNewline(drive.eligibleDepartments);

        if (!isNonEmptyString(drive.eligibleDepartments)) {

            printf(
                "Eligible departments cannot be empty.\n"
            );

            continue;
        }

        break;
    }


    /* Required Skills */

    while (1) {

        printf("Enter Required Skills: ");

        fgets(
            drive.requiredSkills,
            sizeof(drive.requiredSkills),
            stdin
        );

        trimNewline(drive.requiredSkills);

        if (!isNonEmptyString(drive.requiredSkills)) {

            printf(
                "Required skills cannot be empty.\n"
            );

            continue;
        }

        break;
    }


    /* Status */

    while (1) {

        printf("Enter Drive Status: ");

        fgets(
            drive.status,
            sizeof(drive.status),
            stdin
        );

        trimNewline(drive.status);

        if (!isNonEmptyString(drive.status)) {

            printf(
                "Drive status cannot be empty.\n"
            );

            continue;
        }

        break;
    }


    /* Save drive */

    if (appendRecord(
            DRIVE_FILE,
            &drive,
            sizeof(PlacementDrive))) {

        printf(
            "\nPlacement drive added successfully!\n"
        );

    } else {

        printf(
            "\nError: Could not save placement drive.\n"
        );
    }
}


/* =========================================
   VIEW PLACEMENT DRIVES
   ========================================= */

void viewDrives(void) {

    PlacementDrive drives[100];

    int count = readAllRecords(
        DRIVE_FILE,
        drives,
        sizeof(PlacementDrive),
        100
    );

    printf("\n========== Placement Drive List ==========\n");

    if (count <= 0) {

        printf("No placement drives found.\n");

        return;
    }


    printf(
        "\n%-10s %-12s %-15s %-10s %-12s %-20s %-25s %-15s\n",
        "Drive ID",
        "Company ID",
        "Date",
        "Min CGPA",
        "Max Backlogs",
        "Departments",
        "Required Skills",
        "Status"
    );

    printf(
        "----------------------------------------------------------------------------------------------------------------------------\n"
    );


    for (int i = 0; i < count; i++) {

        printf(
            "%-10s %-12s %-15s %-10.2f %-12d %-20s %-25s %-15s\n",
            drives[i].id,
            drives[i].companyID,
            drives[i].driveDate,
            drives[i].minimumCGPA,
            drives[i].maximumBacklogs,
            drives[i].eligibleDepartments,
            drives[i].requiredSkills,
            drives[i].status
        );
    }


    printf(
        "\nTotal Placement Drives: %d\n",
        count
    );
}


/* =========================================
   SEARCH PLACEMENT DRIVE
   ========================================= */

void searchDrive(void) {

    PlacementDrive drives[100];

    char searchID[ID_LEN];

    printf("\n========== Search Placement Drive ==========\n");

    printf("Enter Drive ID: ");

    fgets(
        searchID,
        sizeof(searchID),
        stdin
    );

    trimNewline(searchID);


    int count = readAllRecords(
        DRIVE_FILE,
        drives,
        sizeof(PlacementDrive),
        100
    );


    if (count <= 0) {

        printf("\nNo placement drives found.\n");

        return;
    }


    for (int i = 0; i < count; i++) {

        if (strcmp(drives[i].id, searchID) == 0) {

            printf("\nPlacement Drive Found!\n");

            printf("-----------------------------\n");

            printf(
                "Drive ID           : %s\n",
                drives[i].id
            );

            printf(
                "Company ID         : %s\n",
                drives[i].companyID
            );

            printf(
                "Drive Date         : %s\n",
                drives[i].driveDate
            );

            printf(
                "Minimum CGPA       : %.2f\n",
                drives[i].minimumCGPA
            );

            printf(
                "Maximum Backlogs   : %d\n",
                drives[i].maximumBacklogs
            );

            printf(
                "Eligible Departments : %s\n",
                drives[i].eligibleDepartments
            );

            printf(
                "Required Skills    : %s\n",
                drives[i].requiredSkills
            );

            printf(
                "Status             : %s\n",
                drives[i].status
            );

            printf("-----------------------------\n");

            return;
        }
    }


    printf(
        "\nPlacement drive with ID '%s' not found.\n",
        searchID
    );
}


/* =========================================
   UPDATE PLACEMENT DRIVE
   ========================================= */

void updateDrive(void) {

    PlacementDrive drives[100];

    char searchID[ID_LEN];

    printf("\n========== Update Placement Drive ==========\n");

    printf("Enter Drive ID: ");

    fgets(
        searchID,
        sizeof(searchID),
        stdin
    );

    trimNewline(searchID);


    int count = readAllRecords(
        DRIVE_FILE,
        drives,
        sizeof(PlacementDrive),
        100
    );


    if (count <= 0) {

        printf("\nNo placement drives found.\n");

        return;
    }


    int foundIndex = -1;


    for (int i = 0; i < count; i++) {

        if (strcmp(drives[i].id, searchID) == 0) {

            foundIndex = i;

            break;
        }
    }


    if (foundIndex == -1) {

        printf(
            "\nPlacement drive with ID '%s' not found.\n",
            searchID
        );

        return;
    }


    printf(
        "\nPlacement drive found: %s\n",
        drives[foundIndex].id
    );


    /* Company ID */

    while (1) {

        printf("Enter New Company ID: ");

        fgets(
            drives[foundIndex].companyID,
            sizeof(drives[foundIndex].companyID),
            stdin
        );

        trimNewline(drives[foundIndex].companyID);

        if (!isValidID(drives[foundIndex].companyID)) {

            printf("Invalid Company ID.\n");

            continue;
        }

        break;
    }


    /* Drive Date */

    while (1) {

        printf("Enter New Drive Date (DD-MM-YYYY): ");

        fgets(
            drives[foundIndex].driveDate,
            sizeof(drives[foundIndex].driveDate),
            stdin
        );

        trimNewline(drives[foundIndex].driveDate);

        if (!isNonEmptyString(drives[foundIndex].driveDate)) {

            printf("Drive date cannot be empty.\n");

            continue;
        }

        break;
    }


    /* Minimum CGPA */

    while (1) {

        printf("Enter New Minimum CGPA: ");

        if (scanf(
                "%f",
                &drives[foundIndex].minimumCGPA) != 1) {

            printf("Invalid input. Please enter a number.\n");

            clearInputBuffer();

            continue;
        }

        clearInputBuffer();

        if (!isValidCGPA(
                drives[foundIndex].minimumCGPA)) {

            printf(
                "Invalid CGPA. Enter a value between 0 and 10.\n"
            );

            continue;
        }

        break;
    }


    /* Maximum Backlogs */

    while (1) {

        printf(
            "Enter New Maximum Allowed Backlogs: "
        );

        if (scanf(
                "%d",
                &drives[foundIndex].maximumBacklogs) != 1) {

            printf(
                "Invalid input. Please enter a number.\n"
            );

            clearInputBuffer();

            continue;
        }

        clearInputBuffer();

        if (!isValidBacklogs(
                drives[foundIndex].maximumBacklogs)) {

            printf(
                "Invalid backlogs. Enter a value between 0 and 50.\n"
            );

            continue;
        }

        break;
    }


    /* Eligible Departments */

    while (1) {

        printf(
            "Enter New Eligible Departments: "
        );

        fgets(
            drives[foundIndex].eligibleDepartments,
            sizeof(drives[foundIndex].eligibleDepartments),
            stdin
        );

        trimNewline(
            drives[foundIndex].eligibleDepartments
        );

        if (!isNonEmptyString(
                drives[foundIndex].eligibleDepartments)) {

            printf(
                "Eligible departments cannot be empty.\n"
            );

            continue;
        }

        break;
    }


    /* Required Skills */

    while (1) {

        printf(
            "Enter New Required Skills: "
        );

        fgets(
            drives[foundIndex].requiredSkills,
            sizeof(drives[foundIndex].requiredSkills),
            stdin
        );

        trimNewline(
            drives[foundIndex].requiredSkills
        );

        if (!isNonEmptyString(
                drives[foundIndex].requiredSkills)) {

            printf(
                "Required skills cannot be empty.\n"
            );

            continue;
        }

        break;
    }


    /* Status */

    while (1) {

        printf("Enter New Drive Status: ");

        fgets(
            drives[foundIndex].status,
            sizeof(drives[foundIndex].status),
            stdin
        );

        trimNewline(
            drives[foundIndex].status
        );

        if (!isNonEmptyString(
                drives[foundIndex].status)) {

            printf(
                "Drive status cannot be empty.\n"
            );

            continue;
        }

        break;
    }


    /* Save updated drive */

    if (overwriteRecordAt(
            DRIVE_FILE,
            &drives[foundIndex],
            sizeof(PlacementDrive),
            foundIndex)) {

        printf(
            "\nPlacement drive updated successfully!\n"
        );

    } else {

        printf(
            "\nError: Could not update placement drive.\n"
        );
    }
}


/* =========================================
   DELETE PLACEMENT DRIVE
   ========================================= */

void deleteDrive(void) {

    PlacementDrive drives[100];

    char deleteID[ID_LEN];

    char confirmation;


    printf("\n========== Delete Placement Drive ==========\n");

    printf("Enter Drive ID: ");

    fgets(
        deleteID,
        sizeof(deleteID),
        stdin
    );

    trimNewline(deleteID);


    int count = readAllRecords(
        DRIVE_FILE,
        drives,
        sizeof(PlacementDrive),
        100
    );


    if (count <= 0) {

        printf("\nNo placement drives found.\n");

        return;
    }


    int foundIndex = -1;


    for (int i = 0; i < count; i++) {

        if (strcmp(drives[i].id, deleteID) == 0) {

            foundIndex = i;

            break;
        }
    }


    if (foundIndex == -1) {

        printf(
            "\nPlacement drive with ID '%s' not found.\n",
            deleteID
        );

        return;
    }


    printf("\nPlacement Drive Found:\n");

    printf("-----------------------------\n");

    printf(
        "Drive ID             : %s\n",
        drives[foundIndex].id
    );

    printf(
        "Company ID           : %s\n",
        drives[foundIndex].companyID
    );

    printf(
        "Drive Date           : %s\n",
        drives[foundIndex].driveDate
    );

    printf(
        "Minimum CGPA         : %.2f\n",
        drives[foundIndex].minimumCGPA
    );

    printf(
        "Maximum Backlogs     : %d\n",
        drives[foundIndex].maximumBacklogs
    );

    printf(
        "Eligible Departments : %s\n",
        drives[foundIndex].eligibleDepartments
    );

    printf(
        "Required Skills      : %s\n",
        drives[foundIndex].requiredSkills
    );

    printf(
        "Status               : %s\n",
        drives[foundIndex].status
    );

    printf("-----------------------------\n");


    printf(
        "\nAre you sure you want to delete this placement drive? (Y/N): "
    );

    scanf(
        " %c",
        &confirmation
    );

    clearInputBuffer();


    if (confirmation != 'Y' &&
        confirmation != 'y') {

        printf("\nDeletion cancelled.\n");

        return;
    }


    /* Shift records */

    for (int i = foundIndex; i < count - 1; i++) {

        drives[i] = drives[i + 1];
    }


    /* Rewrite binary file */

    if (rewriteAllRecords(
            DRIVE_FILE,
            drives,
            sizeof(PlacementDrive),
            count - 1)) {

        printf(
            "\nPlacement drive deleted successfully!\n"
        );

    } else {

        printf(
            "\nError: Could not delete placement drive.\n"
        );
    }
}