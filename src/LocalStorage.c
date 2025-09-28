#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.h"

char *writeArray(int *array, int length) //  They will be written as characters locally
{
    char *string = (char *)malloc(sizeof(char) * (length + 3));
    string[0] = '[';
    int i;

    for (i = 0; i < length + 1; i++)
        string[i + 1] = (char)array[i];

    string[length + 1] = ']';
    string[length + 2] = '\0';
    return string;
}

int *readArray(char *array, int length) // To obtain actual form of key and pattern
{
    int *originalArray = (int *)malloc(sizeof(int) * length);
    int i;
    for (i = 0; i < length; i++)
        originalArray[i] = (int)array[i + 1];

    return originalArray;
}

void readData(struct passwordLog **firstLog, char *path) // to update database when the program starts
{

    FILE *fPtr = fopen(path, "r");
    int id;
    char siteName[10];
    char siteURL[30];
    char encryptedUsername[30];
    char encryptedPassword[30];
    char keyForIDWritten[30];
    char shufflePatternWritten[30];
    int *keyForID;
    int *shufflePattern;
    if (fPtr != NULL)
    {
        while (!feof(fPtr))
        {
            fscanf(fPtr, "%d - %s(%s) - %s - %s - %s - %s", &id, siteName, siteURL, encryptedUsername, encryptedPassword, keyForIDWritten, shufflePatternWritten);
            keyForID = readArray(keyForIDWritten, strlen(encryptedPassword));
            shufflePattern = readArray(shufflePatternWritten, strlen(encryptedPassword));
            insert(*firstLog, id, siteName, siteURL, encryptedUsername, encryptedPassword, keyForID, shufflePattern);
        }

        fclose(fPtr);
    }
    else
        puts("readData failed!");
}

void writeData(char *path, struct passwordLog *firstLog)
{
    FILE *fPtr = fopen(path, "a");
    int length;

    if (fPtr != NULL)
    {
        while (firstLog != NULL)
        {
            length = strlen(firstLog->encryptedPassword);
            fprintf(fPtr, "%d - %s(%s) - %s - %s - %s - %s\n", firstLog->id, firstLog->siteName, firstLog->siteURL, firstLog->encryptedUsername, firstLog->encryptedPassword, writeArray(firstLog->keyForID, length), writeArray(firstLog->shufflePattern, length));
            firstLog = firstLog->nextLog;
        }
        fclose(fPtr);
    }

    else
        puts("writeData failed!");
}