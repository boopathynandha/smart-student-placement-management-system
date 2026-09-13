#ifndef UTILS_H
#define UTILS_H

/*
 * trimNewline:
 * When you read a line using fgets(), it often keeps the trailing '\n'
 * character. This function removes it in-place.
 */
void trimNewline(char *str);

/*
 * clearInputBuffer:
 * After reading a number with scanf(), leftover characters (like the
 * Enter key) remain in the input buffer and mess up the next fgets().
 * This function flushes them out.
 */
void clearInputBuffer(void);

#endif /* UTILS_H */
