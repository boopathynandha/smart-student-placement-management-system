#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/matching.h"
#include "../include/student.h"
#include "../include/drive.h"
#include "../include/filehandler.h"
#include "../include/utils.h"
#include "../include/constants.h"

/*
 * Remove leading and trailing spaces.
 */
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

/*
 * Check whether a skill exists in a comma-separated
 * skill list.
 */
static int skillExists(
    const char *skills,
    const char *target)
{
    char copy[SKILL_LEN];

    if (skills == NULL || target == NULL)
        return 0;

    strncpy(copy, skills, SKILL_LEN - 1);
    copy[SKILL_LEN - 1] = '\0';

    char *start = copy;

    while (*start != '\0')
    {
        char *comma = strchr(start, ',');

        if (comma != NULL)
            *comma = '\0';

        trimSpaces(start);

        if (strcmp(start, target) == 0)
            return 1;

        if (comma == NULL)
            break;

        start = comma + 1;
    }

    return 0;
}

/*
 * Count total required skills in a comma-separated list.
 */
static int countSkills(const char *skills)
{
    char copy[SKILL_LEN];
    int count = 0;

    if (skills == NULL)
        return 0;

    strncpy(copy, skills, SKILL_LEN - 1);
    copy[SKILL_LEN - 1] = '\0';

    char *start = copy;

    while (*start != '\0')
    {
        char *comma = strchr(start, ',');

        if (comma != NULL)
            *comma = '\0';

        trimSpaces(start);

        if (strlen(start) > 0)
            count++;

        if (comma == NULL)
            break;

        start = comma + 1;
    }

    return count;
}

/*
 * Calculate how many required skills match
 * the student's skills.
 */
static int countMatchedSkills(
    const char *studentSkills,
    const char *requiredSkills)
{
    char copy[SKILL_LEN];
    int matched = 0;

    if (studentSkills == NULL || requiredSkills == NULL)
        return 0;

    strncpy(copy, requiredSkills, SKILL_LEN - 1);
    copy[SKILL_LEN - 1] = '\0';

    char *start = copy;

    while (*start != '\0')
    {
        char *comma = strchr(start, ',');

        if (comma != NULL)
            *comma = '\0';

        trimSpaces(start);

        if (strlen(start) > 0)
        {
            if (skillExists(studentSkills, start))
                matched++;
        }

        if (comma == NULL)
            break;

        start = comma + 1;
    }

    return matched;
}

/*
 * Find a student using Student ID.
 */
static int findStudent(
    Student *students,
    int count,
    const char *studentID)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
            return i;
    }

    return -1;
}

/*
 * Find a placement drive using Drive ID.
 */
static int findDrive(
    PlacementDrive *drives,
    int count,
    const char *driveID)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(drives[i].id, driveID) == 0)
            return i;
    }

    return -1;
}

/*
 * Main Company Matching / Recommendation function.
 */
