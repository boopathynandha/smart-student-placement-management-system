#include <string.h>
#include <stdio.h>
#include "../include/utils.h"

/*
 * trimNewline:
 * strcspn(str, "\n") returns the index of the FIRST '\n' character found.
 * We overwrite that position with '\0' to cut the string short there.
 */
void trimNewline(char *str) {
    if (str == NULL) {
        return;
    }
    str[strcspn(str, "\n")] = '\0';
}

/*
 * clearInputBuffer:
 * Reads and discards characters one by one until it hits a newline
 * or end-of-file. This "cleans up" after scanf() so the next fgets()
 * doesn't accidentally read a leftover '\n'.
 */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard character */
    }
}
