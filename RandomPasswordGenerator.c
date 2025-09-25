#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *passwordGenerator(int passwordGenerationFeatures[])
{
    int length = passwordGenerationFeatures[0];
    int qDigit = passwordGenerationFeatures[1];
    int qLetter = passwordGenerationFeatures[2];
    int qSpecialChar = passwordGenerationFeatures[3];
    int qLowercase = passwordGenerationFeatures[4];
    int qUpperCase = passwordGenerationFeatures[5];

    char randDigit, randSpecialChar, randLowercase, randUppercase;

    char *generatedPassword = (char *)calloc(length, sizeof(char));
    int i;

    // if the letter is selected, lowercase and uppercase shouldn't be asked. also, there is no randLetter, it is either lower or upper
    for (i = 0; i < length; i++)
    {

        randDigit = (char)(rand() % 10);
        randSpecialChar = (char)(rand() % 15 + 33);
        randLowercase = (char)(rand() % 26 + 97);
        randUppercase = (char)(rand() % 26 + 65);
    }
}

char *passwordGeneratorRecommended()
{

    int length = 15;
    int i;
    int charType;
    char *generatedPassword = (char *)calloc(length + 1, sizeof(char));

    for (i = 0; i < length; i++)
    {
        charType = rand() % 4 + 1;

        switch (charType)
        {
        case 1:
            generatedPassword[i] = (char)(rand() % 10 + 48); // Digit
            break;
        case 2:
            generatedPassword[i] = (char)(rand() % 26 + 97); // Lowercase
            break;
        case 3:
            generatedPassword[i] = (char)(rand() % 26 + 65); // Uppercase
            break;
        case 4:
            generatedPassword[i] = (char)(rand() % 15 + 33); // SpecialChar
            break;
        }
    }
    generatedPassword[length] = '\0';
    return generatedPassword;
}
