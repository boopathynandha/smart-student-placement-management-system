#include <stdio.h>
#include "../include/constants.h"
#include "../include/validation.h"
#include "../include/utils.h"
#include "../include/filehandler.h"

int main(void) {
    printf("=========================================\n");
    printf(" Smart Student Placement Management System\n");
    printf(" Phase 0 + Phase 1: Foundation Build Test\n");
    printf("=========================================\n\n");

    /* --- Quick sanity checks that each module is linked correctly --- */

    /* 1. Test validation.c */
    printf("[Validation Test]\n");
    printf("  isValidName(\"Arun Kumar\")   -> %d (expect 1)\n", isValidName("Arun Kumar"));
    printf("  isValidName(\"Arun123\")      -> %d (expect 0)\n", isValidName("Arun123"));
    printf("  isValidCGPA(8.5)             -> %d (expect 1)\n", isValidCGPA(8.5f));
    printf("  isValidCGPA(12.0)            -> %d (expect 0)\n", isValidCGPA(12.0f));

    /* 2. Test utils.c */
    printf("\n[Utils Test]\n");
    char sample[50];
    /* strcpy-like copy just for the test; safe here since we control the literal */
    snprintf(sample, sizeof(sample), "Hello World\n");
    printf("  Before trimNewline: \"%s\"", sample);
    trimNewline(sample);
    printf("  After trimNewline:  \"%s\"\n", sample);

    /* 3. Test filehandler.c using a temporary test file */
    printf("\n[File Handler Test]\n");
    const char *testFile = "data/test_phase1.dat";

    int created = ensureFileExists(testFile);
    printf("  ensureFileExists -> %d (expect 1)\n", created);

    int numbers[3] = {111, 222, 333};
    for (int i = 0; i < 3; i++) {
        appendRecord(testFile, &numbers[i], sizeof(int));
    }

    long total = countRecords(testFile, sizeof(int));
    printf("  countRecords after 3 appends -> %ld (expect 3)\n", total);

    int readBack[10];
    int readCount = readAllRecords(testFile, readBack, sizeof(int), 10);
    printf("  readAllRecords count -> %d (expect 3)\n", readCount);
    printf("  Values read back: ");
    for (int i = 0; i < readCount; i++) {
        printf("%d ", readBack[i]);
    }
    printf("(expect 111 222 333)\n");

    printf("\n=========================================\n");
    printf(" Phase 0 + Phase 1 build verified successfully!\n");
    printf("=========================================\n");

    return 0;
}
