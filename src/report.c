#include <stdio.h>
#include <string.h>

#include "../include/report.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/student.h"
#include "../include/company.h"
#include "../include/drive.h"
#include "../include/application.h"
#include "../include/preparation.h"


/*
 * Generate Placement Report
 *
 * Reads data from binary files and creates
 * a text report inside the reports folder.
 */
void generatePlacementReport(void)
{
    FILE *reportFile;

    Student students[100];
    Company companies[100];
    PlacementDrive drives[100];
    Application applications[100];
    Preparation preparations[100];

    int studentCount;
    int companyCount;
    int driveCount;
    int applicationCount;
    int preparationCount;

    int applied = 0;
    int shortlisted = 0;
    int selected = 0;
    int rejected = 0;


    /*
     * Read records from binary files.
     */
    studentCount = readAllRecords(
        STUDENT_FILE,
        students,
        sizeof(Student),
        100
    );

    companyCount = readAllRecords(
        COMPANY_FILE,
        companies,
        sizeof(Company),
        100
    );

    driveCount = readAllRecords(
        DRIVE_FILE,
        drives,
        sizeof(PlacementDrive),
        100
    );

    applicationCount = readAllRecords(
        APPLICATION_FILE,
        applications,
        sizeof(Application),
        100
    );

    preparationCount = readAllRecords(
        PREPARATION_FILE,
        preparations,
        sizeof(Preparation),
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
     */
    float placementPercentage = 0.0f;

    if (studentCount > 0)
    {
        placementPercentage =
            ((float)selected / (float)studentCount) * 100.0f;
    }


    /*
     * Create the report file.
     *
     * The existing report will be replaced.
     */
    reportFile = fopen(
        "reports/placement_report.txt",
        "w"
    );

    if (reportFile == NULL)
    {
        printf("\nFailed to create placement report.\n");
        printf("Please make sure the 'reports' folder exists.\n");
        return;
    }


    /*
     * Report Header
     */
    fprintf(
        reportFile,
        "============================================================\n"
    );

    fprintf(
        reportFile,
        "       SMART STUDENT PLACEMENT MANAGEMENT SYSTEM\n"
    );

    fprintf(
        reportFile,
        "                    PLACEMENT REPORT\n"
    );

    fprintf(
        reportFile,
        "============================================================\n\n"
    );


    /*
     * Overall Statistics
     */
    fprintf(
        reportFile,
        "================ OVERALL STATISTICS ================\n\n"
    );

    fprintf(
        reportFile,
        "Total Students            : %d\n",
        studentCount
    );

    fprintf(
        reportFile,
        "Total Companies           : %d\n",
        companyCount
    );

    fprintf(
        reportFile,
        "Total Placement Drives    : %d\n",
        driveCount
    );

    fprintf(
        reportFile,
        "Total Applications        : %d\n",
        applicationCount
    );

    fprintf(
        reportFile,
        "Total Preparation Records : %d\n\n",
        preparationCount
    );


    /*
     * Application Statistics
     */
    fprintf(
        reportFile,
        "================ APPLICATION STATISTICS ================\n\n"
    );

    fprintf(
        reportFile,
        "Applied                   : %d\n",
        applied
    );

    fprintf(
        reportFile,
        "Shortlisted               : %d\n",
        shortlisted
    );

    fprintf(
        reportFile,
        "Selected                  : %d\n",
        selected
    );

    fprintf(
        reportFile,
        "Rejected                  : %d\n\n",
        rejected
    );


    /*
     * Placement Performance
     */
    fprintf(
        reportFile,
        "================ PLACEMENT PERFORMANCE ================\n\n"
    );

    fprintf(
        reportFile,
        "Placement Percentage      : %.2f%%\n\n",
        placementPercentage
    );


    /*
     * Student Details
     */
    fprintf(
        reportFile,
        "================ STUDENT DETAILS ================\n\n"
    );

    if (studentCount == 0)
    {
        fprintf(
            reportFile,
            "No student records found.\n\n"
        );
    }
    else
    {
        fprintf(
            reportFile,
            "%-10s %-25s %-15s %-8s %-10s %-30s\n",
            "ID",
            "Name",
            "Department",
            "CGPA",
            "Backlogs",
            "Skills"
        );

        fprintf(
            reportFile,
            "----------------------------------------------------------------------------------------------------\n"
        );

        for (int i = 0; i < studentCount; i++)
        {
            fprintf(
                reportFile,
                "%-10s %-25s %-15s %-8.2f %-10d %-30s\n",
                students[i].id,
                students[i].name,
                students[i].department,
                students[i].cgpa,
                students[i].backlogs,
                students[i].skills
            );
        }

        fprintf(reportFile, "\n");
    }


    /*
     * Company Details
     */
    fprintf(
        reportFile,
        "================ COMPANY DETAILS ================\n\n"
    );

    if (companyCount == 0)
    {
        fprintf(
            reportFile,
            "No company records found.\n\n"
        );
    }
    else
    {
        fprintf(
            reportFile,
            "%-10s %-25s %-20s %-25s %-10s %-10s\n",
            "ID",
            "Company",
            "Location",
            "Role",
            "Min CGPA",
            "Max Backlogs"
        );

        fprintf(
            reportFile,
            "----------------------------------------------------------------------------------------------------\n"
        );

        for (int i = 0; i < companyCount; i++)
        {
            fprintf(
                reportFile,
                "%-10s %-25s %-20s %-25s %-10.2f %-10d\n",
                companies[i].id,
                companies[i].name,
                companies[i].location,
                companies[i].role,
                companies[i].minimumCGPA,
                companies[i].maximumBacklogs
            );
        }

        fprintf(reportFile, "\n");
    }


    /*
     * Placement Drive Details
     */
    fprintf(
        reportFile,
        "================ PLACEMENT DRIVE DETAILS ================\n\n"
    );

    if (driveCount == 0)
    {
        fprintf(
            reportFile,
            "No placement drive records found.\n\n"
        );
    }
    else
    {
        fprintf(
            reportFile,
            "%-10s %-12s %-15s %-10s %-10s %-20s %-15s\n",
            "Drive ID",
            "Company ID",
            "Drive Date",
            "Min CGPA",
            "Max BL",
            "Departments",
            "Status"
        );

        fprintf(
            reportFile,
            "----------------------------------------------------------------------------------------------------\n"
        );

        for (int i = 0; i < driveCount; i++)
        {
            fprintf(
                reportFile,
                "%-10s %-12s %-15s %-10.2f %-10d %-20s %-15s\n",
                drives[i].id,
                drives[i].companyID,
                drives[i].driveDate,
                drives[i].minimumCGPA,
                drives[i].maximumBacklogs,
                drives[i].eligibleDepartments,
                drives[i].status
            );
        }

        fprintf(reportFile, "\n");
    }


    /*
     * Application Details
     */
    fprintf(
        reportFile,
        "================ APPLICATION DETAILS ================\n\n"
    );

    if (applicationCount == 0)
    {
        fprintf(
            reportFile,
            "No application records found.\n\n"
        );
    }
    else
    {
        fprintf(
            reportFile,
            "%-10s %-15s %-12s %-15s %-15s\n",
            "App ID",
            "Student ID",
            "Drive ID",
            "Date",
            "Status"
        );

        fprintf(
            reportFile,
            "--------------------------------------------------------------------------\n"
        );

        for (int i = 0; i < applicationCount; i++)
        {
            fprintf(
                reportFile,
                "%-10s %-15s %-12s %-15s %-15s\n",
                applications[i].id,
                applications[i].studentID,
                applications[i].driveID,
                applications[i].applicationDate,
                applications[i].status
            );
        }

        fprintf(reportFile, "\n");
    }


    /*
     * Preparation Details
     */
    fprintf(
        reportFile,
        "================ PREPARATION DETAILS ================\n\n"
    );

    if (preparationCount == 0)
    {
        fprintf(
            reportFile,
            "No preparation records found.\n\n"
        );
    }
    else
    {
        fprintf(
            reportFile,
            "%-10s %-15s %-20s %-10s %-12s %-15s\n",
            "ID",
            "Student ID",
            "Skill / Topic",
            "Target",
            "Completed",
            "Status"
        );

        fprintf(
            reportFile,
            "--------------------------------------------------------------------------------\n"
        );

        for (int i = 0; i < preparationCount; i++)
        {
            fprintf(
                reportFile,
                "%-10s %-15s %-20s %-10d %-12d %-15s\n",
                preparations[i].id,
                preparations[i].studentID,
                preparations[i].skill,
                preparations[i].target,
                preparations[i].completed,
                preparations[i].status
            );
        }

        fprintf(reportFile, "\n");
    }


    /*
     * Report Footer
     */
    fprintf(
        reportFile,
        "============================================================\n"
    );

    fprintf(
        reportFile,
        "                  END OF PLACEMENT REPORT\n"
    );

    fprintf(
        reportFile,
        "============================================================\n"
    );


    /*
     * Close report file.
     */
    fclose(reportFile);


    /*
     * Display success message.
     */
    printf("\n====================================================\n");
    printf("          PLACEMENT REPORT GENERATED\n");
    printf("====================================================\n");

    printf("\nReport successfully generated!\n");
    printf("File: reports/placement_report.txt\n");
}

