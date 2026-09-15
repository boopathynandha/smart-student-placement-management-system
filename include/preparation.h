#ifndef PREPARATION_H
#define PREPARATION_H

#include "constants.h"

typedef struct
{
    char id[ID_LEN];

    char studentID[ID_LEN];

    char skill[NAME_LEN];

    int target;

    int completed;

    char status[STATUS_LEN];

    char remarks[SKILL_LEN];

} Preparation;


/*
 * Placement Preparation Tracker
 */

void addPreparation(void);

void viewPreparations(void);

void searchPreparation(void);

void updatePreparation(void);

void deletePreparation(void);

int isPreparationIDExists(const char *preparationID);

#endif