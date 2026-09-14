#ifndef DRIVE_H
#define DRIVE_H

#include "constants.h"

typedef struct {

    char id[ID_LEN];
    char companyID[ID_LEN];
    char driveDate[DATE_LEN];

    float minimumCGPA;
    int maximumBacklogs;

    char eligibleDepartments[DEPT_LEN];
    char requiredSkills[SKILL_LEN];

    char status[STATUS_LEN];

} PlacementDrive;


/* Placement Drive management functions */

void addDrive(void);
void viewDrives(void);
void searchDrive(void);
void updateDrive(void);
void deleteDrive(void);


/* Duplicate ID checking */

int isDriveIDExists(const char *driveID);

#endif