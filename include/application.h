#ifndef APPLICATION_H
#define APPLICATION_H

#include "constants.h"

typedef struct
{
    char id[ID_LEN];
    char studentID[ID_LEN];
    char driveID[ID_LEN];

    char applicationDate[DATE_LEN];
    char status[STATUS_LEN];

} Application;


/* Student Application management functions */

void addApplication(void);
void viewApplications(void);
void searchApplication(void);
void updateApplication(void);
void deleteApplication(void);


/* Duplicate Application ID checking */

int isApplicationIDExists(const char *applicationID);


/* Duplicate Student + Drive application checking */

int isStudentAlreadyApplied(const char *studentID,
                            const char *driveID);

#endif