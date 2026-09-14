#ifndef COMPANY_H
#define COMPANY_H

#include "constants.h"

typedef struct {

    char id[ID_LEN];
    char name[NAME_LEN];
    char location[NAME_LEN];
    char role[NAME_LEN];

    float minimumCGPA;
    int maximumBacklogs;

    char requiredSkills[SKILL_LEN];

} Company;


/* Company management functions */

void addCompany(void);
void viewCompanies(void);
void searchCompany(void);
void updateCompany(void);
void deleteCompany(void);


/* Duplicate ID checking */

int isCompanyIDExists(const char *companyID);

#endif