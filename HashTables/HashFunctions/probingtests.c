# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <assert.h>
# include <time.h>
# include "hashFunctions.h"
# include "probingFunctions.h"
# include "testing.h"
# include "primes.h"

void testLinearProbing ();

int main (void) {
  testLinearProbing();

  return 0;
}

void testLinearProbing () {
  testLinearProbing(2, 1, simpleDivisionMethodHash);
  testLinearProbing(2, 0.5, simpleDivisionMethodHash);

  testLinearProbing(PRIME_NUMS[11], 1, simpleDivisionMethodHash);
  testLinearProbing(PRIME_NUMS[11], 0.5, simpleDivisionMethodHash);
  testLinearProbing(PRIME_NUMS[11], 0.25, simpleDivisionMethodHash);


  testLinearProbing(PRIME_NUMS[111], 1, simpleDivisionMethodHash);
  testLinearProbing(PRIME_NUMS[111], 0.5, simpleDivisionMethodHash);
  testLinearProbing(PRIME_NUMS[111], 0.25, simpleDivisionMethodHash);

  testLinearProbing(PRIME_NUMS[111], 1, simpleDivisionMethodHash);
  testLinearProbing(PRIME_NUMS[111], 0.5, simpleDivisionMethodHash);
  testLinearProbing(PRIME_NUMS[111], 0.25, simpleDivisionMethodHash);

  testLinearProbing(PRIME_NUMS[9111], 1, simpleDivisionMethodHash);
  testLinearProbing(PRIME_NUMS[9111], 0.5, simpleDivisionMethodHash);
  testLinearProbing(PRIME_NUMS[9111], 0.25, simpleDivisionMethodHash);
}

void testLinearProbingIntTable (long m, double loadFactor, HashFunction hf) {
  int **table = calloc(m, sizeof(int*));
  int *elems; 
  long i, h, n;
  int k;

  n = (long)(m * loadFactor);
  elems = malloc(n * sizeof(int));

  srand(time(NULL));
  for ( i = 0;  i < n;  ++i ) {
    elems[i] = k = rand();
    h = linearProbeInsert(table, &k, m, hf);
    table[h] = elems + i;
  }

  for ( i = 0;  i < n;  ++i ) {
    assert(elems[i] == *table[linearProbeSearch(table, elems + i, m, sizeof(int), hf)]);
  }

  free(table);
  free(elems);
}

void testLinearProbingStringTable (long m, double loadFactor, HashFunction hf) {
  char **table = calloc(m, sizeof(char*));
  char **elems; 
  int len;
  long i, j, h, n;

  n = (long)(m * loadFactor);
  elems = malloc(n * sizeof(char*));

  srand(time(NULL));
  for ( i = 0;  i < n;  ++i ) {
    len = (i+1) % 128;
    elems[i] = malloc(len+1);
    elems[i][len] = '\0';

    for (j=0; j < len; ++j) {
      elems[j/128][j] = j % 128;   
    }

    h = linearProbeInsert(table, elems + i, m, bigEndianStringHash);
    table[h] = elems[i];
  }

  for ( i = 0;  i < n;  ++i ) {
    assert(elems[i] == *table[linearProbeSearch(table, , m, sizeof(int), hf)]);
  }

  free(table);
  free(elems);
}

