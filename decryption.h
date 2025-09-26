#ifndef DECRYPTION_H
#define DECRYPTION_H

char *strDecryption(int *key, int *shufflePattern, int id, char *str);
char *deshuffler(char *str, int length, int *shufflePattern);

#endif
