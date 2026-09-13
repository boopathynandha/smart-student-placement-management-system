#include <string.h>
#include <ctype.h>
#include "../include/validation.h"

/*
 * isNonEmptyString:
 * Checks the string is not NULL and not just empty/whitespace.
 * Used as a building block by other validators.
 */
int isNonEmptyString(const char *str) {
    if (str == NULL) {
        return 0;
    }
    /* strlen() counts characters until it hits '\0' (the null terminator
       every C string ends with). If length is 0, string is empty. */
    if (strlen(str) == 0) {
        return 0;
    }
    return 1;
}

/*
 * isValidName:
 * Name must be non-empty and contain only letters and spaces.
 */
int isValidName(const char *name) {
    if (!isNonEmptyString(name)) {
        return 0;
    }

    for (int i = 0; name[i] != '\0'; i++) {
        /* isalpha() checks if a character is a letter (A-Z, a-z) */
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

/*
 * isValidID:
 * ID must be non-empty and have no spaces (IDs are single tokens like "STU1001").
 */
int isValidID(const char *id) {
    if (!isNonEmptyString(id)) {
        return 0;
    }

    for (int i = 0; id[i] != '\0'; i++) {
        if (isspace((unsigned char)id[i])) {
            return 0;
        }
    }
    return 1;
}

/*
 * isValidCGPA:
 * CGPA must realistically be between 0.0 and 10.0 (common Indian grading scale).
 */
int isValidCGPA(float cgpa) {
    return (cgpa >= 0.0f && cgpa <= 10.0f);
}

/*
 * isValidBacklogs:
 * Backlogs cannot be negative, and a sane upper limit avoids typos (e.g. 999).
 */
int isValidBacklogs(int backlogs) {
    return (backlogs >= 0 && backlogs <= 50);
}
