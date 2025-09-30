#include "password.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int *randomKeyGenerator(int length)
{
    srand(time(NULL));
    int *key = (int *)calloc(length, sizeof(int));
    int i;
    for (i = 0; i < length; i++)
        key[i] = rand() % 127 + 1;

    return key;
}

int *randomShufflePatternGenerator(int length)
{
    int i, randomIndex, tempNumber;

    int *pattern = (int *)calloc(length, sizeof(int));
    for (i = 0; i < length; i++)
        pattern[i] = i;

    srand(time(NULL));
    for (i = 0; i < length; i++)
    {
        randomIndex = rand() % length;
        tempNumber = pattern[i];
        pattern[i] = pattern[randomIndex];
        pattern[randomIndex] = tempNumber;
    }
    return pattern;
}

char *strEncryption(int id, char *str, int *keyForID, int *shufflePattern)
{
    int length = strlen(str);

    char *encryptedStr = (char *)calloc(length + 1, sizeof(char));
    int i;
    for (i = 0; i < length; i++)
        encryptedStr[i] = str[i] ^ keyForID[i + 1];

    encryptedStr[length] = '\0';

    char *encryptedStrShuffled = (char *)calloc(length + 1, sizeof(char));

    for (i = 0; i < length; i++)
        encryptedStrShuffled[i] = encryptedStr[shufflePattern[i]];

    encryptedStrShuffled[length] = '\0';
    return encryptedStrShuffled;
}
