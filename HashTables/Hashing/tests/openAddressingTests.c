# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <assert.h>
# include <time.h>
# include "../HashFunctions/hashFunctions.h"
# include "../OpenAddressing/openAddressingOperations.h"
# include "testing.h"
# include "primes.h"

void testKeyCopy ();
void testSimpleArrays ();
void testSimpleIntArray (int m, double loadFactor, NumericProbingHashFunction hf);
void testStructArray1 (int m, double loadFactor, NumericProbingHashFunction hf);
void testStructArray2 (int m, double loadFactor, NumericProbingHashFunction hf);


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

  c = -1;
  i = -1;
  l = -1;

  assert(keyCopy(&c, sizeof(char)) == -1);
  assert(keyCopy(&i, sizeof(int) ) == -1);
  assert(keyCopy(&l, sizeof(long) ) == -1);
}

void testSimpleArrays() {
  NumericProbingHashFunction hfs[] = {
    divisionMethodHash_linearProbe,
    multiplicationMethodHash_linearProbe,
    divisionMethodHash_quadraticProbe,
    multiplicationMethodHash_quadraticProbe 
  };
  int i;

  for (i = 0; i < 4; ++i) {
    printf("---> %d\n", i);
    testSimpleIntArray(2, 1, hfs[i]);
    testSimpleIntArray(128, 1, hfs[i]);
    testSimpleIntArray(128, 0.5, hfs[i]);
    testSimpleIntArray(128, 0.25, hfs[i]);
  }
}


void testStructArrays() {
  /*testStructArray1(2, 1);*/
  /*testStructArray1(128, 1);*/
  /*testStructArray1(128, 0.5);*/
  /*testStructArray1(128, 0.25);*/

  /*testStructArray1(PRIME_NUMS[100], 1);*/
  /*testStructArray1(PRIME_NUMS[100], 0.5);*/
  /*testStructArray1(PRIME_NUMS[100], 0.25);*/
  /*testStructArray1(PRIME_NUMS[100], 0.125);*/

  /*testStructArray2(2, 1);*/
  /*testStructArray2(128, 1);*/
  /*testStructArray2(128, 0.5);*/
  /*testStructArray2(128, 0.25);*/

  /*testStructArray2(PRIME_NUMS[100], 1);*/
  /*testStructArray2(PRIME_NUMS[100], 0.5);*/
  /*testStructArray2(PRIME_NUMS[100], 0.25);*/
  /*testStructArray2(PRIME_NUMS[100], 0.125);*/
}

void testSimpleIntArray(int m, double loadFactor, NumericProbingHashFunction hf) {
  int *array;
  int i, n;
  OpenAddressTable oat;

  array = malloc(m * sizeof(int));
  memset(array, -1, m * sizeof(int));
  
  oat = (OpenAddressTable) {
    array,
    m,
    sizeof(int),
    sizeof(int),
    0,
    -1,
    -2,
    hf
  };

  n = (int)(m * loadFactor);

  for(i = 0; i < n; ++i) {
    if (openAddressTable_Insert(&oat, &i) == TABLE_FULL) {
      printf("-->TABLE_FULL\n");
    } 
  }

  for(i = 0; i < n; ++i) {
    assert(openAddressTable_Search(&oat, &i) != NOT_FOUND); 
  }

  for(i = 0; i < n; ++i) {
    if (i%2) continue;
    openAddressTable_Delete(&oat, &i);
  }

  for(i = 0; i < n; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");


  for(i = 0; i < n; ++i) {
    if (i%2) {
      assert(openAddressTable_Search(&oat, &i) != NOT_FOUND);
    } else {
      if (openAddressTable_Search(&oat, &i) != NOT_FOUND) printf("-ERROR- %d not deleted.\n", i);
      /*assert(openAddressTable_Search(&oat, &i) == NOT_FOUND); */
    }
  }

  free(array);
}


void testStructArray1(int m, double loadFactor, NumericProbingHashFunction hf) {

  /*OpenAddressTable oat;*/

  /*struct testerStruct_1 {*/
    /*char string[10];*/
    /*char id;*/
  /*};*/

  /*int n = (int)(m * loadFactor);*/
  /*int i;*/
  /*int key;*/
  
  /*struct testerStruct_1 *array = malloc (n * sizeof(struct testerStruct_1));*/
 
  /*oat = (OpenAddressTable) {*/
    /*array,*/
    /*m,*/
    /*sizeof(struct testerStruct_1),*/
    /*sizeof(char),*/
    /*offsetof(struct testerStruct_1, id),*/
    /*-1,*/
    /*-2,*/
    /*hf*/
  /*};*/


  /*for (i = 0; i < n; ++i) {*/
    /*array[i].id = (i * 3) % n;  */
  /*} */

  /*for (i = 0; i < n; ++i) {*/
    /*key = (i * 3) % n;*/
    /*assert(openAddressTable_Search(&oat, &key) != NOT_FOUND); */
  /*}*/

  /*for (i = 0; i < n; ++i) {*/
    /*if (i % 2) continue;*/
    /*key = (i * 3) % n;*/
    /*openAddressTable_Delete(&oat, &key);*/
  /*}*/

  /*for (i = 0; i < n; ++i) {*/
    /*key = (i * 3) % n;*/
    /*if (i % 2) {*/
      /*assert(openAddressTable_Search(&oat, &key) == NOT_FOUND); */
    /*} else {*/
      /*assert(openAddressTable_Search(&oat, &key) != NOT_FOUND); */
    /*}*/
  /*}*/

  /*free(array);*/
}

void testStructArray2(int m, double loadFactor, NumericProbingHashFunction hf) {

  /*OpenAddressTable oat;*/

  /*struct testerStruct_2 {*/
    /*char c;*/
    /*void *ptr;*/
  /*};*/

  /*int n = (int)(m * loadFactor);*/
  /*int i;*/
  /*int key;*/
  
  /*struct testerStruct_2 *array = malloc (n * sizeof(struct testerStruct_2));*/
 
  /*oat = (OpenAddressTable) {*/
    /*array,*/
    /*m,*/
    /*sizeof(struct testerStruct_2),*/
    /*sizeof(void*),*/
    /*offsetof(struct testerStruct_2, ptr),*/
    /*(long)NULL,*/
    /*-1,*/
    /*hf*/
  /*};*/


  /*for (i = 0; i < n; ++i) {*/
    /*array[i].ptr = array + i;*/
  /*} */

  /*for (i = 0; i < n; ++i) {*/
    /*key = (i * 3) % n;*/
    /*assert(openAddressTable_Search(&oat, &key) != NOT_FOUND); */
  /*}*/

  /*for (i = 0; i < n; ++i) {*/
    /*if (i % 2) continue;*/
    /*key = (i * 3) % n;*/
    /*openAddressTable_Delete(&oat, &key);*/
  /*}*/

  /*for (i = 0; i < n; ++i) {*/
    /*key = (i * 3) % n;*/
    /*if (i % 2) {*/
      /*assert(openAddressTable_Search(&oat, &key) == NOT_FOUND); */
    /*} else {*/
      /*assert(openAddressTable_Search(&oat, &key) != NOT_FOUND); */
    /*}*/
  /*}*/

  /*free(array);*/
}
