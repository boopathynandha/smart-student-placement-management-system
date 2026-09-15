#include <stdio.h>
#include <string.h>

#include "../include/statistics.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/student.h"
#include "../include/company.h"
#include "../include/drive.h"
#include "../include/application.h"
#include "../include/preparation.h"

/*
 * Placement Statistics Module
 *
 * Displays overall statistics of the
 * Smart Student Placement Management System.
 */

void displayPlacementStatistics(void)
{
    long totalStudents;
    long totalCompanies;
    long totalDrives;
    long totalApplications;
    long totalPreparations;

    Application applications[100];

    int applied = 0;
    int shortlisted = 0;
    int selected = 0;
    int rejected = 0;

    /*
     * Count records from binary files.
     */
    totalStudents = countRecords(
        STUDENT_FILE,
        sizeof(Student)
    );

    totalCompanies = countRecords(
        COMPANY_FILE,
        sizeof(Company)
    );

    totalDrives = countRecords(
        DRIVE_FILE,
        sizeof(PlacementDrive)
    );

    totalApplications = countRecords(
        APPLICATION_FILE,
        sizeof(Application)
    );

    totalPreparations = countRecords(
        PREPARATION_FILE,
        sizeof(Preparation)
    );

    /*
     * Read application records.
     */
    int applicationCount = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        100
    );

    /*
     * Count application statuses.
     */
    for (int i = 0; i < applicationCount; i++)
    {
        if (strcmp(applications[i].status, "Applied") == 0)
        {
            applied++;
        }
        else if (strcmp(applications[i].status, "Shortlisted") == 0)
        {
            shortlisted++;
        }
        else if (strcmp(applications[i].status, "Selected") == 0)
        {
            selected++;
        }
        else if (strcmp(applications[i].status, "Rejected") == 0)
        {
            rejected++;
        }
    }

    /*
     * Calculate placement percentage.
     *
     * Placement Percentage =
     * Selected Applications / Total Students * 100
     */
    float placementPercentage = 0.0f;

    if (totalStudents > 0)
    {
        placementPercentage =
            ((float)selected / (float)totalStudents) * 100.0f;
    }

    /*
     * Display statistics.
     */
    printf("\n");
    printf("====================================================\n");
    printf("              PLACEMENT STATISTICS\n");
    printf("====================================================\n");

    printf("\n---------------- Overall Statistics ----------------\n");

    printf("Total Students            : %ld\n", totalStudents);
    printf("Total Companies           : %ld\n", totalCompanies);
    printf("Total Placement Drives    : %ld\n", totalDrives);
    printf("Total Applications        : %ld\n", totalApplications);
    printf("Total Preparation Records : %ld\n", totalPreparations);

    printf("\n---------------- Application Statistics ----------------\n");

    printf("Applied                   : %d\n", applied);
    printf("Shortlisted               : %d\n", shortlisted);
    printf("Selected                  : %d\n", selected);
    printf("Rejected                  : %d\n", rejected);

    printf("\n---------------- Placement Performance ----------------\n");

    printf(
        "Placement Percentage      : %.2f%%\n",
        placementPercentage
    );

    printf("\n====================================================\n");
}