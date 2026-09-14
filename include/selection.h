#ifndef SELECTION_H
#define SELECTION_H

#include "constants.h"

typedef struct
{
    char id[ID_LEN];

    char applicationID[ID_LEN];
    char studentID[ID_LEN];
    char driveID[ID_LEN];

    int roundNumber;

    char roundName[NAME_LEN];
    char status[STATUS_LEN];
    char remarks[SKILL_LEN];

} Selection;


/* Selection Round management functions */

void addSelectionRound(void);
void viewSelectionRounds(void);
void searchSelectionRound(void);
void updateSelectionRound(void);
void deleteSelectionRound(void);


/* Duplicate Selection ID checking */

int isSelectionIDExists(const char *selectionID);

#endif