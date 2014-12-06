# ifndef PROBINGFUNCTIONS_H
# define PROBINFFUNCTIONS_H 1

# include <stdlib.h>
# include "hashFunctions.h"

long linearProbeInsert (void *table, void *key, long m, HashFunction hashFunc);
long linearProbeSearch_fixedKeyLen (void *table, void *key, long m, size_t size, HashFunction hashFunc);
long linearProbeSearch_stringKey (void *table, void *key, long m, HashFunction hashFunc);
long quadraticProbe (void *table, void *key, long m, HashFunction hashFunc);

# endif
