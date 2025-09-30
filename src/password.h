#ifndef PASSWORD_H
#define PASSWORD_H

struct passwordLog
{
    int id;
    char siteName[10];
    char siteURL[30];
    char encryptedUsername[30];
    char encryptedPassword[30];
    int *keyForID;
    int *shufflePattern;
    struct passwordLog *nextLog;
};

void insert(struct passwordLog **firstLog, int id, char *siteName, char *siteURL, char *encryptedUsername, char *encryptedPassword, int *keyForID, int *shufflePattern);
void delete (struct passwordLog **firstLog, int id);
void printRequestedLog(struct passwordLog *firstLog, char *siteName);
void printWholeLogAdmin(struct passwordLog *firstLog);
int isEmpty(struct passwordLog *firstLog);

char *strEncryption(int id, char *str, int *keyForID, int *shufflePattern);
int *randomKeyGenerator(int length);
int *randomShufflePatternGenerator(int length);

char *strDecryption(int *key, int *shufflePattern, int id, char *str);
char *deshuffler(char *str, int length, int *shufflePattern);

char *writeArray(int *array, int length);
int *readArray(char *array, int length);
void readData(struct passwordLog **firstLog, const char *path);
void writeData(char *path, struct passwordLog *firstLog);

char *passwordGenerator(int passwordGenerationFeatures[]);
char *passwordGeneratorRecommended();

void clearScanf();
void clearList(struct passwordLog *firstLog);

extern int numberOfLogs;

#endif