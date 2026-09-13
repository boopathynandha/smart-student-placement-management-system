#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stddef.h>  /* for size_t */

/*
 * These functions are GENERIC: they don't know or care whether you're
 * saving a Student, a Company, or anything else. They just work with
 * raw bytes ("void *"), as long as you tell them how big one record is
 * (recordSize). This means Phase 3 (student.c), Phase 4 (company.c),
 * etc. can all reuse this SAME code instead of duplicating file logic.
 *
 * Every function returns:
 *   1 (success) or 0 (failure) for actions,
 *   or a count/number for query-type functions.
 */

/* Ensures the data file exists (creates an empty one if missing). */
int ensureFileExists(const char *filename);

/* Appends one record to the end of the file. */
int appendRecord(const char *filename, const void *record, size_t recordSize);

/* Reads ALL records from the file into a pre-allocated buffer array.
 * 'maxRecords' is the buffer's capacity (to prevent overflow).
 * Returns the actual number of records read. */
int readAllRecords(const char *filename, void *buffer, size_t recordSize, int maxRecords);

/* Returns how many records currently exist in the file. */
long countRecords(const char *filename, size_t recordSize);

/* Overwrites the record at a specific position (0-based index) with
 * new data. Used for "Update" operations. Returns 1 on success. */
int overwriteRecordAt(const char *filename, const void *record, size_t recordSize, long index);

/* Rewrites the ENTIRE file from a buffer array. Used after deleting
 * a record (we filter it out, then save everything else back). */
int rewriteAllRecords(const char *filename, const void *buffer, size_t recordSize, int count);

#endif /* FILEHANDLER_H */
