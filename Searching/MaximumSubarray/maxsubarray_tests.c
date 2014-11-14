# include <assert.h>
# include <stdlib.h>
# include "maxsubarray.h"


typedef struct maxSubarrayTuple (*MaxSubarray_Func)(int arr[], size_t numElems);

void testNullArray (MaxSubarray_Func msFunc) {
  msFunc(NULL, 1);
}

void testEmptyArray (MaxSubarray_Func msFunc) {

  struct maxSubarrayTuple mst;
  int a = 10;;

  mst = msFunc(&a, 0);
  assert(mst.low == NULL);
  assert(mst.high == NULL);
  assert(mst.sum == 0);
}

void testSingleNegElement (MaxSubarray_Func msFunc) {

  struct maxSubarrayTuple mst;
  int arr[] = { -1 };

  mst = msFunc(arr, 1);

  assert(mst.low == arr);
  assert(mst.high == arr);
  assert(mst.sum == -1);
}

void testSinglePosElement (MaxSubarray_Func msFunc) {

  struct maxSubarrayTuple mst;
  int arr[] = { 1 };

  mst = msFunc(arr, 1);

  assert(mst.low == arr);
  assert(mst.high == arr);
  assert(mst.sum == 1);
}

void testTwoElements (MaxSubarray_Func msFunc) {

  struct maxSubarrayTuple mst;
  int arr[] = { 1, 2 };

  mst = msFunc(arr, 2);
  assert(mst.low == arr);
  assert(mst.high == arr + 1);
  assert(mst.sum == 3);

  arr[0] = -2;
  mst = msFunc(arr, 2);
  assert(mst.low == arr + 1);
  assert(mst.high == arr + 1);
  assert(mst.sum == 2);

  arr[1] = -1;
  mst = msFunc(arr, 2);
  assert(mst.low == arr + 1);
  assert(mst.high == arr + 1);
  assert(mst.sum == -1);

  arr[0] = 0;
  mst = msFunc(arr, 2);
  assert(mst.low == arr);
  assert(mst.high == arr);
  assert(mst.sum == 0);
}

void test5Elements (MaxSubarray_Func msFunc) {

  struct maxSubarrayTuple mst;
  int arr[] = { 4, 2, 1, 3, 5 };
  int i;

  mst = msFunc(arr, 5);
  assert(mst.low == arr);
  assert(mst.high == arr + 4);
  assert(mst.sum == 15);

  for (i=0; i<5; ++i) {
    arr[i] *= -1;
  }

  mst = msFunc(arr, 5);
  assert(mst.low == arr + 2);
  assert(mst.high == arr + 2);
  assert(mst.sum == -1);

  arr[1] *= -1;
  arr[3] *= -1;

  mst = msFunc(arr, 5);
  assert(mst.low = arr + 1);
  assert(mst.high = arr + 3);
  assert(mst.sum == 4);
}


int main (void) {

  testNullArray(maxsubarray_NLgN);  
  testEmptyArray(maxsubarray_NLgN);
  testSingleNegElement(maxsubarray_NLgN);
  testSinglePosElement(maxsubarray_NLgN);
  testTwoElements(maxsubarray_NLgN);
  test5Elements(maxsubarray_NLgN);

  testNullArray(maxsubarray_Linear);  
  testEmptyArray(maxsubarray_Linear);
  testSingleNegElement(maxsubarray_Linear);
  testSinglePosElement(maxsubarray_Linear);
  testTwoElements(maxsubarray_Linear);
  test5Elements(maxsubarray_Linear);

  return 0;
}
