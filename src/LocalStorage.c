#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.h"

int numberOfLogs = 0;
int numberOfWritten = 0;

char *writeArray(int *array, int length)
{
    char *string = (char *)malloc(sizeof(char) * (length + 3));
    if (string == NULL)
    {
        puts("Memory allocation failed!");
        return NULL;
    }

    string[0] = '[';
    int i;

    for (i = 0; i < length; i++)
        string[i + 1] = (char)array[i];

    string[length + 1] = ']';
    string[length + 2] = '\0';
    return string;
}

int *readArray(char *array, int length)
{
    int *originalArray = (int *)malloc(sizeof(int) * length);
    if (originalArray == NULL)
    {
        puts("Memory allocation failed!");
        return NULL;
    }
    int i;
    for (i = 0; i < length; i++)
        originalArray[i] = (int)(unsigned char)array[i + 1];

    return originalArray;
}

void readData(struct passwordLog **firstLog, const char *path)
{
    FILE *fPtr = fopen(path, "r");
    if (fPtr == NULL)
    {
        puts("First installation mode activated - no password logs found!\n");
        numberOfLogs = 10;
        return;
    }
    int id;
    char siteName[10];
    char siteURL[30];
    char encryptedUsername[30];
    char encryptedPassword[30];
    char keyForIDWritten[35];
    char shufflePatternWritten[35];
    int *keyForID;
    int *shufflePattern;
    while (1)
    {
        int fetch = fscanf(fPtr, "%d - %s(%s) - %s - %s - %s - %s", &id, siteName, siteURL, encryptedUsername, encryptedPassword, keyForIDWritten, shufflePatternWritten);
        if (fetch != 7 || fetch == EOF)
            break;
        keyForID = readArray(keyForIDWritten, strlen(encryptedPassword));
        shufflePattern = readArray(shufflePatternWritten, strlen(encryptedPassword));
        insert(firstLog, id, siteName, siteURL, encryptedUsername, encryptedPassword, keyForID, shufflePattern);
        numberOfLogs++;
    }

    fclose(fPtr);
    printf("%d password logs are loaded!", numberOfLogs);
}

void writeData(char *path, struct passwordLog *firstLog)
{
    FILE *fPtr = fopen(path, "w");
    int length;

    if (fPtr != NULL)
    {
        while (firstLog != NULL)
        {
            length = strlen(firstLog->encryptedPassword);
            fprintf(fPtr, "%d - %s(%s) - %s - %s - %s - %s\n", firstLog->id, firstLog->siteName, firstLog->siteURL, firstLog->encryptedUsername, firstLog->encryptedPassword, writeArray(firstLog->keyForID, length), writeArray(firstLog->shufflePattern, length));
            firstLog = firstLog->nextLog;
            numberOfWritten++;
        }
        fclose(fPtr);
        print("%d logs successfully written to %s file", numberOfWritten, path);
    }

    else
        puts("writeData failed!");
}