#include <stdio.h>
#include <stdlib.h>
#include "password.h"

char *passwordGenerator(int passwordGenerationFeatures[])
{
    int charType;
    int length = passwordGenerationFeatures[0];
    int qDigit = passwordGenerationFeatures[1];
    int qLetter = passwordGenerationFeatures[2];
    int qSpecialChar = passwordGenerationFeatures[3];
    int qLowercase = passwordGenerationFeatures[4];
    int qUpperCase = passwordGenerationFeatures[5];

    if (length <= 0 || length > 30)
    {
        printf("Length is invalid, 1-30 number of characters are supported!\n");
        return NULL;
    }
    if (!(qDigit || qLetter || qSpecialChar))
    {
        printf("At least one character type must be selected!\n");
        return NULL;
    }
    if (!qLetter || qUpperCase || qLowercase == 0)
    {
        qUpperCase = 1;
        qLowercase = 1;
    }

    char *generatedPassword = (char *)calloc(length + 1, sizeof(char));
    if (generatedPassword == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int i = 0;
    int charType = 0;
    char newChar = 0;

    while (i < length)
    {
        charType = rand() % 4;

        switch (charType)
        {
        case 0:
            if (qDigit)
                newChar = (char)(rand() % 10 + 48);
            break;
        case 1:
            if (qLetter && qLowercase)
                newChar = (char)(rand() % 26 + 97);
            break;
        case 2:
            if (qLetter && qUpperCase)
                newChar = (char)(rand() % 26 + 65);
            break;
        case 3:
            if (qSpecialChar)
                newChar = (char)(rand() % 15 + 33);
            break;
        }
        if (newChar != 0)
        {
            generatedPassword[i] = newChar;
            i++;
        }
    }
    generatedPassword[length] = '\0';
    return generatedPassword;
}

char *passwordGeneratorRecommended()
{

    int length = 15;
    char *generatedPassword = (char *)calloc(length + 1, sizeof(char));
    if (generatedPassword == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    int i;
    int charType;
    for (i = 0; i < length; i++)
    {
        charType = rand() % 4;

        switch (charType)
        {
        case 0:
            generatedPassword[i] = (char)(rand() % 10 + 48);
            break;
        case 1:
            generatedPassword[i] = (char)(rand() % 26 + 97);
            break;
        case 2:
            generatedPassword[i] = (char)(rand() % 26 + 65);
            break;
        case 3:
            generatedPassword[i] = (char)(rand() % 15 + 33);
            break;
        }
    }
    generatedPassword[length] = '\0';
    return generatedPassword;
}
