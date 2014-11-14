/*
 *
 * Based on the pseudocode found on pages 71 & 72 of 
 *    Intro to Algoritms by Cormen, Leiserson, Rivest, and Stein. 
 *
 */


# include <limits.h>
# include "maxsubarray.h"



/* Definition of static functions. */
static struct maxSubarrayTuple maxSubarray (int *low, int *high);
static struct maxSubarrayTuple maxCrossingSubarray (int *low, int *mid, int *high);



/* The public facing function. */
struct maxSubarrayTuple maxsubarray_NLgN (int arr[], size_t numElems) {

  struct maxSubarrayTuple mst;

  if (arr == NULL || (numElems == 0)) {
    mst.low = mst.high = NULL;
    mst.sum = 0;
    return mst;
  } else return maxSubarray(arr, (arr + numElems -1));
}


/* !!!NO SAFETY CHECKS DONE!!! */
/* Check edge cases before calling from the public facing function. */
/* low and high are inclusive */
static struct maxSubarrayTuple maxSubarray (int *low, int *high) {

  struct maxSubarrayTuple leftMST, rightMST, crossMST;
  int *mid;

  /* Base Case: One element */
  if ((high - low) == 0) {
    leftMST.low = leftMST.high = low;
    leftMST.sum = *low;
    return leftMST;
  } 

  /* Recursive Case: More than one element. */
  mid = low + (high - low)/2;

  leftMST  = maxSubarray(low, mid);
  rightMST = maxSubarray(mid + 1, high);
  crossMST = maxCrossingSubarray(low, mid, high);

  if (leftMST.sum >= rightMST.sum && leftMST.sum >= crossMST.sum) {
    return leftMST;
  } else if (rightMST.sum >= crossMST.sum) {
    return rightMST;
  } else {
    return crossMST;
  }
}


static struct maxSubarrayTuple maxCrossingSubarray (int *low, int *mid, int *high) {
  struct maxSubarrayTuple mst;

  int *maxLeft, *maxRight, *cur;
  int leftSum, rightSum, sum;
  leftSum = rightSum = INT_MIN;

  for (cur = mid, sum = 0; cur >= low; --cur) {
    sum += *cur;
    if (sum > leftSum) {
      leftSum = sum;
      maxLeft = cur;
    }
  }
  for (cur = mid+1, sum = 0; cur <= high; ++cur) {
    sum += *cur;
    if (sum > rightSum) {
      rightSum = sum;
      maxRight = cur;
    }
  }

  mst.low = maxLeft;
  mst.high = maxRight;
  mst.sum = leftSum + rightSum;

  return mst;
}  
