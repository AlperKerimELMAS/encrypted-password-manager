#include <stdio.h>

void mainMenu();
void passwordGenerationMenu();

int main(void)
{
    int mainMenuChoice;
    int passwordGenerationChoice;
    int passwordGenerationFeatures[6];
    char *passwordFeatureNames[6] = {"Length? ", "Digits included? ", "Letters included? ",
                                     "Special Character included? ", "Lowercase characters included? ", "Uppercase characters included? "};

    printf("%50s\n", "Local Encrypted Password Manager");
    mainMenu();

    printf("Choice input: ");
    scanf("%d", &mainMenuChoice);

    while (mainMenuChoice != 5)
    {
        switch (mainMenuChoice)
        {
        case 1:
        case 2:
        case 3:
            passwordGenerationMenu();
            printf("Choice input: ");
            scanf("%d", &passwordGenerationChoice);

            if (passwordGenerationChoice == 1)
            {
            }
            else if (passwordGenerationChoice == 2)
            {
                printf("0 = NO, 1 = YES\n");
                int i = 0;
                for (; i < 6; i++)
                {
                    printf("%s", passwordFeatureNames[i]);
                    scanf("%d", &passwordGenerationFeatures[i]);
                    printf("\n");
                }
            }
            else
            {
                printf("Wrong input!");
            }
            break;
        case 4:
        case 9:
            mainMenu();
            break;

        default:
            printf("Wrong input, input 9 for the main menu.\n");
            break;
        }
        printf("Choice input: ");
        scanf("%d", &mainMenuChoice);
    }

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