void recommendCompany(void)
{
    Student students[100];
    PlacementDrive drives[100];

    char studentID[ID_LEN];
    char driveID[ID_LEN];

    int studentCount;
    int driveCount;

    int studentIndex;
    int driveIndex;

    /*
     * Read students and placement drives.
     */
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

    printf("\n========== Company Matching / Recommendation ==========\n");

    /*
     * Check whether students exist.
     */
    if (studentCount <= 0)
    {
        printf("\nNo students found.\n");
        return;
    }

    /*
     * Check whether placement drives exist.
     */
    if (driveCount <= 0)
    {
        printf("\nNo placement drives found.\n");
        return;
    }

    /*
     * Get Student ID.
     */
    printf("\nEnter Student ID: ");
    fgets(studentID, ID_LEN, stdin);
    trimNewline(studentID);

    studentIndex = findStudent(
        students,
        studentCount,
        studentID
    );

    if (studentIndex == -1)
    {
        printf("\nStudent ID '%s' not found.\n", studentID);
        return;
    }

    /*
     * Get Drive ID.
     */
    printf("Enter Drive ID: ");
    fgets(driveID, ID_LEN, stdin);
    trimNewline(driveID);

    driveIndex = findDrive(
        drives,
        driveCount,
        driveID
    );

    if (driveIndex == -1)
    {
        printf("\nDrive ID '%s' not found.\n", driveID);
        return;
    }

    Student *student = &students[studentIndex];
    PlacementDrive *drive = &drives[driveIndex];

    /*
     * Display student and drive details.
     */
    printf("\n----------------------------------------\n");

    printf("Student ID       : %s\n", student->id);
    printf("Student Name     : %s\n", student->name);
    printf("Student CGPA     : %.2f\n", student->cgpa);
    printf("Student Backlogs : %d\n", student->backlogs);
    printf("Student Dept     : %s\n", student->department);
    printf("Student Skills   : %s\n", student->skills);

    printf("\nDrive ID         : %s\n", drive->id);
    printf("Minimum CGPA     : %.2f\n", drive->minimumCGPA);
    printf("Maximum Backlogs : %d\n", drive->maximumBacklogs);
    printf("Eligible Dept    : %s\n", drive->eligibleDepartments);
    printf("Required Skills  : %s\n", drive->requiredSkills);

    printf("----------------------------------------\n");

    /*
     * Calculate individual matching criteria.
     */

    int cgpaMatch = 0;
    int backlogMatch = 0;
    int departmentMatch = 0;

    /*
     * CGPA Match
     */
    if (student->cgpa >= drive->minimumCGPA)
        cgpaMatch = 1;

    /*
     * Backlog Match
     */
    if (student->backlogs <= drive->maximumBacklogs)
        backlogMatch = 1;

    /*
     * Department Match
     *
     * The eligible department list may contain:
     * CSE, IT
     *
     * We check each department separately.
     */
    char departmentCopy[DEPT_LEN];

    strncpy(
        departmentCopy,
        drive->eligibleDepartments,
        DEPT_LEN - 1
    );

    departmentCopy[DEPT_LEN - 1] = '\0';

    char *departmentStart = departmentCopy;

    while (*departmentStart != '\0')
    {
        char *comma = strchr(departmentStart, ',');

        if (comma != NULL)
            *comma = '\0';

        trimSpaces(departmentStart);

        if (strcmp(
                departmentStart,
                student->department) == 0)
        {
            departmentMatch = 1;
            break;
        }

        if (comma == NULL)
            break;

        departmentStart = comma + 1;
    }

    /*
     * Skill Match
     */
    int totalRequiredSkills =
        countSkills(drive->requiredSkills);

    int matchedSkills =
        countMatchedSkills(
            student->skills,
            drive->requiredSkills
        );

    float skillMatchPercentage = 0.0f;

    if (totalRequiredSkills > 0)
    {
        skillMatchPercentage =
            ((float)matchedSkills /
             (float)totalRequiredSkills) * 100.0f;
    }

    /*
     * Calculate overall score.
     *
     * CGPA       = 25%
     * Backlogs   = 20%
     * Department = 20%
     * Skills     = 35%
     *
     * Total      = 100%
     */
    float cgpaScore = cgpaMatch ? 25.0f : 0.0f;
    float backlogScore = backlogMatch ? 20.0f : 0.0f;
    float departmentScore = departmentMatch ? 20.0f : 0.0f;
    float skillScore = skillMatchPercentage * 0.35f;

    float overallMatch =
        cgpaScore +
        backlogScore +
        departmentScore +
        skillScore;

    /*
     * Display matching details.
     */
    printf("\n========== Matching Analysis ==========\n");

    printf("\nCGPA Match        : %s\n",
           cgpaMatch ? "YES" : "NO");

    printf("Backlog Match     : %s\n",
           backlogMatch ? "YES" : "NO");

    printf("Department Match  : %s\n",
           departmentMatch ? "YES" : "NO");

    printf("Skill Match        : %.2f%%\n",
           skillMatchPercentage);

    printf("\n----------------------------------------\n");

    printf("CGPA Score        : %.2f / 25\n",
           cgpaScore);

    printf("Backlog Score     : %.2f / 20\n",
           backlogScore);

    printf("Department Score  : %.2f / 20\n",
           departmentScore);

    printf("Skill Score       : %.2f / 35\n",
           skillScore);

    printf("----------------------------------------\n");

    printf("Overall Match     : %.2f%%\n",
           overallMatch);

    /*
     * Recommendation.
     */
    printf("\nRecommendation    : ");

    if (!cgpaMatch ||
        !backlogMatch ||
        !departmentMatch)
    {
        printf("NOT ELIGIBLE\n");
    }
    else if (overallMatch >= 90.0f)
    {
        printf("HIGHLY RECOMMENDED\n");
    }
    else if (overallMatch >= 70.0f)
    {
        printf("RECOMMENDED\n");
    }
    else if (overallMatch >= 50.0f)
    {
        printf("CONSIDER IMPROVING SKILLS\n");
    }
    else
    {
        printf("LOW MATCH\n");
    }

    printf("----------------------------------------\n");
}