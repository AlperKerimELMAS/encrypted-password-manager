// id structure is an obligation for multi-account. PasswordList should be updated, the struct as well.

#include "encryption.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// These keys and shufflePattern should be stored in an array or linked list!
// key[0] stores id for sitename

char *randomKeyGenerator(int id, int length)
{
    srand(time(NULL));
    char *key = (char *)calloc(length + 1, sizeof(char));
    key[0] = id;

    int i;
    for (i = 1; i < length + 1; i++)
        key[i] = rand() % 127 + 1;

    return key;
}

int *randomShufflePatternGenerator(int length)
{
    int i;
    int randomIndex;
    int tempNumber;

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

char *strEncryption(int key, int id, char *str)
{
    int length = strlen(str);
    char *keyForID = randomKeyGenerator(id, length);

    char *encryptedStr = (char *)calloc(length + 1, sizeof(char));
    int i;
    for (i = 0; i < length; i++)
        encryptedStr[i] = str[i] ^ keyForID[i + 1];

    encryptedStr[length] = '\0';

    char *encryptedStrShuffled = (char *)calloc(length + 1, sizeof(char));

    int *shufflePattern = randomShufflePatternGenerator(length);
    for (i = 0; i < length; i++)
        encryptedStrShuffled[i] = encryptedStr[shufflePattern[i]];

    encryptedStrShuffled[length] = '\0';
    return encryptedStrShuffled;
}
