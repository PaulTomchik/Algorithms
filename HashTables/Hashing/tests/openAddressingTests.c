# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <assert.h>
# include <time.h>
# include "../HashFunctions/hashFunctions.h"
# include "../OpenAddressing/openAddressingOperations.h"
# include "testing.h"
# include "primes.h"

struct testerStruct_1 {
  char string[10];
  char id;
};

struct testerStruct_2 {
  char c;
  void *ptr;
};

void testKeyCopy();
void testSimpleArrays();
void testSimpleIntArray(int m, double loadFactor);


int main (void) {
  testKeyCopy();
  testSimpleArrays();
  return 0;
}

void testKeyCopy() {
  char c = 1;
  int  i = 1;
  long l = 1;

  assert(keyCopy(&c, sizeof(char)) == 1);
  assert(keyCopy(&i, sizeof(int) ) == 1);
  assert(keyCopy(&l, sizeof(long) ) == 1);
}

void testSimpleArrays() {
  testSimpleIntArray(2, 1);
  testSimpleIntArray(128, 1);
  testSimpleIntArray(128, 0.5);
  testSimpleIntArray(128, 0.25);
}

void testSimpleIntArray(int m, double loadFactor) {
  int *array;
  int i, n;
  OpenAddressTable oat;

  array = calloc(m, sizeof(int));
  
  oat = (OpenAddressTable) {
    array,
    m,
    sizeof(int),
    sizeof(int),
    0,
    0,
    -1,
    divisionMethodHash_linearProbe
  };

  n = (int)(m * loadFactor);

  for(i = 1; i <= n; ++i) {
    openAddressTable_Insert(&oat, &i); 
  }

  for(i = 1; i <= n; ++i) {
    assert(openAddressTable_Search(&oat, &i) != NOT_FOUND); 
  }

  for(i = 1; i <= (n/2); ++i) {
    openAddressTable_Delete(&oat, array + 2*i - 1);
  }

  for(i = 1; i < n; ++i) {
    if (i%2) {
      assert(openAddressTable_Search(&oat, &i) == NOT_FOUND);
    } else {
      assert(openAddressTable_Search(&oat, &i) != NOT_FOUND); 
    }
  }

  free(array);
}
