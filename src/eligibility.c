#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/eligibility.h"
#include "../include/constants.h"
#include "../include/filehandler.h"
#include "../include/utils.h"


/*
 * Check whether student's department
 * is present in drive's eligible departments.
 */
static int isDepartmentEligible(const char *studentDepartment,
                                const char *eligibleDepartments)
{
    char departments[DEPT_LEN];
    char *token;

    strcpy(departments, eligibleDepartments);

    token = strtok(departments, ",");

    while (token != NULL)
    {
        /* Remove leading spaces */
        while (*token == ' ')
        {
            token++;
        }

        /* Remove trailing spaces */
        int len = strlen(token);

        while (len > 0 && isspace((unsigned char)token[len - 1]))
        {
            token[len - 1] = '\0';
            len--;
        }

        if (strcmp(studentDepartment, token) == 0)
        {
            return 1;
        }

        token = strtok(NULL, ",");
    }

    return 0;
}


/*
 * Check whether student has at least
 * one required skill.
 */
 static int skillExists(const char *skills, const char *target)
{
    char copy[SKILL_LEN];

    strcpy(copy, skills);

    char *token = strtok(copy, ",");

    while (token != NULL)
    {
        while (*token == ' ')
        {
            token++;
        }

        int len = strlen(token);

        while (len > 0 &&
               isspace((unsigned char)token[len - 1]))
        {
            token[len - 1] = '\0';
            len--;
        }

        if (strcmp(token, target) == 0)
        {
            return 1;
        }

        token = strtok(NULL, ",");
    }

    return 0;
}


static int hasRequiredSkill(const char *studentSkills,
                            const char *requiredSkills)
{
    char requiredCopy[SKILL_LEN];

    strcpy(requiredCopy, requiredSkills);

    /*
     * Manually parse required skills.
     */
    char *start = requiredCopy;

    while (*start != '\0')
    {
        char skill[SKILL_LEN];
        int i = 0;

        while (*start != '\0' &&
               *start != ',' &&
               i < SKILL_LEN - 1)
        {
            skill[i++] = *start++;
        }

        skill[i] = '\0';

        /* Trim leading spaces */
        char *trimmed = skill;

        while (*trimmed == ' ')
        {
            trimmed++;
        }

        /* Trim trailing spaces */
        int len = strlen(trimmed);

        while (len > 0 &&
               isspace((unsigned char)trimmed[len - 1]))
        {
            trimmed[len - 1] = '\0';
            len--;
        }

        if (skillExists(studentSkills, trimmed))
        {
            return 1;
        }

        if (*start == ',')
        {
            start++;
        }
    }

    return 0;
}

/*
 * Main eligibility checking function.
 *
 * Returns:
 * 1 -> Eligible
 * 0 -> Not Eligible
 */
int checkStudentEligibility(const Student *student,
                            const PlacementDrive *drive)
{
    if (student == NULL || drive == NULL)
    {
        return 0;
    }

    /* Check CGPA */
    if (student->cgpa < drive->minimumCGPA)
    {
        return 0;
    }

    /* Check backlogs */
    if (student->backlogs > drive->maximumBacklogs)
    {
        return 0;
    }

    /* Check department */
    if (!isDepartmentEligible(student->department,
                              drive->eligibleDepartments))
    {
        return 0;
    }

    /* Check skills */
    if (!hasRequiredSkill(student->skills,
                          drive->requiredSkills))
    {
        return 0;
    }

    return 1;
}


/*
 * Interactive Eligibility Checker
 */
void eligibilityChecker(void)
{
    Student students[100];
    PlacementDrive drives[100];

    char studentID[ID_LEN];
    char driveID[ID_LEN];

    int studentCount;
    int driveCount;

    int studentFound = 0;
    int driveFound = 0;

    printf("\n========== Automatic Eligibility Checker ==========\n");

    printf("Enter Student ID: ");
    fgets(studentID, sizeof(studentID), stdin);
    trimNewline(studentID);

    printf("Enter Drive ID: ");
    fgets(driveID, sizeof(driveID), stdin);
    trimNewline(driveID);

    studentCount = readAllRecords(
        STUDENT_FILE,
        students,
        sizeof(Student),
        100
    );

    driveCount = readAllRecords(
        DRIVE_FILE,
        drives,
        sizeof(PlacementDrive),
        100
    );

    /* Find student */
    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            studentFound = 1;
            break;
        }
    }

    /* Find drive */
    for (int i = 0; i < driveCount; i++)
    {
        if (strcmp(drives[i].id, driveID) == 0)
        {
            driveFound = 1;
            break;
        }
    }

    if (!studentFound)
    {
        printf("\nStudent with ID '%s' not found.\n", studentID);
        return;
    }

    if (!driveFound)
    {
        printf("\nPlacement drive with ID '%s' not found.\n", driveID);
        return;
    }

    /*
     * Find the actual records again
     * and perform eligibility checking.
     */
    Student *student = NULL;
    PlacementDrive *drive = NULL;

    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            student = &students[i];
            break;
        }
    }

    for (int i = 0; i < driveCount; i++)
    {
        if (strcmp(drives[i].id, driveID) == 0)
        {
            drive = &drives[i];
            break;
        }
    }

    printf("\n========== Eligibility Result ==========\n");

    printf("Student ID       : %s\n", student->id);
    printf("Student Name     : %s\n", student->name);
    printf("Student CGPA     : %.2f\n", student->cgpa);
    printf("Student Backlogs : %d\n", student->backlogs);
    printf("Department       : %s\n", student->department);
    printf("Skills           : %s\n", student->skills);

    printf("\nDrive ID         : %s\n", drive->id);
    printf("Minimum CGPA     : %.2f\n", drive->minimumCGPA);
    printf("Maximum Backlogs : %d\n", drive->maximumBacklogs);
    printf("Departments      : %s\n", drive->eligibleDepartments);
    printf("Required Skills  : %s\n", drive->requiredSkills);

    printf("\n----------------------------------------\n");

    if (checkStudentEligibility(student, drive))
    {
        printf("RESULT: ELIGIBLE\n");
    }
    else
    {
        printf("RESULT: NOT ELIGIBLE\n");
    }

    printf("----------------------------------------\n");
}