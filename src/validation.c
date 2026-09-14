#include <string.h>
#include <ctype.h>

#include "../include/validation.h"
#include "../include/constants.h"

/*
 * Checks whether a string is not NULL, not empty,
 * and contains at least one non-whitespace character.
 */
int isNonEmptyString(const char *str) {
    if (str == NULL) {
        return 0;
    }

    if (strlen(str) == 0) {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            return 1;
        }
    }

    return 0;
}

/*
 * Validates a person's name.
 * Only alphabets and spaces are allowed.
 * At least one alphabetic character must exist.
 */
int isValidName(const char *name) {
    if (!isNonEmptyString(name)) {
        return 0;
    }

    int hasLetter = 0;

    for (int i = 0; name[i] != '\0'; i++) {
        if (isalpha((unsigned char)name[i])) {
            hasLetter = 1;
        }
        else if (name[i] != ' ') {
            return 0;
        }
    }

    return hasLetter;
}

/*
 * Validates an ID.
 * ID must:
 * - not be empty
 * - contain no spaces
 * - be shorter than ID_LEN
 * - contain only letters, digits, '-' or '_'
 */
int isValidID(const char *id) {
    if (!isNonEmptyString(id)) {
        return 0;
    }

    if (strlen(id) >= ID_LEN) {
        return 0;
    }

    for (int i = 0; id[i] != '\0'; i++) {
        if (!isalnum((unsigned char)id[i]) &&
            id[i] != '-' &&
            id[i] != '_') {
            return 0;
        }
    }

    return 1;
}

/*
 * CGPA must be between 0.0 and 10.0.
 */
int isValidCGPA(float cgpa) {
    return (cgpa >= 0.0f && cgpa <= 10.0f);
}

/*
 * Backlogs must be between 0 and 50.
 */
int isValidBacklogs(int backlogs) {
    return (backlogs >= 0 && backlogs <= 50);
}