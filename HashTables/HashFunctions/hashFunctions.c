# include <stdio.h>
# include <stdlib.h>
# include <math.h> 
# include "hashFunctions.h"

# define NONNEG_CHECK(key) do {\
    if (k < 0) {\
      fprintf(stderr, "Negative value passed as key to HashFunction.\n");\
      exit(1);\
    }\
  } while(0)


long simpleDivisionMethodHash(long k, long m) {
  NONNEG_CHECK(k);
  return k % m;
}

long simpleMultiplicationMethodHash(long k, long m) {
  double temp = k * 0.6180339887;

  NONNEG_CHECK(k);
  temp -= (long)temp;
  return (long) (m * temp); 
}
