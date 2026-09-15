#include <stdio.h>
#include <string.h>

#include "../include/backup.h"
#include "../include/constants.h"


/*
 * Copy one binary file to another.
 *
 * Returns:
 * 1  - Success
 * 0  - Failure
 */
static int copyBinaryFile(
    const char *source,
    const char *destination
)
{
    FILE *sourceFile;
    FILE *destinationFile;

    unsigned char buffer[4096];

    size_t bytesRead;


    /*
     * Open source file in binary read mode.
     */
    sourceFile = fopen(source, "rb");

    if (sourceFile == NULL)
    {
        /*
         * Source file does not exist.
         * This is not treated as a fatal error
         * because some data files may not exist yet.
         */
        return 0;
    }


    /*
     * Open destination file in binary write mode.
     */
    destinationFile = fopen(destination, "wb");

    if (destinationFile == NULL)
    {
        fclose(sourceFile);
        return 0;
    }


    /*
     * Copy file in blocks.
     */
    while ((bytesRead = fread(
                buffer,
                1,
                sizeof(buffer),
                sourceFile)) > 0)
    {
        if (fwrite(
                buffer,
                1,
                bytesRead,
                destinationFile) != bytesRead)
        {
            fclose(sourceFile);
            fclose(destinationFile);

            return 0;
        }
    }


    /*
     * Check for read error.
     */
    if (ferror(sourceFile))
    {
        fclose(sourceFile);
        fclose(destinationFile);

        return 0;
    }


    /*
     * Close files.
     */
    fclose(sourceFile);
    fclose(destinationFile);

    return 1;
}


/*
 * Backup one data file.
 *
 * Displays whether the file exists and
 * whether the backup was successful.
 */
static void backupSingleFile(
    const char *source,
    const char *destination,
    const char *fileName
)
{
    if (copyBinaryFile(source, destination))
    {
        printf(
            "Backup successful : %s\n",
            fileName
        );
    }
    else
    {
        printf(
            "Backup skipped    : %s "
            "(file not found or copy failed)\n",
            fileName
        );
    }
}


/*
 * Restore one data file.
 */
static void restoreSingleFile(
    const char *source,
    const char *destination,
    const char *fileName
)
{
    if (copyBinaryFile(source, destination))
    {
        printf(
            "Restore successful : %s\n",
            fileName
        );
    }
    else
    {
        printf(
            "Restore skipped    : %s "
            "(backup file not found or copy failed)\n",
            fileName
        );
    }
}


/*
 * Backup Data
 *
 * Copies all existing binary data files
 * from the data folder to the backup folder.
 */
void backupData(void)
{
    printf("\n");
    printf("====================================================\n");
    printf("                 DATA BACKUP\n");
    printf("====================================================\n\n");


    /*
     * Backup student data.
     */
    backupSingleFile(
        STUDENT_FILE,
        "backup/students.dat",
        "students.dat"
    );


    /*
     * Backup company data.
     */
    backupSingleFile(
        COMPANY_FILE,
        "backup/companies.dat",
        "companies.dat"
    );


    /*
     * Backup placement drive data.
     */
    backupSingleFile(
        DRIVE_FILE,
        "backup/drives.dat",
        "drives.dat"
    );


    /*
     * Backup application data.
     */
    backupSingleFile(
        APPLICATION_FILE,
        "backup/applications.dat",
        "applications.dat"
    );


    /*
     * Backup selection data.
     */
    backupSingleFile(
        SELECTION_FILE,
        "backup/selections.dat",
        "selections.dat"
    );


    /*
     * Backup preparation data.
     */
    backupSingleFile(
        PREPARATION_FILE,
        "backup/preparation.dat",
        "preparation.dat"
    );


    /*
     * Backup admin data if it exists.
     */
    backupSingleFile(
        ADMIN_FILE,
        "backup/admin.dat",
        "admin.dat"
    );


    printf("\n");
    printf("Backup process completed.\n");
    printf("Backup location: backup/\n");
}


/*
 * Restore Data
 *
 * Copies backup files from the backup folder
 * back into the data folder.
 */
void restoreData(void)
{
    char confirmation;


    printf("\n");
    printf("====================================================\n");
    printf("                 DATA RESTORE\n");
    printf("====================================================\n");


    /*
     * Warning before restoring.
     */
    printf("\nWARNING!\n");
    printf(
        "Restoring data will replace the current "
        "data files.\n"
    );

    printf(
        "Do you want to continue? (Y/N): "
    );


    scanf(" %c", &confirmation);


    /*
     * Check confirmation.
     */
    if (confirmation != 'Y' && confirmation != 'y')
    {
        printf("\nRestore operation cancelled.\n");
        return;
    }


    printf("\n");


    /*
     * Restore student data.
     */
    restoreSingleFile(
        "backup/students.dat",
        STUDENT_FILE,
        "students.dat"
    );


    /*
     * Restore company data.
     */
    restoreSingleFile(
        "backup/companies.dat",
        COMPANY_FILE,
        "companies.dat"
    );


    /*
     * Restore placement drive data.
     */
    restoreSingleFile(
        "backup/drives.dat",
        DRIVE_FILE,
        "drives.dat"
    );


    /*
     * Restore application data.
     */
    restoreSingleFile(
        "backup/applications.dat",
        APPLICATION_FILE,
        "applications.dat"
    );


    /*
     * Restore selection data.
     */
    restoreSingleFile(
        "backup/selections.dat",
        SELECTION_FILE,
        "selections.dat"
    );


    /*
     * Restore preparation data.
     */
    restoreSingleFile(
        "backup/preparation.dat",
        PREPARATION_FILE,
        "preparation.dat"
    );


    /*
     * Restore admin data.
     */
    restoreSingleFile(
        "backup/admin.dat",
        ADMIN_FILE,
        "admin.dat"
    );


    printf("\n");
    printf("Restore process completed.\n");
    printf("Data restored from: backup/\n");
}