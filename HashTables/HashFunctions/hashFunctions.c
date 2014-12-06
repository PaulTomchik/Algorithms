# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h> 
# include "hashFunctions.h"

# define NONNEG_CHECK(key) do {\
    if (k < 0) {\
      fprintf(stderr, "Negative value passed as key to HashFunction.\n");\
      exit(1);\
    }\
  } while(0)


long simpleDivisionMethodHash (void *key, long m) {
  long k = *((long*)key);
  NONNEG_CHECK(k);
  return k % m;
}

long simpleMultiplicationMethodHash (void *key, long m) {
  long k = *((long*)key);
  double temp = k * 0.6180339887;

  NONNEG_CHECK(k);
  temp -= (long)temp;
  return (long) (m * temp); 
}

/* clrs 11.3-2 */
long bigEndianStringHash (void *key, long m) {
  char *k = (char*)key;
  int i, len;
  long modSum, radixMod;
  
  if((k == NULL) || !(len = strlen(k))) return 0;

  modSum = 0;
  radixMod = 1;
  for (i = len-1; i >= 0; --i) {
    modSum += (radixMod * k[i]);
    modSum %= m;
    radixMod = (radixMod << 7) % m;
  }

  return modSum;
}


long littleEndianStringHash (void *key, long m) {
  char *k = (char*)key;
  int i, len;
  long modSum, radixMod;
  
  if((k == NULL) || !(len = strlen(k))) return 0;

  modSum = 0;
  radixMod = 1;
  for (i = 0; i < len; --i) {
    modSum += (radixMod * k[i]);
    modSum %= m;
    radixMod = (radixMod << 7) % m;
  }

  return modSum;
}


