#ifndef VALIDATION_H
#define VALIDATION_H

/*
 * All validation functions return 1 (TRUE) if the input is VALID,
 * and 0 (FALSE) if the input is INVALID.
 * This consistent convention makes them easy to use in "if" checks.
 */

int isValidName(const char *name);
int isValidID(const char *id);
int isValidCGPA(float cgpa);
int isValidBacklogs(int backlogs);
int isNonEmptyString(const char *str);

#endif /* VALIDATION_H */
