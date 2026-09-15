#include <stdio.h>
#include <string.h>

#include "../include/admin.h"
#include "../include/constants.h"
#include "../include/utils.h"


/*
 * Check whether an admin account already exists.
 */
static int adminExists(void)
{
    FILE *file;
    Admin admin;

    file = fopen(ADMIN_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    if (fread(&admin, sizeof(Admin), 1, file) == 1)
    {
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}


/*
 * Create the first admin account.
 */
void setupAdmin(void)
{
    Admin admin;
    FILE *file;

    if (adminExists())
    {
        return;
    }

    printf("\n");
    printf("====================================================\n");
    printf("              FIRST TIME ADMIN SETUP\n");
    printf("====================================================\n");

    do
    {
        printf("\nEnter Admin Username: ");

        fgets(admin.username, NAME_LEN, stdin);
        trimNewline(admin.username);

        if (strlen(admin.username) == 0)
        {
            printf("Username cannot be empty.\n");
        }

    } while (strlen(admin.username) == 0);


    do
    {
        printf("Enter Admin Password: ");

        fgets(admin.password, NAME_LEN, stdin);
        trimNewline(admin.password);

        if (strlen(admin.password) == 0)
        {
            printf("Password cannot be empty.\n");
        }

    } while (strlen(admin.password) == 0);


    file = fopen(ADMIN_FILE, "wb");

    if (file == NULL)
    {
        printf("\nFailed to create admin account.\n");
        return;
    }


    if (fwrite(&admin, sizeof(Admin), 1, file) != 1)
    {
        printf("\nFailed to save admin account.\n");

        fclose(file);

        return;
    }


    fclose(file);

    printf("\nAdmin account created successfully!\n");
}


/*
 * Admin Login
 *
 * Returns:
 * 1 - Login successful
 * 0 - Login failed
 */
int adminLogin(void)
{
    Admin admin;

    char username[NAME_LEN];
    char password[NAME_LEN];

    FILE *file;

    int attempts;


    file = fopen(ADMIN_FILE, "rb");

    if (file == NULL)
    {
        printf("\nAdmin account not found.\n");

        return 0;
    }


    if (fread(&admin, sizeof(Admin), 1, file) != 1)
    {
        fclose(file);

        printf("\nFailed to read admin account.\n");

        return 0;
    }

    fclose(file);


    /*
     * Allow maximum 3 login attempts.
     */
    for (attempts = 1; attempts <= 3; attempts++)
    {
        printf("\n");
        printf("====================================================\n");
        printf("                    ADMIN LOGIN\n");
        printf("====================================================\n");

        printf("\nUsername: ");

        fgets(username, NAME_LEN, stdin);
        trimNewline(username);


        printf("Password: ");

        fgets(password, NAME_LEN, stdin);
        trimNewline(password);


        /*
         * Check username and password.
         */
        if (strcmp(username, admin.username) == 0 &&
            strcmp(password, admin.password) == 0)
        {
            printf("\nLogin successful!\n");
            printf("Welcome, %s!\n", admin.username);

            return 1;
        }


        printf("\nInvalid username or password.\n");


        if (attempts < 3)
        {
            printf(
                "Attempts remaining: %d\n",
                3 - attempts
            );
        }
    }


    printf("\nMaximum login attempts exceeded.\n");
    printf("Access denied.\n");

    return 0;
}