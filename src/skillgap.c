#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/skillgap.h"
#include "../include/student.h"
#include "../include/drive.h"
#include "../include/filehandler.h"
#include "../include/utils.h"

static void trimSpaces(char *str)
{
    char *start;
    char *end;

    if (str == NULL)
        return;

    start = str;

    while (isspace((unsigned char)*start))
        start++;

    if (start != str)
        memmove(str, start, strlen(start) + 1);

    if (*str == '\0')
        return;

    end = str + strlen(str) - 1;

    while (end >= str && isspace((unsigned char)*end))
    {
        *end = '\0';
        end--;
    }
}

static int skillExists(const char *skills, const char *target)
{
    char copy[SKILL_LEN];

    if (skills == NULL || target == NULL)
        return 0;

    strncpy(copy, skills, SKILL_LEN - 1);
    copy[SKILL_LEN - 1] = '\0';

    char *token = strtok(copy, ",");

    while (token != NULL)
    {
        trimSpaces(token);

        if (strcmp(token, target) == 0)
            return 1;

        token = strtok(NULL, ",");
    }

    return 0;
}

static int countSkills(const char *skills)
{
    char copy[SKILL_LEN];
    int count = 0;

    if (skills == NULL)
        return 0;

    strncpy(copy, skills, SKILL_LEN - 1);
    copy[SKILL_LEN - 1] = '\0';

    char *token = strtok(copy, ",");

    while (token != NULL)
    {
        trimSpaces(token);

        if (strlen(token) > 0)
            count++;

        token = strtok(NULL, ",");
    }

    return count;
}

static int findStudentIndex(
    Student *students,
    int studentCount,
    const char *studentID)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
            return i;
    }

    return -1;
}

static int findDriveIndex(
    PlacementDrive *drives,
    int driveCount,
    const char *driveID)
{
    for (int i = 0; i < driveCount; i++)
    {
        if (strcmp(drives[i].id, driveID) == 0)
            return i;
    }

    return -1;
}

void analyzeSkillGap(void)
{
    Student students[100];
    PlacementDrive drives[100];

    char studentID[ID_LEN];
    char driveID[ID_LEN];

    int studentCount;
    int driveCount;

    int studentIndex;
    int driveIndex;

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

    printf("\n========== Skill Gap Analyzer ==========\n");

    if (studentCount <= 0)
    {
        printf("\nNo students found.\n");
        return;
    }

    if (driveCount <= 0)
    {
        printf("\nNo placement drives found.\n");
        return;
    }

    printf("\nEnter Student ID: ");
    fgets(studentID, ID_LEN, stdin);
    trimNewline(studentID);

    studentIndex = findStudentIndex(
        students,
        studentCount,
        studentID
    );

    if (studentIndex == -1)
    {
        printf("\nStudent ID '%s' not found.\n", studentID);
        return;
    }

    printf("Enter Drive ID: ");
    fgets(driveID, ID_LEN, stdin);
    trimNewline(driveID);

    driveIndex = findDriveIndex(
        drives,
        driveCount,
        driveID
    );

    if (driveIndex == -1)
    {
        printf("\nDrive ID '%s' not found.\n", driveID);
        return;
    }

    printf("\n----------------------------------------\n");

    printf("Student ID       : %s\n",
           students[studentIndex].id);

    printf("Student Name     : %s\n",
           students[studentIndex].name);

    printf("Student Skills   : %s\n",
           students[studentIndex].skills);

    printf("\nDrive ID         : %s\n",
           drives[driveIndex].id);

    printf("Required Skills  : %s\n",
           drives[driveIndex].requiredSkills);

    printf("----------------------------------------\n");

    int totalRequiredSkills =
        countSkills(drives[driveIndex].requiredSkills);

    int matchedSkills = 0;
    int missingSkills = 0;

    /*
     * Display matched skills.
     * Manual comma processing is used here
     * to avoid nested strtok() problems.
     */

    char requiredCopy[SKILL_LEN];

    strncpy(
        requiredCopy,
        drives[driveIndex].requiredSkills,
        SKILL_LEN - 1
    );

    requiredCopy[SKILL_LEN - 1] = '\0';

    printf("\nMatched Skills:\n");

    char *start = requiredCopy;

    while (*start != '\0')
    {
        char *comma = strchr(start, ',');

        if (comma != NULL)
            *comma = '\0';

        trimSpaces(start);

        if (strlen(start) > 0)
        {
            if (skillExists(
                    students[studentIndex].skills,
                    start))
            {
                printf("  - %s\n", start);
                matchedSkills++;
            }
        }

        if (comma == NULL)
            break;

        start = comma + 1;
    }

    /*
     * Display missing skills.
     */

    char missingCopy[SKILL_LEN];

    strncpy(
        missingCopy,
        drives[driveIndex].requiredSkills,
        SKILL_LEN - 1
    );

    missingCopy[SKILL_LEN - 1] = '\0';

    printf("\nMissing Skills:\n");

    start = missingCopy;

    while (*start != '\0')
    {
        char *comma = strchr(start, ',');

        if (comma != NULL)
            *comma = '\0';

        trimSpaces(start);

        if (strlen(start) > 0)
        {
            if (!skillExists(
                    students[studentIndex].skills,
                    start))
            {
                printf("  - %s\n", start);
                missingSkills++;
            }
        }

        if (comma == NULL)
            break;

        start = comma + 1;
    }

    /*
     * Calculate percentage.
     */

    float matchPercentage = 0.0f;

    if (totalRequiredSkills > 0)
    {
        matchPercentage =
            ((float)matchedSkills /
             (float)totalRequiredSkills) * 100.0f;
    }

    printf("\n----------------------------------------\n");

    printf("Total Required Skills : %d\n",
           totalRequiredSkills);

    printf("Matched Skills        : %d\n",
           matchedSkills);

    printf("Missing Skills        : %d\n",
           missingSkills);

    printf("Skill Match           : %.2f%%\n",
           matchPercentage);

    /*
     * Determine status.
     */

    if (missingSkills == 0)
    {
        printf("Status                : FULLY MATCHED\n");
    }
    else if (matchPercentage >= 50.0f)
    {
        printf("Status                : NEEDS IMPROVEMENT\n");
    }
    else
    {
        printf("Status                : MAJOR SKILL GAP\n");
    }

    printf("----------------------------------------\n");
}