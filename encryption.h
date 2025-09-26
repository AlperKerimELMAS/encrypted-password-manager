#ifndef ENCRYPTION_H
#define ENCRYPTION_H

char *strEncryption(int key, int id, char *str);
char *randomKeyGenerator(int id, int length);
int *randomShufflePatternGenerator(int length);

#endif
