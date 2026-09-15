#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/advanced_search.h"
#include "../include/constants.h"
#include "../include/student.h"
#include "../include/drive.h"
#include "../include/eligibility.h"
#include "../include/validation.h"
#include "../include/utils.h"

#define MAX_RECORDS 100


/*
 * Convert a string to lowercase.
 */
static void toLowerCase(char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}


/*
 * Check whether a student has a particular skill.
 *
 * Example:
 * Student skills: C, C++, Python
 *
 * Searching Python -> MATCH
 * Searching Java   -> NO MATCH
 */
static int studentHasSkill(
    const char *studentSkills,
    const char *searchSkill
)
{
    char skills[SKILL_LEN];
    char skill[NAME_LEN];
    char target[NAME_LEN];

    int i;
    int start;
    int end;
    int length;


    /*
     * Copy student's skills.
     */
    strncpy(
        skills,
        studentSkills,
        sizeof(skills) - 1
    );

    skills[sizeof(skills) - 1] = '\0';


    /*
     * Copy search skill.
     */
    strncpy(
        target,
        searchSkill,
        sizeof(target) - 1
    );

    target[sizeof(target) - 1] = '\0';

    toLowerCase(target);


    /*
     * Process comma-separated skills.
     */
    i = 0;

    while (skills[i] != '\0')
    {
        /*
         * Skip spaces and commas.
         */
        while (
            skills[i] == ' ' ||
            skills[i] == ','
        )
        {
            i++;
        }

        if (skills[i] == '\0')
        {
            break;
        }


        /*
         * Find start of current skill.
         */
        start = i;


        /*
         * Find end of current skill.
         */
        while (
            skills[i] != '\0' &&
            skills[i] != ','
        )
        {
            i++;
        }

        end = i - 1;


        /*
         * Remove trailing spaces.
         */
        while (
            end >= start &&
            skills[end] == ' '
        )
        {
            end--;
        }


        /*
         * Copy current skill.
         */
        if (end >= start)
        {
            length = end - start + 1;

            if (length >= NAME_LEN)
            {
                length = NAME_LEN - 1;
            }

            strncpy(
                skill,
                &skills[start],
                length
            );

            skill[length] = '\0';


            /*
             * Convert skill to lowercase.
             */
            toLowerCase(skill);


            /*
             * Compare complete skill.
             */
            if (strcmp(skill, target) == 0)
            {
                return 1;
            }
        }
    }

    return 0;
}


/*
 * Display student table heading.
 */
static void displayStudentHeading(void)
{
    printf("\n");

    printf(
        "%-10s %-20s %-12s %-8s %-10s %s\n",
        "ID",
        "Name",
        "Department",
        "CGPA",
        "Backlogs",
        "Skills"
    );

    printf(
        "-------------------------------------------------------------------------------\n"
    );
}


/*
 * Display one student.
 */
static void displayStudent(
    const Student *student
)
{
    printf(
        "%-10s %-20s %-12s %-8.2f %-10d %s\n",
        student->id,
        student->name,
        student->department,
        student->cgpa,
        student->backlogs,
        student->skills
    );
}


/*
 * ==================================================
 * OPTION 39
 * Search Students by Department
 * ==================================================
 */
void searchStudentsByDepartment(void)
{
    FILE *file;

    Student student;

    char department[DEPT_LEN];

    int found = 0;


    printf("\n");
    printf("====================================================\n");
    printf("          SEARCH STUDENTS BY DEPARTMENT\n");
    printf("====================================================\n");


    printf("\nEnter Department: ");

    fgets(
        department,
        sizeof(department),
        stdin
    );

    trimNewline(department);


    if (!isNonEmptyString(department))
    {
        printf("\nDepartment cannot be empty.\n");
        return;
    }


    /*
     * Convert search department to lowercase.
     */
    toLowerCase(department);


    file = fopen(STUDENT_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }


    printf(
        "\nStudents in Department: %s\n",
        department
    );

    displayStudentHeading();


    while (
        fread(
            &student,
            sizeof(Student),
            1,
            file
        ) == 1
    )
    {
        char studentDepartment[DEPT_LEN];


        strncpy(
            studentDepartment,
            student.department,
            sizeof(studentDepartment) - 1
        );

        studentDepartment[
            sizeof(studentDepartment) - 1
        ] = '\0';


        toLowerCase(studentDepartment);


        if (
            strcmp(
                studentDepartment,
                department
            ) == 0
        )
        {
            displayStudent(&student);

            found++;
        }
    }


    fclose(file);


    if (found == 0)
    {
        printf(
            "\nNo students found in this department.\n"
        );
    }
    else
    {
        printf(
            "\nTotal Students Found: %d\n",
            found
        );
    }
}


/*
 * ==================================================
 * OPTION 40
 * Filter Students by Minimum CGPA
 * ==================================================
 */
void filterStudentsByCGPA(void)
{
    FILE *file;

    Student student;

    float minimumCGPA;

    int found = 0;


    printf("\n");
    printf("====================================================\n");
    printf("          FILTER STUDENTS BY MINIMUM CGPA\n");
    printf("====================================================\n");


    printf("\nEnter Minimum CGPA: ");


    if (
        scanf(
            "%f",
            &minimumCGPA
        ) != 1
    )
    {
        printf("\nInvalid CGPA.\n");

        clearInputBuffer();

        return;
    }


    clearInputBuffer();


    if (!isValidCGPA(minimumCGPA))
    {
        printf(
            "\nCGPA must be between 0.00 and 10.00.\n"
        );

        return;
    }


    file = fopen(STUDENT_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }


    printf(
        "\nStudents with CGPA >= %.2f\n",
        minimumCGPA
    );

    displayStudentHeading();


    while (
        fread(
            &student,
            sizeof(Student),
            1,
            file
        ) == 1
    )
    {
        if (student.cgpa >= minimumCGPA)
        {
            displayStudent(&student);

            found++;
        }
    }


    fclose(file);


    if (found == 0)
    {
        printf(
            "\nNo students found with the given CGPA.\n"
        );
    }
    else
    {
        printf(
            "\nTotal Students Found: %d\n",
            found
        );
    }
}


