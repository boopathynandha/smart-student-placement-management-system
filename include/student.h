#ifndef STUDENT_H
#define STUDENT_H

#include "constants.h"

typedef struct {
    char id[ID_LEN];
    char name[NAME_LEN];
    char department[DEPT_LEN];
    float cgpa;
    int backlogs;
    char skills[SKILL_LEN];
} Student;


/* Student management functions */

void addStudent(void);
void viewStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);


/* Duplicate ID checking */

int isStudentIDExists(const char *studentID);

#endif