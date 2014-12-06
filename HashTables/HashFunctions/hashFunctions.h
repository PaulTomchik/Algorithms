# ifndef HASHFUNCTIONS_H
# define HASHFUNCTIONS_H 1

typedef long (*HashFunction)(void *key, long m);

long simpleDivisionMethodHash (void *key, long m);

long simpleMultiplicationMethodHash(void *key, long m);

long bigEndianStringHash (void *key, long m);
long littleEndianStringHash (void *key, long m);

# endif