/*
 * ==================================================
 * OPTION 41
 * Search Students by Skill
 * ==================================================
 */
void searchStudentsBySkill(void)
{
    FILE *file;

    Student student;

    char skill[NAME_LEN];

    int found = 0;


    printf("\n");
    printf("====================================================\n");
    printf("             SEARCH STUDENTS BY SKILL\n");
    printf("====================================================\n");


    printf("\nEnter Skill: ");


    fgets(
        skill,
        sizeof(skill),
        stdin
    );

    trimNewline(skill);


    if (!isNonEmptyString(skill))
    {
        printf("\nSkill cannot be empty.\n");
        return;
    }


    file = fopen(STUDENT_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }


    printf(
        "\nStudents with Skill: %s\n",
        skill
    );

    displayStudentHeading();


    while (
        fread(
            &student,
            sizeof(Student),
            1,
            file
        ) == 1
    )
    {
        if (
            studentHasSkill(
                student.skills,
                skill
            )
        )
        {
            displayStudent(&student);

            found++;
        }
    }


    fclose(file);


    if (found == 0)
    {
        printf(
            "\nNo students found with this skill.\n"
        );
    }
    else
    {
        printf(
            "\nTotal Students Found: %d\n",
            found
        );
    }
}


/*
 * ==================================================
 * OPTION 42
 * Find Eligible Students for a Drive
 * ==================================================
 */
void findEligibleStudentsForDrive(void)
{
    FILE *studentFile;
    FILE *driveFile;

    Student students[MAX_RECORDS];
    PlacementDrive drives[MAX_RECORDS];

    char driveID[ID_LEN];

    int studentCount;
    int driveCount;

    int driveIndex = -1;

    int found = 0;

    int i;


    printf("\n");
    printf("====================================================\n");
    printf("          FIND ELIGIBLE STUDENTS FOR DRIVE\n");
    printf("====================================================\n");


    printf("\nEnter Drive ID: ");


    fgets(
        driveID,
        sizeof(driveID),
        stdin
    );

    trimNewline(driveID);


    if (!isValidID(driveID))
    {
        printf("\nInvalid Drive ID.\n");
        return;
    }


    /*
     * Open placement drive file.
     */
    driveFile = fopen(DRIVE_FILE, "rb");

    if (driveFile == NULL)
    {
        printf(
            "\nNo placement drive records found.\n"
        );

        return;
    }


    /*
     * Read all drives.
     */
    driveCount = (int)fread(
        drives,
        sizeof(PlacementDrive),
        MAX_RECORDS,
        driveFile
    );

    fclose(driveFile);


    /*
     * Find requested drive.
     */
    for (i = 0; i < driveCount; i++)
    {
        if (
            strcmp(
                drives[i].id,
                driveID
            ) == 0
        )
        {
            driveIndex = i;
            break;
        }
    }


    if (driveIndex == -1)
    {
        printf(
            "\nPlacement Drive not found.\n"
        );

        return;
    }


    /*
     * Open student file.
     */
    studentFile = fopen(STUDENT_FILE, "rb");

    if (studentFile == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }


    /*
     * Read all students.
     */
    studentCount = (int)fread(
        students,
        sizeof(Student),
        MAX_RECORDS,
        studentFile
    );

    fclose(studentFile);


    /*
     * Display drive details.
     */
    printf("\n");
    printf(
        "---------------- DRIVE DETAILS --------------------\n"
    );


    printf(
        "\nDrive ID              : %s\n",
        drives[driveIndex].id
    );

    printf(
        "Company ID            : %s\n",
        drives[driveIndex].companyID
    );

    printf(
        "Drive Date            : %s\n",
        drives[driveIndex].driveDate
    );

    printf(
        "Minimum CGPA          : %.2f\n",
        drives[driveIndex].minimumCGPA
    );

    printf(
        "Maximum Backlogs      : %d\n",
        drives[driveIndex].maximumBacklogs
    );

    printf(
        "Eligible Departments  : %s\n",
        drives[driveIndex].eligibleDepartments
    );

    printf(
        "Required Skills       : %s\n",
        drives[driveIndex].requiredSkills
    );

    printf(
        "Status                : %s\n",
        drives[driveIndex].status
    );


    /*
     * Display eligible students.
     */
    printf("\n");
    printf(
        "--------------- ELIGIBLE STUDENTS ----------------\n"
    );


    displayStudentHeading();


    for (i = 0; i < studentCount; i++)
    {
        if (
            checkStudentEligibility(
                &students[i],
                &drives[driveIndex]
            )
        )
        {
            displayStudent(
                &students[i]
            );

            found++;
        }
    }


    if (found == 0)
    {
        printf(
            "\nNo eligible students found for this drive.\n"
        );
    }
    else
    {
        printf(
            "\nTotal Eligible Students: %d\n",
            found
        );
    }
}