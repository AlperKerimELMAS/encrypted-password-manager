#include "password.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *deshuffler(char *str, int length, int *shufflePattern)
{
    char *deshuffledStr = (char *)calloc(length + 1, sizeof(char));
    int i;
    for (i = 0; i < length; i++)
        deshuffledStr[shufflePattern[i]] = str[i];

    deshuffledStr[length] = '\0';
    return deshuffledStr;
}

char *strDecryption(int *key, int *shufflePattern, int id, char *str)
{
    int length = strlen(str);
    char *deshuffledStr = deshuffler(str, length, shufflePattern);

    char *decryptedStr = (char *)calloc(length + 1, sizeof(char));
    int i;

    for (i = 0; i < length; i++)
        decryptedStr[i] = deshuffledStr[i] ^ key[i + 1];

    decryptedStr[length] = '\0';
    return decryptedStr;
}