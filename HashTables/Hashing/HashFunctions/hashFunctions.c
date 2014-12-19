# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <time.h>
# include <math.h> 
# include "hashFunctions.h"


long simpleDivisionMethodHash (long key, long m) {
  key %= m;
  if (key < 0) {
    key *= -1;
  }
  return key;
}

long simpleMultiplicationMethodHash (long key, long m) {
  double temp = key * 0.6180339887;
  temp -= (long)temp;
  return (long) (m * temp); 
}


/*************************************************************/
/*                                                           */
/* NOTE: The probing functions are implemented as follows to */
/*         a) stay true to the crls examples.                */
/*         b) facilitate statistics keeping.                 */
/*                                                           */
/*************************************************************/
long divisionMethodHash_linearProbe (long key, long m, long i) {
  return (simpleDivisionMethodHash(key, m) + i) % m;
}

long multiplicationMethodHash_linearProbe (long key, long m, long i) {
  return (simpleMultiplicationMethodHash(key, m) + i) % m;
}


long divisionMethodHash_quadraticProbe (long key, long m, long i) {
  return (simpleDivisionMethodHash(key, m) + (int)(i/(double)2 + (i*i)/(double)2)) % m;
}

long multiplicationMethodHash_quadraticProbe (long key, long m, long i) {
  return (simpleMultiplicationMethodHash(key, m)  + (int)(i/(double)2 + (i*i)/(double)2)) % m;
}


/* clrs 11.3-2 */
long bigEndianStringHash (const char key[], long m) {
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


/* clrs 11.3-2 */
long littleEndianStringHash (const char key[], long m) {
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

static long UHFunction (long key, long p, long m) {
  return (key % p) % m;
}

UniversalHashFunction newUniversalHashFunction (long m) {
  UniversalHashFunction uhf;

  srand(time(NULL));

  uhf.hf = UHFunction;
  uhf.m  = m;

  while(!(uhf.p = rand())) ;

  return uhf;
}
