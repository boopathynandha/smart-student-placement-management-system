#ifndef ADMIN_H
#define ADMIN_H

#include "constants.h"

typedef struct
{
    char username[NAME_LEN];
    char password[NAME_LEN];

} Admin;

void setupAdmin(void);
int adminLogin(void);

#endif