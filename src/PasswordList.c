// isEmpty control for delete and print functions are left to main.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.h"

void insert(struct passwordLog **firstLog, int id, char *siteName, char *siteURL, char *encryptedUsername, char *encryptedPassword, int *keyForID, int *shufflePattern)
{
    struct passwordLog *newLog = (struct passwordLog *)malloc(sizeof(struct passwordLog));
    if (newLog != NULL)
    {
        newLog->id = id;
        strcpy(newLog->siteName, siteName);
        strcpy(newLog->siteURL, siteURL);
        strcpy(newLog->encryptedUsername, encryptedUsername);
        strcpy(newLog->encryptedPassword, encryptedPassword);
        newLog->keyForID = keyForID;
        newLog->shufflePattern = shufflePattern;
        newLog->nextLog = NULL;

        struct passwordLog *previousLog = NULL;
        struct passwordLog *currentLog = *firstLog;

        while (currentLog != NULL && strcmp(siteName, currentLog->siteName) > 0)
        {
            previousLog = currentLog;
            currentLog = currentLog->nextLog;
        }

        if (previousLog == NULL)
        {
            newLog->nextLog = *firstLog;
            *firstLog = newLog;
        }
        else
        {
            previousLog->nextLog = newLog;
            newLog->nextLog = currentLog;
        }
    }
    else
        puts("Memory allocation failed, no memory available.");
}

void delete(struct passwordLog **firstLog, int id)
{
    if ((*firstLog)->id == id)
    {
        struct passwordLog *temp = *firstLog;
        *firstLog = (*firstLog)->nextLog;
        free(temp);
    }

    else
    {
        struct passwordLog *previousLog = *firstLog;
        struct passwordLog *currentLog = (*firstLog)->nextLog;

        while (currentLog != NULL && currentLog->id != id)
        {
            previousLog = currentLog;
            currentLog = currentLog->nextLog;
        }

        if (currentLog == NULL)
        {
            puts("The given site name is not on the Password Manager.");
            return;
        }

        else
        {
            previousLog->nextLog = currentLog->nextLog;
            free(currentLog);
        }
    }

    printf("Log is deleted from the Password Manager.");
}

void printRequestedLog(struct passwordLog *firstLog, char *siteName)
{
    while (firstLog != NULL)
    {
        if (strcmp(firstLog->siteName, siteName) == 0)
            break;

        firstLog = firstLog->nextLog;
    }

    if (firstLog != NULL)
    {
        printf("%-20s (%s)%-20s%-20s\n", "Site Name", "Site URL", "Username (Encrypted)", "Password (Encrypted)");
        printf("%-20s (%s)%-20s%-20s\n", firstLog->siteName, firstLog->siteURL, firstLog->encryptedUsername, firstLog->encryptedPassword);
    }
    else
        puts("The given site is not on the list.\n");
}

void printWholeLogAdmin(struct passwordLog *firstLog)
{
    printf("%30s\n", "All Password Log (ADMIN ACCESS)");
    printf("-----------------------------------\n");
    printf("%-20s (%s)%-20s%-20s\n", "Site Name", "Site URL", "Username (Encrypted)", "Password (Encrypted)");

    while (firstLog != NULL)
    {
        printf("%-20s (%s)%-20s%-20s\n", firstLog->siteName, firstLog->siteURL, firstLog->encryptedUsername, firstLog->encryptedPassword);
        firstLog = firstLog->nextLog;
    }
    printf("-----------------------------------\n");
}

int isEmpty(struct passwordLog *firstLog)
{
    return firstLog == NULL;
}