#include <stdio.h>
#include <stdlib.h>
#include "../include/filehandler.h"

/*
 * ensureFileExists:
 * Tries to open the file for reading ("rb" = read binary).
 * If that fails, the file doesn't exist yet, so we create it by
 * opening in "ab" (append binary) mode, which creates an empty file
 * if none exists, then immediately close it.
 */
int ensureFileExists(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp != NULL) {
        fclose(fp);
        return 1; /* already exists */
    }

    fp = fopen(filename, "ab");
    if (fp == NULL) {
        printf("ERROR: Could not create file '%s'\n", filename);
        return 0;
    }
    fclose(fp);
    return 1;
}

/*
 * appendRecord:
 * Opens the file in "ab" (append binary) mode - this always writes
 * at the END of the file, never overwriting existing data.
 * fwrite(pointer, sizeOfOneItem, howManyItems, filePointer)
 */
int appendRecord(const char *filename, const void *record, size_t recordSize) {
    FILE *fp = fopen(filename, "ab");
    if (fp == NULL) {
        printf("ERROR: Could not open file '%s' for writing\n", filename);
        return 0;
    }

    size_t written = fwrite(record, recordSize, 1, fp);
    fclose(fp);

    if (written != 1) {
        printf("ERROR: Failed to write record to '%s'\n", filename);
        return 0;
    }
    return 1;
}

/*
 * readAllRecords:
 * Opens the file in "rb" (read binary) mode and reads records one
 * after another into the buffer array until either the file ends
 * or the buffer is full (maxRecords reached).
 *
 * IMPORTANT: 'buffer' must already point to enough memory to hold
 * maxRecords items of size recordSize (the CALLER allocates this).
 */
int readAllRecords(const char *filename, void *buffer, size_t recordSize, int maxRecords) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        /* File not existing yet just means "0 records", not an error */
        return 0;
    }

    int count = 0;
    /* We advance the buffer pointer manually using byte arithmetic.
       (char *) casts buffer to a byte-sized pointer so "+ recordSize"
       moves forward by the correct number of bytes each time. */
    char *bufPtr = (char *) buffer;

    while (count < maxRecords &&
           fread(bufPtr + ((size_t)count * recordSize), recordSize, 1, fp) == 1) {
        count++;
    }

    fclose(fp);
    return count;
}

/*
 * countRecords:
 * Uses fseek/ftell to measure the file's total byte size, then
 * divides by recordSize to know how many whole records fit.
 */
long countRecords(const char *filename, size_t recordSize) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return 0;
    }

    fseek(fp, 0, SEEK_END);   /* jump to end of file */
    long fileSize = ftell(fp); /* get current position = total bytes */
    fclose(fp);

    if (recordSize == 0) {
        return 0;
    }
    return fileSize / (long)recordSize;
}

/*
 * overwriteRecordAt:
 * Opens file in "r+b" (read/write binary, file must already exist).
 * fseek() jumps to the exact byte position of the record we want to
 * replace: index * recordSize bytes from the start (SEEK_SET).
 * Then fwrite() overwrites just that one record's bytes.
 */
int overwriteRecordAt(const char *filename, const void *record, size_t recordSize, long index) {
    FILE *fp = fopen(filename, "r+b");
    if (fp == NULL) {
        printf("ERROR: Could not open file '%s' for updating\n", filename);
        return 0;
    }

    long offset = index * (long)recordSize;
    if (fseek(fp, offset, SEEK_SET) != 0) {
        printf("ERROR: Could not seek to record position\n");
        fclose(fp);
        return 0;
    }

    size_t written = fwrite(record, recordSize, 1, fp);
    fclose(fp);

    if (written != 1) {
        printf("ERROR: Failed to overwrite record\n");
        return 0;
    }
    return 1;
}

/*
 * rewriteAllRecords:
 * Opens file in "wb" (write binary) mode, which ERASES the existing
 * file content and starts fresh. Then writes 'count' records from
 * the buffer array. Used mainly for Delete operations: we load
 * everything into memory, skip the one to delete, then save the rest.
 */
int rewriteAllRecords(const char *filename, const void *buffer, size_t recordSize, int count) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("ERROR: Could not open file '%s' for rewriting\n", filename);
        return 0;
    }

    if (count > 0) {
        size_t written = fwrite(buffer, recordSize, (size_t)count, fp);
        if (written != (size_t)count) {
            printf("ERROR: Failed to rewrite all records\n");
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}
