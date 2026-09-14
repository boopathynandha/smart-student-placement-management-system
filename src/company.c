#include <stdio.h>
#include <string.h>

#include "../include/company.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/validation.h"
#include "../include/utils.h"


/* =========================================
   CHECK DUPLICATE COMPANY ID
   ========================================= */

int isCompanyIDExists(const char *companyID) {

    Company companies[100];

    int count = readAllRecords(
        COMPANY_FILE,
        companies,
        sizeof(Company),
        100
    );

    for (int i = 0; i < count; i++) {

        if (strcmp(companies[i].id, companyID) == 0) {
            return 1;
        }
    }

    return 0;
}


/* =========================================
   ADD COMPANY
   ========================================= */

void addCompany(void) {

    Company company;

    printf("\n========== Add Company ==========\n");


    /* Company ID */
    while (1) {

        printf("Enter Company ID: ");
        fgets(company.id, sizeof(company.id), stdin);
        trimNewline(company.id);

        if (!isValidID(company.id)) {
            printf("Invalid ID. Use letters, numbers, '-' or '_'.\n");
            continue;
        }

        if (isCompanyIDExists(company.id)) {
            printf("Company ID '%s' already exists. Please enter a different ID.\n",
                   company.id);
            continue;
        }

        break;
    }


    /* Company Name */
    while (1) {

        printf("Enter Company Name: ");
        fgets(company.name, sizeof(company.name), stdin);
        trimNewline(company.name);

        if (!isNonEmptyString(company.name)) {
            printf("Company name cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Location */
    while (1) {

        printf("Enter Location: ");
        fgets(company.location, sizeof(company.location), stdin);
        trimNewline(company.location);

        if (!isNonEmptyString(company.location)) {
            printf("Location cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Job Role */
    while (1) {

        printf("Enter Job Role: ");
        fgets(company.role, sizeof(company.role), stdin);
        trimNewline(company.role);

        if (!isNonEmptyString(company.role)) {
            printf("Job role cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Minimum CGPA */
    while (1) {

        printf("Enter Minimum CGPA: ");

        if (scanf("%f", &company.minimumCGPA) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (!isValidCGPA(company.minimumCGPA)) {
            printf("Invalid CGPA. Enter a value between 0 and 10.\n");
            continue;
        }

        break;
    }


    /* Maximum Backlogs */
    while (1) {

        printf("Enter Maximum Allowed Backlogs: ");

        if (scanf("%d", &company.maximumBacklogs) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (!isValidBacklogs(company.maximumBacklogs)) {
            printf("Invalid backlogs. Enter a value between 0 and 50.\n");
            continue;
        }

        break;
    }


    /* Required Skills */
    while (1) {

        printf("Enter Required Skills: ");
        fgets(company.requiredSkills,
              sizeof(company.requiredSkills),
              stdin);

        trimNewline(company.requiredSkills);

        if (!isNonEmptyString(company.requiredSkills)) {
            printf("Required skills cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Save company */
    if (appendRecord(
            COMPANY_FILE,
            &company,
            sizeof(Company))) {

        printf("\nCompany added successfully!\n");

    } else {

        printf("\nError: Could not save company.\n");
    }
}


/* =========================================
   VIEW COMPANIES
   ========================================= */

void viewCompanies(void) {

    Company companies[100];

    int count = readAllRecords(
        COMPANY_FILE,
        companies,
        sizeof(Company),
        100
    );

    printf("\n========== Company List ==========\n");

    if (count <= 0) {

        printf("No companies found.\n");
        return;
    }


    printf("\n%-10s %-20s %-15s %-25s %-10s %-12s %-30s\n",
           "ID",
           "Company",
           "Location",
           "Job Role",
           "Min CGPA",
           "Max Backlogs",
           "Required Skills");

    printf("------------------------------------------------------------------------------------------------------------------------\n");


    for (int i = 0; i < count; i++) {

        printf("%-10s %-20s %-15s %-25s %-10.2f %-12d %-30s\n",
               companies[i].id,
               companies[i].name,
               companies[i].location,
               companies[i].role,
               companies[i].minimumCGPA,
               companies[i].maximumBacklogs,
               companies[i].requiredSkills);
    }


    printf("\nTotal Companies: %d\n", count);
}


/* =========================================
   SEARCH COMPANY
   ========================================= */

void searchCompany(void) {

    Company companies[100];
    char searchID[ID_LEN];

    printf("\n========== Search Company ==========\n");

    printf("Enter Company ID: ");
    fgets(searchID, sizeof(searchID), stdin);
    trimNewline(searchID);


    int count = readAllRecords(
        COMPANY_FILE,
        companies,
        sizeof(Company),
        100
    );

    if (count <= 0) {

        printf("\nNo companies found.\n");
        return;
    }


    for (int i = 0; i < count; i++) {

        if (strcmp(companies[i].id, searchID) == 0) {

            printf("\nCompany Found!\n");
            printf("-----------------------------\n");
            printf("Company ID       : %s\n", companies[i].id);
            printf("Company Name     : %s\n", companies[i].name);
            printf("Location         : %s\n", companies[i].location);
            printf("Job Role         : %s\n", companies[i].role);
            printf("Minimum CGPA     : %.2f\n", companies[i].minimumCGPA);
            printf("Maximum Backlogs : %d\n", companies[i].maximumBacklogs);
            printf("Required Skills  : %s\n", companies[i].requiredSkills);
            printf("-----------------------------\n");

            return;
        }
    }


    printf("\nCompany with ID '%s' not found.\n", searchID);
}


/* =========================================
   UPDATE COMPANY
   ========================================= */

void updateCompany(void) {

    Company companies[100];
    char searchID[ID_LEN];

    printf("\n========== Update Company ==========\n");

    printf("Enter Company ID: ");
    fgets(searchID, sizeof(searchID), stdin);
    trimNewline(searchID);


    int count = readAllRecords(
        COMPANY_FILE,
        companies,
        sizeof(Company),
        100
    );

    if (count <= 0) {

        printf("\nNo companies found.\n");
        return;
    }


    int foundIndex = -1;


    for (int i = 0; i < count; i++) {

        if (strcmp(companies[i].id, searchID) == 0) {

            foundIndex = i;
            break;
        }
    }


    if (foundIndex == -1) {

        printf("\nCompany with ID '%s' not found.\n", searchID);
        return;
    }


    printf("\nCompany found: %s\n",
           companies[foundIndex].name);


    /* Update Company Name */
    while (1) {

        printf("Enter New Company Name: ");

        fgets(
            companies[foundIndex].name,
            sizeof(companies[foundIndex].name),
            stdin
        );

        trimNewline(companies[foundIndex].name);

        if (!isNonEmptyString(companies[foundIndex].name)) {
            printf("Company name cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Update Location */
    while (1) {

        printf("Enter New Location: ");

        fgets(
            companies[foundIndex].location,
            sizeof(companies[foundIndex].location),
            stdin
        );

        trimNewline(companies[foundIndex].location);

        if (!isNonEmptyString(companies[foundIndex].location)) {
            printf("Location cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Update Job Role */
    while (1) {

        printf("Enter New Job Role: ");

        fgets(
            companies[foundIndex].role,
            sizeof(companies[foundIndex].role),
            stdin
        );

        trimNewline(companies[foundIndex].role);

        if (!isNonEmptyString(companies[foundIndex].role)) {
            printf("Job role cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Update Minimum CGPA */
    while (1) {

        printf("Enter New Minimum CGPA: ");

        if (scanf("%f", &companies[foundIndex].minimumCGPA) != 1) {

            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (!isValidCGPA(companies[foundIndex].minimumCGPA)) {

            printf("Invalid CGPA. Enter a value between 0 and 10.\n");
            continue;
        }

        break;
    }


    /* Update Maximum Backlogs */
    while (1) {

        printf("Enter New Maximum Allowed Backlogs: ");

        if (scanf("%d", &companies[foundIndex].maximumBacklogs) != 1) {

            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (!isValidBacklogs(companies[foundIndex].maximumBacklogs)) {

            printf("Invalid backlogs. Enter a value between 0 and 50.\n");
            continue;
        }

        break;
    }


    /* Update Required Skills */
    while (1) {

        printf("Enter New Required Skills: ");

        fgets(
            companies[foundIndex].requiredSkills,
            sizeof(companies[foundIndex].requiredSkills),
            stdin
        );

        trimNewline(companies[foundIndex].requiredSkills);

        if (!isNonEmptyString(companies[foundIndex].requiredSkills)) {

            printf("Required skills cannot be empty.\n");
            continue;
        }

        break;
    }


    /* Save updated company */
    if (overwriteRecordAt(
            COMPANY_FILE,
            &companies[foundIndex],
            sizeof(Company),
            foundIndex)) {

        printf("\nCompany updated successfully!\n");

    } else {

        printf("\nError: Could not update company.\n");
    }
}


/* =========================================
   DELETE COMPANY
   ========================================= */

void deleteCompany(void) {

    Company companies[100];
    char deleteID[ID_LEN];
    char confirmation;


    printf("\n========== Delete Company ==========\n");

    printf("Enter Company ID: ");

    fgets(
        deleteID,
        sizeof(deleteID),
        stdin
    );

    trimNewline(deleteID);


    int count = readAllRecords(
        COMPANY_FILE,
        companies,
        sizeof(Company),
        100
    );


    if (count <= 0) {

        printf("\nNo companies found.\n");
        return;
    }


    int foundIndex = -1;


    /* Find company */
    for (int i = 0; i < count; i++) {

        if (strcmp(companies[i].id, deleteID) == 0) {

            foundIndex = i;
            break;
        }
    }


    /* Company not found */
    if (foundIndex == -1) {

        printf(
            "\nCompany with ID '%s' not found.\n",
            deleteID
        );

        return;
    }


    /* Display company */
    printf("\nCompany Found:\n");
    printf("-----------------------------\n");
    printf("Company ID       : %s\n",
           companies[foundIndex].id);

    printf("Company Name     : %s\n",
           companies[foundIndex].name);

    printf("Location         : %s\n",
           companies[foundIndex].location);

    printf("Job Role         : %s\n",
           companies[foundIndex].role);

    printf("Minimum CGPA     : %.2f\n",
           companies[foundIndex].minimumCGPA);

    printf("Maximum Backlogs : %d\n",
           companies[foundIndex].maximumBacklogs);

    printf("Required Skills  : %s\n",
           companies[foundIndex].requiredSkills);

    printf("-----------------------------\n");


    /* Confirmation */
    printf(
        "\nAre you sure you want to delete this company? (Y/N): "
    );

    scanf(" %c", &confirmation);

    clearInputBuffer();


    if (confirmation != 'Y' && confirmation != 'y') {

        printf("\nDeletion cancelled.\n");
        return;
    }


    /* Shift records */
    for (int i = foundIndex; i < count - 1; i++) {

        companies[i] = companies[i + 1];
    }


    /* Rewrite binary file */
    if (rewriteAllRecords(
            COMPANY_FILE,
            companies,
            sizeof(Company),
            count - 1)) {

        printf("\nCompany deleted successfully!\n");

    } else {

        printf("\nError: Could not delete company.\n");
    }
}