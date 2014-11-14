# include "maxsubarray.h"

struct maxSubarrayTuple maxsubarray_Linear (int arr[], size_t numElems) {

  struct maxSubarrayTuple max;
  int *curLow, *curHigh;
  int curSum;

  if ((arr == NULL) || (!numElems)) {
    max.low = max.high = NULL;
    max.sum = 0;
    return max;
  } 

  max.low = max.high = curLow = arr;
  max.sum = curSum = *arr;
  
  for (curHigh = (arr + 1); (curHigh - arr) < numElems; ++curHigh) {
    if (curSum < 0) {
      curLow = curHigh;
      curSum = 0;
    } 
    
    if ((curSum += *curHigh) > max.sum) {
      max.low = curLow;
      max.high = curHigh;
      max.sum = curSum;
    } 
  }

  return max;
}
