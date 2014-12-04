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


long simpleDivisionMethodHash (long k, long m) {
  NONNEG_CHECK(k);
  return k % m;
}


long simpleMultiplicationMethodHash (long k, long m) {
  double temp = k * 0.6180339887;

  NONNEG_CHECK(k);
  temp -= (long)temp;
  return (long) (m * temp); 
}


/* clrs 11.3-2 */
long stringHash (char string[], long m) {
  int i, len;
  long modSum, radixMod;
  
  if((string == NULL) || !(len = strlen(string))) return 0;

  modSum = 0;
  radixMod = 1;
  for (i = len-1; i >= 0; --i) {
    modSum += (radixMod * string[i]);
    modSum %= m;
    radixMod = (radixMod << 7) % m;
  }

  return modSum;
}


