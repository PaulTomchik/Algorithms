/*
 The MIT License (MIT)

 Copyright (c) 2014 Paul Tomchik

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

/* TODO: Test structs. */
/*       Test elems whose size is not a multiple of 4 */

# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <assert.h>

# include "c_insertionSort.h"
# include "arm_insertionSort.h"

# define ARR_LEN_MAX 1000
# define NUM_TRIALS 1000
# define MAX_NUM 1111

typedef void (*Sorter)(void *array, int numElems, size_t elemSize, int (*comparator)(void *elem1, void*elem2));

int intComparator(void *a, void *b) {
  int x = *(int*)a;
  int y = *(int*)b;

  if (x == y) {
    return 0;
  } else if (x < y) {
    return -1;
  } else return 1;
}

void simpleIntTest(Sorter sorter) {
  int arr[] = {3, 2, 1};
  int i;

  printf("   B4: {");
  for (i = 0; i < 3; ++i) {
    printf(" %d", arr[i]);
  }
  printf(" }\n");

  sorter(arr, 3, sizeof(int), intComparator);

  printf("AFTER: {");
  for (i = 0; i < 3; ++i) {
    printf(" %d", arr[i]);
  }
  printf(" }\n");
}

void testNullArray(Sorter sorter) {
  sorter(NULL, 100, 4, intComparator);
}


void testEmptyArray(Sorter sorter) {
  int arr[1];

  sorter(arr, 0, sizeof(int), intComparator);
}

void intTests (Sorter sorter) {
  int arr[ARR_LEN_MAX];
  int i, j;
  int len, sumA, sumB;

  srand(time(NULL));
  for (i = 0; i < NUM_TRIALS; ++i) {
    
    len = rand()%(ARR_LEN_MAX+1);
    sumA = 0;
    for (j = 0; j < len; ++j) {
      sumA += (arr[j] = (rand() % MAX_NUM));  
    }

  # if 0
    printf("B4: {");
    for (j = 0; j < len; ++j) {
      printf(" %d", arr[j]);
    }
    printf(" }\n");
  # endif

    sorter(arr, len, sizeof(int), intComparator);

  # if 0
    printf("AFTER: {");
    for (j = 0; j < len; ++j) {
      printf(" %d", arr[j]);
    }
    printf(" }\n");
  # endif

    sorter(arr, len, sizeof(int), intComparator);
    if (len) {
      sumB = arr[0];
    } else {
      sumB = 0;
    }
    for (j = 1; j < len; ++j) {
      assert(arr[j-1] <= arr[j]);
      sumB += arr[j];
    }

    assert(sumA == sumB);
  }
}


int doubleComparator(void *a, void *b) {
  double x = *(double*)a;
  double y = *(double*)b;

  if (x == y) {
    return 0;
  } else if (x < y) {
    return -1;
  } else return 1;
}

void doubleTests (Sorter sorter) {
  double arr[ARR_LEN_MAX];
  int i, j;
  int n, d;
  int len;
  double sumA, sumB;

  srand(time(NULL));
  for (i = 0; i < NUM_TRIALS; ++i) {
    
    len = rand()%(ARR_LEN_MAX+1);
    sumA = 0;
    for (j = 0; j < len; ++j) {
      n = rand() % MAX_NUM;
      d = (rand() % MAX_NUM) + 1;
      if (!d) d = 1;
      sumA += (arr[j] = (double)n / (double)d);
    }

    sorter(arr, len, sizeof(double), doubleComparator);

    if (len) {
      sumB = arr[0];
    } else {
      sumB = 0;
    }
    for (j = 1; j < len; ++j) {
      assert(arr[j-1] <= arr[j]);
      sumB += arr[j];
    }

    assert((sumA - sumB)*(sumA - sumB) < 1);
  }
}

int main (void) {
  /*printf("Testing C sorter on null array.\n");*/
  testNullArray(c_insertionSort);
  /*printf("Testing C sorter on empty array.\n");*/
  testEmptyArray(c_insertionSort);
  /*printf("Testing C int sorting.\n");*/
  intTests(c_insertionSort);
  /*printf("Testing C double sorting.\n");*/
  doubleTests(c_insertionSort);

  /*printf("Testing ARM sorter on null array.\n");*/
  testNullArray(arm_insertionSort);
  /*printf("Testing ARM sorter on empty array.\n");*/
  testEmptyArray(arm_insertionSort);
  /*printf("Testing ARM int sorting.\n");*/
  intTests(arm_insertionSort);
  /*printf("Testing ARM double sorting.\n");*/
  doubleTests(arm_insertionSort);
  return 0;
}
