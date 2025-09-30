#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "password.h"

void mainMenu();
void passwordGenerationMenu();
void clearScanf();
void clearList(struct passwordLog *firstLog);

int main(void)
{
    srand(time(NULL));

    struct passwordLog *firstLog = NULL;
    readData(&firstLog, "passwordLog.txt");
    int id = numberOfLogs + 1;
    char siteName[10];
    char siteURL[30];
    char username[30];
    char password[30];

    char encryptedPassword[30];

    int mainMenuChoice;
    int passwordMenuChoice;
    char siteChoice[10];
    int passwordGenerationChoice;
    int passwordGenerationFeatures[6] = {0};
    char *passwordFeatureNames[6] = {"Length? ", "Digits included? ", "Letters included? ",
                                     "Special Character included? ", "Lowercase characters included? ", "Uppercase characters included? "};

    printf("%50s\n", "Local Encrypted Password Manager");
    mainMenu();

    printf("Choice input: ");
    scanf("%d", &mainMenuChoice);
    clearScanf();

    while (mainMenuChoice != 5)
    {
        switch (mainMenuChoice)
        {
        case 1:
            printf("Enter the name of the site: ");
            scanf("%9s", siteName);
            clearScanf();

            printf("Enter the URL of the site: ");
            scanf("%29s", siteURL);
            clearScanf();

            printf("Enter the username:");
            scanf("%29s", username);
            clearScanf();

            printf("Enter the password: ");
            scanf("%29s", password);
            clearScanf();

            int *keyForID = randomKeyGenerator(strlen(password));
            int *shufflePattern = randomShufflePatternGenerator(strlen(password));

            strcpy(encryptedPassword, strEncryption(id, password, keyForID, shufflePattern));

            insert(&firstLog, id, siteName, siteURL, username, encryptedPassword, keyForID, shufflePattern);
            writeData("passwordLog.txt", firstLog);
            id++;

            printf("Password is saved successfully!\n");
            break;
        case 2:
            if (isEmpty(firstLog))
            {
                printf("There is no password stored yet!\n");
                break;
            }
            printf("Password Menu Choice (1 - Print a single log, 2 - Print all logs): ");
            scanf("%d", &passwordMenuChoice);
            clearScanf();
            switch (passwordMenuChoice)
            {
            case 1:
                printf("Enter the name of the site: ");
                scanf("%9s", siteChoice);
                clearScanf();
                printRequestedLog(firstLog, siteChoice);
                break;
            case 2:
                printWholeLogAdmin(firstLog);
                break;
            default:
                puts("Wrong input!");
                break;
            }
            break;
        case 3:
            passwordGenerationMenu();
            printf("Choice input: ");
            scanf("%d", &passwordGenerationChoice);
            clearScanf();

            if (passwordGenerationChoice == 1)
            {
                printf("Recommended password:\n%s\n", passwordGeneratorRecommended());
            }
            else if (passwordGenerationChoice == 2)
            {
                printf("0 = NO, 1 = YES\n");
                int i = 0;
                for (; i < 6; i++)
                {
                    if ((i == 4 || i == 5) && passwordGenerationFeatures[2] == 0)
                        continue;
                    printf("%s", passwordFeatureNames[i]);
                    scanf("%d", &passwordGenerationFeatures[i]);
                    clearScanf();
                }
                if (passwordGenerationFeatures[0] <= 0 || passwordGenerationFeatures[0] > 30)
                {
                    printf("Invalid length!");
                    break;
                }
                printf("Recommended password:\n%s\n", passwordGenerator(passwordGenerationFeatures));
            }
            else
            {
                printf("Wrong input!");
            }
            break;
        case 4:
            printf("Go to \"%s\" to contibute!\n", "github.com/AlperKerimELMAS/encrypted-password-manager");
            break;
        case 9:
            mainMenu();
            break;

        default:
            printf("Wrong input, input 9 for the main menu.\n");
            break;
        }
        printf("Choice input: ");
        scanf("%d", &mainMenuChoice);
        clearScanf();
    }
    clearList(firstLog);
    puts("The program terminated successfully.");
}

void mainMenu()
{
    printf("%5s\n%5s\n%5s\n%5s\n\n", "1- New Password Input", "2- Registered Password Menu",
           "3- Random Password Generator", "4- Github", "5 -Terminate");
}

void passwordGenerationMenu()
{
    printf("%s\n%s\n", "1- RECOMMENDED Password Structure", "2- Custom Password Structure");
}

void clearScanf()
{
    int clear;
    while ((clear = getchar()) != '\n' && clear != EOF)
        continue;
}

void clearList(struct passwordLog *firstLog)
{
    struct passwordLog *temp = NULL;

    while (firstLog != NULL)
    {
        temp = firstLog->nextLog;
        free(firstLog->keyForID);
        free(firstLog->shufflePattern);
        free(firstLog);
        firstLog = temp;
    }
}