# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <time.h>
# include "hashFunctions.h"
# include "testing.h"


void testSimpleDivisionIntegerHashing ();
void testSimpleMultiplicationIntegerHashing ();
void testStringHashing ();

static void intKeyTester(NumericHashFunction hfunc, double loadFactor);
static void runIntKeyTest (int array[], int sz, double loadFactor, NumericHashFunction hfunc);
static void fillIntKeyTable (int array[], int sz, double loadFactor, NumericHashFunction hfunc);

static void stringHashTester(StringHashFunction hfunc, double loadFactor);
static void runStringKeyTest (int array[], int sz, double loadFactor, StringHashFunction hfunc);
static void fillStringKeyTable (int array[], int sz, double loadFactor, StringHashFunction hfunc);

static int getCollisionCount(int array[], int sz);


int main (void) {
  stat_printf("\n(Stats given are tableSize & collisionRatio.)\n\n");
  testSimpleDivisionIntegerHashing();
  testSimpleMultiplicationIntegerHashing();
  testStringHashing();
  return 0;
}

void testSimpleDivisionIntegerHashing() {
  stat_printf("\nUsing simpleDivisionMethodHash: load factor = 1.\n");
  intKeyTester(simpleDivisionMethodHash, 1);

  stat_printf("\nUsing simpleDivisionMethodHash: load factor = 3/4.\n");
  intKeyTester(simpleDivisionMethodHash, (double)3/(double)4);

  stat_printf("\nUsing simpleDivisionMethodHash: load factor = 1/2.\n");
  intKeyTester(simpleDivisionMethodHash, (double)1/(double)2);

  stat_printf("\nUsing simpleDivisionMethodHash: load factor = 1/4.\n");
  intKeyTester(simpleDivisionMethodHash, (double)1/(double)4);

  stat_printf("\nUsing simpleDivisionMethodHash: load factor = 1/8.\n");
  intKeyTester(simpleDivisionMethodHash, (double)1/(double)8);
}

void testSimpleMultiplicationIntegerHashing() {
  stat_printf("\nUsing simpleMultiplicationMethodHash: load factor = 1.\n");
  intKeyTester(simpleMultiplicationMethodHash, 1);

  stat_printf("\nUsing simpleMultiplicationMethodHash: load factor = 3/4.\n");
  intKeyTester(simpleMultiplicationMethodHash, (double)3/(double)4);

  stat_printf("\nUsing simpleMultiplicationMethodHash: load factor = 1/2.\n");
  intKeyTester(simpleMultiplicationMethodHash, (double)1/(double)2);

  stat_printf("\nUsing simpleMultiplicationMethodHash: load factor = 1/4.\n");
  intKeyTester(simpleMultiplicationMethodHash, (double)1/(double)4);

  stat_printf("\nUsing simpleMultiplicationMethodHash: load factor = 1/8.\n");
  intKeyTester(simpleMultiplicationMethodHash, (double)1/(double)8);
}

void testStringHashing () {
  stat_printf("\nUsing stringHash : load factor = 1.\n");
  stringHashTester(bigEndianStringHash, 1);

  stat_printf("\nUsing stringHash: load factor = 3/4.\n");
  stringHashTester(bigEndianStringHash, (double)3/(double)4);

  stat_printf("\nUsing stringHash: load factor = 1/2.\n");
  stringHashTester(bigEndianStringHash, (double)1/(double)2);

  stat_printf("\nUsing stringHash: load factor = 1/4.\n");
  stringHashTester(bigEndianStringHash, (double)1/(double)4);

  stat_printf("\nUsing stringHash: load factor = 1/8.\n");
  stringHashTester(bigEndianStringHash, (double)1/(double)8);
}


static void intKeyTester(NumericHashFunction hfunc, double loadFactor) {

  int arr[MAX_M];
  int sz;
  
  for (sz=2; sz < MAX_M; sz *= 2) {
    runIntKeyTest(arr, sz, loadFactor, hfunc);
  }
  
  for (sz=10; sz < MAX_M; sz *= 10) {
    runIntKeyTest(arr, sz, loadFactor, hfunc);
  }
  
  for (sz=10; (sz+1) < MAX_M; sz *= 10) {
    runIntKeyTest(arr, sz+1, loadFactor, hfunc);
  }

  for (sz=2; sz < PRIME_NUMS_LEN; sz *= 2) {
    runIntKeyTest(arr, PRIME_NUMS[sz], loadFactor, hfunc);
  }
}

static void stringHashTester(StringHashFunction hfunc, double loadFactor) {
  int arr[MAX_M];
  int sz;

  
  for (sz=2; sz < MAX_M; sz *= 2) {
    runStringKeyTest(arr, sz, loadFactor, hfunc);
  }
  
  for (sz=10; sz < MAX_M; sz *= 10) {
    runStringKeyTest(arr, sz, loadFactor, hfunc);
  }
  
  for (sz=10; (sz+1) < MAX_M; sz *= 10) {
    runStringKeyTest(arr, sz+1, loadFactor, hfunc);
  }

  for (sz=2; sz < PRIME_NUMS_LEN; sz *= 2) {
    runStringKeyTest(arr, PRIME_NUMS[sz], loadFactor, hfunc);
  }
}

static void runIntKeyTest(int array[], int sz, double loadFactor, NumericHashFunction hfunc) {
  double collisionPercentage;

  memset(array, 0, sz * sizeof(int));

  fillIntKeyTable(array, sz, loadFactor, hfunc);

  collisionPercentage = (double)getCollisionCount(array, sz) / (double)sz * 100;
  stat_printf("%15d    %.3f\n", sz, collisionPercentage);
}


static void fillIntKeyTable(int array[], int sz, double loadFactor, NumericHashFunction hfunc) {
  int i;

  for (i=1; i <= (int)(sz * loadFactor); ++i) {
    array[hfunc(INT_MAX/i, sz)] += 1;
  }       
}

static void runStringKeyTest(int array[], int sz, double loadFactor, StringHashFunction hfunc) {
  double collisionPercentage;

  memset(array, 0, sz * sizeof(int));

  fillStringKeyTable(array, sz, loadFactor, hfunc);

  collisionPercentage = (double)getCollisionCount(array, sz) / (double)sz * 100;
  stat_printf("%15d    %.3f\n", sz, collisionPercentage);
}


static void fillStringKeyTable(int array[], int sz, double loadFactor, StringHashFunction hfunc) {
  int i, r;
  char string[101];

  srand(time(NULL));

  for (i=1; i <= (int)(sz * loadFactor); ++i) {
    r = rand() % 100;
    string[r] = '\0';
    while(r--) {
      string[r] = rand() % 128;
    }
    array[hfunc(string, sz)] += 1;
  }       
}


static int getCollisionCount(int array[], int sz) {
  int collisionCount = 0;
  int i;

  for (i=0; i < sz; ++i) {
    if (array[i] > 1) {
      ++collisionCount;
    }
  }

  return collisionCount;
}
